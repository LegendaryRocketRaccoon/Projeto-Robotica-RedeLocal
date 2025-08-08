#include "servidor.h"
#include "pagina_web.h"
#include "estados.h"
#include "pinos.h"
#include "estado_maquina.h"
#include "funcoes.h"


WebServer server(80);

void configurarServidor() {
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", htmlPage);
  });

  server.on("/tempo", HTTP_GET, []() {
    unsigned long elapsed = 0;
    if (estadoAtual == AUTOMATICO_EM_EXECUCAO || estadoAtual >= ESTADO_1) {
      elapsed = millis() - startTime;
    }
    server.send(200, "text/plain", String(elapsed / 1000));
  });

  server.on("/contador", HTTP_GET, []() {
    String json = "{";
    json += "\"metal\":" + String(contadorMetal) + ",";
    json += "\"plastico\":" + String(contadorPlastico);
    json += "}";
    server.send(200, "application/json", json);
  });

  // comandos manuais (ligar/desligar etc.)
   server.on("/comando", HTTP_GET, []()
            {
    String acao = server.arg("acao");

    if (acao == "ligarProcesso") {
  startTime = millis(); 
  estadoAtual = AUTOMATICO_EM_EXECUCAO;
  server.send(200, "text/plain", "Processo automático iniciado");
  return;
}

if (acao == "iniciarContinuo") {
  startTime = millis();
  estadoAtualAnterior = CONTINUO_EM_EXECUCAO;
  estadoAtual = AUTOMATICO_EM_EXECUCAO;
  server.send(200, "text/plain", "Modo contínuo iniciado");
  return;
}

if (acao == "pararContinuo") {
  estadoAtualAnterior = MANUAL;
  estadoAtual = MANUAL;
  desligarTodosAtuadores();
  server.send(200, "text/plain", "Modo contínuo interrompido");
  return;
}



    if (acao == "ligarEsteira") {
      digitalWrite(PINO_ESTEIRA, HIGH);
      server.send(200, "text/plain", "Esteira ligada");
    } else if (acao == "desligarEsteira") {
      digitalWrite(PINO_ESTEIRA, LOW);
      server.send(200, "text/plain", "Esteira desligada");
    }

    if (acao == "ligarSeparador") {
      digitalWrite(PINO_SEPARADOR, HIGH);
      server.send(200, "text/plain", "Separador ligado");
    } else if (acao == "desligarSeparador") {
      digitalWrite(PINO_SEPARADOR, LOW);
      server.send(200, "text/plain", "Separador desligado");
    }

    if (acao == "ligarTrava") {
      digitalWrite(PINO_TRAVA, HIGH);
      server.send(200, "text/plain", "Trava ligada");
    } else if (acao == "desligarTrava") {
      digitalWrite(PINO_TRAVA, LOW);
      server.send(200, "text/plain", "Trava desligada");
    }

    if (acao == "ligarMedidor") {
      digitalWrite(PINO_MEDIDOR, HIGH);
      server.send(200, "text/plain", "Medidor ligado");
    } else if (acao == "desligarMedidor") {
      digitalWrite(PINO_MEDIDOR, LOW);
      server.send(200, "text/plain", "Medidor desligado");
    }

    if (acao == "ligarMagazine") {
      digitalWrite(PINO_MAGAZINE, HIGH);
      server.send(200, "text/plain", "Magazine ligado");
    } else if (acao == "desligarMagazine") {
      digitalWrite(PINO_MAGAZINE, LOW);
      server.send(200, "text/plain", "Magazine desligado");
    }
  });

  server.begin();
}
