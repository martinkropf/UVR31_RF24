#!/usr/bin/python
#  NRF24L01/RPi Model B+ connections:-
#  -----------------------------------
#   NRF24      RPi- pin
#   1 GND      GND
#   2 3.3v   1 3.3v
#   3 CE      22 GPIO25
#   4 CSN      24 CE0_0
#   5 SCK      23 SCLK_0
#   6 MOSI   19 MOSI_0
#   7 MISO   21 MISO_0
#   8 N/C
#  -----------------------------------

from RF24 import *
import requests

OPENHAB_URL="http://10.0.0.50:8080/rest/items/"
EMONCMS_URL="http://10.0.0.50/emoncms/input/post.json?node=";
EMONCMS_APIKEY="INSERT_API_KEY_HERE"
PIPE = [0x4e32525655]#UVR2NRF24
SOLAR_INPUT_NODE="0"

try:
    radio = RF24(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ)
    radio.begin()
    radio.setRetries(5,15)
    radio.setAutoAck(1)
    radio.openReadingPipe(1,PIPE[0])
    radio.startListening()
    radio.printDetails()
    while True:
        if radio.available():
            while radio.available():
                len = radio.getDynamicPayloadSize()
                receive_payload = radio.read(len)
                counter  = receive_payload.split('\x00')[0]
                if '&' in counter:
                    splitted = counter.split('&')
                    s1 = float(splitted[0])/10
                    s2 = float(splitted[1])/10
                    s3 = float(splitted[2])/10
                    state = splitted[3]
                    print s1,s2,s3,state
                    
                    s1_openhab_url = OPENHAB_URL + "Temperature_S1/state"
                    s2_openhab_url = OPENHAB_URL + "Temperature_S2/state"
                    s3_openhab_url = OPENHAB_URL + "Temperature_S3/state"
                    state_openhab_url = OPENHAB_URL + "Solar_Status/state"
                    
                    r = requests.put(s1_openhab_url, data=str(s1), headers={'content-type': 'text/plain'})
                    r = requests.put(s2_openhab_url, data=str(s2), headers={'content-type': 'text/plain'})
                    r = requests.put(s3_openhab_url, data=str(s3), headers={'content-type': 'text/plain'})
                    r = requests.put(state_openhab_url, data=str(state), headers={'content-type': 'text/plain'})
                    
                    solar = str(s1)+","+str(s2)+","+str(s3)+","+state
                    solar_input_url = EMONCMS_URL  + "&node=" + SOLAR_INPUT_NODE + "&csv="+  solar + "&apikey="+EMONCMS_APIKEY
                    r = requests.get(solar_input_url)

except KeyboardInterrupt:
    print "\n Program stopped \n"
