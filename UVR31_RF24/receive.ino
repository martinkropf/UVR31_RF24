/*  
 ~~~~~~~~~~
 UVR31_RF24
 ~~~~~~~~~~
 Martin Kropf 2015 
 
 receive.ino:
 Receive and save data frames
 
 */

namespace Receive {

  void start() {
    pulse_count = got_first = last_bit_change = 0;
    receiving = true;
    Serial.print("\nReceiving ... ");
    // on a CHANGE on the data pin pin_changed is called
    attachInterrupt(interrupt, pin_changed, CHANGE);
  }

  void stop() {
    detachInterrupt(interrupt);
    Serial.print("\nReceived. ");
    receiving = false;
  }

  void pin_changed() {
    byte val = digitalRead(dataPin); // read state
    unsigned long time_diff = micros() - last_bit_change;
    last_bit_change = micros();
    // singe pulse width?
    if (time_diff >= low_width && time_diff <= high_width) {
      process_bit(val);
      return;   
    }
    // double pulse width?
    if (time_diff >= double_low_width && time_diff <= double_high_width) {
      process_bit(!val);
      process_bit(val);
      return;   
    } 
  }

  void process_bit(byte b) {
    // ignore first pulse
    pulse_count++;
    if (pulse_count % 2)
      return;

    if (b)
      Process::data_bits[BIT_COUNT / 8] |= 1 << BIT_COUNT % 8; // set bit
    else
      Process::data_bits[BIT_COUNT / 8] &= ~(1 << BIT_COUNT % 8);  // clear bit

    if (BIT_COUNT == 192)
      stop(); // stop receiving when data frame is complete
  }

}



