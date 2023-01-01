 void reading_sonar(){

   // Clears the trigPin condition
  digitalWrite(trigPin_left, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_left, LOW);

  duration_left = pulseIn(echoPin_left, HIGH);

  digitalWrite(trigPin_right, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_right, LOW);

  duration_right = pulseIn(echoPin_right, HIGH);

 // Calculating the distance
  distance_left = (duration_left * 0.034 / 2);  // Speed of sound wave divided by 2 (go and back)
  distance_right = (duration_right * 0.034 / 2);
  if(distance_left>50)distance_left=50;
  if(distance_right>50)distance_right=50;


 }
 
 