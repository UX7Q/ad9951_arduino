#include <SPI.h>
#include <AD9954.h>


AD9954 DDS(10, 2, 3, 0, 0, 0);

void setup() {

SPI.begin();
SPI.setClockDivider(4);
SPI.setDataMode(SPI_MODE0);
delay(500);
DDS.initialize(100000000);

 
}

float fq = 53000000;
void loop() {

DDS.setFreq(fq); 
delay(500);
  
}
