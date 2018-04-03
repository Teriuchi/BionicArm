// Miika Laeslehto & Jaakko Palomäki

#include <Servo.h>                // Servo library
Servo finger;                     // Määritetään servo
int flex = 0;                     // Onko sormi koukistettu
int raja = 20;                    // EMG rajan ylitys aktivoimaan servo
unsigned long previousMillis = 0; // Säilyttää milloin viimeksi servo liikkunut
const long interval = 3000;       // viive

void setup() {
  finger.attach(3);   //Servo
  pinMode(A0, INPUT); //EMG
  Serial.begin(9600); // Serial monitor
  finger.write(0);    //Nollataan servo
  
}

void loop() {
  int emg = analogRead(A0); // lukee myosignaalin
  unsigned long currentMillis = millis(); // muuttuva tila
  
  if(emg > raja && flex == 0 && currentMillis -previousMillis >= interval){
    finger.write(180);  
    flex = 1;
  }    
  else if(emg > raja && flex == 1 && currentMillis -previousMillis >= interval){
    finger.write(0);
    flex = 0;
  }
  
  Serial.println(analogRead(A0));  //Tulostaa EMG-signaalin
  
  delay(10);  // Viive jotta stabiili
}
