//22 may 2017 t czerwonka tczerwonka@gmail.com
//test code for piaq board
//sensors:



//MICS4514

//generic
#include <Wire.h>

#define LED_PIN 9
#define CTRL(x) ('x' & 0x1F)


#include "TSL2561.h"


#include "Adafruit_SHT31.h"
Adafruit_SHT31 sht31 = Adafruit_SHT31();

#include <Adafruit_MPL3115A2.h>
// Power by connecting Vin to 3-5V, GND to GND
// Uses I2C - connect SCL to the SCL pin, SDA to SDA pin
// See the Wire tutorial for pinouts for each Arduino
// http://arduino.cc/en/reference/wire
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();


//Register addresses for CCS811
#define CSS811_STATUS 0x00
#define CSS811_MEAS_MODE 0x01
#define CSS811_ALG_RESULT_DATA 0x02
#define CSS811_RAW_DATA 0x03
#define CSS811_ENV_DATA 0x05
#define CSS811_NTC 0x06
#define CSS811_THRESHOLDS 0x10
#define CSS811_BASELINE 0x11
#define CSS811_HW_ID 0x20
#define CSS811_HW_VERSION 0x21
#define CSS811_FW_BOOT_VERSION 0x23
#define CSS811_FW_APP_VERSION 0x24
#define CSS811_ERROR_ID 0xE0
#define CSS811_APP_START 0xF4
#define CSS811_SW_RESET 0xFF
//These are the air quality values obtained from the sensor
unsigned int tVOC = 0;
unsigned int CO2 = 0;
#define CCS811_ADDR 0x5B //7-bit unshifted default I2C Address
#define WAKE 8 //!Wake on breakout connected to pin 5 on Arduino -- was 13 but not used on this board



// The address will be different depending on whether you let
// the ADDR pin float (addr 0x39), or tie it to ground or vcc. In those cases
// use TSL2561_ADDR_LOW (0x29) or TSL2561_ADDR_HIGH (0x49) respectively
TSL2561 tsl(TSL2561_ADDR_FLOAT);




//MICS4514 stuff
#define PRE_PIN          3 //actually pin 1 on the ATMEGA
#define VNOX_PIN         A1
#define VRED_PIN         A2
#define PRE_HEAT_SECONDS 10
int vnox_value = 0;
int vred_value = 0;



////////////////////////////////////////////////////////////////////////////////
// setup
////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println("#iaq code version_3");
  Serial.println("#T Czerwonka 22 may 2017");

  pinMode(LED_PIN, OUTPUT);


  ////////////////////
  //ccs811 init
  ////////////////////
  pinMode(WAKE, OUTPUT);
  digitalWrite(WAKE, LOW);
  configureCCS811(); //Turn on sensor
  unsigned int result = getBaseline();
  //Serial.print("baseline for this sensor: 0x");
  //if(result < 0x100) Serial.print("0");
  //if(result < 0x10) Serial.print("0");
  //Serial.println(result, HEX);


  ////////////////////
  //TSL2561 init
  ////////////////////
  if (tsl.begin()) {
    Serial.println("#TSL2561 found.");
  } else {
    Serial.println("#TSL2561 not found");
  }


  // You can change the gain on the fly, to adapt to brighter/dimmer light situations
  //tsl.setGain(TSL2561_GAIN_0X);         // set no gain (for bright situtations)
  tsl.setGain(TSL2561_GAIN_16X);          // set 16x gain (for dim situations)
  // Changing the integration time gives you a longer time over which to sense light
  // longer timelines are slower, but are good in very low light situtations!
  //tsl.setTiming(TSL2561_INTEGRATIONTIME_13MS);      // shortest integration time (bright light)
  tsl.setTiming(TSL2561_INTEGRATIONTIME_101MS);   // medium integration time (medium light)
  //tsl.setTiming(TSL2561_INTEGRATIONTIME_402MS);   // longest integration time (dim light)

    


  ////////////////////
  //SHT31 init
  ////////////////////
  Serial.println("#SHT31 init");
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("#Couldn't find SHT31");
    //while (1) delay(1);
  }




  ////////////////////
  //mics4514 init
  ////////////////////
  // Setup preheater pin
  pinMode(PRE_PIN, OUTPUT);
  // Wait for preheating
  Serial.println("#MICS4514 10 second preheat");
  digitalWrite(PRE_PIN, 1);
  delay(PRE_HEAT_SECONDS * 1000);
  digitalWrite(PRE_PIN, 0);
  Serial.println("#MICS4514 preheat done");
 
  

  Serial.println("#####");

}



////////////////////////////////////////////////////////////////////////////////
// loop
////////////////////////////////////////////////////////////////////////////////
void loop() {


  digitalWrite(LED_PIN, HIGH);
  read_ccs811();      //CO2 and VOCs
  read_sht31();       //temp and humidity
  read_tsl2561();     //light
  read_mpl3115a2();   //pressure
  read_mics4514();
  digitalWrite(LED_PIN, LOW);
  Serial.print((char)CTRL(D));
  Serial.println("#####");
  delay(1000);
}






////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
