#include <Servo.h>

// Definições de pinos
const int buttonPin2 = 2;   // Pino do botão 1 (Interrupção no pino 2)
const int buttonPin3 = 3;   // Pino do botão 2 (Interrupção no pino 3)
const int ledPin = 13;      // Pino para o LED
const int segPins[] = {2, 3, 4, 5, 6, 7, 8}; // Pinos para o display de 7 segmentos
const int servoPin = 11;    // Pino para o servo motor

// Variável do contador, atualizada nas rotinas de interrupção
volatile int contador = 0;
Servo myServo;  // Objeto Servo para controlar o motor

// Padrões de segmentos para os dígitos de 0 a 9 no display de 7 segmentos (cátodo comum)
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
  // Configuração dos pinos do display de 7 segmentos
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }

  // Configuração dos pinos do botão e LED
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(ledPin, OUTPUT);

  // Anexar o servo ao pino
  myServo.attach(servoPin);

  // Configuração das interrupções
  attachInterrupt(digitalPinToInterrupt(2), isr_pino2, RISING); // Pino 2 gera interrupção
  attachInterrupt(digitalPinToInterrupt(3), isr_pino3, RISING); // Pino 3 gera interrupção

  // Exibir o dígito inicial no display
  displayDigit(contador);
}

void loop() {
  // Incrementar o contador a cada segundo
  delay(1000);
  contador++;
  if (contador > 9) {
    contador = 0;
  }
  
  // Exibir o valor no display de 7 segmentos
  displayDigit(contador);
  
  // Controlar o LED com base no valor do contador
  int pwmValue = map(contador, 0, 9, 0, 255);  // Mapear o valor do contador para PWM
  analogWrite(ledPin, pwmValue);

  // Controlar o servo motor com base no valor do contador
  int servoAngle = map(contador, 0, 9, 0, 180); // Mapear o contador para o ângulo do servo (0-180º)
  myServo.write(servoAngle);
}

// Função para exibir o dígito no display de 7 segmentos
void displayDigit(int digit) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digits[digit][i]);
  }
}

// ISR para o pino 2 - Zerar o contador
void isr_pino2() {
  contador = 0;
  displayDigit(contador); // Atualizar o display imediatamente
}

// ISR para o pino 3 - Definir o contador para 100 (ajustado para lidar com o display)
void isr_pino3() {
  contador = 9;  // Como o display vai de 0 a 9, o máximo é 9
  displayDigit(contador); // Atualizar o display imediatamente
}
