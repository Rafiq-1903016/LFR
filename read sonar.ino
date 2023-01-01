void READ_sonar() {
  while (1) {
    reading();
    reading_sonar();
    if (sensorValues[0] > threshold || sensorValues[1] > threshold || sensorValues[2] > threshold || sensorValues[3] > threshold || sensorValues[4] > threshold || sensorValues[5] > threshold || sensorValues[6] > threshold || sensorValues[7] > threshold || sensorValues[8] > threshold || sensorValues[9] > threshold) break;
    else PID_sonar();
  }
  READ_black();
  delay(500);
}