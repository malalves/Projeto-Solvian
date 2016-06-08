/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

IRsend irsend;

bool state = 0;

void setup()
{
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.read() != -1) {
    /*for (int i = 0; i < 3; i++) {
      irsend.sendSony(0xa90, 12); // Sony TV power code
      Serial.println("ok");
      delay(40);
    }*/
    if(state){
      digitalWrite(13,HIGH);
      Serial.println("H");
      state=!state;
    }
    else{
      digitalWrite(13,LOW);
      Serial.println("L");
      state=!state;
    }
  }
}
