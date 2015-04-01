/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  PWM test - this will drive 16 PWMs in a 'wave'

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define MAX_MILLIS_TO_WAIT 100  //or whatever

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

int count = 0;
int startTimeMs = 0;
byte readByte = 0x00;
byte receivedDataArray[] = {0x00,0x00,0x00,0x00,0x00};

int intensity;
int channel;

unsigned long starttime;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!

  pwm.begin();
  pwm.setPWMFreq(500);  // This is the maximum PWM frequency
    
  // save I2C bitrate
  uint8_t twbrbackup = TWBR;
  // must be changed after calling Wire.begin() (inside pwm.begin())f
  TWBR = 12; // upgrade to 400KHz!
//  pwm.setPWM(7,0,0);
//    
//       while(Serial.available()){
//       receivedDataArray[0] = Serial.read();
//       intensity = 4000;
//       //channel = 7;
//       //intensity = (int)(receivedDataArray[0] & 0x01)*273;
//       channel = (int)(receivedDataArray[0] >> 4);
//       pwm.setPWM(channel,0,intensity);}
       pwm.setPWM(0,0,0);
 
}

void loop() {
  if(Serial.available())
  {
       receivedDataArray[0] = Serial.read();
       Serial.println(receivedDataArray[0]);
       intensity = (int)(receivedDataArray[0] & 0x0F)*250;
       channel = (int)(receivedDataArray[0] >> 4);
       pwm.setPWM(channel,0,intensity);
  }
  
  /*
  // Drive each PWM in a 'wave'
  starttime = millis();
  while ((Serial.available() < 5) && ((millis() - starttime) < MAX_MILLIS_TO_WAIT) )
  {
    
  }
  if(Serial.available() < 5)
  {
    Serial.flush();
  }
  else
  {
     for(int i = 0; i < 5; i++)
     {
        receivedDataArray[i] = Serial.read(); // Then: Get them. 
     }
     if(receivedDataArray[0] > 0)
     {
       intensity = (int)(receivedDataArray[0] & 0x01)*273;
       channel = (int)(receivedDataArray[0] >> 4);
       pwm.setPWM(channel,0,intensity);
     }
     else
     {
       pwm.setPWM(0,0,0);
     }
  }
  /*if(Serial.available() > 0) 
  {
    readByte = Serial.read();
    if(readByte == -1) // no data available 
    {
      // error handling
    }
    else
    {
      if(count == 5)
      {
        count = 0;
      }
      receivedDataArray[count++] = readByte;
    }
  }
  
  if(receivedDataArray[0] > 0)
  {
    pwm.setPWM(0,0,4094);
  }
  else
  {
    pwm.setPWM(0,0,0);
  }*/
  
  /*if(count == 0)
  {
    pwm.setPWM(0,0,0);
    count = 1;
  }*/
}
