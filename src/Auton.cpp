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
    def::sm_mg.mcontrolEnabled = false;
    // awp

    switch (auton)
    {
    case Autons::none:
        break;
    case Autons::awp:
        // Drivetrain::turnToAngle(-30_deg, cutDrive(10));
        Drivetrain::tankToPoint({18_in, 0_in, 0_deg}, cutDrive(12));
        startAsyncTaskWithSettings([&]()
                                   { return def::sm_lift.goalInRange(); },
                                   makeFunc({ def::sm_lift.engageClaw(); }));
        Drivetrain::straightToPoint({15_in, 25_in, 0_deg}, cutDrive(3));
        Drivetrain::turnToAngle(90_deg);
        Drivetrain::tankToPoint({16_in, -83_in, 0_deg}, {AsyncAction(70, makeFunc({ def::sm_lift.disengageClaw(); }))});
        Drivetrain::turnToAngle(0_deg);
        Drivetrain::tankToPoint({0_in, -93_in, 0_deg});
        def::sm_mg.setState(MG_STATES::bottom);
        Drivetrain::turnToAngle(-83_deg);
        Drivetrain::tankToPoint({-8_in, -76_in, 0_deg}, cutDrive(4));
        def::sm_mg.setState(MG_STATES::top);
        def::sm_lift.setState(LIFT_STATES::top);
        pros::delay(1800);
        def::sm_mg.setState(MG_STATES::bottom);
        def::sm_lift.setState(LIFT_STATES::bottom);
        pros::delay(1000);
        Drivetrain::tankToPoint({0_in, -18_in, 0_deg});

        // Drivetrain::turnToAngle(100_deg, cutDrive(10));
        break;
    case Autons::awp1N:
        Drivetrain::tankToPoint({18_in, 0_in, 0_deg}, cutDrive(12));
        Drivetrain::straightToPoint({15_in, 25_in, 0_deg});
        Drivetrain::turnToAngle(90_deg);
        Drivetrain::tankToPoint({22_in, 10_in, 0_deg}, {}, 0.5);
        Drivetrain::turnToAngle(0_deg);
        startAsyncTaskWithSettings([&]()
                                   { return def::sm_lift.goalInRange(); },
                                   makeFunc({ def::sm_lift.engageClaw(); }));
        Drivetrain::tankToPoint({45_in, 10_in, 0_deg});
        pros::delay(200);
        // def::sm_lift.engageClaw();
        Drivetrain::tankToPoint({5_in, 10_in, 0_deg});
        // def::sm_lift.engageClaw();
        break;
    case Autons::oneNeutral:
        startAsyncTaskWithSettings([&]()
                                   { return def::sm_lift.goalInRange(); },
                                   makeFunc({ def::sm_lift.engageClaw(); }));
        Drivetrain::tankToPoint({50_in, 0_in, 0_deg});
        Drivetrain::tankToPoint({5_in, 0_in, 0_deg});
        break;
    case Autons::twoNeutral:
        break;
    case Autons::prog:
        Drivetrain::tankToPoint({8_ft, 0_in, 0_deg});
        Drivetrain::turnToAngle(40_deg);
        Drivetrain::tankToPoint({12_in, 6_ft, 0_deg});
        Drivetrain::turnToAngle(0_deg);
        Drivetrain::tankToPoint({8_in, 6_ft, 0_deg});
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
