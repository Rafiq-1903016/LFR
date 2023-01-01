void READ_white() {
  while (1) {
    reading();
    int L = analogRead(A4);
    int R = analogRead(A5);
    //***************** loop break for black line ***************
    if ((sensorValues[0] < threshold_w && sensorValues[1] < threshold_w) && (sensorValues[9] < threshold_w && sensorValues[8] < threshold_w) && (sensorValues[2] > threshold_w || sensorValues[3] > threshold_w || sensorValues[4] > threshold_w || sensorValues[5] > threshold_w || sensorValues[6] > threshold_w || sensorValues[7] > threshold_w)) {

      RUN(1, turnSpeed, 0);  // ( left motor , speed , high or low )
      RUN(2, turnSpeed, 0);  // ( right motor , speed , high or low )
      delay(50);

      stop();
      delay(500);
      reading();
      if (sensorValues[3] > threshold_w && sensorValues[4] > threshold_w && sensorValues[5] > threshold_w && sensorValues[6] > threshold_w) {

        //go left for shortest way

        digitalWrite(buzzer, LOW);
        delay(100);
        digitalWrite(buzzer, HIGH);

        RUN(1, 60, 0);  // ( left motor , speed , high or low )
        RUN(2, 60, 1);  // ( right motor , speed , high or low )
        while (sensorValues[4] > threshold_w && sensorValues[5] > threshold_w) reading();
        RUN(1, 60, 1);  // ( left motor , speed , high or low )
        RUN(2, 60, 0);  // ( right motor , speed , high or low )
        delay(25);
      } else break;

    }
    //***************** when all in black ***********************
    else if (sensorValues[0] > threshold_w && sensorValues[1] > threshold_w && sensorValues[2] > threshold_w && sensorValues[3] > threshold_w && sensorValues[4] > threshold_w && sensorValues[5] > threshold_w && sensorValues[6] > threshold_w && sensorValues[7] > threshold_w && sensorValues[8] > threshold_w && sensorValues[9] > threshold_w) {
      //Serial.println("straight");
      RUN(1, 60, 1);  // ( left motor , speed , high or low )
      RUN(2, 60, 1);  // ( right motor , speed , high or low )
      delay(50);

      if (flag != 's') {
        RUN(1, 60, 0);  // ( left motor , speed , high or low )
        RUN(2, 60, 0);  // ( right motor , speed , high or low )
        delay(100);
        stop();
        delay(100);

        if (flag == 'r') {

          RUN(1, 60, 1);  // ( left motor , speed , high or low )
          RUN(2, 60, 0);  // ( right motor , speed , high or low )
          while (sensorValues[4] > threshold_w && sensorValues[5] > threshold_w) reading();
          RUN(1, 60, 0);  // ( left motor , speed , high or low )
          RUN(2, 60, 1);  // ( right motor , speed , high or low )
          delay(30);
        }

        else if (flag == 'l') {
          RUN(1, 60, 0);  // ( left motor , speed , high or low )
          RUN(2, 60, 1);  // ( right motor , speed , high or low )
          while (sensorValues[4] > threshold_w && sensorValues[5] > threshold_w) reading();
          RUN(1, 60, 1);  // ( left motor , speed , high or low )
          RUN(2, 60, 0);  // ( right motor , speed , high or low )
          delay(30);
        }
        flag = 's';
      }
    }

    //*************** 90 degree turn ***********************
    else if (sensorValues[0] < threshold_w && sensorValues[9] > threshold_w) {
      //1---0
      //Serial.println("go left");
      flag = 'l';

    }

    else if (sensorValues[9] < threshold_w && sensorValues[0] > threshold_w) {
      //1---0
      //Serial.println("go left");
      flag = 'r';

    }

    //******************* try to make my lfr in line *********************
    else if (sensorValues[1] < threshold_w && sensorValues[8] > threshold_w) {
      //1---0
      //Serial.println("go left");
      RUN(1, 60, 0);  // ( left motor , speed , high or low )
      RUN(2, 60, 1);  // ( right motor , speed , high or low )
      while (sensorValues[4] > threshold_w && sensorValues[5] > threshold_w) reading();

    }

    else if (sensorValues[8] < threshold_w && sensorValues[1] > threshold_w) {
      //0---1
      //Serial.println("go right");
      RUN(1, 60, 1);  // ( left motor , speed , high or low )
      RUN(2, 60, 0);  // ( right motor , speed , high or low )
      while (sensorValues[4] > threshold_w && sensorValues[5] > threshold_w) reading();


    }

    else {
      PID_white();
    }
  }

  READ_black();
}
