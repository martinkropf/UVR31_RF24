/*  
 ~~~~~~~~~~
 UVR31_RF24
 ~~~~~~~~~~
 Martin Kropf 2015 
 
 dump.ino:
 Ausgabe der Daten auf der seriellen Schnittstelle
 Data output via serial interface
 
 */

#ifdef DEBUG

namespace Dump {

  void start() {
     sensors();
  //  heat_meters();
  //  outputs();
  //  speed_steps();
  }



  void sensors() {
    Serial.println("Sensors:");
    for (int i = 1; i <= 3; i++) {
      Process::fetch_sensor(i);
      sensor();
    }
  }

  void sensor() {
    Serial.print("   Sensor ");
    Serial.print(Process::sensor.number);
    Serial.print(": ");
    if (Process::sensor.invalid)
      Serial.print("-");
    else
      Serial.print(Process::sensor.value);
    switch (Process::sensor.type) {
    case UNUSED:
      Serial.print(" (unused)");
      break;
    case DIGITAL:
      Serial.print(" (digital)");
      break;
    case TEMP:
      Serial.print(" ^C");
      break;
    case VOLUME_FLOW:
      Serial.print(" l/h volume flow");
      break;
    case RAYS:
      Serial.print(" W/m^2 rays");
      break;
    case ROOM:
      Serial.print(" ^C room ");
      switch (Process::sensor.mode) {
      case AUTO:
        Serial.print("automatic");
        break;
      case NORMAL:
        Serial.print("normal");
        break;
      case LOWER:
        Serial.print("lower");
        break;
      case STANDBY:
        Serial.print("standby");
        break;
      }
      break;
    }
    Serial.println();
  }
}

#endif



