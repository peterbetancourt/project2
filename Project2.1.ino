#include <Sparki.h> // include the sparki library

int distance;
int threshold = 500;
int servoAngle = 0;
int i = 0;
int left = 0;
int center;
boolean counterclockwise = false;

void setup() 
{
  sparki.servo(SERVO_CENTER); // Center the Servo
  sparki.gripperClose();
  // Find out if we're going clockwise or counterclockwise
  while(i < 50)
  {
    distance = sparki.ping();
    if(distance <= 13)
    {
      i = 200;
    }
    i++;
    sparki.clearLCD(); // wipe the screen

    sparki.print("counterclockwise = ");
    sparki.println(counterclockwise);
    sparki.print("i = ");
    sparki.println(i);
    sparki.print("left = ");
    sparki.println(left);
    sparki.print("distance = ");
    sparki.println(distance);
   
    sparki.updateLCD();
    onLine();
    if( left >= 5)
    {
      counterclockwise = true;
    }
  }
  sparki.clearLCD(); // wipe the screen
  sparki.print("counterclockwise = ");
  sparki.println(counterclockwise);
  
  sparki.updateLCD();
}

void loop() 
{
 if(!counterclockwise)
 { 
    onLine();
    if(i >= 2)
    {
      servoAngle = 20;
    }
    if(i >= 4)
    {
      servoAngle = 45;
    }
    if(i > 6)
    {
      servoAngle = 0;
      i = 0;
    }
    sparki.servo(servoAngle);
    i++;

    distance = sparki.ping();
    sparki.clearLCD(); // wipe the screen
    sparki.print("distance = ");
    sparki.println(distance);
    sparki.updateLCD();
    
    // if cup is found
    if((distance <= 8) && (distance > 0))
    {
      distance = sparki.ping();
      if((distance <= 8) && (distance > 0))
      {
        sparki.servo(-75);
        if(servoAngle == 0)
        {
          sparki.moveRight();
          delay(1600);
          sparki.moveForward();
          delay(1000);
         }
         else if(servoAngle == 20)
         {
          sparki.moveRight();
          delay(2650);
          sparki.moveForward();
          delay(900);
         }
         else if(servoAngle == 45)
         {
          sparki.moveRight();
          delay(2800);
          sparki.moveForward();
          delay(1000);
         }
         while(onWhite())
         {
           distance = sparki.ping();
           if((distance <= 9)  && (distance > 0))
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
         sparki.moveForward();
         delay(300);
       }
       sparki.moveForward();
       delay(400); 
       sparki.moveRight();
       delay(400);
       }
    }
 }
 if(counterclockwise)
 {
   onLine();
   if(i >= 2)
    {
      servoAngle = -20;
    }
    if(i >= 4)
    {
      servoAngle = -45;
    }
    if(i > 6)
    {
      servoAngle = 0;
      i = 0;
    }
    sparki.servo(servoAngle);
    i++;
  
    sparki.clearLCD(); // wipe the screen
    sparki.print("distance = ");
    sparki.println(distance);
    sparki.updateLCD();   

    distance = sparki.ping();
    // if cup is found
    if((distance <= 8) && (distance > 0))
    {
      distance = sparki.ping();
      if((distance <= 8) && (distance > 0))
      {
       sparki.servo(75);
       if(servoAngle == 0)
       {
          sparki.moveLeft();
          delay(1600);
          sparki.moveForward();
          delay(1000);
        }
        else if(servoAngle == -20)
        {
          sparki.moveLeft();
          delay(2550);
          sparki.moveForward();
          delay(900);
        }
        else if(servoAngle == -45)
        {
          sparki.moveLeft();
          delay(2700);
          sparki.moveForward();
          delay(1000);
        }
        while(onWhite())
        {
          distance = sparki.ping();
          if((distance <= 9)  && (distance > 0))
        {
          sparki.moveForward();
        }
        else
        {
          sparki.moveRight();
        }
      }
      // back on the black line so now we have to align ourselves
      int lineLeft  = sparki.lineLeft();  // measure the right IR sensor
      int lineLeftEdge = sparki.edgeLeft();
      // if the right sensor is on the black line
      if(lineLeft < threshold)
      {
        while(lineLeftEdge > threshold)
        {
          lineLeftEdge = sparki.edgeLeft();
          sparki.moveLeft();
        }
        sparki.moveLeft();
        delay(500);
      }
      else
      {
        sparki.moveForward();
        delay(300);
      }
      sparki.moveForward();
      delay(400); 
      sparki.moveLeft();
      delay(400);
     }
   }
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
    center++;
    if(center >= 150)
    {
      left = 0;
    }
  }
  else{
    if ( lineLeft < threshold ) // if line is below left line sensor
    {  
      sparki.moveLeft(); // turn left
      left++;
    }
  
    if ( lineRight < threshold ) // if line is below right line sensor
    {  
      sparki.moveRight(); // turn right
      left = 0;
    }
  }
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
