/*  
 ~~~~~~~~~~
 UVR31_RF24
 ~~~~~~~~~~
 Martin Kropf 2015 
 
 process.h:
 Processing of saved data frames
 
 */

namespace Process {
  // one data frame has 8 data bytes + SYNC, so 8 * (8+1+1) + 16 = 96
  // 96 * 2 = 192 (twice as much as a data frame is saved
  // so there's one complete data frame
  const int bit_number = (8 * (8 + 1 + 1) + 16) * 2 ;
  byte data_bits[bit_number / 8 + 1]; // every bit gets sorted into a bitmap
  int start_bit;  // first bit of data frame
  
  // sensor types
//#define UNUSED      0b000
//#define DIGITAL     0b001
//#define TEMP        0b010
//#define VOLUME_FLOW 0b011
//#define RAYS        0b110
//#define ROOM   0b111


  // sensor
  typedef struct {
    byte number;
    byte type;
    byte mode;
    boolean invalid;
    float value;
  }
  sensor_t;
  sensor_t sensor;
  boolean output;


  // Datenrahmen
  // data frame
  void start(); // Datenrahmen auswerten
  boolean prepare(); // Datenrahmen vorbereiten
  int analyze(); // Datenrahmen analysieren
  void invert(); // Datenrahmen invertieren
  byte read_bit(int pos); // aus Bitmap lesen // read from bitmap
  void write_bit(int pos, byte set); // Bitmap beschreiben // write to bitmap
  void trim(); // Datenrahmen in Bitmap schreiben // remove start and stop bits
  boolean check_device(); // Datenrahmen überprüfen // verify data frame

  // Informationen auslesen
  // readout information
  void fetch_sensor(int sensor); // Sensor
  void fetch_output(); // State


}



