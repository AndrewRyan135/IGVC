#include <iostream>
#include <stdio.h>
#include <string.h>
#include <geometry_msgs/Twist.h>
#include "ros/ros.h"
#include "std_msgs/String.h"

#include "RoboteqDevice.h"
#include "ErrorCodes.h"
#include "Constants.h"

RoboteqDevice device;

void chatterCallback(const geometry_msgs::Twist& msg)
{
	if (msg.angular.z > 0){
		ROS_INFO_STREAM("Subscriber velocities:"<<" linear="<<msg.linear.x<<" 	angular="<<msg.angular.z);
	}
	
	cout << "I am here" << endl;
	
	float x_val = 0;
	float z_val = 0;
	int status = 0;

	
	/*int result;
	device.SetConfig(_DINA, 1, 1);
	device.SetConfig(_DINA, 2, 1);
	device.GetConfig(_DINA, 1, result);
	device.GetConfig(_DINA, 2, result);
	device.GetValue(_ANAIN, 1, result);
	device.GetValue(_ANAIN, 2, result);*/

        //Wait 10 ms before sending another command to devicerosrun not detecting motor controll
        //sleepms(10);

	int motor1_max = 300;
	int motor2_max = 305;
	int turn_max = 300;
	int motor1_cmd = 0;
	int motor2_cmd = 0;

	cout << "X: " << msg.linear.x << " Z: " << msg.angular.z << endl;

	if(msg.linear.x > 0.4){
		x_val = 1;
		z_val = 0;
	}
	else if (msg.linear.x < -0.4){
		x_val = -1;
		z_val = 0;
        }
	else {
		x_val = 0;
	}
	if(msg.angular.z > 0.4){
		z_val = 1;
		x_val = 0;
	}
	else if (msg.angular.z < -0.4){
		z_val = -1;
		x_val = 0;
        }
	else {
		z_val = 0;
	}


	//Forward/ Backward
	if (x_val != 0){
		motor1_cmd = x_val*motor1_max;
		motor2_cmd = x_val*motor2_max;
	}
	
	//Left
	if (z_val == 1){
		motor2_cmd = 0;
		motor1_cmd = z_val*turn_max;
	}

	//Right
	if (z_val == -1){
		motor1_cmd = 0;
		motor2_cmd = -z_val*turn_max;
	}

	cout << "\n\n" << endl;
	cout << motor1_cmd << endl;
	cout << motor2_cmd << endl;
	cout << "\n\n" << endl;

	

	
	cout<<"msg.linear.x : " << msg.linear.x <<endl;
	cout<<"msg.angular.z: " << msg.angular.z <<endl;
	
	//int diff = max/4;
	//int init = 0;

	//for (int tmp = 0; tmp < 4; tmp++)
	//{
		
	//	motor1_cmd = motor1_cmd/4-tmp;
	//	motor2_cmd = motor2_cmd/4-tmp;
		
		//********************************************************
		//****************Motor 1*********************************
		cout<<"- SetCommand(_GO, 1, 100)...";
		if((status = device.SetCommand(_GO, 1, motor1_cmd)) != RQ_SUCCESS)
		        cout<<"failed --> "<<status<<endl;
		else
		{
		        cout<<"succeeded."<<endl;
		        device.SetCommand(_GO, 1, motor1_cmd);
			//cout<<"succeeded."<<endl;
		        //device.SetCommand(_GO, 2, motor1_cmd);

		}

		//sleepms(10);


		//*****************************Motor 2*******************
		///******************************************************
		cout<<"- SetCommand(_GO, 2, 100)...";
		if((status = device.SetCommand(_GO, 2, motor2_cmd)) != RQ_SUCCESS)
		        cout<<"failed --> "<<status<<endl;
		else
		{
		        cout<<"succeeded."<<endl;
		        device.SetCommand(_GO, 2, motor2_cmd);

		}
		//*******************************************************
		//********************************************************
	//	sleepms(250);
	//}
        return;



}


int main(int argc, char **argv)
{
	std::string response = "";
	//RoboteqDevice device;
        int status = device.Connect("/dev/ttyACM0");

        if(status != RQ_SUCCESS)
        {
                cout<<"Error connecting to device: "<<status<<"."<<endl;
                return 0;
        }

	
        cout<<"- SetConfig(_DINA, 1)...";
        if((status = device.SetConfig(_DINA, 1, 1)) != RQ_SUCCESS)
                cout<<"failed --> "<<status<<endl;
        else
                cout<<"succeeded."<<endl;
        cout<<"- SetConfig(_DINA, 2)...";
        if((status = device.SetConfig(_DINA, 2, 1)) != RQ_SUCCESS)
                cout<<"failed --> "<<status<<endl;
        else
                cout<<"succeeded."<<endl;

        //Wait 10 ms before sending another command to device
        sleepms(10);

        int result;
        cout<<"- GetConfig(_DINA, 1)...";
        if((status = device.GetConfig(_DINA, 1, result)) != RQ_SUCCESS)
                cout<<"failed --> "<<status<<endl;
        else
                cout<<"returned --> "<<result<<endl;
        cout<<"- GetConfig(_DINA, 2)...";
        if((status = device.GetConfig(_DINA, 2, result)) != RQ_SUCCESS)
                cout<<"failed --> "<<status<<endl;
        else
                cout<<"returned --> "<<result<<endl;

        //Wait 10 ms before sending another command to device
        sleepms(10);

	cout<<"- GetValue(_ANAIN, 1)...";
        if((status = device.GetValue(_ANAIN, 1, result)) != RQ_SUCCESS)
                cout<<"failed --> "<<status<<endl;
        else
                cout<<"returned --> "<<result<<endl;
        cout<<"- GetValue(_ANAIN, 2)...";
        if((status = device.GetValue(_ANAIN, 2, result)) != RQ_SUCCESS)
                cout<<"failed --> "<<status<<endl;
        else
                cout<<"returned --> "<<result<<endl;

	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("cmd_vel", 1000, chatterCallback);

	ros::spin();
	device.Disconnect();
	return 0;
}
