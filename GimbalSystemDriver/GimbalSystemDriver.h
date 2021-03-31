//Team 305, Haptic Feedback Controller
#include "Adafruit_INA219.h"
#include <Wire.h>

#ifndef GIMBAL_SYS_DRIVE
#define GIMBAL_SYS_DRIVE

//Default Pin Assignments
#define DEFAULT_MENA 7
#define DEFAULT_MIN1 8
#define DEFAULT_MIN2 9
#define DEFAULT_ENC1 13
#define DEFAULT_ENC2 14

//Default System parameters
#define DEFAULT_MOTOR_THRESH 10 //In Percent
#define DEFAULT_STALL_THRESH 25 //In Percent
#define DEFAULT_REFRESH_PERIOD 0.01 //100Hz
#define DEFUALT_PWM_RES 8

//Current Sensor Parameters
#define DEFAULT_INA219_ADR 1
#define 

#define DEFAULT_IIR_A 0.8

class GimbalSystemDriver{
  public:
    //utility
    GimbalSystemDriver(void);
    int setMotorPins(int _ena, int _in1, int _in2);
    int setEncoderPins(int _enc1, int _enc2);
    int configureINA219(void);
    int configurePWM(int _resPWM);
  
    //Parameterization
    int setMotorKs(float kv);
    //int setGimbalParams();
    int setCCPID(float kp, float ki, float kd, float kc); //Set current/torque control PID parameters
    int setSCPID(float kp, float ki, float kd, float kc); //Set speed control PID parameters
    int setSamplePeriod(float T);
    
    //Action!
    int driveSpeed(const int speed);
    int driveCurrent(const int cur);
    //int driveTorque(const int torque);
    int findZero(void);
   
    //Read Data
    float readSpeed(void);
    float readCurrent_raw(void);
    float readCurrent_filter1(void);
    float readCurrent_filter2(void);
    float readTorque(void);
    
    //Pins
    int ena, in1, in2; //Motor Pins
    int enc1, enc2; //Encoder Pins
    //System Parameters
    float refresh_period; //In seconds
    int resPWM; //PWM resolution in bits
    float motor_thresh;
  
    //Motor Parameters
    float stall_thresh;
    float kv;
    float km;
    
    //INA_219 Output Data
    float shuntvoltage;
    float busvoltage;
    float current_mA;
    float loadvoltage;
    float power_mW;

    //Filter Data IIR Filter
    float a1, a2, a3, a4;
    int f1_stages, f2_stages;
  
    //PID Controller Setpoints
    float desspeed; float descur; float destorque;
    //PID Controller Constants
    float kp_speed; float kp_cur; //Proportional constant
    float kd_speed; float kd_cur; //Derivative constant
    float ki_speed; float ki_cur; //Integral constant
    float kc_speed; float kc_cur; //Overall Controller Gain
    //PID Error Terms
    float nowerr_c; float nowerr_s;
    float lasterr_c; float lasterr_s;
    float deriv_c; float deriv_s;
    float integ_c; float integ_s;
};
