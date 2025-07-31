#ifndef PAGINA_WEB_H
#define PAGINA_WEB_H

const char *htmlPage = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
  <title>Controle da Máquina</title>
  <style>
    :root {
      --azul: #007bff;
      --azul-hover: #0056b3;
      --fundo: #f2f4f8;
      --texto: #2c3e50;
      --cinza-claro: #dfe6e9;
      --borda: #bdc3c7;
    }

    body {
      margin: 0;
      font-family: 'Segoe UI', sans-serif;
      background-color: var(--fundo);
      color: var(--texto);
      display: flex;
      flex-direction: column;
      align-items: center;
      padding: 20px;
      padding-bottom: 80px;
    }

    h1 {
      margin-top: 20px;
      color: var(--azul);
      font-size: 2.2em;
    }

    h2 {
      margin-top: 40px;
      color: #444;
      font-size: 1.4em;
      border-bottom: 2px solid var(--azul);
      padding-bottom: 5px;
      width: 90%;
      max-width: 500px;
      text-align: left;
    }

    .grid {
      display: grid;
      grid-template-columns: repeat(auto-fill, minmax(180px, 1fr));
      gap: 15px;
      width: 100%;
      max-width: 600px;
      margin-top: 20px;
    }

    button {
      background-color: var(--azul);
      color: white;
      border: none;
      padding: 14px;
      border-radius: 10px;
      font-size: 16px;
      transition: 0.3s ease;
      box-shadow: 0 4px 6px rgba(0,0,0,0.1);
      cursor: pointer;
    }

    button:hover {
      background-color: var(--azul-hover);
    }

    #status {
      margin-top: 30px;
      font-weight: bold;
      font-size: 1.1em;
      color: #555;
      background-color: var(--cinza-claro);
      padding: 10px 20px;
      border-radius: 8px;
      border: 1px solid var(--borda);
    }

    footer {
  width: 100%;
  background-color: #333;
  color: #fff;
  text-align: center;
  padding: 15px 0;
  position: fixed;
  bottom: 0;
  left: 0;
  font-size: 14px;
  font-weight: 400;
  box-shadow: 0 -2px 6px rgba(0,0,0,0.2);
}

footer p {
  margin: 0;
}

    @media(max-width: 500px) {
      h1 { font-size: 1.7em; }
      button { font-size: 15px; padding: 12px; }
    }
  </style>
</head>
<body>
  <h1>Controle da Máquina</h1>

  <h2>Processo Automático</h2>
  <div class="grid">
    <button onclick="enviarComando('ligarProcesso')">▶ Iniciar Processo Automático</button>
  </div>

  <h2>Etapas Individuais</h2>
  <div class="grid">
    <button onclick="enviarComando('ligarTrava')">1️⃣ Ativar Pino/Trava</button>
    <button onclick="enviarComando('ligarEsteira')">2️⃣ Ligar Esteira</button>
    <button onclick="enviarComando('ligarSeparador')">3️⃣ Ativar Separador</button>
    <button onclick="enviarComando('ligarMagazine')">4️⃣ Ativar Magazine</button>
    <button onclick="enviarComando('ligarMedidor')">5️⃣ Ligar Medidor</button>
  </div>

  <h2>Desligar Dispositivos</h2>
  <div class="grid">
    <button onclick="enviarComando('desligarTrava')">Desativar Trava</button>
    <button onclick="enviarComando('desligarEsteira')">Desligar Esteira</button>
    <button onclick="enviarComando('desligarSeparador')">Desligar Separador</button>
    <button onclick="enviarComando('desligarMagazine')">Desativar Magazine</button>
    <button onclick="enviarComando('desligarMedidor')">Desligar Medidor</button>
  </div>

  <h2>Tempo decorrido</h2>
<p id="tempoDecorrido">0s</p>

<h2>Contador de Peça</h2>
<p>Peças metálicas</p> <p id="contadorMetal"></p>
<p>Peças não metálicas</p> <p id="contadorPlastico"></p>


  <p id="status">Aguardando comandos...</p>

<footer>
  <p>Desenvolvido por Gustavo Chimello, Lucas Miyaki & Olavo Xavier</p>
</footer>

  <script>
    function enviarComando(cmd) {
      fetch("/comando?acao=" + cmd)
        .then(response => response.text())
        .then(data => document.getElementById("status").innerText = data)
        .catch(() => document.getElementById("status").innerText = "Erro ao enviar comando.");
    }

    function atualizarTempo() {
  fetch("/tempo")
    .then(response => response.text())
    .then(data => {
      document.getElementById("tempoDecorrido").innerText = data + " segundos";
    })
    .catch(() => {
      document.getElementById("tempoDecorrido").innerText = "Erro ao obter tempo";
    });
}

function atualizarContadores() {
    fetch("/contador")
      .then(response => response.json())
      .then(data => {
        document.getElementById("contadorMetal").innerText = data.metal;
        document.getElementById("contadorPlastico").innerText = data.plastico;
      })
      .catch(() => {
        document.getElementById("contadorMetal").innerText = "Erro";
        document.getElementById("contadorPlastico").innerText = "Erro";
      });
}

// Atualiza o tempo a cada 1 segundo
setInterval(() => {
    atualizarTempo();
    atualizarContadores();
}, 1000);

  </script>
</body>
</html>
)rawliteral";

#endif