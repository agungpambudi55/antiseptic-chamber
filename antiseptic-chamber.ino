/*
  Created on Apr 2020
  Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#define pinTrig     9
#define pinEcho     8
#define pinBuzeer   3
#define pinPump     2

int state;
/*
 * 0 pendeteksian org lewat masuk
 * 1 persiapan 5 detik ditandai bunyi buzzer setiap detiknya
 * 2 penyemprotan 5 detik diakhiri buzzer 2 kali cepat
 */

void setup() {
//  Serial.begin (115200);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(pinBuzeer, OUTPUT);
  pinMode(pinPump, OUTPUT);
  digitalWrite(pinBuzeer, HIGH);
  digitalWrite(pinPump, HIGH);
  state = 0;
}

void loop() {
  if(state == 0){
//    Serial.println("State pendeteksian");
    for(;;){
      digitalWrite(pinTrig, LOW);
      delayMicroseconds(2);
      digitalWrite(pinTrig, HIGH);
      delayMicroseconds(10);
      digitalWrite(pinTrig, LOW);
      long duration = pulseIn(pinEcho, HIGH);
      long distance = (duration/2) / 29.1;
      
//      Serial.print("Sensor ");
//      Serial.print(distance);
//      Serial.println(" cm");
  
      if(distance >= 5 && distance <= 30){ break; }
      delay(100);    
    }
    
    state = 1;
  }else if(state == 1){
//    Serial.println("State persiapan");

    for(int i=0; i<5; i++){
      digitalWrite(pinBuzeer, LOW);
      delay(100);
      digitalWrite(pinBuzeer, HIGH);
      delay(900);
    }
    
    state = 2;
  }else if(state == 2){
//    Serial.println("State penyemprotan");
    digitalWrite(pinPump, LOW);
    delay(3000);
    digitalWrite(pinPump, HIGH);

    for(int i=0; i<3; i++){
      digitalWrite(pinBuzeer, LOW);
      delay(75);
      digitalWrite(pinBuzeer, HIGH);
      delay(75);
    }
    
    state = 0;
  }
}
