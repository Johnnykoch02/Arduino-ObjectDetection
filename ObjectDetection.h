#ifndef ObjectDetection_h
#define ObjectDetection_h

#include <Servo.h>

class ObjectDetection {
private:

	// VARIABLES

	int trigPin;
	int echoPin;
	float distance;
	int motion1;
	int motion2;
	int currentMotion; // 0 is NA, -1 is Left, 1 is Right.
	int currentAngle;
	int state_current;
	// Servo neck;

	// METHODS

	void update_distance();
	void set_distance_sensor();
	int angleToMic(int angle);
	bool left();
	bool right();

public:
	ObjectDetection(int trig, int echo, int ir1, int ir2, int servopin); // Needs servo update
	int updateObjDetection(float dt);
	float get_distance();
	int get_servo_angle();

};

#endif
