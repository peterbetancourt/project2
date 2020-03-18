#include <Sparki.h> // include the sparki library

int distance;
int threshold = 500;
boolean foundLine = false;

void setup() 
{
  sparki.servo(SERVO_CENTER); // Center the Servo
}

void loop() 
{
  onLine();
  foundLine = false;
  
  sparki.servo(SERVO_CENTER);
  delay(0);
  
  for(int i = 0; i < 5; i++)
  {
    onLine();
    distance = sparki.ping();
    sparki.servo(i*14);
    if(distance <= 11)
    {
      sparki.moveRight();
      delay(2400);
      sparki.servo(-60);
      for(i = 0; i < 30; i++)
      {
        sparki.moveForward();
        if(!onWhite())
        {
          sparki.moveRight();
          foundLine = true;
          i = 2000;
          delay(1000);
          while(onWhite())
          {
            sparki.moveForward();
          }
          
        }
        distance = sparki.ping();
        if(distance<= 16)
        {
          i = 0;
        }
      }
      if(!foundLine)
      {
        sparki.moveLeft();
        delay(2300);
        sparki.moveForward();
        for(i = 0; i < 40; i++)
        {
          distance = sparki.ping();
          if(distance<=12)
          {
            i=0;
          }
          if(!onWhite())
          {
            i = 2000;
            foundLine = true;
          }
        }
        if(!foundLine)
        {
          sparki.moveLeft();
          delay(500);
        }
        while(onWhite())
        {
         sparki.moveForward();
        }
        sparki.moveRight();
        delay(1200);
        sparki.moveForward();
        delay(500);
        while(onWhite())
        {
          sparki.moveForward();
        }
      }

    }
    
  }
//  for(int i = 0; i > -20; i--)
//  {    
//    distance = sparki.ping();
//    sparki.servo(i*3);
//    if(distance <= 15)
//    {
//      sparki.moveRight();
//      delay(2000);
//      sparki.moveForward();
//      delay(4000);
//      sparki.moveLeft();
//      delay(2000);
//      while(onWhite())
//      {
//        sparki.moveForward();
//      }
//    }
//    delay(0);
//    onLine();
//  }

  

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

  distance = sparki.ping();
  
  sparki.clearLCD(); // wipe the screen
  
  sparki.print("Line Left: "); // show left line sensor on screen
  sparki.println(lineLeft);
  
  sparki.print("Line Center: "); // show center line sensor on screen
  sparki.println(lineCenter);
  
  sparki.print("Line Right: "); // show right line sensor on screen
  sparki.println(lineRight);

  sparki.print("Distance: ");
  sparki.println(distance);
  
  sparki.updateLCD(); // display all of the information written to the screen
}

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
