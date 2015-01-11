# UVR31_RF24
This project reads out Technische Alternative (TA) solar heating control UVR31. Readings are then send via a nrf24l01+ radio module to a python script, which runs on a Raspberry Pi in my setup.
The signal proecessing part of the sketch is based on Elias Kuiter's project uvr2web (https://github.com/ekuiter/uvr2web), who reads out a similiar solar heating control (UVR1611) from TA.

