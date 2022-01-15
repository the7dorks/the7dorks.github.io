/**
 * Auton.cpp
 *
 * This contains the definitions of the Auton struct,
 * which is responsible for reading the sd card to determine
 * which auton is selected, and running the correct auton.
 */
#include "main.h" // gives access to Auton and other dependencies

Auton::Autons Auton::auton;    // default auton is deploy, if the sd card is not installed
Auton::Sides Auton::side;      // default side is Right if the sd card is not installed
Auton::Colors Auton::color;    // default color is Red if the sd card is not installed
Auton::Colors Auton::opponent; // default color is Red if the sd card is not installed

void Auton::readSettings() // read the sd card to set the settings
{
    FILE *file;                    // cpp a file object to be used later
    if (pros::usd::is_installed()) // checks if the sd card is installed before trying to read it
    {
        file = fopen("/usd/auton_settings.txt", "r"); // open the auton settings
        if (file)                                     // check to see if the file opened correctly
        {
            int autonSideAndColor;
            fscanf(file, "%i", &autonSideAndColor);

            auton = (Auton::Autons)(autonSideAndColor / 100);
            side = (Auton::Sides)((autonSideAndColor / 10) % 10);
            color = (Auton::Colors)(autonSideAndColor % 10);
            opponent = color == Auton::Colors::Red ? Auton::Colors::Blue : Auton::Colors::Red;

            std::cout << "autonSideAndColor in sd card is " << std::to_string(autonSideAndColor) << ". Auton is " << (int)auton << ", side is " << (int)side << ", and color is " << (int)color << "." << std::endl;
        }
        else
        {
            std::cout << "/usd/auton_settings.txt is null."
                      << std::endl; // if the file didn't open right, tell the terminal
        }
        fclose(file); // close the file
    }
}
void Auton::suspendAsyncTask()
{
    masync_task.suspend();
}

void Auton::runAuton() // runs the selected auton
{
    pros::Task auton_task(auton_task_func);
}

/* ----------------------------------------------------------- */
/*                     Private Information                     */
/* ----------------------------------------------------------- */
void Auton::auton_task_func(void *) // separate thread for running the auton, in case a particular
                                    // auton needs control over its thread
{
    // when making autons, you must add the text to the dropdown in DisplayControl.cpp, a new enum
    // value in Auton.hpp, and a new case is this switch
    Auton::readSettings();

    waitForImu();
    CustomOdometry::setStateInitial({0_in, 0_in, -def::imu1.get_rotation() * degree});
    // awp

    LiftStateMachine::disableControl();
    IntakeStateMachine::disableControl();
    HolderStateMachine::disableControl();
    def::sm_dt.setState(DT_STATES::busy);

    switch (auton)
    {
    case Autons::none:
        break;
    case Autons::awp:
        Drivetrain::straightToPoint({-7_in, 0_in, 0_deg}, cutDrive(1.5));
        HolderStateMachine::setState(HOLDER_STATES::closed);
        IntakeStateMachine::setState(INTAKE_STATES::in);
        pros::delay(1500);
        HolderStateMachine::setState(HOLDER_STATES::open);
        // Drivetrain::straightForDistance(17_in);
        Drivetrain::straightToPoint({12_in, 0_in, 0_deg}, cutDrive(1));
        Drivetrain::straightToPoint({-11_in, -17_in, 0_deg}, cutDrive(3));
        Drivetrain::straightToPoint({-98_in, -23_in, 0_deg}, cutDrive(15));
        Drivetrain::arcadeFor(-0.25, 0, 1500);
        pros::delay(500);
        HolderStateMachine::setState(HOLDER_STATES::closed);
        LiftStateMachine::setState(LIFT_STATES::top);
        pros::delay(700);
        Drivetrain::turnToAngle(90_deg);
        Drivetrain::setMaxSpeed(0.5);
        Drivetrain::straightToPoint({-106_in, 5_in, 0_deg}, cutDrive(1));
        Drivetrain::straightToPoint({-106_in, -14_in, 0_deg}, cutDrive(1));
        Drivetrain::straightToPoint({-106_in, 5_in, 0_deg}, cutDrive(1));
        Drivetrain::straightToPoint({-106_in, -14_in, 0_deg}, cutDrive(1));
        Drivetrain::straightToPoint({-106_in, 5_in, 0_deg}, cutDrive(1));
        HolderStateMachine::setState(HOLDER_STATES::open);
        break;
    case Autons::awp1N:
        Drivetrain::straightToPoint({43_in, 0_in, 0_deg});
        LiftStateMachine::engageClaw();
        Drivetrain::straightToPoint({19_in, 0_in, 0_deg});
        Drivetrain::turnToAngle(90_deg);
        LiftStateMachine::disengageClaw();
        Drivetrain::straightToPoint({12_in, 0_in, 0_deg}, cutDrive(3));

        Drivetrain::arcadeFor(-0.25, 0, 1000);
        pros::delay(500);
        HolderStateMachine::setState(HOLDER_STATES::closed);
        LiftStateMachine::setState(LIFT_STATES::top);
        pros::delay(700);
        Drivetrain::turnToAngle(180_deg);
        Drivetrain::setMaxSpeed(0.5);
        Drivetrain::straightToPoint({2_in, -20_in, 0_deg}, cutDrive(1));
        Drivetrain::straightToPoint({22_in, -20_in, 0_deg}, cutDrive(1));
        Drivetrain::straightToPoint({2_in, -20_in, 0_deg}, cutDrive(1));
        Drivetrain::straightToPoint({22_in, -20_in, 0_deg}, cutDrive(1));
        Drivetrain::straightToPoint({2_in, -20_in, 0_deg}, cutDrive(1));
        HolderStateMachine::setState(HOLDER_STATES::open);

        break;
    case Autons::oneNeutral:
        // pros::delay(1000);
        // LiftStateMachine::disengageClaw();
        // pros::delay(1000);
        Drivetrain::straightToPoint({43_in, 0_in, 0_deg}, cutDrive(2));
        LiftStateMachine::engageClaw();
        Drivetrain::straightToPoint({10_in, 0_in, 0_deg}, cutDrive(1));
        break;
    case Autons::twoNeutral:
        break;
    case Autons::prog:
        break;
    }
}

void Auton::startAsyncTaskWithSettings(std::function<bool()> iasyncCondition, std::function<void()> iasyncAction)
{
    masyncCondition = iasyncCondition;
    masyncAction = iasyncAction;
    masync_task.resume();
}
void Auton::async_task_func(void *)
{
    while (true)
    {
        if (masyncCondition())
        {
            masyncAction();
            masync_task.suspend();
        }
        pros::delay(20);
    }
}
std::function<bool()> Auton::masyncCondition = []()
{ return false; };
std::function<void()> Auton::masyncAction;
pros::Task Auton::masync_task(Auton::async_task_func);
