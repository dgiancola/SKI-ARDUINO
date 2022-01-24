#include <Wire.h>
#include <TinyGPS++.h>

//On ESP32: GPIO-21(SDA), GPIO-22(SCL)
#define OLED_RESET -1 //Reset pin # (or -1 if sharing Arduino reset pin)

#define RXD2 16
#define TXD2 17
HardwareSerial neogps(1);

TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  //Begin serial communication Arduino IDE (Serial Monitor)

  //Begin serial communication Neo6mGPS
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
    
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (neogps.available())
    {
      if (gps.encode(neogps.read()))
      {
        newData = true;
      }
    }
  }

  //If newData is true
  if(newData == true)
  {
    newData = false;
    Serial.println(gps.satellites.value());
    print_speed();
  }
  else
  {
    Serial.println("No Data");
  }  
}

void print_speed()
{      
  if (gps.location.isValid() == 1)
  {
   //String gps_speed = String(gps.speed.kmph());
   
    Serial.print("Lat: ");
    Serial.println(gps.location.lat());

    Serial.print("Lng: ");
    Serial.println(gps.location.lng());

  
    Serial.print("Speed: ");
 
    Serial.println(gps.speed.kmph());
    
    Serial.print("SAT:");
    Serial.println(gps.satellites.value());

    Serial.print("ALT:");
    Serial.println(gps.altitude.meters());
    
  }
  else
  {
    Serial.println("No Data");
  }  
}
