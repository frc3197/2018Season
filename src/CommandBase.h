#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <memory>
#include <string>

#include <Commands/Command.h>

#include "OI.h"
#include "Subsystems/RobotDriveWithJoystick.h"
#include "Subsystems/Mechanisms.h"

class CommandBase: public frc::Command {
public:
	CommandBase(const std::string& name);
	CommandBase() = default;
	static void init();

	static std::unique_ptr<OI> oi;
	static RobotDriveWithJoystick *robotDrive;
	static Mechanisms *auxMotors;
	static Preferences *prefs;
};

#endif  // COMMAND_BASE_H
