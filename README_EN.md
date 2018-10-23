# Automatic Controller For Community Vegetable Garden

Automated system using a NodeMCU to control soil moisture and irrigation; it keeps logs of moisture, water flow usage, and soil temperature on the ThingSpeak platform. The system is designed to reuse rainwater from a cistern. Developed by Willian Barbosa Rodrigues, undergraduate student of the Federal Technological University - Paraná, Campus Campo Mourão, under the supervision of Professor Ivanilton Polato.

## Item list
To assembly this controller you need:
1. Node MCU
2. Solenoid Valve
3. Flow Sensor
4. Soil moisture sensor
5. Temperature Sensor DS18B20
6. Relay Module 5v
7. Voltage Regulator L7805CV
8. Power supply 12v
9. Resistance 220Ω
10. 2 3/4" pipe elbows for hose
12. 3/4" sleeve with thread
13. ThingSpeak Account
14. File ```3D Model.obj``` printed

## Schematic for mounting
To install the controller, you should follow use diagram below. The Fritzing project file is also available for download in this repository.

![Screenshot](https://raw.githubusercontent.com/utfpr/HortaOS/master/Images/scheme.jpg)

## Code Upload
Before upload your code to the NodeMCU, change the values for the following variables in the ```HortaOS.ino``` file:

1. ```SSID_WIFI```
2. ```PSWD_WIFI```
3. ```WriteKey```

**SSID_WIFI:** the Wi-Fi network SSID, which the NodeMCU will connect

**PSWD_WIFI:** the Wi-Fi password

**WriteKey:** the ThingSpeak key to write data

After these changes you can upload the file ```HortaOS.ino``` to the NodeMCU. 

## Final Assembly
To the final assembly we designed a 3D printed model. The model is separated in two parts: one holds the controller part; the other one holds the water control, including pipes and the solenoid valve.

![Screenshot](https://raw.githubusercontent.com/utfpr/HortaOS/master/Images/box.png)

### Power Supply
The NodeMCU uses 3,3 to 5V external power supply. To reuse the 12V power supply we assembled a voltage regulator using the ```L7805CV``` component.

![Screenshot](https://raw.githubusercontent.com/utfpr/HortaOS/master/Images/regulator.png)

### Hydraulic parts assembly

To assembly this component, you need the ```2```, ``` 3```, ```12``` and ``` 13``` items. Just follow the assembly schematics below.

![Screenshot](https://raw.githubusercontent.com/utfpr/HortaOS/master/Images/diagram.jpg)
