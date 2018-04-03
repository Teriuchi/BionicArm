#include <Servo.h>  //Servo library
Servo finger;
int flex = 0; // Onko sormi koukistettu
int raja = 20; // EMG rajan ylitys aktivoimaan servo
const long interval = 1000;

void setup() {
  finger.attach(3);   //Servo
  pinMode(A0, INPUT); //EMG
  Serial.begin(9600);
  finger.write(0);  //Nollataan servo
  
}

void loop() {
  int emg = analogRead(A0);

  if(emg > raja && flex == 0){
    finger.write(180);  
    flex = 1;
    unsigned long viive1 = millis();
    while(viive1 <= interval);  
  }

  emg = analogRead(A0);
    
  if(emg > raja && flex == 1){
    finger.write(0);
    flex = 0;
    unsigned long viive2 = millis();
    while(viive2 <= interval); 
  }
  

  Serial.println(analogRead(A0));  //Tulostaa EMG-signaalin
  
  delay(10);  // Viive jotta stabiili
}