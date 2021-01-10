#include <SPI.h>
#include <AD9954.h>


AD9954 DDS(10, 2, 3, 0, 0, 0);



String inputString = ""; 
bool stringComplete = false;  

void setup() {
  Serial.begin(115200); 
  inputString.reserve(200);


SPI.begin();
SPI.setClockDivider(4);
SPI.setDataMode(SPI_MODE0);
delay(500);
DDS.initialize(100000000);

   
}

String prev = "";
void loop() {

    delay(100);
    Serial.write("FA;");



   if (stringComplete) {

      if(inputString != prev){
       inputString.replace("FA","");
        String fq = getValue(inputString,';',0);
        fq.replace(";","");
        float freq = fq.toInt();
        DDS.setFreq(freq*4); 
        inputString = prev;
      }
    
      stringComplete = false;
  }

  
}





String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
      

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read(); 
    inputString += inChar;
    if (inChar == ';') {
      stringComplete = true;
    } 
  }
}
