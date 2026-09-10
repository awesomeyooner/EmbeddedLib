#include "EmbeddedLib/math/control/pid_controller.hpp"


using namespace math;


PIDController::PIDController(double kP, double kI, double kD, double kV, double kF, FeedForwardType ff_type)
{
    m_kP = kP;
    m_kI = kI;
    m_kD = kD;
    m_kV = kV;
    m_kF = kF;
    m_ff_type = ff_type;


} // end of "PIDController"


double PIDController::get_error()
{
    // Using the sign convention of 
    // if a positive output gives an increase in position
    return m_setpoint - m_state.get_value();

} // end of "get_error"


double PIDController::get_accumulated_error()
{
    return m_accumulated_error;

} // end of "get_accumulated_error"


double PIDController::get_error_rate()
{
    return -m_state_rate;

} // end of "get_error_rate"


double PIDController::calculate(double timestamp, double state)
{
    // Call the overload function with m_setpoint passed in as the setpoint
    return calculate(timestamp, state, m_setpoint);

} // end of "calculate"


double PIDController::calculate(double timestamp, double state, double setpoint)
{
    double state_rate = m_state.get_rate(state, timestamp);

    return calculate(
        timestamp, 
        state, 
        state_rate, 
        setpoint
    );

} // end of "calculate"


double PIDController::calculate(double timestamp, double state, double state_rate, double setpoint)
{
    // Update the setpoint
    m_setpoint = setpoint;

    // Update the states
    m_state.update(state, timestamp);
    m_state_rate = state_rate;

    // Update the error area
    update_accumulated_error(timestamp);

    // Get the errors and feedforward
    double error = get_error();
    double error_rate = get_error_rate();
    double accumulated_error = get_accumulated_error();
    double static_ff = get_static_feedforward();
    double velocity_ff = get_velocity_feedforward(setpoint);

    double P = m_kP * error;
    double I = m_kI * accumulated_error;
    double D = m_kD * error_rate;

    double F = static_ff;
    double V = velocity_ff;

    // PID(F) Equation
    double output = P + I + D + F + V;

    // Keep track of last time this was called
    m_prev_error.update(error, timestamp);

    return output;

} // end of "calculate(double, double, double, double)"


void PIDController::update_accumulated_error(double timestamp)
{
    double dt = timestamp - m_prev_error.get_timestamp();
    
    double error1 = get_error();
    double error2 = m_prev_error.get_value(); 

    // Formula for area of trapezoid
    double area = (error1 + error2) * dt / 2;

    m_accumulated_error += area;

    // Clamp the accumulated error for anti-windup
    m_accumulated_error = clamp(m_accumulated_error, -m_integral_max_output, m_integral_max_output);

} // end of "update_accumulated_error()"


double PIDController::update_error_rate(double timestamp)
{
    double error = get_error();

    // Calculate the slope and return it;
    double de = error - m_prev_error.get_value();
    double dt = timestamp - m_prev_error.get_timestamp();

    double slope = de / dt;

    m_state_rate = -slope;

    return slope;

} // end of "update_error_rate(double)"


double PIDController::get_static_feedforward()
{
    // Return the correspodning values based on the type
    switch(m_ff_type)
    {
        // Constant effort
        case FeedForwardType::STATIC:
            return m_kF;
        
        // Constant, but the direction of effort is based on sign of error 
        case FeedForwardType::STATIC_SIGNED:
            return std::copysign(m_kF, get_error());

        // Effort is the gain times the cos of position
        case FeedForwardType::COS:
            return m_kF * std::cos(m_state.get_value());

        // Effort is the gain times the sin of position
        case FeedForwardType::SIN:
            return m_kF * std::cos(m_state.get_value());

        // Default to no effort
        default:
            return 0;
    }

} // end of "get_static_feedforward()"


double PIDController::get_velocity_feedforward(double setpoint)
{
    return m_kV * setpoint;

} // end of "get_velocity_feedforward(double)"