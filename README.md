# Controlador Automático Para Horta Comunitária
Controlador automático baseado em um controlador Node MCU que controla a irrigação baseado na umidade do solo que registra os logs de umidade, fluxo de água, e temperatura do solo na plataforma ThingSpeak. Desenvolvido pela Universidade Tecnológica Federal do Paraná, Campus Campo Mourão, sob supervisão do Professor Ivanilton Polato.

## Itens Necessários
Para montar este controlador, você vai precisar dos seguintes items:
1. Node MCU
2. Válvula Solenóide
3. Sensor de Fluxo
4. Sensor de umidade do solo
5. Sensor de temperatura DS18B20
6. Módulo Relé 5v
7. Fonte 12v
8. Resistor 220Ω
9. Conta no ThingSpeak

## Esquema para montagem
Para realizar a montagem do controlador, você deverá seguir o esquema abaixo. Caso prefira, o projeto do fritzing também está disponível para download neste repositório.

![Screenshot](https://raw.githubusercontent.com/WillianRod/Controlador-Autom-tico-Para-Horta-Comunit-ria/master/Esquema%20de%20montagem.jpg)

## Configuração da IDE do Arduino para o NodeMCU
Entre na IDE do Arduino e clicar em **Arquivo -> Preferências**:

![Screenshot](https://www.filipeflop.com/wp-content/uploads/2016/05/IDE-Arquivo.png)

Na tela seguinte, digite o link abaixo no campo URLs adicionais de Gerenciadores de Placas:

http://arduino.esp8266.com/stable/package_esp8266com_index.json

A sua tela ficará assim:

![Screenshot](https://www.filipeflop.com/wp-content/uploads/2016/05/IDE-Preferencias.png)

Clique em OK para retornar à tela principal da IDE

Agora clique em Ferramentas -> Placa -> Gerenciador de Placas:

![Screenshot](https://www.filipeflop.com/wp-content/uploads/2016/05/IDE-Menu-Ferramentas-Placa.png)

Utilize a barra de rolagem para encontrar o esp8266 by ESP8266 Community e clique em INSTALAR

![Screenshot](https://www.filipeflop.com/wp-content/uploads/2016/05/IDE-Gerenciador-de-placas.png)

Após alguns minutos as placas da linha ESP8266 já estarão disponíveis na lista de placas da IDE do Arduino.

(Tutorial por [FilipeFlop](https://www.filipeflop.com/blog/programar-nodemcu-com-ide-arduino/))

## Upload do código
Após realizar o passo anterior, você deverá alterar algumas variáveis. São elas:

1. SSID_WIFI
2. PSWD_WIFI
3. WriteKey

**SSID_WIFI:** é a variável que armazena o nome da rede Wifi que o NodeMCU vai se conectar
**PSWD_WIFI:** é a variável que armazena a senha da rede WIFI
**WriteKey:** Guarda a chave de escrita para o ThingSpeak

Após realizar essas alterações, você poderá enviar o arquivo ```HortaOS.ino``` para o Node MCU. 

## Montagem Final
Para montagem final, foi feito um molde 3D para impressão, onde colocaremos o nosso projeto dentro.
![Screenshot](https://raw.githubusercontent.com/WillianRod/Controlador-Autom-tico-Para-Horta-Comunit-ria/master/Caixa%203D.png)
Para ver/editar o projeto, acesse o modelo no [TinkerCad](https://www.tinkercad.com/things/bN6BkPSU1yL-caixa-horta).
