# UVR31_RF24
The Arduino sketch in this project reads out Technische Alternative (TA) solar heating control UVR31. 
Readings are then send via nrf24l01+ radio module to a Raspberry Pi in my setup, where a python script subsequently forwards the readings to OpenHab and emoncms. These web-applications provide persistence and visualization services and also provide access to the readings via mobile applications.
The signal processing part of the sketch is based on Elias Kuiter's project uvr2web (https://github.com/ekuiter/uvr2web), who works with a similiar TA solar heating control (UVR1611).

