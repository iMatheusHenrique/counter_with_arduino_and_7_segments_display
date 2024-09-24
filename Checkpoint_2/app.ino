#include <TimerOne.h>

int segmentPins[] = {2, 3, 4, 5, 6, 7, 8};
int digit = 0;                             // Contador de dígitos
bool fastInterval = true;                  // Controla o intervalo entre 0,5s e 2s
bool running = true;                       // Controla se o contador está rodando ou não

void showNumber(int num) {
  switch (num) {
    case 0:
      digitalWrite(2, 1);
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(7, 1);
      digitalWrite(8, 0);
      break;
    case 1:
      digitalWrite(2, 0);
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
      break;
    case 2:
      digitalWrite(2, 1);
      digitalWrite(3, 1);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(7, 0);
      digitalWrite(8, 1);
      break;
    case 3:
      digitalWrite(2, 1);
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 0);
      digitalWrite(7, 0);
      digitalWrite(8, 1);
      break;
    case 4:
      digitalWrite(2, 0);
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(7, 1);
      digitalWrite(8, 1);
      break;
    case 5:
      digitalWrite(2, 1);
      digitalWrite(3, 0);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 0);
      digitalWrite(7, 1);
      digitalWrite(8, 1);
      break;
    case 6:
      digitalWrite(2, 1);
      digitalWrite(3, 0);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(7, 1);
      digitalWrite(8, 1);
      break;
    case 7:
      digitalWrite(2, 1);
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
      break;
    case 8:
      digitalWrite(2, 1);
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(7, 1);
      digitalWrite(8, 1);
      break;
    case 9:
      digitalWrite(2, 1);
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 0);
      digitalWrite(7, 1);
      digitalWrite(8, 1);
      break;
  }
}

void incrementCounter() {
  if (running) {
    digit = (digit + 1) % 10; // Incrementa o contador e reseta para 0 após 9
    showNumber(digit);        // Exibe o número no display de 7 segmentos
    
    Serial.print("Valor Atual: ");
    Serial.println(digit);
    
    if (fastInterval) {
      Serial.println("Próximo intervalo: 2 segundos");
      Timer1.initialize(2000000);
    } else {
      Serial.println("Próximo intervalo: 0,5 segundos");
      Timer1.initialize(500000);
    }
    fastInterval = !fastInterval; // Alterna o intervalo
  }
}

void setup() {
  for (int i = 2; i <= 8; i++) {
    pinMode(i, OUTPUT);
  }

  Serial.begin(9600);

  // Timer1 com 0,5 segundos
  Timer1.initialize(500000);  
  Timer1.attachInterrupt(incrementCounter); // Configurar a função de interrupção
 
  // Exibir o número inicial no display (0)
  showNumber(digit);

  // Mensagem inicial no monitor serial
  Serial.println("Contador iniciado");
}

void loop() {

}
