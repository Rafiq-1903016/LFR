void READ_black() {
  while (1) {
    reading();
    int R = analogRead(A4);
    int L = analogRead(A5);
    //************* loop break for white line ************
    if ((sensorValues[0] > threshold && sensorValues[1] > threshold) && (sensorValues[9] > threshold && sensorValues[8] > threshold) && (sensorValues[2] < threshold || sensorValues[3] < threshold || sensorValues[4] < threshold || sensorValues[5] < threshold || sensorValues[6] < threshold || sensorValues[7] < threshold)) {
      RUN(1, turnSpeed, 0);  // ( left motor , speed , high or low )
      RUN(2, turnSpeed, 0);  // ( right motor , speed , high or low )
      delay(70);

      stop();
      delay(50);

      reading();
      if (sensorValues[2] < threshold && sensorValues[3] < threshold && sensorValues[4] < threshold && sensorValues[5] < threshold && sensorValues[6] < threshold && sensorValues[7] < threshold) {
        go_right();
        while (sensorValues[4] < threshold && sensorValues[5] < threshold) reading();
        RUN(1, turnSpeed, 0);  // ( left motor , speed , high or low )
        RUN(2, turnSpeed, 1);  // ( right motor , speed , high or low )
        delay(200);
      } else break;
    }


    //************** when all in white **********
    else if (sensorValues[0] < threshold && sensorValues[1] < threshold && sensorValues[2] < threshold && sensorValues[3] < threshold && sensorValues[4] < threshold && sensorValues[5] < threshold && sensorValues[6] < threshold && sensorValues[7] < threshold && sensorValues[8] < threshold && sensorValues[9] < threshold) {
      //Serial.println("straight");
      RUN(1, turnSpeed , 1);  // ( left motor , speed , high or low )
      RUN(2, turnSpeed , 1);  // ( right motor , speed , high or low )
      delay(50);


      reading_sonar();
      if (distance_left < 30 && distance_right < 30) {
        READ_sonar();
      }

      else if (flag != 's') {
        RUN(1, turnSpeed, 0);  // ( left motor , speed , high or low )
        RUN(2, turnSpeed, 0);  // ( right motor , speed , high or low )
        delay(200);
        stop();
        delay(50);

        if (flag == 'r') {
          go_right();
          while (sensorValues[4] < threshold && sensorValues[5] < threshold) reading();
          RUN(1, turnSpeed, 0);  // ( left motor , speed , high or low )
          RUN(2, turnSpeed, 1);  // ( right motor , speed , high or low )
          delay(200);

        } else if (flag == 'l') {
          go_left();
          while (sensorValues[4] < threshold && sensorValues[5] < threshold) reading();
          RUN(1, turnSpeed, 1);  // ( left motor , speed , high or low )
          RUN(2, turnSpeed, 0);  // ( right motor , speed , high or low )
          delay(200);
        }
        flag = 's';
      }
    }


    //*********** 30 degree logic ****************
    else if (R < RL && sensorValues[9] > threshold && (sensorValues[4] > threshold || sensorValues[5] > threshold) && L > RL && sensorValues[0] < threshold) {

      //Serial.println("30 right");
      turn_30_right();

    }

    else if (L < RL && sensorValues[0] > threshold && (sensorValues[4] > threshold || sensorValues[5] > threshold) && R > RL && sensorValues[9] < threshold) {
      turn_30_left();
    }


    //************** 90 degree logic **************
    else if (sensorValues[0] > threshold && sensorValues[1] > threshold && sensorValues[2] > threshold && sensorValues[9] < threshold) {
      //1---0
      //Serial.println("go left");
      flag = 'l';
    }

    else if (sensorValues[9] > threshold && sensorValues[8] > threshold && sensorValues[7] > threshold && sensorValues[0] < threshold) {
      //1---0
      //Serial.println("go right");
      flag = 'r';

    }

    //************* try to make my lfr in line ***************
    else if (sensorValues[1] > threshold && sensorValues[8] < threshold) {
      //1---0
      //Serial.println("go left");
      go_left();
      while (sensorValues[3] < threshold && sensorValues[4] < threshold) reading();
    }

    else if (sensorValues[8] > threshold && sensorValues[1] < threshold) {
      //0---1
      //Serial.println("go right");
      go_right();
      while (sensorValues[5] < threshold && sensorValues[6] < threshold) reading();
    }

    //*************** loop break for extended line *****************

    //right hand rule
    //priority right That's why we turn right in "T" section
    else if (R < RL && L > RL && sensorValues[0] < threshold && sensorValues[9] < threshold && (sensorValues[1] > threshold || sensorValues[2] > threshold || sensorValues[3] > threshold || sensorValues[4] > threshold || sensorValues[5] > threshold || sensorValues[6] > threshold || sensorValues[7] > threshold || sensorValues[8] > threshold)) {
      //1111---00
      //Serial.println("force right");
      force_right();

    }


    //********************** stop point & T section *******************

    else if (sensorValues[0] > threshold && sensorValues[1] > threshold && sensorValues[2] > threshold && sensorValues[3] > threshold && sensorValues[4] > threshold && sensorValues[5] > threshold && sensorValues[6] > threshold && sensorValues[7] > threshold && sensorValues[8] > threshold && sensorValues[9] > threshold) {
      //11111-11111

      RUN(1, turnSpeed, 0);  // ( left motor , speed , high or low )
      RUN(2, turnSpeed, 0);  // ( right motor , speed , high or low )
      delay(70);

      stop();
      delay(50);
      reading();

      //**************** turn right beacuse of our prioity right ******************
      if (sensorValues[0] < threshold && sensorValues[1] < threshold && sensorValues[2] < threshold && sensorValues[3] < threshold && sensorValues[4] < threshold && sensorValues[5] < threshold && sensorValues[6] < threshold && sensorValues[7] < threshold && sensorValues[8] < threshold && sensorValues[9] < threshold) {
        //all white
        // T- Section
        //00000-00000
        //Serial.println("t section go right");
        go_right();
        while (sensorValues[4] < threshold && sensorValues[5] < threshold) reading();
      }

      //**************** when all are in black line*********************
      else {
        //1-11111-11111-1
        //all black
        //Serial.println("stop");
        RUN(1, turnSpeed, 0);  // ( left motor , speed , high or low )
        RUN(2, turnSpeed, 0);  // ( right motor , speed , high or low )
        delay(120);

        stop();
        while (sensorValues[0] > threshold && sensorValues[1] > threshold && sensorValues[2] > threshold && sensorValues[3] > threshold && sensorValues[4] > threshold && sensorValues[5] > threshold && sensorValues[6] > threshold && sensorValues[7] > threshold) {
          reading();
        }
        delay(1000);
      }
    }

    else PID_black();
  }

  READ_white();
}