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
    // when making autons, you must add the text to the dropdown in DisplayControl.cpp, a new enum
    // value in Auton.hpp, and a new case is this switch
    Auton::readSettings();
    Auton::suspendAsyncTask();

    Timer timer = Timer();
    QTime startTime = timer.millis();

    waitForImu();
    CustomOdometry::setStateInitial({0_in, 0_in, -def::imu1.get_rotation() * degree});

    DrivetrainStateMachine::disableControl();
    LiftStateMachine::disableControl();
    IntakeStateMachine::disableControl();
    HolderStateMachine::disableControl();

    DrivetrainStateMachine::setState(DT_STATES::busy);

    switch (auton)
    {
    case Autons::none:
        break;
    case Autons::left:
        Auton::startAsyncTaskWithSettings(
            makeFunc({ return LiftStateMachine::goalInRange(def::SET_LIFT_DISTANCE_MIN_MM + 15); }), // if the goal is in range
            makeFunc({ LiftStateMachine::engageClaw();
                    pros::delay(50);
                    Drivetrain::disable();  // stop driving forward
                    pros::delay(500); 
                    LiftStateMachine::setState(LIFT_STATES::rings); }));

        LiftStateMachine::disengageClaw();
        Drivetrain::straightToPoint({47_in, -12_in, 0_deg}, cutDrive(1)); // drive towards the goal
        Drivetrain::straightToPoint({-1_in, 5_in, 0_deg}, cutDrive(1));
        Drivetrain::turnToAngle(60_deg, cutDrive(10)); // turn towards alliance goal

        // pros::delay(1000);
        // Drivetrain::straightToPoint(
        //     {-5_in, -17_in, 0_deg}, {AsyncAction(22, makeFunc({ Drivetrain::setMaxSpeed(0.4); })), AsyncAction(12, makeFunc({ Drivetrain::disable(); }))}, false, 6_in, 1.7, PID(0.3, 0.0, 0.8, 0.0, 0.25, 0.00001, 1_ms), PID(0.07, 0.02, 0.3, 1, 0.25, 0.01, 1_ms));
        // Drivetrain::setMaxSpeed(1);
        // HolderStateMachine::setState(HOLDER_STATES::closed);
        seekHolder(); // EXPERIMENTAL
        Drivetrain::straightToPoint({2_in, 4_in, 0_deg}, cutDrive(1));
        LiftStateMachine::disengageClaw();
        IntakeStateMachine::setState(INTAKE_STATES::in);
        Drivetrain::straightToPoint({30_in, -20_in, 0_deg}, {AsyncAction(13, makeFunc({ Drivetrain::setMaxSpeed(0.33); })), AsyncAction(3, makeFunc({ Drivetrain::disable(); }))}, true);
        Drivetrain::setMaxSpeed(0.5);
        Drivetrain::straightToPoint({30_in, -70_in, 0_deg}, {AsyncAction(38, makeFunc({ Drivetrain::setMaxSpeed(0.25); })), AsyncAction(3, makeFunc({ Drivetrain::disable(); }))});
        break;
    case Autons::right:
        Auton::startAsyncTaskWithSettings(
            makeFunc({ return LiftStateMachine::goalInRange(def::SET_LIFT_DISTANCE_MIN_MM + 15); }), // if the goal is in range
            makeFunc({ LiftStateMachine::engageClaw();
                    pros::delay(50);
                    Drivetrain::disable();  // stop driving forward
                    pros::delay(1000); 
                    LiftStateMachine::setState(LIFT_STATES::top); }));
        LiftStateMachine::disengageClaw();
        Drivetrain::straightToPoint({52_in, 0_in, 0_deg}, {AsyncAction(17, makeFunc({ Drivetrain::setMaxSpeed(0.4); })), AsyncAction(2, makeFunc({ Drivetrain::disable(); }))});

        pros::delay(200);
        Drivetrain::setMaxSpeed(0.75);
        Drivetrain::straightToPoint({17_in, 0_in, 0_deg}, cutDrive(1));
        Drivetrain::setMaxSpeed(1);
        Drivetrain::turnToAngle(90_deg, cutDrive(5));
        // Drivetrain::straightToPoint({17_in, -18_in, 0_deg}, {AsyncAction(17, makeFunc({ Drivetrain::setMaxSpeed(0.5); })), AsyncAction(9, makeFunc({ Drivetrain::disable(); }))});
        // HolderStateMachine::setState(HOLDER_STATES::closed); // get the alliance goal
        // pros::delay(10);
        seekHolder(); // EXPERIMENTAL
        Drivetrain::setMaxSpeed(1);
        pros::delay(10);
        Drivetrain::straightToPoint({17_in, -12_in, 0_deg}, cutDrive(3)); // back up
        Drivetrain::turnToPoint({50_in, -12_in, 0_deg}, cutDrive(5));     // turn to face the row of rings
        IntakeStateMachine::setState(INTAKE_STATES::in);
        Drivetrain::straightToPoint({50_in, -12_in, 0_deg}, {AsyncAction(35, makeFunc({ Drivetrain::setMaxSpeed(0.35); })), AsyncAction(3, makeFunc({ Drivetrain::disable(); }))}, true); // drive into the row of rings
        Drivetrain::setMaxSpeed(1);
        Drivetrain::turnToPoint({50_in, -24_in, 0_deg}, cutDrive(5)); // turn to the next row
        Drivetrain::setMaxSpeed(0.35);
        Drivetrain::straightToPoint({50_in, -24_in, 0_deg}, cutDrive(1)); // drive into the next row

        Drivetrain::setMaxSpeed(1);
        Drivetrain::turnToAngle(0_deg, cutDrive(45));
        LiftStateMachine::setState(LIFT_STATES::rings);
        Drivetrain::straightToPoint({8_in, -12_in, 0_deg}, cutDrive(3));
        HolderStateMachine::setState(HOLDER_STATES::open);
        Drivetrain::arcadeFor(0.5, 0, 200);
        break;
    case Autons::awp:
        /*
            // drop rings in the first alliance goal
            LiftStateMachine::setState(LIFT_STATES::top);
            pros::delay(600);
            LiftStateMachine::disengageClaw();
            pros::delay(100);

            // drive up to second alliance goal
            Drivetrain::straightToPoint({-3_in, 17_in, 0_deg}, cutDrive(6));
            LiftStateMachine::setState(LIFT_STATES::bottom);
            // Drivetrain::straightToPoint({75_in, 24_in, 0_deg}, {AsyncAction(35, makeFunc({ Drivetrain::setMaxSpeed(0.5); })), AsyncAction(2, makeFunc({ Drivetrain::disable(); }))});
            LiftStateMachine::setState(LIFT_STATES::rings);
            Drivetrain::straightToPoint({90_in, 23_in, 0_deg}, {AsyncAction(16, makeFunc({ Drivetrain::setMaxSpeed(0.5); })), AsyncAction(2, makeFunc({ Drivetrain::disable(); }))});
            Drivetrain::setMaxSpeed(1);
            HolderStateMachine::setState(HOLDER_STATES::closed);

            IntakeStateMachine::setState(INTAKE_STATES::in);

            Drivetrain::straightToPoint({93_in, 60_in, 0_deg}, {AsyncAction(28, makeFunc({ Drivetrain::setMaxSpeed(0.4); })), AsyncAction(1, makeFunc({ Drivetrain::disable(); }))}, true);
            Drivetrain::setMaxSpeed(1);
            Drivetrain::straightToPoint({100_in, 20_in, 0_deg}, cutDrive(3));
            HolderStateMachine::setState(HOLDER_STATES::open); // back up with 14 seconds left
            */
        LiftStateMachine::setState(LIFT_STATES::top);
        pros::delay(600);
        LiftStateMachine::disengageClaw();
        pros::delay(100);

        LiftStateMachine::setState(LIFT_STATES::bottom);
        Drivetrain::turnToPoint({15_in, 18_in, 0_deg}, cutDrive(5));
        Drivetrain::straightToPoint({15_in, 18_in, 0_deg}, cutDrive(3));
        Drivetrain::straightToPoint({73_in, 20_in, 0_deg}, {AsyncAction(45, makeFunc({ Drivetrain::setMaxSpeed(0.5); })), AsyncAction(1, makeFunc({ Drivetrain::disable(); }))});
        pros::delay(200);
        Drivetrain::setMaxSpeed(1);
        Drivetrain::turnToAngle(180_deg);
        Drivetrain::setMaxSpeed(0.5);
        Drivetrain::straightToPoint({95_in, 24_in, 0_deg}, cutDrive(30));
        seekHolder(); // EXPERIMENTAL
        pros::delay(500);
        IntakeStateMachine::setState(INTAKE_STATES::in);
        pros::delay(500);

        Drivetrain::straightToPoint({65_in, 22_in, 0_deg}, cutDrive(3));
        HolderStateMachine::setState(HOLDER_STATES::open);

        break;
    case Autons::awp1N:
        LiftStateMachine::setState(LIFT_STATES::top);
        pros::delay(600);
        LiftStateMachine::disengageClaw();
        pros::delay(100);
        LiftStateMachine::setState(LIFT_STATES::bottom);
        Drivetrain::turnToPoint({14_in, 48_in, 0_deg});
        Auton::startAsyncTaskWithSettings(
            makeFunc({ return LiftStateMachine::goalInRange(); }), // if the goal is in range
            makeFunc({ LiftStateMachine::engageClaw();
                    pros::delay(50);
                    Drivetrain::disable();  // stop driving forward
                    pros::delay(500); 
                    LiftStateMachine::setState(LIFT_STATES::top); }));
        Drivetrain::straightForDistance(5.5_ft);
        Drivetrain::straightToPoint({13_in, 38_in, 0_deg}, cutDrive(10)); // back up with the neutral goal

        // Drivetrain::turnToPoint({42_in, 39_in, 0_deg}, cutDrive(10), PID(0.07, 0.02, 0.3, 1, 0.25, 0.01, 1_ms)); // turn towards ring pile
        Drivetrain::straightToPoint({37_in, 39_in, 0_deg}, cutDrive(8), true, 6_in, 1.7, PID(0.3, 0.0, 0.8, 0.0, 0.25, 0.00001, 1_ms), PID(0.07, 0.02, 0.3, 1, 0.25, 0.01, 1_ms));

        // Drivetrain::turnToAngle(-82_deg, cutDrive(1)); // face the platform
        waitUntil(makeFunc({ return LiftStateMachine::getAngle() > def::SET_LIFT_TOP_DEG - 10; }));
        Drivetrain::setMaxSpeed(0.5);
        Drivetrain::straightToPoint({49_in, 21_in, 0_deg}, cutDrive(1), false, 6_in, 1.7, PID(0.3, 0.0, 0.8, 0.0, 0.25, 0.00001, 1_ms), PID(0.07, 0.02, 0.3, 1, 0.25, 0.01, 1_ms)); // drive towards the platform
        Drivetrain::setMaxSpeed(1);
        Drivetrain::turnToAngle(-90_deg, cutDrive(1), PID(0.07, 0.02, 0.3, 1, 0.25, 0.01, 1_ms));
        LiftStateMachine::disengageClaw();
        pros::delay(300);
        // Drivetrain::arcadeFor(-0.5, 0.0, 100);

        Drivetrain::turnToAngle(180_deg); // face the alliance goal with the holder
        Drivetrain::straightToPoint({98_in, 23_in, 0_deg}, {AsyncAction(16, makeFunc({ Drivetrain::setMaxSpeed(0.5); })), AsyncAction(2, makeFunc({ Drivetrain::disable(); }))});
        Drivetrain::setMaxSpeed(1);
        HolderStateMachine::setState(HOLDER_STATES::closed);

        // Drivetrain::straightToPoint({97_in, 24_in, 0_deg}, cutDrive(1)); // get the row of rings
        IntakeStateMachine::setState(INTAKE_STATES::in);
        // Drivetrain::turnToAngle(90_deg, cutDrive(0.5));

        // Auton::startAsyncTaskWithSettings(makeFunc({ return (timer.millis() - startTime) > 14_s; }), makeFunc({
        //     Drivetrain::disable();
        //     Drivetrain::setMaxSpeed(1);
        //     Drivetrain::straightToPoint({97_in, 24_in, 0_deg}, cutDrive(3)); HolderStateMachine::setState(HOLDER_STATES::open); })); // back up with 14 seconds left

        Drivetrain::straightToPoint({97_in, 60_in, 0_deg}, {AsyncAction(28, makeFunc({ Drivetrain::setMaxSpeed(0.4); })), AsyncAction(1, makeFunc({ Drivetrain::disable(); }))}, true);
        Drivetrain::setMaxSpeed(1);
        Drivetrain::straightToPoint({107_in, 20_in, 0_deg}, cutDrive(3));
        HolderStateMachine::setState(HOLDER_STATES::open); // back up with 14 seconds left
        break;
    case Autons::oneNeutral:
        Auton::startAsyncTaskWithSettings(
            makeFunc({ return LiftStateMachine::goalInRange(def::SET_LIFT_DISTANCE_MIN_MM + 15); }), // if the goal is in range
            makeFunc({ LiftStateMachine::engageClaw();
                    pros::delay(50);
                    Drivetrain::disable();  // stop driving forward
                    pros::delay(1000); 
                    LiftStateMachine::setState(LIFT_STATES::rings); }));

        LiftStateMachine::disengageClaw();
        Drivetrain::straightToPoint({52_in, 0_in, 0_deg}, cutDrive(2));

        Drivetrain::straightToPoint({10_in, 0_in, 0_deg}, {}, false, 6_in);
        break;
    case Autons::safeLeft:
        LiftStateMachine::setState(LIFT_STATES::top);
        pros::delay(600);
        LiftStateMachine::disengageClaw();
        pros::delay(100);
        LiftStateMachine::setState(LIFT_STATES::bottom);
        Drivetrain::turnToPoint({14_in, 48_in, 0_deg});
        Auton::startAsyncTaskWithSettings(
            makeFunc({ return LiftStateMachine::goalInRange(); }), // if the goal is in range
            makeFunc({ LiftStateMachine::engageClaw();
                    pros::delay(50);
                    Drivetrain::disable();  // stop driving forward
                    pros::delay(500); 
                    LiftStateMachine::setState(LIFT_STATES::top); }));
        Drivetrain::straightForDistance(5.5_ft);
        Drivetrain::straightToPoint({13_in, 38_in, 0_deg}, cutDrive(10)); // back up with the neutral goal

        break;
    case Autons::prog:
        LiftStateMachine::disengageClaw();
        Drivetrain::straightToPoint({8_in, 0_in, 0_deg}, cutDrive(1));
        LiftStateMachine::engageClaw();
        Drivetrain::straightToPoint({0_in, 0_in, 0_deg}, cutDrive(1));
        break;
    }
}

/* ----------------------------------------------------------- */
/*                     Private Information                     */
/* ----------------------------------------------------------- */

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
