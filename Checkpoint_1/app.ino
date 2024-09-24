#include <Servo.h>

const int buttonPin = 2;
const int ledPin = 13;
const int segPins[] = {12,3,4,5,6,7,8};
const int servoPin = 11;

volatile int contador = 0;
Servo myServo;
volatile bool buttonPressed = false;

const int digits[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  myServo.attach(servoPin);

  attachInterrupt(digitalPinToInterrupt(buttonPin), handleInterrupt, RISING );

  displayDigit(contador);
}

void loop() {
  buttonPressed = false;
  digitalWrite(ledPin, LOW);
  if (!buttonPressed) {
    delay(1000);
    contador++;
    if (contador > 9) {
      contador = 0;
    }

    displayDigit(contador);


    int servoAngle = map(contador, 0, 9, 0, 180);
    myServo.write(servoAngle);
  }
}

void displayDigit(int digit) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digits[digit][i]);
  }
}

void handleInterrupt() {
  buttonPressed = true;

  digitalWrite(ledPin, HIGH);

  myServo.write(90);

  contador = 0;
  displayDigit(contador);

  delay(50);
}
