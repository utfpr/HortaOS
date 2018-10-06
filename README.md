For English, please click [HERE](https://github.com/utfpr/HortaOS/blob/master/README_EN.md) or read the README_EN.md file!

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
7. Regulador de tensão L7805CV
8. Fonte 12v
9. Resistor 220Ω
10. 2 Cotovelos de cano 3/4" para mangueira
12. Luva 3/4" com rosca
13. Conta no ThingSpeak
14. Arquivo ```Modelo 3D.obj``` impresso

## Esquema para montagem
Para realizar a montagem do controlador, você deverá seguir o esquema abaixo. Caso prefira, o projeto do Fritzing também está disponível para download neste repositório.

![Screenshot](https://raw.githubusercontent.com/utfpr/HortaOS/master/Images/scheme.jpg)

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

1. ```SSID_WIFI```
2. ```PSWD_WIFI```
3. ```WriteKey```

**SSID_WIFI:** é a variável que armazena o nome da rede Wifi que o NodeMCU vai se conectar

**PSWD_WIFI:** é a variável que armazena a senha da rede WIFI

**WriteKey:** Guarda a chave de escrita para o ThingSpeak

Após realizar essas alterações, você poderá enviar o arquivo ```HortaOS.ino``` para o Node MCU. 

## Montagem Final
Para montagem final, foi feito um molde 3D para impressão separados em dois modulos. Sendo um deles para o microcontrolador e o outro para parte onde será instalado o solenóide e o sensor de fluxo.
![Screenshot](https://raw.githubusercontent.com/utfpr/HortaOS/master/Images/box.png)

### Alimentação
Não pe possível alimentar o Node MCU com 12v diretos da fonte, então para isso, utilizamos o ```L7805CV``` para reduzir a alimentação da fonte para 5v.

![Screenshot](https://raw.githubusercontent.com/utfpr/HortaOS/master/Images/regulator.png)

Com isso, basta ligar os 5v no ```VIN``` do Node MCU e o negativo no ```GROUND```

### Montagem da parte hidraulica
Para montar esta parte, é necessário dos itens ```2```, ```3```, ```12``` e ```13```. Basta seguir o esquema de montagem da imagem abaixo

![Screenshot](https://raw.githubusercontent.com/utfpr/HortaOS/master/Images/diagram.jpg)
