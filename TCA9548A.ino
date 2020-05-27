
// TCA9548A I2C Switch Demo
// Using multiple PCF8574 GPIO expanders as I2C devices to control
//
// TCA9548 module I2C address:  0x70
// TCA9548 I2C channel 2 contains  PCF8574 address 0x20
// TCA9548 I2C channel 7 contains  PCF8574 address 0x20, 0x21
// 
// Gadget Reboot

#include <Wire.h>

#define addr1   0x20       // PCF8574 device 1 (I2C bus 1)
#define addr2   0x20       // PCF8574 device 2 (I2C bus 2)
#define addr3   0x21       // PCF8574 device 3 (I2C bus 2)

#define TCAADDR 0x70       // address of I2C switch module
#define bus1    2          // first  I2C bus channel (0..7)
#define bus2    7          // second I2C bus channel (0..7)

void setup() {

  // I2C init
  Wire.begin();

  // Turn off all leds on I2C expanders by writing all "1"
  tcaselect(bus1);               // enable I2C channel 
  sendbyte(addr1, 0xFF);         // send data to PCF8574 at addr1

  tcaselect(bus2);               // enable I2C channel
  sendbyte(addr2, 0xFF);         // send data to PCF8574 at addr2
  sendbyte(addr3, 0xFF);         // send data to PCF8574 at addr3
 
}

void loop() {

  // control LEDs on first I2C channel
  tcaselect(bus1);

  sendbyte(addr1, 0xFE);   // led bit 0 on
  delay(500);
  sendbyte(addr1, 0xFD);   // led bit 1 on
  delay(500);
  sendbyte(addr1, 0xFF);   // leds off

  // control LEDs on second I2C channel
  tcaselect(bus2);

  sendbyte(addr2, 0xFE);   // led bit 0 on
  delay(500);
  sendbyte(addr2, 0xFD);   // led bit 1 on
  delay(500);
  sendbyte(addr2, 0xFF);   // leds off

  sendbyte(addr3, 0xFE);   // led bit 0 on
  delay(500);
  sendbyte(addr3, 0xFD);   // led bit 1 on
  delay(500);
  sendbyte(addr3, 0xFF);   // leds off

}

// enable requested I2C channel (0..7)
void tcaselect(byte i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

// transmit a byte to the requested I2C address
void sendbyte(byte addr, byte data) {
  Wire.beginTransmission(addr);
  Wire.write(data);
  Wire.endTransmission();
}
