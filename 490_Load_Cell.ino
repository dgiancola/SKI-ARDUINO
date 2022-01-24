#include <HX711_ADC.h>          //HX711 library
#include <Wire.h>               //needed for SDA and SCL pins
#include "soc/rtc.h"

HX711_ADC Load_Cell(2,0);   
//connected the dt pin of cell to pin 2 of ESP32
//connected the sck pin of cell to pin 0 of ESP32

float cal_factor = 450;                         //holds the value that changes the Calibration factor

void setup() {
  Serial.begin(115200);                         //Initialize the serial monitor
  rtc_clk_cpu_freq_set(RTC_CPU_FREQ_80M);       //ESP32 will now only run at 80 MHz
  Load_Cell.begin();                            //Start connection with HX711
  Load_Cell.start(2000);                        //Load cell gets 2 seconds to stabilize
  Load_Cell.setCalFactor(cal_factor);           //Set the Calibration Factor to input value (cal_factor)    
                                        
}

void loop() {
  Load_Cell.update();             //communicates with the load cell
  float i = Load_Cell.getData();  //gets the output value from the load cell
  Serial.print("Weight: ");
  Serial.println(i);
  delay(100);                     //can see the number changes
}
