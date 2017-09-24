//swiped from here https://github.com/ShawnHymel/MICS-4514_CO_and_NOx_Sensor_Breakout


void read_mics4514() {
  
  // Read analog values, print them out, and wait
  vnox_value = analogRead(VNOX_PIN);
  vred_value = analogRead(VRED_PIN);
  Serial.print("Vnox.$$$.MICS4514 ");
  Serial.println(vnox_value, DEC);
  Serial.print("Vred.$$$.MICS4514 ");
  Serial.println(vred_value, DEC);
  //delay(1000);
}
