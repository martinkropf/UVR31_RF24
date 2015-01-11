# UVR31_RF24_
The arduino sketch in this project reads out a solar heating control UVR31 from Technische Alternative (TA). 
The signal proecessing part of the sketch is based on Elias Kuiter's project uvr2web (https://github.com/ekuiter/uvr2web), which reads out a similiar solar heating control (UVR1611) from TA.
Temperatures and the status of the pump are read out and send via an nrf24l01+ Radio Module to an receiver which could be for example, a Raspberry Pi.
The receiver part of the project is implemented in python and forwards the values via HTTP to two further applications (OpenHAB and emoncms) which are responsible for persistence and visualization.


