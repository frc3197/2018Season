#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
<<<<<<< HEAD

#include <Commands/AutoCommands/Nothing.h>
#include <Commands/AutoCommands/DriveInside.h>
#include <Commands/AutoCommands/DriveStraight.h>
#include <Commands/AutoCommands/DriveOutsideSame.h>
#include <Commands/AutoCommands/DriveOutsideOpp.h>
=======
//
//#include <Commands/AutoCommands/Nothing.h>
//#include <Commands/AutoCommands/DriveInside.h>
//#include <Commands/AutoCommands/DriveStraight.h>
//#include <Commands/AutoCommands/DriveOutsideSame.h>
//#include <Commands/AutoCommands/DriveOutsideOpp.h>
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5

#include "CommandBase.h"

class Robot: public frc::IterativeRobot {

private:
	std::unique_ptr<frc::Command> autonomousCommand;
	frc::SendableChooser<std::string> positionChooser;

public:
	void RobotInit() {
		CommandBase::init();

		positionChooser.AddDefault("Nothing", "N");
		positionChooser.AddObject("Straight", "S");
		positionChooser.AddObject("Left", "L");
		positionChooser.AddObject("Middle", "M");
		positionChooser.AddObject("Right", "R");

		SmartDashboard::PutData("Position", &positionChooser);

	}

	void DisabledInit() override {

	}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void AutonomousInit() override {
		std::string gameData;
		gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
		if (gameData[1] == 'L') {
			CommandBase::oi->setGamePrefs(-1);
		} else {
			CommandBase::oi->setGamePrefs(1);
		}

		std::string position = positionChooser.GetSelected();

<<<<<<< HEAD
		if (position.compare("M") == 0) {
			if (gameData[0] == 'L') {
					CommandBase::oi->setGamePrefs(-1);
				} else {
					CommandBase::oi->setGamePrefs(1);
				}
			autonomousCommand.reset(new DriveInside());
		} else if (position.compare("L") == 0 || position.compare("R") == 0) {
			if (position.compare(gameData.substr(1, 1)) == 0) {
				autonomousCommand.reset(new DriveOutsideSame());
			} else {
				autonomousCommand.reset(new DriveOutsideOpp());
			}
		} else if (position.compare("S") == 0) {
			autonomousCommand.reset(new DriveStraight());
		} else {
			autonomousCommand.reset(new Nothing());
		}
=======
//		if (position.compare("M") == 0) {
//			if (gameData[0] == 'L') {
//					CommandBase::oi->setGamePrefs(-1);
//				} else {
//					CommandBase::oi->setGamePrefs(1);
//				}
//			autonomousCommand.reset(new DriveInside());
//		} else if (position.compare("L") == 0 || position.compare("R") == 0) {
//			if (position.compare(gameData.substr(1, 1)) == 0) {
//				autonomousCommand.reset(new DriveOutsideSame());
//			} else {
//				autonomousCommand.reset(new DriveOutsideOpp());
//			}
//		} else if (position.compare("S") == 0) {
//			autonomousCommand.reset(new DriveStraight());
//		} else {
//			autonomousCommand.reset(new Nothing());
//		}
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5

//		SmartDashboard::PutString("position", position);
//		SmartDashboard::PutString("gamedata", gameData.substr(1, 1));
//		SmartDashboard::PutNumber("compare", position.compare("R"));


		if (autonomousCommand.get() != nullptr) {
			autonomousCommand->Start();
		}


//		autonomousCommand.reset(chooser.GetSelected());
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		if (autonomousCommand != nullptr) {
			autonomousCommand->Cancel();
		}
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TestPeriodic() override {
//		frc::LiveWindow::GetInstance()->Run();
	}

};

START_ROBOT_CLASS(Robot)
