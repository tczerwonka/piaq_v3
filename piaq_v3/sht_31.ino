/*************************************************** 
  This is an example for the SHT31-D Humidity & Temp Sensor

  Designed specifically to work with the SHT31-D sensor from Adafruit
  ----> https://www.adafruit.com/products/2857

  These sensors use I2C to communicate, 2 pins are required to  
  interface
 ****************************************************/
 





int read_sht31() {
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  if (! isnan(t)) {  // check if 'is not a number'
    Serial.print("temperature.$$$.sht31 "); 
    Serial.println((1.8*t)+32.0);
    Serial.print("dewpoint.$$$.sht31 ");
    Serial.println((1.8*dewPoint(t, h))+32.0);
    //Serial.println(t);
  } else { 
    //Serial.println("Failed to read temperature");
  }
  
  if (! isnan(h)) {  // check if 'is not a number'
    Serial.print("humidity.$$$.sht31 "); Serial.println(h);
  } else { 
    //Serial.println("Failed to read humidity");
  }

  
  //Serial.println();
  //delay(1000);
  return t;
}



// dewPoint function NOAA
// reference: http://wahiduddin.net/calc/density_algorithms.htm 
double dewPoint(double celsius, double humidity)
{
        double A0= 373.15/(273.15 + celsius);
        double SUM = -7.90298 * (A0-1);
        SUM += 5.02808 * log10(A0);
        SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
        SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
        SUM += log10(1013.246);
        double VP = pow(10, SUM-3) * humidity;
        double T = log(VP/0.61078);   // temp var
        return (241.88 * T) / (17.558-T);
}
