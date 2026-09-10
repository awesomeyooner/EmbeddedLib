#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP

#include <vector>
#include <iostream>
#include <deque>
#include <cmath>

#include "EmbeddedLib/system.hpp"
#include "EmbeddedLib/util/stamped_value.hpp"
#include "EmbeddedLib/math/math_util.hpp"


// Options for what Feed Forward method to use
enum class FeedForwardType{
    
    // Applies a constant feedforward, regardless of direction
    STATIC,

    // Applies a constant feedforward based on the direction / sign of error
    STATIC_SIGNED,

    // Applies a feedforward based on the cosine of the position (position must be in radians)
    COS,

    // Applies a feedforward based on the sine of the position (position must be in radians)
    SIN

}; // enum FeedForwardType


// Class for a PID Controller, implementing feedforwards in addition to PID.
class PIDController{

    public:

        // Proportional Gain
        double m_kP = 0;
        
        // Integral Gain
        double m_kI = 0;
        
        // Derivative Gain
        double m_kD = 0;

        // Static Feedforward Gain. Type is determined by `m_ff_type`
        double m_kF = 0;

        // Velocity Feedforward Gain. This is proportional to the setpoint
        double m_kV = 0;

        // The type of feedforward to use
        FeedForwardType m_ff_type = FeedForwardType::STATIC_SIGNED;

        /* 
            The maximum output the integral part of PID can contribute to. This takes
            kI into account, so that max output will be in units of the desired output. For example,
            if the output is used to control voltage applied to a motor, then this variable will
            determine the max voltage the integral part contributes to the total output.
        */
        double m_integral_max_output = -1;

        // The setpoint to go towards
        double m_setpoint = 0;

        // The current state of the PID controller. If PID is used to control position, this would be "position"
        StampedValue<double> m_state = 0;

        // The current rate of the state. If PID is used to control position, this would be "velocity"
        double m_state_rate = 0;

        PIDController(double kP = 0, double kI = 0, double kD = 0, double kV = 0, double kF = 0, FeedForwardType ff_type = FeedForwardType::STATIC_SIGNED);

        double get_error();
        double get_accumulated_error();
        double get_error_rate();

        double calculate(double timestamp, double state);
        double calculate(double timestamp, double state, double setpoint);
        double calculate(double timestamp, double state, double state_rate, double setpoint);

    private:

        // The timestamp since the last time `calculate` was called
        StampedValue<double> m_prev_error = 0;
        
        // The accumulated error (integral of error, starting at t = 0)
        double m_accumulated_error = 0;

        void update_accumulated_error(double timestamp);
        double update_error_rate(double timestamp);
        double get_static_feedforward();
        double get_velocity_feedforward(double setpoint);


}; // class PIDController

#endif // PID_CONTROLLER_HPP