
// Example for demonstrating the TSL2561 library - public domain!

// connect SCL to analog 5
// connect SDA to analog 4
// connect VDD to 3.3V DC
// connect GROUND to common ground
// ADDR can be connected to ground, or vdd or left floating to change the i2c address


void read_tsl2561() {
  // Simple data read example. Just read the infrared, fullspecrtrum diode 
  // or 'visible' (difference between the two) channels.
  // This can take 13-402 milliseconds! Uncomment whichever of the following you want to read
  uint16_t x = tsl.getLuminosity(TSL2561_VISIBLE);     
  //uint16_t x = tsl.getLuminosity(TSL2561_FULLSPECTRUM);
  //uint16_t x = tsl.getLuminosity(TSL2561_INFRARED);
  
  //Serial.println(x, DEC);

  // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
  // That way you can do whatever math and comparisons you want!
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  Serial.print("infrared.$$$.tsl2561 "); Serial.println(ir);
  Serial.print("luminosity-full.$$$.tsl2561 "); Serial.println(full);
  Serial.print("luminosity-visible.$$$.tsl2561 "); Serial.println(full - ir);
  Serial.print("luminosity-lux.$$$.tsl2561 "); Serial.println(tsl.calculateLux(full, ir));
}
