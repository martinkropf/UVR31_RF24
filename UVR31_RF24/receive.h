/*  
 ~~~~~~~~~~
 UVR31_RF24
 ~~~~~~~~~~
 Martin Kropf 2015 
 
 receive.h:
 Receive and save data frames by the heating control
 
 */

namespace Receive {
  
  // Decoding the manchester code of UVR31
  // pulse width at 50hz: 1000ms/50 = 20ms = 20000µs
  // 20000µs / 2 = 10000µs (2 pulses for one bit)

  const unsigned long pulse_width = 10000; //µs
  const int percentage_variance = 3; // % tolerance for variances at the pulse width
  // 1001 or 0110 are two sequential pulses without transition
  const unsigned long double_pulse_width = pulse_width * 2;
  // calculating the tolerance limits for variances
  const unsigned long low_width = pulse_width - (pulse_width *  percentage_variance / 100);
  const unsigned long high_width = pulse_width + (pulse_width * percentage_variance / 100);
  const unsigned long double_low_width = double_pulse_width - (pulse_width * percentage_variance / 100);
  const unsigned long double_high_width = double_pulse_width + (pulse_width * percentage_variance / 100);
  boolean got_first = 0;  // first or second pulse for one bit?
  unsigned long last_bit_change = 0;  // remember the last transition
  int pulse_count; // number of received pulses
#define BIT_COUNT (pulse_count / 2)
  byte receiving;  // currently receiving?
  void start();// start receiving
  void stop(); // stop receiving
  void pin_changed(); // is called when the state of the data pin changes
  void process_bit(unsigned char b); // saves a bit detected by pin_changed

}



