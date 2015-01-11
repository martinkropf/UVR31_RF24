/*  
 ~~~~~~~~~~
 UVR31_RF24
 ~~~~~~~~~~
 Martin Kropf 2015 
 
 process.ino:
 Processing of saved data frames
 
 */

namespace Process {

  void start() {
    // prepare data frame
    if (prepare()) {
      // either dump via serial or web upload
#ifdef DEBUG
      if (Dump::active)
        Dump::start();
#else
      NRF24::upload();
#endif
    } else
      Serial.print("Data frame damaged.");
  }
  
  
  
  boolean prepare() {
    start_bit = analyze();  // find the start of data frame
    // inverted signal?
    if (start_bit == -1) {
      invert();  // invert again
      start_bit = analyze();
    }
    trim(); // remove start and stop bits
    return check_device(); 
  } 

  int analyze() {
    byte sync;
    // find SYNC (16 * sequential 1)
    for (int i = 0; i < bit_number; i++) {
      if (read_bit(i))
        sync++;
      else
        sync = 0;
      if (sync == 16) {
       // find first 0
        while (read_bit(i) == 1)
          i++;
        return i;  // beginning of data frame
      }
    }
    return -1; // no data frame available. check signal?
  }

  void invert() {
    for (int i = 0; i < read_bit(i); i++)
      write_bit(i, read_bit(i) ? 0 : 1);  // invert every bit
  }

  byte read_bit(int pos) {
    int row = pos / 8;  // detect position in bitmap
    int col = pos % 8;
    return (((data_bits[row]) >> (col)) & 0x01);  // return bit
  }
  
  void write_bit(int pos, byte set) {
    int row = pos / 8;  // detect position in bitmap
    int col = pos % 8;
    if (set)
      data_bits[row] |= 1 << col; // set bit
    else
      data_bits[row] &= ~(1 << col);  // clear bit
  }

  void trim() {    
    for (int i = start_bit, bit = 0; i < bit_number; i++) {
      int offset = i - start_bit;
      // ignore start and stop bits:
      // start bits: 0 10 20 30, also  x    % 10 == 0
      // stop bits:  9 19 29 39, also (x+1) % 10 == 0
      if (offset % 10 && (offset + 1) % 10) {
        write_bit(bit, read_bit(i));
        bit++;
      }
    }
  }

  boolean check_device() {
    // data frame of UVR31
    if (data_bits[0] == 0x30 && data_bits[8]==0xFF)
      return true;
    else
      return false;
  }

 

  void fetch_sensor(int number) {
    sensor.number = number;
    sensor.invalid = false;
    sensor.mode = -1;
    float value;
    number = -1 + number * 2; // sensor 1 is on byte 8 and 9
    byte sensor_low = data_bits[number];
    byte sensor_high = data_bits[number + 1];
    number = sensor_high << 8 | sensor_low;
    sensor.type = (number & 0x7000) >> 12;
    if (!(number & 0x8000)) { // sign positive
      number &= 0xfff;
      value = number * 0.1;      
    } 
    else { // sign negative
      number |= 0xf000;
      value = (number - 65536) * 0.1;
    }
    sensor.value = value;
  }

  void fetch_output() {
    if (data_bits[7]==0)
      output=0;
    else
      output=1;
  }

}



