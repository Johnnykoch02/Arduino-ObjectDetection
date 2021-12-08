This class was designed to be re-usable for an ObjectDetection / Follow-Me Robot.

HOW TO USE:
    For Proper functionality, ensure your robot has at-least two Motion IR Sensors, and an
     ultrasonic distance sensor, recommended in the front of your design.

   	ObjectDetection(int trig, int echo, int ir1, int ir2, int servopin);

        - These are the following pins you need to hook up to corresponding pins on the arduino.
    
    int updateObjDetection(float dt)

        - This function doesn't currently require a dt variable. 
        - The int returned from this function corresponds to the drive direction required to be passed

Future Updates:

    - Fix Servo, by implementing a custom Servo Library *NOTE the current servo library should work, so you 
     can try to get it to work by uncommenting it. It is meant to control a servo neck which harbor the distance sensor and two motion IR sensors.
