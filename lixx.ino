/* Readme

//// Tags ////

#indev（in development）作成中
#unveri（unverified）作ったけど動作未検証
#imlat（improve later)　後で改良
#devlat（develop later)　後で実装
#dellat（delete later） 後で消す

*/ 

#include <Arduino.h>
 
//// Pin config ////

//for Motor
const int Pin_leftMotorIn1 =  26;
const int Pin_leftMotorIn2 =  25;
const int Pin_rightMotorIn1 = 32;
const int Pin_rightMotorIn2 = 33;

//for PhotoReflector
const int Pin_leftSensor = 36;
const int Pin_rightSensor = 39;

//// Function Declarations ////

void forward()
{
  digitalWrite(Pin_rightMotorIn1, 0);
  digitalWrite(Pin_rightMotorIn2, 1);
  digitalWrite(Pin_leftMotorIn1, 0);
  digitalWrite(Pin_leftMotorIn2, 1);
}

void forward(int duty_r, int duty_l)
{
  ledcWrite(3, duty_r);
  ledcWrite(1, duty_l);
  digitalWrite(Pin_rightMotorIn1, 0);
  digitalWrite(Pin_leftMotorIn1, 0);
}
/*
  ledcAttachPin(Pin_leftMotorIn1, 0);  //0ch setting
  ledcAttachPin(Pin_leftMotorIn2, 1);  //1ch setting
  ledcAttachPin(Pin_rightMotorIn1, 2);  //2ch setting
  ledcAttachPin(Pin_rightMotorIn2, 3);  //3ch setting
*/

void backward()
{
  digitalWrite(Pin_rightMotorIn1, 1);
  digitalWrite(Pin_rightMotorIn2, 0);
  digitalWrite(Pin_leftMotorIn1, 1);
  digitalWrite(Pin_leftMotorIn2, 0);
}

void left_turn()
{
  digitalWrite(Pin_rightMotorIn1, 1);
  digitalWrite(Pin_rightMotorIn2, 0);
  digitalWrite(Pin_leftMotorIn1, 0);
  digitalWrite(Pin_leftMotorIn2, 1);  
}

void right_turn()
{
  digitalWrite(Pin_rightMotorIn1, 0);
  digitalWrite(Pin_rightMotorIn2, 1);
  digitalWrite(Pin_leftMotorIn1, 1);
  digitalWrite(Pin_leftMotorIn2, 0);  
}

void free(int time_ms)
{
  digitalWrite(Pin_rightMotorIn1, 0);
  digitalWrite(Pin_rightMotorIn2, 0);
  digitalWrite(Pin_leftMotorIn1, 0);
  digitalWrite(Pin_leftMotorIn2, 0);
  delay(time_ms);  
}

void brake(int time_ms)
{
  digitalWrite(Pin_rightMotorIn1, 1);
  digitalWrite(Pin_rightMotorIn2, 1);
  digitalWrite(Pin_leftMotorIn1, 1);
  digitalWrite(Pin_leftMotorIn2, 1);
  delay(time_ms);  
}


void setup()
{
  Serial.begin(115200);
  Serial.println("lixx startup"); 

  pinMode(Pin_leftMotorIn1, OUTPUT);
  pinMode(Pin_leftMotorIn2, OUTPUT);
  pinMode(Pin_rightMotorIn1, OUTPUT);
  pinMode(Pin_rightMotorIn2, OUTPUT);

  ledcSetup(0, 12800, 10); //0ch, 10kHz, 10bit(1024)Resolution
  ledcSetup(1, 12800, 10); //0ch, 10kHz, 10bit(1024)Resolution
  ledcSetup(2, 12800, 10); //0ch, 10kHz, 10bit(1024)Resolution
  ledcSetup(3, 12800, 10); //0ch, 10kHz, 10bit(1024)Resolution
  ledcAttachPin(Pin_leftMotorIn1, 0);  //0ch setting
  ledcAttachPin(Pin_leftMotorIn2, 1);  //1ch setting
  ledcAttachPin(Pin_rightMotorIn1, 2);  //2ch setting
  ledcAttachPin(Pin_rightMotorIn2, 3);  //3ch setting
}

void loop()
{
  static int duty = 0;
  static int diff = 1;
  
  forward(duty, duty);

  if(duty <= 0)
  {
    diff = 2;
    delay(1000);
  }
  else if(duty >= 1023)
  {
    diff = -2;
    delay(1000);
  }

  duty += diff;

  Serial.print("diff: ");
  Serial.println(diff);
  Serial.print("duty: ");
  Serial.println(duty);

  //Getting PhotoReflectors Value 
  int analogValueL = analogRead(Pin_leftSensor);  //adcから値を取得
  int analogValueR = analogRead(Pin_rightSensor); //adcから値を取得

  Serial.print("leftSensor: ");
  Serial.println(analogValueL);
  Serial.print("rightSensor: ");
  Serial.println(analogValueR);
  Serial.println();

/*
  //左右（白白）→直進
  forward();
  delay(500);
  brake(250);

  //左右（白白）→後進
  backward();
  delay(500);
  brake(250);  

  //左右（黒白）→右旋回（左モータ正転）
  right_turn();
  delay(500);
  brake(250);  

  //左右（白黒）→左旋回（右モータ正転）
  left_turn();
  delay(500);
  brake(250);  

  delay(1000);
  */

}
