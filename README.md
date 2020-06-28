# Interface_ opdracht
De uitwerking van de Interface Opdracht voor WoR World van Hemmy en Jari.

# **BELANGRIJK PORTNAAM (PORTNAME)**
**Zet de juiste usb-poortnaam van de robot in de document "RobotLD.cpp" op regel 9.**

## Simulatie usb poort (optioneel)


### Terminal 1: Aanmaken van de poorten
Voer het command "**socat -d -d pty,echo=0,raw,b115200,parenb=0,cs8,cstopb=0 pty,echo=0,raw,b115200,parenb=0,cs8,cstopb=0**" uit.

    2017/09/18 11:12:42 socat[3238] N PTY is /dev/pts/2
    2017/09/18 11:12:42 socat[3238] N PTY is /dev/pts/3
    2017/09/18 11:12:42 socat[3238] N starting data transfer loop with FDs [5,5] and [7,7]

**Let op cstopb setting is een bool:**
* 0 resulteert in één stopbit
* 1 resulteert in twee stopbits

## Terminal 2: Stuur de binnenkomende berichten naar de terminal
Voer het command "**cat < /dev/pts/2**" uit. Om de command berichten binnen te krijgen. **Zet de poortnaam dat onderaan staat in
"RobotLD.cpp" op regel 9**. ("/dev/pts/3")

## Installatie
Om de software te bouwen:
* Clone de repository in **CATKIN_WORKSPACE\*/src** of kopieer de package in de **CATKIN_WORKSPACE\*/src**-map.
* Voer het commando **"catkin_make"** uit in CATKIN_WORKSPACE*
* Voer het command "source devel/setup.bash" uit om de applicatie vindbaar te maken voor ROS

## Kalibratie (optioneel)
Het systeem heeft een kalibratiebestand (RobotLDOffsets.h) waarbij de verschillende offsets per servo kan worden gezet. De offsets kan waarden hebben tussen de -100 en 100 dat staat gelijk aan 15 graden. De applicatie moet wel opnieuw gecompileerd worden om de kalibratie effect te laten hebben.

## Uitvoeren van demo
Voor het uitvoeren van de demo moeten er nieuwe **drie** terminals opgestart worden en in de root van de **CATKIN_WORKSPACE** bevinden. Om er zeker van te zijn dat de applicatie gevonden kan worden moet het commando "**source devel/setup.bash**" uitgevoerd worden in alle terminals. 

### **Terminal 1 (ros)**
Voer het command "**roscore**" uit.

### **Terminal 2 (de interface)**
Voer het command "**rosrun interface_opdracht robot_interface**" uit.

### Terminal 3 (demo)
Voer het command "**rosrun interface_opdracht robot_interface_client**" uit. Hierop word de robotarm naar de rechtopstaandpositie gestuurd en daarna naar de readypositie. De demo gaat nu verder op de terminalscherm.  