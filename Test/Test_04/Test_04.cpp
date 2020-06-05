#include "HHAL_GPIO.h"
#include "HHAL_Prop.h"
#include "HHAL_Analog.h"

HHAL_Analog analog_A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);
  
  if (!(analog_A0.begin(A0)))
  {
//    Serial.println("Failed !!!");
//    Serial.println();
  }
}
 
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    String rev_mess;
    while (Serial.available() > 0)
    {
      rev_mess += (char)Serial.read();
      delayMicroseconds(150);
    }

    char res[MAX_JSON_DOC_SIZE];
    
    if (!analog_A0.messageHandler(rev_mess.c_str(), rev_mess.length(), res, sizeof(res)))
    {
      Serial.println(res);
    }
  }
}