#include "estados.h"

Estado estadoAtual = MANUAL;
unsigned long startTime = 0;
unsigned long contadorMetal = 0;
unsigned long contadorPlastico = 0;

#include <Arduino.h>
#include <WiFi.h>

#include "pinos.h"
#include "estados.h"
#include "funcoes.h"
#include "servidor.h"
#include "estado_maquina.h"

const char *ssid = "R2D2";
const char *password = "Procyon Lotor";

void setup() {
  Serial.begin(9600);
  startTime = millis();

  // Configurar saídas
  pinMode(PINO_ESTEIRA, OUTPUT);
  pinMode(PINO_SEPARADOR, OUTPUT);
  pinMode(PINO_TRAVA, OUTPUT);
  pinMode(PINO_MAGAZINE, OUTPUT);
  pinMode(PINO_MEDIDOR, OUTPUT);

  // Configurar sensores (entradas)
  pinMode(ENTRADA_VP, INPUT);
  pinMode(ENTRADA_VN, INPUT);
  pinMode(ENTRADA_D34, INPUT);
  pinMode(ENTRADA_D32, INPUT);

  desligarTodosAtuadores();

  WiFi.softAP(ssid, password);
  Serial.println("Rede Wi-Fi criada");
  Serial.print("Acesse: http://");
  Serial.println(WiFi.softAPIP());

  configurarServidor();
}

void loop() {
  server.handleClient();
  atualizarEstado();
  delay(300);
}