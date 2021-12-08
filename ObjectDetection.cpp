#include "Arduino.h"
#include "ObjectDetection.h"	

int state_current = -1;

ObjectDetection::ObjectDetection(int trigPin, int echoPin, int motion1, int motion2, int servopin) {
	this->trigPin = trigPin; // Trig Pin
	this->echoPin = echoPin; // Echo Pin
	this->motion1 = motion1; // Motion 1
	this->motion2 = motion2; // Motion 2
	this->currentAngle = 90; // Current Angle is at 90
	this->currentMotion = 0; // Our motion is set to NA
	set_distance_sensor();
	// neck.attach(servopin);
	// neck.writeMicroseconds(angleToMic(this->currentAngle));
}


int ObjectDetection::updateObjDetection(float dt) {
	/**
	 * @brief will call our Distance Sensor to update the distance value
	 */
	update_distance();
	/*NON-SERVO MODEL*/
	if (right() && left())
	{
		this->currentMotion = 0;
		//Sets drive to foward or backward.
		if (this->distance - 15.0  > 2.0) { state_current = 0; } // Object is over our target
		else if (this->distance - 15.0 < -2.0) { state_current = 5;	} // Object is under our target
		else { state_current = -1; } // Object is within reasonable bound of our target
	}
	else if (right()) /*FIX*/
	{
		this->currentMotion = 1;
	}

	else if(left())
	{
		this->currentMotion = -1;
	}

	if (this->currentMotion == 1)
	{
		state_current = 2;
	}
	else if(this->currentMotion == -1)
	{
		state_current = 4 ;
	}


	/*NON-SERVO MODEL*/

	/**
	 * @brief The code below is commented out due to a hardware issue from the servo motor. 
	 *  Feel free to try and uncomment this code out and 
	 */
	/* NEEDS A SERVO UPDATE*/	


	// Serial.print("Current Angle: ");
	// Serial.println(this->currentAngle);

	/**
	 * @brief Our goal is to move the target object into our direct frame.
	 *  Our first goal is to make sure the object is in our Direct view.
	 * right and left.
	 */

	// if(right() && left()) 
	// {
	// 	this->currentMotion = 0;
	// 	/* Our object is directly in front of us. */
	// 	/* We need to make sure our neck angle is at 90 */

	// 	/* Case angle is at 90 */
	// 	if (this->currentAngle == 90)
	// 	{//Sets drive to foward or backward.
	// 	if (this->distance - 15.0  > 2.0) { state_current = 0; } // Object is over our target
	// 	else if (this->distance - 15.0 < -2.0) { state_current = 5;	} // Object is under our target
	// 	else { state_current = -1; } // Object is within reasonable bound of our target
	// 	}
	// 	/* Case angle is less than 90 */
	// 	else if (this->currentAngle < 90) 
	// 	{
	// 		state_current = -2;
	// 		this->currentAngle+=15;
	// 		// neck.writeMicroseconds(angleToMic(this->currentAngle));
	// 	}
	// 	else if(this->currentAngle > 90)
	// 	{
	// 		state_current = -3;
	// 		this->currentAngle-=15;
	// 		// neck.writeMicroseconds(angleToMic(this->currentAngle));
	// 	}

	// }

	// else if (right()) /*FIX*/
	// {
	// 	this->currentMotion = 1;
	// }

	// else if(left())
	// {
	// 	this->currentMotion = -1;
	// }


	// if (this->currentMotion == -1) // going Left:
	// {
	// 	if(this->currentAngle>= 15) // We can still turn our servo
	// 	{
	// 		this->currentAngle-=15;
	// 		// neck.writeMicroseconds(angleToMic(this->currentAngle));
	// 		state_current = -1;
	// 	}	
	// 	else // We can no longer turn the servo
	// 	{
	// 		state_current = 4;
	// 	}
	// }

	
	// else if (this->currentMotion == 1) // going right:
	// {
	// 	if(this->currentAngle<= 165) // We can still turn our servo
	// 	{
	// 		this->currentAngle+=15;
	// 		// neck.writeMicroseconds(angleToMic(this->currentAngle));
	// 		state_current = -1;
	// 	}	
	// 	else // We can no longer turn the servo
	// 	{
	// 		state_current = 1;
	// 	}
	// }
	

/* NEEDS A SERVO UPDATE*/

	return state_current;
}

void ObjectDetection::set_distance_sensor() {
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
}
void ObjectDetection::update_distance() {
	// To start, send a low signal to the Sensor
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	// Then we want to send power to the sensor for ten microseconds, causing a sound wave to generate
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	// Then, we want to change the signal back to low on the sensor
	digitalWrite(trigPin, LOW);
	// the Pulse in from the echoPin will give us the length in time it took for the signal to bounce back to the Sensor
	long duration = pulseIn(echoPin, HIGH);
	this->distance = (duration / 2) * 0.0343;
}

float ObjectDetection::get_distance() { return this->distance; }

bool ObjectDetection::left() {
	return (digitalRead(motion2) == 0);
}
bool ObjectDetection::right() {
	return (digitalRead(motion1) == 0);
}

int ObjectDetection::angleToMic(int angle) {
	return (angle *21) +544;
}

int ObjectDetection::get_servo_angle(){ return this->currentAngle;}

