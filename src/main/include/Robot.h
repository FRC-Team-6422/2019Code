#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include "AHRS.h"
#include <ctre/Phoenix.h>
#include <frc/WPIlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include <adi/ADIS16448_IMU.h>
#include <liftTargetingTable.h>
#include <frc/Encoder.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Compressor.h>

const float kUpdatePeriod = 0.005;
const float kValueToCM = 0.144;

static bool reverseControl __attribute__((unused)) = false;
static double visionPwr __attribute__((unused)) = 0;

	/*
	* Button Key
	* Each dimension of this array represents a controller, and the elements represent a button. If an element of the array is true, that button was pressed and has not
	* yet been lifted up
	*
	* 0: A
	* 1: B
	* 2: X
	* 3: Y
	* 4: L1
	* 5: R1
	*/
static bool buttonsPressed [2][6] = {
	{false, false, false, false, false, false}, 
	{false, false, false, false, false, false}
};

static bool joystickMode = true;
static bool mecanumDrive = true;

static double prevAnlge = 0.0;
static double currentAnlge = 0.0;
static int targetAngle = -1;

static double frontCameraOutput = 0.0;
static double rearCameraOutput = 0.0;

static int alignLoopCount = 0;
static bool networkUpdating = false;
static std::string alignState = "none";

static bool autoCompleted = false;
static int startPosition = 0;
static double desAutoDelay = 0;
static double smartDashTimerAuto = 0;
static double autoDelayTimer = 0;
static float leftDistance = 0;
static float rightDistance = 0;
static int stepCount = 0;
static float accelX = 0.0;
static float accelY = 0.0;
static float lastAccelX = 0.0;
static float lastAccelY = 0.0;
static bool colliding = false;
static double frontWallDistance = 0.0;
static double rearWallDistance = 0.0;
static double liftHeightLow = 0.0;
static double liftHeightHigh = 0.0;
static double liftLowSpeed = 0.5;
static double liftHighSpeed = 0.5;
static bool holdingHatch = false;

static double prevTime = 0.0;
static double bumperHoldTime = 0.0;

static int testMotor = -1;
static double motorPower = 0.0;

static std::string desLiftPosition = "low";

// static std::string sensorBoardType = "navx";
static std::string sensorBoardType = "analogDev";

static bool autoMode = true;

static std::vector<WPI_TalonSRX> testTalons;

class Robot: public frc::TimedRobot {

  public: 
	Robot();
    virtual ~Robot(){}

		// FRC built in functions - never delete thsese
	  void DisabledInit()  override;
	  void DisabledPeriodic()  override {}
	  void RobotInit()  override;
	  void RobotPeriodic()  override {}
	  void AutonomousInit() override;
	  void AutonomousPeriodic() override;
	  void TeleopInit() override;
	  void TeleopPeriodic() override;
	  void TestInit() override;
  	void TestPeriodic() override;

	void InitEncoder(frc::Encoder &enc);
	void CameraLightOn();
	void CameraLightOff();

  private:
	static void VisionThread();
	void MotorSpeedLeft(const float val);
	void MotorSpeedRight(const float val);
	int kUltrasonicPort = 0;

	double maxpwr[6];
	int waitper = 0;

		// Here, the first 2 arguments are the port numbers for the two digital inputs and the bool tells it wether to reverse
	frc::Encoder liftEncoderHigh { 0, 1, true, Encoder::k4X };
	frc::Encoder leftEncoder { 2, 3, false, Encoder::k4X };
	frc::Encoder rightEncoder { 4, 5, false, Encoder::k4X };
	frc::Encoder grabberEncoder {6, 7, false, Encoder::k4X};

	frc::DoubleSolenoid grabber { 0, 0, 1 };

	float winchSpeed = 0.0;
	float rampSpeed = 0.0;

	frc::SendableChooser<std::string> chooser;

	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;
	frc::XboxController xboxcontroller0{0};
	frc::XboxController xboxcontroller1{1};
	frc::XboxController xboxcontroller2{2};
	
	frc::PowerDistributionPanel m_pdp;
	WPI_TalonSRX FrontLeft;
	WPI_TalonSRX BackLeft;
	WPI_TalonSRX FrontRight;
	WPI_TalonSRX BackRight;
	WPI_TalonSRX liftLow;
	WPI_TalonSRX liftHigh;
	WPI_TalonSRX intake;
	WPI_TalonSRX grabberWinch;

	WPI_TalonSRX testTalon0;
	WPI_TalonSRX testTalon1;
	WPI_TalonSRX testTalon2;
	WPI_TalonSRX testTalon3;
	WPI_TalonSRX testTalon4;
	WPI_TalonSRX testTalon5;
	WPI_TalonSRX testTalon6;
	WPI_TalonSRX testTalon7;
	WPI_TalonSRX testTalon8;
	WPI_TalonSRX testTalon9;

	// Driver station cameras get initialized here
	cs::UsbCamera camera0;
	cs::UsbCamera camera1;

	frc::Compressor *compressor = new frc::Compressor(0);

	AnalogInput *frontUltraSonic;
	AnalogInput *rearUltraSonic;
	
	AnalogInput *boxPotentiometer;

	AHRS *navx;
	frc::ADIS16448_IMU analogDev{
		frc::ADIS16448_IMU::kZ,
		frc::ADIS16448_IMU::kComplementary,
		frc::SPI::kMXP
	};

	float angle;

	liftTargetingTable liftLowTargets {"low"};
	liftTargetingTable liftHighTargets {"high"};
};

#endif /* SRC_ROBOT_H_ */