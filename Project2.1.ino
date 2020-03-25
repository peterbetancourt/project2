#include <Sparki.h> // include the sparki library

int distance;
int threshold = 500;
int servoAngle = 0;
int i = 0;

void setup() 
{
  sparki.servo(SERVO_CENTER); // Center the Servo
  sparki.gripperClose();
}

void loop() 
{
    if(i >= 3)
    {
      servoAngle = 20;
    }
    if(i >= 6)
    {
      servoAngle = 35;
    }
    if(i > 9)
    {
      servoAngle = 0;
      i = 0;
    }
    sparki.servo(servoAngle);
    i++;
    onLine();
    //screen();
    distance = sparki.ping();
    // if cup is found
    if((distance <= 10) && (distance > 0))
    {
      sparki.servo(-70);
      sparki.moveRight();
      delay(2300);
      sparki.moveForward();
      delay(700);
      while(onWhite())
      {
        distance = sparki.ping();
        //screen();
        if((distance <= 11)  && (distance > 0))
        {
          sparki.moveForward();
        }
        else
        {
          sparki.moveLeft();
        }
      }
      // back on the black line so now we have to align ourselves
      int lineRight  = sparki.lineRight();  // measure the right IR sensor
      int lineRightEdge = sparki.edgeRight();
      // if the right sensor is on the black line
      if(lineRight < threshold)
      {
        while(lineRightEdge > threshold)
        {
          lineRightEdge = sparki.edgeRight();
          sparki.moveRight();
        }
        sparki.moveRight();
        delay(500);
      }
      else
      {
        sparki.moveRight();
        delay(300);
        sparki.moveForward();
      }
      sparki.moveForward();
      delay(400); 
      sparki.moveRight();
      delay(400);
    }
}

void onLine()
{
  int lineLeftEdge = sparki.edgeLeft();
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor
  int lineRightEdge = sparki.edgeRight();

  if ( lineCenter < threshold ) // if line is below left line sensor
  {  
    sparki.moveForward(); // move forward
  }
  else{
    if ( lineLeft < threshold ) // if line is below left line sensor
    {  
      sparki.moveLeft(); // turn left
    }
  
    if ( lineRight < threshold ) // if line is below right line sensor
    {  
      sparki.moveRight(); // turn right
    }
  }
}

//void screen()
//{
//  int lineLeftEdge = sparki.edgeLeft();
//  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
//  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
//  int lineRight  = sparki.lineRight();  // measure the right IR sensor
//  int lineRightEdge = sparki.edgeRight();
//  distance = sparki.ping();
//  
//  sparki.clearLCD(); // wipe the screen
//  
//  sparki.print("Line Left: "); // show left line sensor on screen
//  sparki.println(lineLeft);
//  
//  sparki.print("Line Center: "); // show center line sensor on screen
//  sparki.println(lineCenter);
//  
//  sparki.print("Line Right: "); // show right line sensor on screen
//  sparki.println(lineRight);
//
//  sparki.print("Distance: ");
//  sparki.println(distance);
//  
//  sparki.updateLCD(); // display all of the information written to the screen
//}

boolean onWhite() 
{
  // If the robot is over white...
  if(sparki.lineLeft() > threshold && sparki.lineCenter() > threshold && sparki.lineRight() > threshold)
  {
    return true;
  }
  else
  {
    return false;
  }
}
