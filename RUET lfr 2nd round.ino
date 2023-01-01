#include <QTRSensors.h>

#define Kp 1.5           //best kp =2 kd = 2.84 Ki 0.00000000001 at base speed 100
#define Ki 0.0000000001  //kp 2 kd 10 at base speed 200
#define Kd 15

#define Kpw 0.5           //best kp =1.485 kd = 2.84 Ki 0.00000000001 at base speed 100
#define Kiw 0.0000000001  //kp .08 kd .3 at base speed 200
#define Kdw 5

#define Kps 2             // kp =0.2 kd = 0.6 Ki 0.00000000001 at base speed 100
#define Kis 0.0000000001  //kp .08 kd .3 at base speed 200
#define Kds 5

#define trigPin_left A0
#define echoPin_left A1

#define trigPin_right A2
#define echoPin_right A3

// defines variables
long duration_left;  // variable for the duration of sound wave travel
int distance_left;   // variable for the distance measurement
long duration_right;
int distance_right;

int MaxSpeed = 200;        // max speed of the robot
int BaseSpeed = 100;        // this is the speed at which the motors should spin when the robot is perfectly on the line
int MaxSpeed_white = 150;  // max speed of the robot
int BaseSpeed_white = 70;

int MaxSpeed_Sonar = 70;
int BaseSpeed_Sonar = 40;

int lastError = 0;

int RL = 600;
int threshold = 400;
int threshold_w = 400;
int turnSpeed = 60;
int turnSpeed_white = 60;

char flag = 's';

//define motor pin

#define rightMotor1 6
#define rightMotor2 7
#define rightMotorPWM 3


#define leftMotor1 4
#define leftMotor2 5
#define leftMotorPWM 2

//buzzer
int buzzer = 27;


QTRSensors qtr;
const uint8_t SensorCount = 10;
uint16_t sensorValues[SensorCount];

void setup() {

  pinMode(buzzer, OUTPUT);

  digitalWrite(buzzer, HIGH);

  delay(2000);
  Serial.begin(9600);

  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){ 31, 33, 35, 37, 39, 41, 43, 45, 47, 51 }, SensorCount);
  qtr.setEmitterPin(53);  //LEDON PIN

  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);

  pinMode(trigPin_left, OUTPUT);  // Sets the trigPin as an OUTPUT
  pinMode(echoPin_left, INPUT);   // Sets the echoPin as an INPUT
  pinMode(trigPin_right, OUTPUT);
  pinMode(echoPin_right, INPUT);

  
  for (int i = 0; i < 30; i++)  // calibrate for sometime by sliding the sensors across the line, or you may use auto-calibration instead
  {
    //comment this part out for automatic calibration
    if (i < 10 || i >= 20)  // turn to the left and right to expose the sensors to the brightest and darkest readings that may be encountered
    {
      RUN(1, 55, 1);  // ( left motor , speed , high or low )
      RUN(2, 55, 1);  // ( right motor , speed , high or low )
    } else {
      RUN(1, 55, 0);  // ( left motor , speed , high or low )
      RUN(2, 55, 0);  // ( right motor , speed , high or low )
    }
    qtr.calibrate();
    delay(20);
  }
  
  stop();
  delay(1000);
}


void loop() {
  READ_black();
}



void RUN(int motor, int speed, int direction) {

  boolean inPin1 = HIGH;
  boolean inPin2 = LOW;

  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
    //1=FORWARD
  }
  if (direction == 0) {
    inPin1 = LOW;
    inPin2 = HIGH;
    //0=BACKWARD
  }

  if (motor == 1) {
    digitalWrite(rightMotor1, inPin1);
    digitalWrite(rightMotor2, inPin2);
    analogWrite(rightMotorPWM, speed);
    // 2=B
  }

  if (motor == 2) {
    digitalWrite(leftMotor1, inPin1);
    digitalWrite(leftMotor2, inPin2);
    analogWrite(leftMotorPWM, speed);
    // 1=A
  }
}

void go_right() {
  RUN(1, turnSpeed+20, 1);  // ( left motor , speed , high or low )
  RUN(2, turnSpeed, 0);  // ( right motor , speed , high or low )
}
void go_left() {
  RUN(1, turnSpeed, 0);  // ( left motor , speed , high or low )
  RUN(2, turnSpeed+20, 1);  // ( right motor , speed , high or low )
}



void force_right() {
  RUN(1, turnSpeed, 0);  // ( left motor , speed , high or low )
  RUN(2, turnSpeed, 0);  // ( right motor , speed , high or low )
  delay(200);
  stop();

  digitalWrite(buzzer, LOW);
  delay(10);
  digitalWrite(buzzer, HIGH);

  go_right();
  reading();
  while (sensorValues[7] < threshold && sensorValues[8] < threshold) reading();
}

void force_left() {
  RUN(1, turnSpeed, 0);  // ( left motor , speed , high or low )
  RUN(2, turnSpeed, 0);  // ( right motor , speed , high or low )
  delay(200);
  stop();

  digitalWrite(buzzer, LOW);
  delay(10);
  digitalWrite(buzzer, HIGH);

  go_left();
  reading();
  while (sensorValues[1] < threshold && sensorValues[2] < threshold) reading();
}


void turn_30_right() {
  if (1) {
    RUN(1, turnSpeed, 1);  // ( left motor , speed , high or low )
    RUN(2, turnSpeed, 1);  // ( right motor , speed , high or low )
    delay(50);
    RUN(1, turnSpeed, 0);  // ( left motor , speed , high or low )
    RUN(2, turnSpeed, 0);  // ( right motor , speed , high or low )
    delay(30);
    stop();

    digitalWrite(buzzer, LOW);

    RUN(1, turnSpeed + 20, 1);  // ( left motor , speed , high or low )
    RUN(2, turnSpeed, 0);       // ( right motor , speed , high or low )
    delay(200);

    reading();
    while (sensorValues[6] < threshold && sensorValues[7] < threshold) reading();

    RUN(1, turnSpeed, 0);       // ( left motor , speed , high or low )
    RUN(2, turnSpeed + 20, 1);  // ( right motor , speed , high or low )
    delay(80);

    RUN(1, turnSpeed + 30, 1);  // ( left motor , speed , high or low )
    RUN(2, turnSpeed + 30, 1);  // ( right motor , speed , high or low )
    delay(150);

    digitalWrite(buzzer, HIGH);
  }
}
void turn_30_left() {
  if (1) {
    RUN(1, turnSpeed, 1);  // ( left motor , speed , high or low )
    RUN(2, turnSpeed, 1);  // ( right motor , speed , high or low )
    delay(50);
    RUN(1, turnSpeed, 0);  // ( left motor , speed , high or low )
    RUN(2, turnSpeed, 0);  // ( right motor , speed , high or low )
    delay(30);
    stop();

    digitalWrite(buzzer, LOW);


    RUN(1, turnSpeed, 0);       // ( left motor , speed , high or low )
    RUN(2, turnSpeed + 20, 1);  // ( right motor , speed , high or low )
    delay(200);

    reading();
    while (sensorValues[2] < threshold && sensorValues[3] < threshold) reading();

    RUN(1, turnSpeed + 20, 1;  // ( left motor , speed , high or low )
    RUN(2, turnSpeed, 0);       // ( right motor , speed , high or low )
    delay(80);

    RUN(1, turnSpeed + 30, 1);  // ( left motor , speed , high or low )
    RUN(2, turnSpeed + 30, 1);  // ( right motor , speed , high or low )
    delay(150);



    digitalWrite(buzzer, HIGH);
  }
}


void stop() {
  analogWrite(leftMotorPWM, 0);
  analogWrite(rightMotorPWM, 0);
}