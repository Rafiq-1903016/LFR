void PID_sonar() {
  reading_sonar();
  float sonar_Position = ((distance_left * 0) + (distance_right * 1000)) / (distance_left + distance_right);
  int error = 500 - sonar_Position;

  float P = error;
  float I = I + error;
  float D = error - lastError;
  lastError = error;

  int motorSpeed = Kps * error + Kis * I + Kds * D;


  int rightMotorSpeed = BaseSpeed_Sonar + motorSpeed;
  int leftMotorSpeed = BaseSpeed_Sonar - motorSpeed;

  if (rightMotorSpeed > MaxSpeed_Sonar) rightMotorSpeed = MaxSpeed_Sonar;  // prevent the motor from going beyond max speed
  if (leftMotorSpeed > MaxSpeed_Sonar) leftMotorSpeed = MaxSpeed_Sonar;    // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0) rightMotorSpeed = 0;
  if (leftMotorSpeed < 0) leftMotorSpeed = 0;

  RUN(1, rightMotorSpeed, 1);  //forward
  RUN(2, leftMotorSpeed, 1);   //forward
  Serial.println("sonar");
}