#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 110
#define SERVOMAX 490

#define LL 0
#define RL 1
#define LF 2
#define RF 3

#define TRIG 8
#define ECHO 9
#define BUZZER 13

int t = 495;

void setServo(uint8_t ch, int angle){
  int pulse = map(angle,0,180,SERVOMIN,SERVOMAX);
  pwm.setPWM(ch,0,pulse);
}

void home(){
  setServo(LL,90);
  setServo(RL,90);
  setServo(LF,90);
  setServo(RF,90);
}

long ultrasonic_distance_simple(){

  long duration;
  long distance;

  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG,LOW);

  duration = pulseIn(ECHO,HIGH);

  distance = duration/58;

  return distance;
}

void walkForward(){

  setServo(LL,70);
  setServo(RL,110);
  delay(250);

  setServo(LF,110);
  setServo(RF,70);
  delay(250);

  setServo(LL,110);
  setServo(RL,70);
  delay(250);

  setServo(LF,70);
  setServo(RF,110);
  delay(250);

}

void walkBackward(){

  setServo(LL,110);
  setServo(RL,70);
  delay(250);

  setServo(LF,110);
  setServo(RF,70);
  delay(250);

  setServo(LL,70);
  setServo(RL,110);
  delay(250);

  setServo(LF,70);
  setServo(RF,110);
  delay(250);

}

void turnLeft(){

  setServo(LL,70);
  setServo(RL,70);
  delay(300);

  setServo(LF,110);
  setServo(RF,90);
  delay(300);

}

void turnRight(){

  setServo(LL,110);
  setServo(RL,110);
  delay(300);

  setServo(LF,90);
  setServo(RF,70);
  delay(300);

}

void jump(){

  setServo(LF,60);
  setServo(RF,120);
  delay(200);

  setServo(LF,120);
  setServo(RF,60);
  delay(200);

  home();
}

void swing(){

  setServo(LL,60);
  setServo(RL,120);
  delay(400);

  setServo(LL,120);
  setServo(RL,60);
  delay(400);

}

void moonwalkLeft(){

  for(int i=0;i<4;i++){

    setServo(LL,70);
    setServo(RL,110);
    delay(200);

    setServo(LL,90);
    setServo(RL,90);
    delay(200);

  }
}

void moonwalkRight(){

  for(int i=0;i<4;i++){

    setServo(LL,110);
    setServo(RL,70);
    delay(200);

    setServo(LL,90);
    setServo(RL,90);
    delay(200);

  }
}

void kickLeft(){

  setServo(LL,50);
  delay(200);

  setServo(LL,90);
  delay(200);

}

void kickRight(){

  setServo(RL,130);
  delay(200);

  setServo(RL,90);
  delay(200);

}

void drunkDance(){

  for(int i=0;i<4;i++){

    setServo(LL,60);
    setServo(RL,120);
    delay(300);

    setServo(LL,120);
    setServo(RL,60);
    delay(300);

  }

}

void flapping(){

  for(int i=0;i<10;i++){

    setServo(LF,80);
    setServo(RF,100);
    delay(150);

    setServo(LF,100);
    setServo(RF,80);
    delay(150);

  }

}

void dance(){

  walkForward();
  walkForward();

  turnLeft();

  swing();

  kickLeft();
  kickRight();

  moonwalkLeft();
  moonwalkRight();

  drunkDance();

  jump();

  flapping();

  walkBackward();
}

void setup(){

  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(50);

  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);

  pinMode(BUZZER,OUTPUT);

  delay(500);

  home();

}

void loop(){

  long distance = ultrasonic_distance_simple();

  if(distance < 15){

    tone(BUZZER,1000,200);

    turnRight();
    walkForward();

  }

  else{

    dance();

  }

}