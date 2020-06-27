# interface_ opdracht
De uitwerking van de Interface Opdracht voor WoR World van Hemmy en Jari.

## installatie
Om de software te bouwen:
* Clone de repository in CATKIN_WORKSPACE*/src
* Voer het commando "catkin_make" uit in CATKIN_WORKSPACE*
* Voer het command "source devel/setup.bash" uit om de applicatie vindbaar te maken voor ROS

## Kalibratie
Het systeem heeft een kalibratiebestand (RobotLDOffsets.h) waarbij de verschillende offsets per servo kan worden gezet. De offsets kan waarden hebben tussen de -100 en 100 dat staat gelijk aan 15 graden. De applicatie moet wel opnieuw gecompileerd worden om de kalibratie effect te laten hebben.

## Uitvoeren van demo
Voor het uitvoeren van de demo moeten er drie terminals opgestart worden en in de root van de CATKIN_WORKSPACE bevinden. Om er zeker van te zijn dat de applicatie gevonden kan worden moet het commando 'source devel/setup.bash' uitgevoerd worden in alle terminals. 

### Terminal een (ros)
Voer het command 'roscore' uit.

### Terminal twee (de interface)
Voer het command 'rosrun interface_opdracht robot_interface' uit.

### Terminal drie (demo)
Voer het command 'rosrun interface_opdracht robot_interface_client' uit. Hierop word de robotarm naar de rechtopstaandpositie gestuurd en daarna naar de readypositie. De demo gaat nu verder op de terminalscherm.  