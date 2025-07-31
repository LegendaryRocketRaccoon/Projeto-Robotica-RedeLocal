#include "funcoes.h"
#include <Arduino.h>

void desligarTodosAtuadores() {
  // Desligar atuadores inicialmente
  digitalWrite(PINO_ESTEIRA, LOW);
  digitalWrite(PINO_SEPARADOR, LOW);
  digitalWrite(PINO_TRAVA, HIGH);
  digitalWrite(PINO_MAGAZINE, HIGH);
  digitalWrite(PINO_MEDIDOR, LOW);
}