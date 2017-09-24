/**************************************************************************/
/*!
    @file     Adafruit_MPL3115A2.cpp
    @author   K.Townsend (Adafruit Industries)
    @license  BSD (see license.txt)

    Example for the MPL3115A2 barometric pressure sensor

    This is a library for the Adafruit MPL3115A2 breakout
    ----> https://www.adafruit.com/products/1893

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!

    @section  HISTORY

    v1.0 - First release
*/
/**************************************************************************/




void read_mpl3115a2() {
  if (! baro.begin()) {
    Serial.println("Couldnt find mpl3115a2 sensor");
    return;
  }
  
  float pascals = baro.getPressure();
  // Our weather page presents pressure in Inches (Hg)
  // Use http://www.onlineconversion.com/pressure.htm for other units
  Serial.print("pressure.$$$.mpl3115a2 ");
  Serial.println(pascals/100.00); 

  Serial.print("inHg.$$$.mpl3115a2 ");
  Serial.println(pascals/3377); 

  //not too useful on an iaq device
  //float altm = baro.getAltitude();
  //Serial.print("meters.$$$.mpl3115a2 ");
  //Serial.println(altm);

  float tempC = baro.getTemperature();
  Serial.print("temperature.$$$.mpl3115a2 ");
  Serial.println((1.8*tempC)+32.0);

  //delay(250);
}
