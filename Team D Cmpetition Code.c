#pragma config(Sensor, dgtl1,  flywheelEnc,    sensorQuadEncoder)
#pragma config(Motor,  port1,           driveBackRight, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           driveFrontLeft, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           flywheelLeftTop, tmotorVex393_MC29, openLoop, reversed, encoderPort, dgtl1)
#pragma config(Motor,  port4,           flywheelLeftBot, tmotorVex393_MC29, openLoop, encoderPort, dgtl1)
#pragma config(Motor,  port5,           conveyor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           flywheelRightTop, tmotorVex393_MC29, openLoop, encoderPort, dgtl1)
#pragma config(Motor,  port7,           flywheelRightBot, tmotorVex393_MC29, openLoop, reversed, encoderPort, dgtl1)
#pragma config(Motor,  port8,           conveyor2,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           driveFrontRight, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          driveBackLeft, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "PIDController.h" //credit to JMMcKinneyWPI on Github, Jason McKinney for his PID Control Loop

PID flywheel; //The pid struct to be used and monitored


/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

void driveFlywheel(int output)
{
	motor[flywheelLeftTop] = output;
	motor[flywheelLeftBot] = output;
	motor[flywheelRightBot] = output;
	motor[flywheelRightTop] = output;
}
	float rpmAvg = 0;
	float dT; //delta T in seconds
	float out ;
	float sp = 2040;
	bool set = false;
	int firstShot = 0;
task autonomous()
	{
		clearTimer(T1);
		pidInit(flywheel, 0.01, 0.03, 0.001, 3, 50);//p, i, d, epsilon, slew
		unsigned long lastTime = nPgmTime;
		resetMotorEncoder(flywheelLeftBot);
		float rpm, lastRpm1, lastRpm2, lastRpm3, lastRpm4;

		int counter = 0;

			bool btn7DPressed;
		while (true)
		{

	if(1==1)
		{
			dT = (float)(nPgmTime - lastTime)/1000;
			lastTime = nPgmTime;

			if(dT != 0)
			{
				rpm = 60.00*25*(((float)getMotorEncoder(flywheelLeftBot))/dT)/360;
			}
			else
			{
				rpm = 0;
			}
			resetMotorEncoder(flywheelLeftBot);
			lastRpm4 = lastRpm3;
			lastRpm3 = lastRpm2;
			lastRpm2 = lastRpm1;
			lastRpm1 = rpm;

			rpmAvg = (rpm + lastRpm1 + lastRpm2 + lastRpm3 + lastRpm4) / 5;

			if(flywheel.errorSum > 18000)
			{
				flywheel.errorSum = 18000;
			}

			if(rpmAvg >= sp && !set)
			{
				set = true;
			}
			if( rpm <= sp - 700)
			{
				set = false;
			}
			out = pidExecute(flywheel, sp-rpmAvg);

			if(vexRT(Btn7U) == 1)
			{
				btn7DPressed = false;
				pidReset(flywheel);
				out = 0;
			}

			if(out < 1)
			{
				out = 1;
			}
			driveFlywheel(out);
		}
	//	debugStrea
		if(time1[T1] >= 7250 && time1[T1] <= 9000)
		{
			motor[conveyor] = 127;
			motor[conveyor2] = 127;
		}
	}
	/*dank memes
*/
/*
	motor[flywheelLeftTop] = 63;
	motor[flywheelLeftBot] = 63;
	motor[flywheelRightTop] = 63;
	motor[flywheelRightBot] = 63;
	wait1Msec(2500);
	motor[conveyor] = 127;
	wait1Msec(1000);
	motor[conveyor] = 0;
	wait1Msec(1500);
	motor[conveyor] = 127;
	wait1Msec(1000);
	motor[conveyor] = 0;
	wait1Msec(1000);
	motor[flywheelLeftTop] = 65;
	motor[flywheelLeftBot] = 65;
	motor[flywheelRightTop] = 65;
	motor[flywheelRightBot] = 65;
	motor[conveyor] = 127;
	wait1Msec(1000);
	motor[conveyor] = 0;
	wait1Msec(1000);
	motor[conveyor] = 127;
	wait1Msec(1000);
	motor[conveyor] = 0;
*/

	//PROGRAMMING SKILLS
/*	while(1==1)
	{
		motor[flywheelLeftTop] = 63;
		motor[flywheelLeftBot] = 63;
		motor[flywheelRightTop] = 63;
		motor[flywheelRightBot] = 63;
		motor[conveyor] = 127;
	}*/






}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{

	pidReset(flywheel);
	debugStreamClear;
	float sp = 2050;
	// User control code here, inside the loop
	int currentFlywheelSpeed;

//	pidInit(flywheel, 0.10, 0.01, 0.00001, 3, 50);
pidInit(flywheel, 0.01, 0.03, 0.001, 3, 50);
		unsigned long lastTime = nPgmTime;
		resetMotorEncoder(flywheelLeftBot);
		float rpm, lastRpm1, lastRpm2, lastRpm3, lastRpm4;

		int counter = 0;

			bool btn7DPressed;
		while (true)
		{
		if(vexRT[btn7D] == 1)
		{
			 btn7DPressed = true;
		}

 		if(btn7DPressed == true)
		{
			dT = (float)(nPgmTime - lastTime)/1000;
			lastTime = nPgmTime;

			if(dT != 0)
			{
				rpm = 60.00*25*(((float)getMotorEncoder(flywheelLeftBot))/dT)/360;
			}
			else
			{
				rpm = 0;
			}
			resetMotorEncoder(flywheelLeftBot);
			lastRpm4 = lastRpm3;
			lastRpm3 = lastRpm2;
			lastRpm2 = lastRpm1;
			lastRpm1 = rpm;

			rpmAvg = (rpm + lastRpm1 + lastRpm2 + lastRpm3 + lastRpm4) / 5;

			if(flywheel.errorSum > 18000)
			{
				flywheel.errorSum = 18000;
			}

			if(rpmAvg >= sp && !set)
			{
				set = true;
			}
			if( rpm <= sp - 700)
			{
				set = false;
			}
			out = pidExecute(flywheel, sp-rpmAvg);

			if(vexRT(Btn7U) == 1)
			{
				btn7DPressed = false;
				pidReset(flywheel);
				out = 0;
			}

			if(out < 1)
			{
				out = 1;
			}
			driveFlywheel(out);
		}


			/*
			//motor[Motor1] = 127;
			motor[flywheelLeftTop] = 68;
			motor[flywheelLeftBot] = 68;
			motor[flywheelRightTop] = 68;
			motor[flywheelRightBot] = 68;
			currentFlywheelSpeed = 68;
		}
		if(vexRT[Btn7L] == 1)
		{
			currentFlywheelSpeed -= 2;
			motor[flywheelLeftTop] = currentFlywheelSpeed;
			motor[flywheelLeftBot] = currentFlywheelSpeed;
			motor[flywheelRightTop] = currentFlywheelSpeed;
			motor[flywheelRightBot] = currentFlywheelSpeed;
			wait1Msec(400);
		}
		if(vexRT[Btn7R] == 1)
		{
			currentFlywheelSpeed += 2;
			motor[flywheelLeftTop] = currentFlywheelSpeed;
			motor[flywheelLeftBot] = currentFlywheelSpeed;
			motor[flywheelRightTop] = currentFlywheelSpeed;
			motor[flywheelRightBot] = currentFlywheelSpeed;
			wait1Msec(400);
		}



		if(vexRT[Btn7U] == 1)
		{
			//		motor[Motor1] = 0;
			motor[flywheelLeftTop] = 0;
			motor[flywheelLeftBot] = 0;
			motor[flywheelRightTop] = 0;
			motor[flywheelRightBot] = 0;
		}


		if(vexRT[Btn8L] == 1)
		{

		motor[flywheelLeftTop] = 48;
			motor[flywheelLeftBot] = 48;
			motor[flywheelRightTop] = 48;
			motor[flywheelRightBot] = 48;
			currentFlywheelSpeed = 48;

		}*/

		if(vexRT[Btn8D] == 1)
		{
			motor[conveyor] = 127;
			motor[conveyor2] = 127;
		}

		if(vexRT[Btn8R] == 1)
		{
			motor[conveyor] = 0;
			motor[conveyor2] = 0;

		}

		if(vexRT[Btn8U] == 1)
		{
			motor[conveyor] = -127;
			motor[conveyor2] = -127;

		}

		/*	motor[driveFrontRight] = vexRT[Ch1] + vexRT[Ch4];
		motor[driveFrontLeft] = vexRT[Ch1] - vexRT[Ch4];
		motor[driveBackRight] = vexRT[Ch1] - vexRT[Ch4];
		motor[driveBackLeft] = vexRT[Ch1] + vexRT[Ch4];*/
		motor[driveFrontRight] = vexRT[Ch2];
		motor[driveBackRight] = vexRT[Ch2];
		motor[driveFrontLeft] = vexRT[Ch3];
		motor[driveBackLeft] = vexRT[Ch3];

		while(vexRT(Btn5U)) //Left strafe
		{
			motor[driveFrontRight] = 127;
			motor[driveBackRight] = -127;
			motor[driveFrontLeft] = -127;
			motor[driveBackLeft] = 127;
		}
		while(vexRT(Btn6U))//RIGHT STRAFE
		{
			motor[driveFrontRight] = -127;
			motor[driveBackRight] = 127;
			motor[driveFrontLeft] = 127;
			motor[driveBackLeft] = -127;
		}
		/*
		if(vexRT[Ch2] > 2)
		{
		motor[driveFrontRight] = 127;
		motor[driveFrontLeft] = -127;
		motor[driveBackRight] = 127;
		motor[driveBackLeft] = -127;
		}

		if(vexRT[Ch2] < -2)
		{
		motor[driveFrontRight] = -127;
		motor[driveFrontLeft] = 127;
		motor[driveBackRight] = -127;
		motor[driveBackLeft] = 127;
		}
		*/



		writeDebugStreamLine("%f", rpm);
		wait1Msec(20);


	}
}
