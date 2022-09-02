

void printTemperature(DeviceAddress deviceAddress)
{
  sensors.requestTemperatures();
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC != -127.00) {
    Serial.print("temperature.$$$.onewire0C "); 
    Serial.println(tempC);
    Serial.print("temperature.$$$.onewire0F "); 
    Serial.println(DallasTemperature::toFahrenheit(tempC));
  }
}
  
