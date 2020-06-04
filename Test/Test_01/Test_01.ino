#include "HHAL_GPIO.h"
#include "HHAL_Prop.h"
#include "HHAL_GPIO_Prop.h"

HHAL_GPIO io_13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
//  Serial.print("INPUT\t");
//  Serial.println(INPUT);
//  Serial.print("INPUT_PULLUP\t");
//  Serial.println(INPUT_PULLUP);
//  Serial.print("OUTPUT\t");
//  Serial.println(OUTPUT);
//  Serial.println();
  
  if (io_13.begin(13, OUTPUT, LOW) != 0)
  {
//    Serial.println("Failed !!!");
//    Serial.println();
  }

//  HHAL_GPIO_Prop* x = ((HHAL_GPIO_Prop*)io_13.getProp());
//  x->setPin(13);
//  x->setMode(OUTPUT);
//  x->setState(true);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  
//  HHAL_GPIO_Prop* x = ((HHAL_GPIO_Prop*)io_13.getProp());
//  
//  uint8_t pin = x->getPin();
//  uint8_t mode = x->getMode();
//  bool state = x->getState();

//  x->setPin((++pin)%13);
//  x->setMode(!mode);
//  x->setState(!state);
  
//  Serial.print(pin); Serial.print('\t');
//  Serial.print(mode); Serial.print('\t');
//  Serial.print(state); Serial.print('\t');
//  Serial.println();

  if (Serial.available() > 0)
  {
    String rev_mess;
    while (Serial.available() > 0)
    {
      rev_mess += (char)Serial.read();
      delay(2);
    }

    char res[MAX_JSON_DOC_SIZE];
    io_13.messageHandler(rev_mess.c_str(), rev_mess.length(), res, sizeof(res));
    Serial.println(res);
  }
  
//  char json[] = "{\"COMMAND\":\"READ_PROPERTIES\"}";
//  char res[MAX_JSON_DOC_SIZE];
//  io_13.messageHandler(json, strlen(json), res, sizeof(res));
//  Serial.println(res);

//  delay(1000);
}