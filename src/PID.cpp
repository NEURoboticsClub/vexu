#include "EZ-Template/PID.hpp"

/**
 * Default constructor.
 */
PID::PID() {
    // initialize constants to default values here?
}

 /**
   * Constructor with constants.
   *
   * \param p
   *        kP
   * \param i
   *        ki
   * \param d
   *        kD
   * \param p_start_i
   *        error value that i starts within
   * \param name
   *        std::string of name that prints 
   */
PID::PID(double p, double i, double d, double start_i, std::string name) {
    constants.kp = p;
    constants.ki = i;
    constants.kd = d;
    constants.start_i = start_i;
    this->name = name;
}

/**
   * Set constants for PID.
   *
   * \param p
   *        kP
   * \param i
   *        ki
   * \param d
   *        kD
   * \param p_start_i
   *        error value that i starts within
   */
void PID::set_constants(double p, double i, double d, double p_start_i) {
    // Set the PID constants in the "constants" struct
    constants.kp = p;
    constants.ki = i;
    constants.kd = d;
    constants.start_i = p_start_i;
}

 /**
   * Set's constants for exit conditions.
   *
   * \param p_small_exit_time
   *        Sets small_exit_time.  Timer for to exit within smalL_error.
   * \param p_small_error
   *        Sets smalL_error. Timer will start when error is within this.
   * \param p_big_exit_time
   *        Sets big_exit_time.  Timer for to exit within big_error.
   * \param p_big_error
   *        Sets big_error. Timer will start when error is within this.
   * \param p_velocity_exit_time
   *        Sets velocity_exit_time.  Timer will start when velocity is 0.
   */
void PID::set_exit_condition(int p_small_exit_time, double p_small_error, int p_big_exit_time, double p_big_error, int p_velocity_exit_time, int p_mA_timeout) {
    // Set the exit conditions in the "exit" struct
    exit.small_exit_time = p_small_exit_time;
    exit.small_error = p_small_error;
    exit.big_exit_time = p_big_exit_time;
    exit.big_error = p_big_error;
    exit.velocity_exit_time = p_velocity_exit_time;
    exit.mA_timeout = p_mA_timeout;
}

  /**
   * Set's target.
   *
   * \param target
   *        Target for PID.
   */
void PID::set_target(double input) {
    // Set the target value
    target = input;
}

// Compute PID
// example compute method here
double PID::compute(double current) {
    // Calculate the error
    double error = target - current;

    // Calculate the derivative of the error
    double derivative = error - previous_error;
    previous_error = error;

    // Calculate the integral of the error
    integral += error;

    // Apply the constants to the error, derivative, and integral
    double output = constants.kp * error + constants.kd * derivative + constants.ki * integral;

    // Limit the output to the maximum and minimum values
    if (output > max_output) {
        output = max_output;
    } else if (output < min_output) {
        output = min_output;
    }

    // Return the computed output
    return output;
}

// add other method implementations