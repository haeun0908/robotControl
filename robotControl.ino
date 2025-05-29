#include <SoftwareSerial.h>
#include <Servo.h>

// LED 및 센서 핀 정의
#define LED_R   8
#define LED_G   10
#define BUTTON  11
#define VOLUME  A0
#define CDS     A1

// 초음파 센서 핀 정의
const int trigPin = 4;
const int echoPin = 5;

float duration, distance;
Servo myservo; 
SoftwareSerial mySerial(2, 3); // RX, TX

bool bStart = false;
int nVol, cdsVol;
unsigned char cVol;
bool isStand = false;

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(CDS, INPUT);
  pinMode(VOLUME, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myservo.attach(9);
  
  Serial.begin(115200);
  Serial.println("---------- 프로그램 시작 ----------");
  
  mySerial.begin(115200);
  Serial.println("---------- Software Serial 시작 ----------");
}

void ledCon(int nVol) {
  digitalWrite(LED_R, HIGH);
  delay(nVol);
  digitalWrite(LED_R, LOW);

  digitalWrite(LED_G, HIGH);
  delay(nVol);
  digitalWrite(LED_G, LOW);
  delay(nVol);
}

void readSensor() {
  cdsVol = analogRead(CDS);
  cVol = nVol = analogRead(VOLUME);

  Serial.print("cdsVol = ");
  Serial.print(cdsVol);
  Serial.print("\t cVol = ");
  Serial.print(cVol);
  Serial.print("\t nVol = ");
  Serial.println(nVol);
}

bool toggleCheck() {
  for (int i = 0; i < 100; i++) {
    if (digitalRead(BUTTON)) {
      return true;
    }
    delay(1);
  }
  return false;
}

void robotCon(int nMotion) {
  unsigned char exeCmd[15] = {0xff, 0xff, 0x4c, 0x53, 
                              0x00, 0x00, 0x00, 0x00,
                              0x30, 0x0c, 
                              0x03, 
                              0x01, 0x00, 100, 
                              0x54};

  exeCmd[11] = nMotion;
  exeCmd[14] = 0x00;
  
  for (int i = 6; i < 14; i++) {
    exeCmd[14] += exeCmd[i];
  }

  mySerial.write(exeCmd, 15);
  delay(50);
}

void ledRobotStat() {
  digitalWrite(LED_G, isStand);
}

void lightReaction() {
  cdsVol = analogRead(CDS);

  if (cdsVol < 500) {
    if (isStand) {
      robotCon(115);
      delay(5000);
      isStand = false;
      myservo.write(0);
      Serial.println("is sitting...");
    } else {
      ledRobotStat();
    }
  } else {
    if (!isStand) {
      robotCon(116);
      delay(5000);
      isStand = true;
      myservo.write(512);
      Serial.println("is standing...");
    } else {
      ledRobotStat();
    }
  }

  if (distance > 150 && isStand) {
    robotCon(115);
    delay(5000);
    isStand = false;
    Serial.println("150cm 이내 사물 없음, 휴식 중...");
  } else if (distance > 100) {
    robotCon(116);
    delay(5000);
    isStand = true;
    Serial.println("물체 인식 완료, 일어납니다.");
  } else if (distance > 50) {
    robotCon(19);
    delay(7000);
    Serial.println("안녕하세요. 이 이상 오면 전투로 간주합니다.");
  } else {
    robotCon(22);
    delay(5000);
    Serial.println("거리 50cm 미만, 전투 준비.");
  }
}

void ultrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
}

void loop() {
  ultrasonic();
  lightReaction();

  for (int i = 0; i < 10; i++) {
    if (toggleCheck()) {
      bStart = !bStart;
    }
  }

  if (bStart) {
    readSensor();
    robotCon(19);
    delay(7000);
    bStart = false;
  } else {
    delay(10);
    Serial.println("Waiting Button...");
  }
}
