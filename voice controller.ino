#include <AFMotor.h>
#include <Servo.h>
#define echoPin 7
#define trigPin 8
#define buzzer 11
long duration;
long distance;
int safetyDistance;
String voice;
AF_DCMotor motor1 (4, MOTOR12_1KHZ);
AF_DCMotor motor2 (2, MOTOR12_1KHZ);
Servo SERVO;

void setup()
{
  Serial.begin(9600);
  SERVO.attach(10);
  SERVO.write(120);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(buzzer, OUTPUT);

}

void loop()
{


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58, 2;

  safetyDistance = distance;
  if (safetyDistance <= 10) {
    digitalWrite(buzzer, HIGH);
  }
  else {
    digitalWrite(buzzer, LOW);
  }
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(50);



  while (Serial.available())
  { //Check if there is an available byte to read
    delay(10); //Delay added to make thing stable
    char c = Serial.read(); //Conduct a serial read
    if (c == '#') {
      break;
    }
    voice += c;
  }
  if (voice.length() > 0) {
    if (voice == "*go ahead") {
      forward_car();
    }
    else if (voice == "*go back") {
      back_car();
    }
    else if (voice == "*go right") {
      right_car();
    }
    else if (voice == "*go left") {
      left_car();
    }
    else if (voice == "*stop") {
      stop_car();
    }


    voice = "";
  }
}

void forward_car()
{
  motor1.run(FORWARD);
  motor1.setSpeed(150);
  motor2.run(FORWARD);
  motor2.setSpeed(150);
  delay(2000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
void back_car()
{
  motor1.run(BACKWARD);
  motor1.setSpeed(150);
  motor2.run(BACKWARD);
  motor2.setSpeed(150);
  delay(2000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void right_car()
{
  SERVO.write(45);
  delay(1000);
  SERVO.write(120);
  delay(1000);
  motor1.run(FORWARD);
  motor1.setSpeed(150);
  motor2.run(BACKWARD);
  motor2.setSpeed(150);
  delay(2000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void left_car()
{
  SERVO.write(180);
  delay(1000);
  SERVO.write(120);
  delay(1000);
  motor1.run(BACKWARD);
  motor1.setSpeed(150);
  motor2.run(FORWARD);
  motor2.setSpeed(150);
  delay(2000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}


void stop_car ()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
