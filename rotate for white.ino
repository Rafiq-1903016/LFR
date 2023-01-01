//------------------------------------------------------------------------------------------//
void force_right_white() {
  RUN(1, turnSpeed, 0);  // ( left motor , speed , high or low )
  RUN(2, turnSpeed, 0);  // ( right motor , speed , high or low )
  delay(100);
  stop();

  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);

  go_right();
  reading();
  while (sensorValues[8] > threshold && sensorValues[9] > threshold) reading();
}

//------------------------------------------------------------------------------------------//
void force_left_white() {
  RUN(1, turnSpeed, 0);  // ( left motor , speed , high or low )
  RUN(2, turnSpeed, 0);  // ( right motor , speed , high or low )
  delay(100);
  stop();

  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);

  go_left();
  reading();
  while (sensorValues[0] > threshold && sensorValues[1] > threshold) reading();
}