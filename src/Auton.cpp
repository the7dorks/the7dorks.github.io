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

    mstartTime = mtimer.millis();

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
            makeFunc({ return LiftStateMachine::goalInRange(def::SET_LIFT_DISTANCE_MIN_MM - 10); }), // if the goal is in range
            makeFunc({
                LiftStateMachine::engageClaw();
                pros::delay(50);
                Drivetrain::disable(); // stop driving forward
                pros::delay(1500);
                LiftStateMachine::setState(LIFT_STATES::rings);
            }));

        LiftStateMachine::disengageClaw();
        LiftStateMachine::setState(LIFT_STATES::bottom);

        Drivetrain::straightToPoint({47_in, -12_in, 0_deg}, cutDrive(1)); // drive towards the goal
        Drivetrain::straightToPoint({-1_in, 5_in, 0_deg}, cutDrive(1));
        Drivetrain::turnToAngle(60_deg, cutDrive(10)); // turn towards alliance goal

        seekHolder();
        Drivetrain::straightToPoint({2_in, 4_in, 0_deg}, cutDrive(1));
        LiftStateMachine::disengageClaw();
        IntakeStateMachine::setState(INTAKE_STATES::in);
        Auton::startTaskAfterDelay(14_s, makeFunc({ HolderStateMachine::setState(HOLDER_STATES::open); 
        Drivetrain::disable();
        Drivetrain::arcadeFor(0.3, 0, 200); }));

        Drivetrain::straightToPoint({30_in, -20_in, 0_deg}, {AsyncAction(20, makeFunc({ Drivetrain::setMaxSpeed(0.25); })), AsyncAction(3, makeFunc({ Drivetrain::disable(); }))}, true);
        Drivetrain::straightToPoint({30_in, -70_in, 0_deg}, {AsyncAction(38, makeFunc({ Drivetrain::setMaxSpeed(0.25); })), AsyncAction(3, makeFunc({ Drivetrain::disable(); }))});
        break;
    case Autons::right:
        Auton::startAsyncTaskWithSettings(
            makeFunc({ return LiftStateMachine::goalInRange(def::SET_LIFT_DISTANCE_MIN_MM); }), // if the goal is in range
            makeFunc({ LiftStateMachine::engageClaw();
                    pros::delay(50);
                    Drivetrain::disable();  // stop driving forward
                    pros::delay(1500); 
                    LiftStateMachine::setState(LIFT_STATES::rings); }));
        LiftStateMachine::disengageClaw();
        LiftStateMachine::setState(LIFT_STATES::bottom);
        Drivetrain::straightToPoint({52_in, 0_in, 0_deg}, cutDrive(2));

        Drivetrain::straightToPoint({17_in, 0_in, 0_deg}, cutDrive(1), false, 6_in, 1.7, PID(0.3, 0.001, 0.8, 3.0, 0.5, 0.00001, 1_ms), PID(0.07, 0.02, 0.20, 1, 0.25, 0.01, 1_ms), Slew(0.05, 0.5));

        Drivetrain::turnToAngle(90_deg, cutDrive(5));
        // Drivetrain::straightToPoint({17_in, -18_in, 0_deg}, {AsyncAction(17, makeFunc({ Drivetrain::setMaxSpeed(0.5); })), AsyncAction(9, makeFunc({ Drivetrain::disable(); }))});
        // HolderStateMachine::setState(HOLDER_STATES::closed); // get the alliance goal
        // pros::delay(10);
        seekHolder(); // EXPERIMENTAL
        LiftStateMachine::setState(LIFT_STATES::top);
        pros::delay(10);
        Drivetrain::straightToPoint({17_in, -10_in, 0_deg}, cutDrive(3)); // back up
        Drivetrain::turnToPoint({50_in, -10_in, 0_deg}, cutDrive(5));     // turn to face the row of rings
        IntakeStateMachine::setState(INTAKE_STATES::in);
        Auton::startTaskAfterDelay(13_s, makeFunc({
                                       Drivetrain::setMaxSpeed(1);
                                       Drivetrain::turnToAngle(0_deg, cutDrive(45));
                                       Drivetrain::straightToPoint({8_in, -12_in, 0_deg}, cutDrive(3));
                                       LiftStateMachine::setState(LIFT_STATES::rings);
                                       HolderStateMachine::setState(HOLDER_STATES::open);
                                       Drivetrain::arcadeFor(0.5, 0, 200);
                                   }));
        Drivetrain::straightToPoint({50_in, -10_in, 0_deg}, {AsyncAction(35, makeFunc({ Drivetrain::setMaxSpeed(0.25); })), AsyncAction(3, makeFunc({ Drivetrain::disable(); }))}, true); // drive into the row of rings
        Drivetrain::setMaxSpeed(1);
        Drivetrain::turnToPoint({50_in, -24_in, 0_deg}, cutDrive(5)); // turn to the next row
        Drivetrain::setMaxSpeed(0.25);
        Drivetrain::straightToPoint({50_in, -24_in, 0_deg}, cutDrive(1)); // drive into the next row

        break;
    case Autons::awp:
        LiftStateMachine::setState(LIFT_STATES::top);
        pros::delay(300);
        LiftStateMachine::disengageClaw();
        pros::delay(100);

        LiftStateMachine::setState(LIFT_STATES::bottom);
        Drivetrain::turnToPoint({15_in, 18_in, 0_deg}, cutDrive(3));
        Drivetrain::straightToPoint({15_in, 18_in, 0_deg}, cutDrive(1));
        Drivetrain::turnToPoint({73_in, 20_in, 0_deg}, cutDrive(3));
        Drivetrain::straightToPoint({73_in, 20_in, 0_deg}, {AsyncAction(45, makeFunc({ Drivetrain::setMaxSpeed(1); })), AsyncAction(1, makeFunc({ Drivetrain::disable(); }))});
        pros::delay(200);
        Drivetrain::setMaxSpeed(1);
        Drivetrain::turnToAngle(180_deg);

        seekHolder();
        pros::delay(500);
        IntakeStateMachine::setState(INTAKE_STATES::in);
        pros::delay(500);
        Drivetrain::straightToPoint({65_in, 23_in, 0_deg}, cutDrive(3));
        HolderStateMachine::setState(HOLDER_STATES::open);
        pros::delay(500);
        Drivetrain::straightToPoint({15_in, 23_in, 0_deg}, cutDrive(1));
        Drivetrain::turnToPoint({15_in, 63_in, 0_deg});
        Drivetrain::straightToPoint({15_in, 63_in, 0_deg}, cutDrive(30));
        if (def::distance_claw.get() < 600)
        {
            seekClaw();
            Drivetrain::straightToPoint({12_in, 25_in, 0_deg});
        }
        else
        {
            Drivetrain::turnToAngle(90_deg);
        }

        // LiftStateMachine::setState(LIFT_STATES::bottom);
        // Drivetrain::turnToPoint({14_in, 22_in, 0_deg}, cutDrive(5));
        // Drivetrain::straightToPoint({14_in, 22_in, 0_deg}, cutDrive(3));
        // Drivetrain::straightToPoint({72_in, 22_in, 0_deg}, {AsyncAction(45, makeFunc({ Drivetrain::setMaxSpeed(1); })), AsyncAction(25, makeFunc({ Drivetrain::disable(); }))});
        // Drivetrain::straightToPoint({76_in, 40_in, 0_deg}, cutDrive(8));
        // pros::delay(200);
        // Drivetrain::turnToAngle(135_deg);
        // seekHolder();
        // pros::delay(500);
        // IntakeStateMachine::setState(INTAKE_STATES::in);
        // pros::delay(500);

        // Drivetrain::straightToPoint({65_in, 26_in, 0_deg}, cutDrive(3));
        // HolderStateMachine::setState(HOLDER_STATES::open);
        // pros::delay(500);
        // Drivetrain::turnToPoint({13_in, 63_in, 0_deg});
        // Drivetrain::straightToPoint({13_in, 63_in, 0_deg}, cutDrive(30));
        // if (def::distance_claw.get() < 600)
        // {
        //     seekClaw();
        //     Drivetrain::straightToPoint({12_in, 25_in, 0_deg});
        // }
        // else
        // {
        //     Drivetrain::turnToAngle(90_deg);
        // }
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
            makeFunc({ return LiftStateMachine::goalInRange(def::SET_LIFT_DISTANCE_MIN_MM); }), // if the goal is in range
            makeFunc({
                LiftStateMachine::engageClaw();
                pros::delay(50);
                Drivetrain::disable(); // stop driving forward
            }));

        LiftStateMachine::disengageClaw();
        LiftStateMachine::setState(LIFT_STATES::bottom);
        Drivetrain::straightToPoint({52_in, 0_in, 0_deg}, cutDrive(2));

        Drivetrain::straightToPoint({10_in, 0_in, 0_deg}, {}, false, 6_in, 1.7, PID(0.3, 0.001, 0.8, 3.0, 0.5, 0.00001, 1_ms), PID(0.07, 0.02, 0.20, 1, 0.25, 0.01, 1_ms), Slew(0.05, 0.5));
        break;
    case Autons::rightMiddle:
        Auton::startAsyncTaskWithSettings(
            makeFunc({ return LiftStateMachine::goalInRange(def::SET_LIFT_DISTANCE_MIN_MM); }), // if the goal is in range
            makeFunc({
                LiftStateMachine::engageClaw();
                pros::delay(50);
                Drivetrain::disable(); // stop driving forward
            }));

        LiftStateMachine::disengageClaw();
        LiftStateMachine::setState(LIFT_STATES::bottom);
        Drivetrain::straightToPoint({71_in, 0_in, 0_deg}, cutDrive(2)); // drive to the middle goal

        Drivetrain::straightToPoint({20_in, 0_in, 0_deg}, cutDrive(3)); // reverse
        break;
    case Autons::right2N:
        Auton::startAsyncTaskWithSettings(
            makeFunc({ return LiftStateMachine::goalInRange(def::SET_LIFT_DISTANCE_MIN_MM); }), // if the goal is in range
            makeFunc({
                LiftStateMachine::engageClaw();
                pros::delay(50);
                Drivetrain::disable(); // stop driving forward
            }));

        LiftStateMachine::disengageClaw();
        LiftStateMachine::setState(LIFT_STATES::bottom);
        Drivetrain::straightToPoint({71_in, 0_in, 0_deg}, cutDrive(2)); // drive to the middle goal

        Drivetrain::straightToPoint({20_in, 0_in, 0_deg}, cutDrive(20));  // reverse
        Drivetrain::straightToPoint({27_in, -10_in, 0_deg}, cutDrive(3)); // turn towards right neutral goal
        Drivetrain::turnToAngle(149_deg, cutDrive(10));                   // face it
        seekHolder();
        Drivetrain::straightToPoint({6_in, 1_in, 0_deg}, cutDrive(3)); // drive back to starting position
        break;
    case Autons::right2NPlus:
        Auton::startAsyncTaskWithSettings(
            makeFunc({ return LiftStateMachine::goalInRange(def::SET_LIFT_DISTANCE_MIN_MM); }), // if the goal is in range
            makeFunc({
                LiftStateMachine::engageClaw();
                pros::delay(50);
                Drivetrain::disable(); // stop driving forward
            }));

        LiftStateMachine::disengageClaw();
        LiftStateMachine::setState(LIFT_STATES::bottom);
        Drivetrain::straightToPoint({71_in, 0_in, 0_deg}, cutDrive(2)); // drive to the middle goal

        Drivetrain::straightToPoint({20_in, 0_in, 0_deg}, cutDrive(20));  // reverse
        Drivetrain::straightToPoint({27_in, -10_in, 0_deg}, cutDrive(3)); // turn towards right neutral goal
        Drivetrain::turnToAngle(149_deg, cutDrive(10));                   // face it
        if (def::distance_eye_back_center.get() < 600)
        {
            seekHolder();
        }
        Drivetrain::straightToPoint({6_in, 1_in, 0_deg}, cutDrive(3)); // drive back to starting position
        LiftStateMachine::disengageClaw();
        Drivetrain::straightToPoint({12_in, -3_in, 0_deg}, cutDrive(2)); // reverse
        Drivetrain::turnToAngle(239_deg);
        Drivetrain::straightForDistance(-1_ft);                           // back up a little
        HolderStateMachine::setState(HOLDER_STATES::open);                // release the second neutral goal
        Drivetrain::straightToPoint({17_in, -10_in, 0_deg}, cutDrive(2)); // drive away from it
        Drivetrain::turnToAngle(59_deg);                                  // turn around
        seekHolder();                                                     // pick up the alliance goal
        pros::delay(100);
        IntakeStateMachine::setState(INTAKE_STATES::in);
        seekClaw(); // pick up the short neutral goal again, but in the claw
        IntakeStateMachine::setState(INTAKE_STATES::off);
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

void Auton::startTaskAfterDelay(QTime idelay, std::function<void()> iaction)
{
    mdelayAction = iaction;
    mdelayTime = idelay;
    mdelay_task.resume();
}
void Auton::delay_task_func(void *)
{
    while (true)
    {
        if (mtimer.millis() - mstartTime > mdelayTime)
        {
            mdelayAction();
            mdelay_task.suspend();
        }
        pros::delay(20);
    }
}
std::function<void()> Auton::mdelayAction;
Timer Auton::mtimer = Timer();
QTime Auton::mstartTime = 0_ms;
QTime Auton::mdelayTime = 2_min;
pros::Task Auton::mdelay_task(Auton::delay_task_func);
