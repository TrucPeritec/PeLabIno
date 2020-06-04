#include "HHAL_GPIO.h"
#include "HHAL_Prop.h"
#include "HHAL_GPIO_Prop.h"

HHAL_GPIO io_13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  
  if (io_13.begin(13, OUTPUT, LOW) != 0)
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
      delay(2);
    }

    char res[MAX_JSON_DOC_SIZE];
    
    if (!io_13.messageHandler(rev_mess.c_str(), rev_mess.length(), res, sizeof(res)))
    {
      Serial.println(res);
    }
  }
}
