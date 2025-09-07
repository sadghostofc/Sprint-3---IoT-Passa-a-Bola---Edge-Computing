
# 🏐 Passa a Bola - Bola Inteligente 

Este projeto apresenta a primeira versão da arquitetura IoT para o desafio Passa a Bola, utilizando um ESP32 simulado no Wokwi, sensores virtuais e uma aplicação web para monitorar dados em tempo real.

A ideia é transformar a bola em um dispositivo inteligente capaz de enviar informações de passes, velocidade e distância percorrida para a nuvem, possibilitando análise e automação.



## 🚀 Funcionalidades

- Contagem de passes (via botão físico).
- Velocidade da bola (simulada com MPU6050 + potenciômetro).
- Distância percorrida (estimada a partir da velocidade).
- Envio de dados para um broker MQTT público (HiveMQ).
- Visualização em tempo real em um site (HTML + MQTT.js).


## 🛠️ Componentes (Simulação no Wokwi)

- ESP32 DevKit V1
- MPU6050 (Acelerômetro + Giroscópio) – simula aceleração/velocidade
- Potenciômetro (10kΩ) – ajusta a escala de velocidade
- Push Button (Botão) – cada clique representa um passe
- Fios virtuais (para conexões no Wokwi)
## ⚡ Arquitetura do Sistema

1. **ESP32 + Sensores (Wokwi)** → coleta e simula dados da bola.  
2. **MQTT (HiveMQ Broker Público)** → recebe mensagens JSON.  
3. **Aplicação Web (index.html)** → se conecta ao broker e mostra os dados em tempo real (passes, velocidade e distância).  
## ▶️ Como Executar

🔗 Abra a Simulação no Wokwi: [https://wokwi.com/projects/441397443781866497] 

1. Clique em **Start Simulation**.  
2. Abra o arquivo `index.html` no navegador ou o link do site no GitHub pages: [https://sadghostofc.github.io/Sprint-3---IoT-Passa-a-Bola---Edge-Computing/] 
3. Veja os dados em tempo real:  
   - **Passes** → cada clique no botão físico.  
   - **Velocidade** → ajustada pelo MPU6050 + potenciômetro.  
   - **Distância** → calculada automaticamente.

## 👨‍💻 Integrantes

* Daniel Laureano da Luz - RM565899
* Gabriel Del Sole Speck - RM562513
* Marcos Antonio da Silva - RM566451
* Paulo Gustavo Pessoa da Silva - RM566194
* Rone Cruz Santos - RM566558
