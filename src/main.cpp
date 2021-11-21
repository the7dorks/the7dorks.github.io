/**
 * main.cpp
 *
 * This file contains the orchestration of all the compenents. It
 * starts all of the separate tasks that are needed for controlling
 * the robot, and has all the functions called by the competition
 * switch.
 */
#include "main.h" // gives access to dependencies from other files

DisplayControl def::display = DisplayControl();
pros::Task odomTask(odomTaskFunc);
pros::Task sm_lift_task(sm_lift_task_func);
pros::Task sm_mg_task(sm_mg_task_func);
pros::Task display_task(display_task_func);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
    def::imu1.reset();
    def::imu2.reset();

    Auton::suspendAsyncTask();
    Auton::readSettings();            // read sd card to remeber the auton selected when the brain was run last
    def::display.setAutonDropdowns(); // update auton dropdown to match the sd card

    def::mtr_dt_left_front.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
    def::mtr_dt_right_front.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
    def::mtr_dt_right_back.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
    def::mtr_dt_left_back.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
    Auton::runAuton(); // uses the auton class to run the slected auton
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
    pros::Task sm_dt_task(sm_dt_task_func);

    ControllerButton up = ControllerDigital::up;
    ControllerButton down = ControllerDigital::down;
    ControllerButton left = ControllerDigital::left;
    ControllerButton right = ControllerDigital::right;
    // there is no need for a loop in opcontrol(), because there are already other tasks running
    // that control all of the movement
    Auton::suspendAsyncTask();
    def::sm_dt.setState(DT_STATES::manual);
    while (true)
    {
        if (up.changedToPressed())
        {
            def::sm_dt.doAutonMotion(makeFunc({
                Drivetrain::tankToPoint({2_ft, 0_ft, 0_deg}, {}, 1, false, 0, 6_in, PID(0.2, 0.0, 0.7, 0.0, 0.25, 0.01, 1_ms), PID(0, 0, 0, 0, 0, 0, 0_ms), Slew(1, 1), Slew(1, 1));
            }));
        }
        else if (right.changedToPressed())
        {
            def::sm_dt.doAutonMotion(makeFunc({
                Drivetrain::turnToAngle(90_deg, {}, PID(0.05, 0.01, 0.15, 2, 0.25, 0.01, 1_ms));
            }));
        }
        pros::delay(20);
    }
}
