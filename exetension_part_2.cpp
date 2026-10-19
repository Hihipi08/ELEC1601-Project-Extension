#include <Servo.h>

Servo servoLeft;
Servo servoRight;

int val_right = 0;
int val_left = 0;
int LED_G_Left = 8;
int LED_G_Right = 4;
int LED_R_Left = 9;
int LED_R_Right = 5;
int IR_LED_Left = 10;
int Sensor_Left = 11;
int IR_LED_Front = 6;
int Sensor_Front = 7;
int IR_LED_Right = 2;
int Sensor_Right = 3;
int ir_valL = 0;
int ir_valF = 0;
int ir_valR = 0;
int distanceL = 0;
int distanceF = 0;
int distanceR = 0;
int Sensor_LED_Left = A2;
int Sensor_LED_Front = A1;
int Sensor_LED_Right = A0;

void setup()
{
  Serial.begin(9600);

  servoLeft.attach(13);
  servoRight.attach(12);
  
  pinMode(IR_LED_Right, OUTPUT);
  pinMode(IR_LED_Left, OUTPUT);
  pinMode(IR_LED_Front, OUTPUT);
  pinMode(Sensor_Left, INPUT);
  pinMode(Sensor_Right, INPUT);
void followRightWall(int rightDistance)
{
  if (rightDistance <= 3) {
    servoLeft.writeMicroseconds(1550);
    servoRight.writeMicroseconds(1432);
  } else if (rightDistance >= 6) {
    servoLeft.writeMicroseconds(1568);
    servoRight.writeMicroseconds(1450);
  } else {
    servoLeft.writeMicroseconds(1568);
    servoRight.writeMicroseconds(1432);
  }
}

  pinMode(Sensor_Front, INPUT);
  int leftDistance = find_distance_left();
  int frontDistance = find_distance_front();
  int rightDistance = find_distance_right();

  if (leftDistance <= 4 && frontDistance >= 10 &&
      rightDistance >= 8 && rightDistance < 10) {
    Serial.println("Left wall present: steering toward right wall");
    followRightWall(rightDistance);
    digitalWrite(Sensor_LED_Left, HIGH);
    digitalWrite(Sensor_LED_Right, HIGH);
    digitalWrite(Sensor_LED_Front, LOW);
  }
  else if (leftDistance >= 6 && leftDistance < 11 &&
           frontDistance >= 10 && rightDistance <= 4) {
    Serial.println("Parallel to right wall");
    followRightWall(rightDistance);
    digitalWrite(Sensor_LED_Left, HIGH);
    digitalWrite(Sensor_LED_Right, LOW);
    digitalWrite(Sensor_LED_Front, HIGH);
  }
  else if (rightDistance <= 4 && frontDistance >= 10 && leftDistance == 11) {
    Serial.println("Angled toward right wall");
    followRightWall(rightDistance);
    digitalWrite(Sensor_LED_Right, HIGH);
    digitalWrite(Sensor_LED_Left, LOW);
    digitalWrite(Sensor_LED_Front, LOW);
  }
  else if (leftDistance <= 4 && frontDistance >= 10 && rightDistance >= 8) {
    Serial.println("Angled away from right wall");
    followRightWall(rightDistance);
    digitalWrite(Sensor_LED_Right, HIGH);
    digitalWrite(Sensor_LED_Left, HIGH);
    digitalWrite(Sensor_LED_Front, HIGH);
  }
  else if (frontDistance >= 10) {
    Serial.println("Following right wall");
    followRightWall(rightDistance);
    digitalWrite(Sensor_LED_Left, HIGH);
    digitalWrite(Sensor_LED_Right, HIGH);
    digitalWrite(Sensor_LED_Front, LOW);
  }
  else if (leftDistance == 11 && rightDistance == 10 && frontDistance >= 10) {
    Serial.println("Seeking right wall");
    followRightWall(rightDistance);
    digitalWrite(Sensor_LED_Left, LOW);
    digitalWrite(Sensor_LED_Right, LOW);
    digitalWrite(Sensor_LED_Front, LOW);
  }
  else if (leftDistance == 11 && rightDistance < 10 && frontDistance < 10) {
    Serial.println("left turn");
    delay(900);
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
    digitalWrite(Sensor_LED_Right, HIGH);
    digitalWrite(Sensor_LED_Left, LOW);
    digitalWrite(Sensor_LED_Front, HIGH);
    delay(1000);
    servoLeft.writeMicroseconds(1450);
    servoRight.writeMicroseconds(1450);
    delay(830);
    servoLeft.writeMicroseconds(1568);
    servoRight.writeMicroseconds(1432);
    delay(2000);
  }
  else if (leftDistance < 11 && rightDistance == 10 && frontDistance < 10) {
    Serial.println("right turn");
    delay(900);
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
    digitalWrite(Sensor_LED_Left, LOW);
    digitalWrite(Sensor_LED_Right, LOW);
    digitalWrite(Sensor_LED_Front, HIGH);
    delay(1000);
    servoLeft.writeMicroseconds(1550);
    servoRight.writeMicroseconds(1550);
    digitalWrite(Sensor_LED_Left, HIGH);
    digitalWrite(Sensor_LED_Right, LOW);
    digitalWrite(Sensor_LED_Front, HIGH);
    delay(780);
    servoLeft.writeMicroseconds(1568);
    servoRight.writeMicroseconds(1432);
    delay(2000);
  }
  else if (leftDistance != 11 && rightDistance != 10 &&
           leftDistance - rightDistance >= -3 &&
           leftDistance - rightDistance <= 3 && frontDistance < 10) {
    Serial.println("180 degree turn");
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
    digitalWrite(Sensor_LED_Right, LOW);
    digitalWrite(Sensor_LED_Left, HIGH);
    digitalWrite(Sensor_LED_Front, LOW);
    delay(1000);
    digitalWrite(Sensor_LED_Right, HIGH);
    digitalWrite(Sensor_LED_Left, HIGH);
    digitalWrite(Sensor_LED_Front, HIGH);
    servoLeft.writeMicroseconds(1550);
    servoRight.writeMicroseconds(1550);
    delay(1660);
    servoLeft.writeMicroseconds(1568);
    servoRight.writeMicroseconds(1432);
    delay(500);
  }
      digitalWrite(Sensor_LED_Front, HIGH);
      servoLeft.writeMicroseconds(1550); //180 degree turn
      servoRight.writeMicroseconds(1550);
      delay(1660); //might need to change this value
      servoLeft.writeMicroseconds(1568); // goes forwards for half a second
      servoRight.writeMicroseconds(1432);
      delay(500);
    }
}

int find_distance_left()
{
  tone(IR_LED_Left, 65000);
  delay(1);
  ir_valL = digitalRead(Sensor_Left);
  if (ir_valL == 0) { distanceL = 2; }
  else
  {
    tone(IR_LED_Left, 55000);
    delay(1);
    ir_valL = digitalRead(Sensor_Left);
    if (ir_valL == 0) { distanceL = 3; }
    else
    {
      tone(IR_LED_Left, 45000);
      delay(1);
      ir_valL = digitalRead(Sensor_Left);
      if (ir_valL == 0) { distanceL = 4; }
      else
      {
        tone(IR_LED_Left, 44000);
        delay(1);
        ir_valL = digitalRead(Sensor_Left);
        if (ir_valL == 0) { distanceL = 5; }
        else
        {
          tone(IR_LED_Left, 40000);
          delay(1);
          ir_valL = digitalRead(Sensor_Left);
          if (ir_valL == 0) { distanceL = 6; }
          else 
          { 
            tone(IR_LED_Left, 39000);
            delay(1);
            ir_valL = digitalRead(Sensor_Left);
            if (ir_valL == 0) { distanceL = 8; }
            else
            {
              tone(IR_LED_Left, 38000);
              delay(1);
              ir_valL = digitalRead(Sensor_Left);
              if (ir_valL == 0) { distanceL = 10; }
              else { distanceL = 11;}
            }
          } 
        }
      }
    }
  }

  noTone(IR_LED_Left);
  return distanceL;
}

int find_distance_right() //done
{
  tone(IR_LED_Right, 65000);
  delay(1);
  ir_valR = digitalRead(Sensor_Right);
  if (ir_valR == 0) { distanceR = 2; }
  else
  {
    tone(IR_LED_Right, 55000);
    delay(1);
    ir_valR = digitalRead(Sensor_Right);
    if (ir_valR == 0) { distanceR = 3; }
    else
    {
      tone(IR_LED_Right, 45000);
      delay(1);
      ir_valR = digitalRead(Sensor_Right);
      if (ir_valR == 0) { distanceR = 4; }
      else
      {
        tone(IR_LED_Right, 43000);
        delay(1);
        ir_valR = digitalRead(Sensor_Right);
        if (ir_valR == 0) { distanceR = 5; }
        else
        {
          tone(IR_LED_Right, 42000);
          delay(1);
          ir_valR = digitalRead(Sensor_Right);
          if (ir_valR == 0) { distanceR = 6; }
          else 
          {
            tone(IR_LED_Right, 40000);
          	delay(1);
          	ir_valR = digitalRead(Sensor_Right);
          	if (ir_valR == 0) { distanceR = 7; }
            else 
            {
              tone(IR_LED_Right, 39000);
              delay(1);
              ir_valR = digitalRead(Sensor_Right);
              if (ir_valR == 0) { distanceR = 8; }
              else 
              {
                tone(IR_LED_Right, 38000);
                delay(1);
                ir_valR = digitalRead(Sensor_Right);
                if (ir_valR == 0) { distanceR = 9; }
                else {distanceR = 10;}
                 
            
              }
            }
          }
        }
      }
    }
  }

  noTone(IR_LED_Right);
  return distanceR;
}
  

int find_distance_front() //done
{
  tone(IR_LED_Front, 65000);
  delay(1);
  ir_valF = digitalRead(Sensor_Front);
  if (ir_valF == 0) { distanceF = 2; }
  else
  {
    tone(IR_LED_Front, 55000);
    delay(1);
    ir_valF = digitalRead(Sensor_Front);
    if (ir_valF == 0) { distanceF = 3; }
    else
    {
      tone(IR_LED_Front, 45000);
      delay(1);
      ir_valF = digitalRead(Sensor_Front);
      if (ir_valF == 0) { distanceF = 4; }
      else
      {
        tone(IR_LED_Front, 43000);
        delay(1);
        ir_valF = digitalRead(Sensor_Front);
        if (ir_valF == 0) { distanceF = 5; }
        else
        {
          tone(IR_LED_Front, 42000);
          delay(1);
          ir_valF = digitalRead(Sensor_Front);
          if (ir_valF == 0) { distanceF = 6; }
          else 
          {
            tone(IR_LED_Front, 41000);
          	delay(1);
          	ir_valF = digitalRead(Sensor_Front);
          	if (ir_valF == 0) { distanceF = 7; }
          	else 
            {
              tone(IR_LED_Front, 40000);
          	  delay(1);
          	  ir_valF = digitalRead(Sensor_Front);
          	  if (ir_valF == 0) { distanceF = 8; }
              else {
                tone(IR_LED_Front, 39000);
                delay(1);
                ir_valF = digitalRead(Sensor_Front);
                if (ir_valF == 0) { distanceF = 10; }
                else 
                {
                  tone(IR_LED_Front, 38000);
                  delay(1);
                  ir_valF = digitalRead(Sensor_Front);
                  if (ir_valF == 0) { distanceF = 11; }
                  else {distanceF = 12;}
                }
              }
            }
          }
        }
      }
    }
  }

  noTone(IR_LED_Front);
  return distanceF;
}
