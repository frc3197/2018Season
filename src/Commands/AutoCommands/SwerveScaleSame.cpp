#include <Commands/AutoCommands/SwerveScaleSame.h>

SwerveScaleSame::SwerveScaleSame() {
	Requires(robotDrive);
//	Requires(auxMotors); dont require 2 or bad things :(
}

// Called just before this Command runs the first time
void SwerveScaleSame::Initialize() {
	timer.Reset();
	timer.Start();

	state = 0;
	finished = false;

	eleTime = CommandBase::prefs->GetFloat("scaleEleTime", 0);

	eleSpeedUp = CommandBase::prefs->GetFloat("eleSpeedUp", 0);
	eleSpeedDown = -CommandBase::prefs->GetFloat("eleSpeedDown", 0);

	baseSpeed = CommandBase::prefs->GetFloat("scaleSameBaseSpeed", 0);
	backupSpeed = CommandBase::prefs->GetFloat("scaleSameBackupSpeed", 0);

	straightDistance = CommandBase::prefs->GetFloat("scaleSameStraightDistance",
			0);

	driveOverTime = CommandBase::prefs->GetFloat("scaleDriveOverTime", 0);
	backupTime = CommandBase::prefs->GetFloat("scaleBackupTime", 0);

	if (CommandBase::oi->getGamePrefs() == 1) {
		extraSpeed = CommandBase::prefs->GetFloat("scaleSameExtraSpeedRight",
				0);
		extraExtraSpeed = CommandBase::prefs->GetFloat(
				"scaleSameExtraESpeedRight", 0);
		swerveAngle = CommandBase::prefs->GetFloat("scaleSameAngleRight", 0);
	} else {
		extraSpeed = CommandBase::prefs->GetFloat("scaleSameExtraSpeedLeft", 0);
		extraExtraSpeed = CommandBase::prefs->GetFloat(
				"scaleSameExtraSpeedLeft", 0);
		swerveAngle = CommandBase::prefs->GetFloat("scaleSameAngleLeft", 0);
	}

	scaleAngle = CommandBase::prefs->GetFloat("scaleSameScaleAngle", 0);
	claw->ResetTimerPickup();
	claw->Reset();
}

void SwerveScaleSame::Execute() {
	SmartDashboard::PutNumber("Scale State", state);
	bool up = claw->Pickup(false);
	float gyroAngle = robotDrive->gyroAngle();
	if (CommandBase::oi->getGamePrefs() == 1) {
		gyroAngle *= -1;
	}
	float l = 0;
	float r = 0;
	float eleSpeed = 0;
	if (up) {
		switch (state) {
		case Straight: //drive straight distance using encoders
			if (robotDrive->gotoDistance(straightDistance, extraSpeed, 0))
				IncrementState();
			break;
		case SwerveIn:
			if (gyroAngle > swerveAngle) {
				l = baseSpeed;
				r = baseSpeed + extraSpeed;
			} else {
				IncrementState();
			}
			break;
		case SwerveOut:
			if (gyroAngle < scaleAngle) {
				l = baseSpeed + extraSpeed;
				r = baseSpeed;
			} else {
				IncrementState();
			}
			break;
		case RaiseFully:
			IncrementState();
			break;
		case DriveOverScale:
			l = -backupSpeed;
			r = -backupSpeed;
			if (timer.HasPeriodPassed(driveOverTime)) {
				IncrementState();
				claw->ResetTimerDrop();
			}
			break;
		case Drop:
			if (claw->Drop()) {
				IncrementState();
			}
			break;
		case Backup:
			l = backupSpeed;
			r = backupSpeed;
			if (timer.HasPeriodPassed(backupTime)) {
				IncrementState();
			}
			break;
		case Turn:
			eleSpeed = eleSpeedDown;
			if (robotDrive->advancedTurnBot(extraSpeed + baseSpeed, -180)) {
				IncrementState();
			}
			break;
		default:
			End();
		}
		if (up && state >= SwerveIn && state <= Drop) {
			eleSpeed = eleSpeedUp;
		}
		if (eleSpeed != 0)
			auxMotors->ElevatorClaw(eleSpeed);
		if (state < Drop)
			auxMotors->Claw(-.4);
	}

	if (l != 0 && r != 0) {
		if (CommandBase::oi->getGamePrefs() == 1)
			Drive(r, l);
		else
			Drive(l, r);
	}

}

bool SwerveScaleSame::IsFinished() {
	return finished;
}

void SwerveScaleSame::End() {
	Drive(0, 0);
	finished = true;
	timer.Stop();
}

void SwerveScaleSame::IncrementState() {
	state++;
	timer.Reset();
	timer.Start();
}

void SwerveScaleSame::Interrupted() {

}

void SwerveScaleSame::Drive(float l, float r) {
	robotDrive->driveBot(l, r);
}
