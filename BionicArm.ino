// Miika Laeslehto & Jaakko Palomäki TTV17S1 Kajaani University of Applied Science

#include <Servo.h>            // Servo library
Servo thumb;                  // Thumb finger servo
Servo index;                  // Index finger servo
Servo middle;                 // Middle finger servo
Servo ring;                   // Ring finger servo
Servo little;                 // Little finger servo 
bool flex = 0;                // Status for fingers
int border = 20;              // EMG signal border to activate servos
unsigned long lastFlex = 0;   // Last time servos moved
const long latency = 1500;    // latency for fingers' movement stability

void setup() {
  thumb.attach(3);            // Define servos
  index.attach(5);  
  middle.attach(6); 
  ring.attach(9);   
  little.attach(10); 
  pinMode(A0, INPUT);         // EMG
  Serial.begin(9600);         // Serial monitor
  thumb.write(0);             // Reset Servos
  index.write(10);    
  middle.write(0);   
  ring.write(120);     
  little.write(175);   
}

void loop() {
  int emg = analogRead(A0);   // Read myosignal from muscle
  unsigned long currentTime = millis(); // Changing current time

  if(emg > border && flex == 0 && currentTime - lastFlex >= latency){
      // If EMG-signal is higher than borderline and movement latency has been passed -> move fingers 
      thumb.write(90);        // Turn servos to close fingers
      index.write(85);    
      middle.write(120);   
      ring.write(5);     
      little.write(50);   
      flex = 1;               // Update status for closed fingers
      lastFlex = millis();    // Register the last fingers' movement time
   }
   
   else if(emg < border && flex == 1 && currentTime - lastFlex >= latency) {
      thumb.write(0);         // Turn servos to open fingers
      index.write(10);    
      middle.write(0);   
      ring.write(120);     
      little.write(175);   
      flex = 0;               // Update status for open fingers
      lastFlex = millis();    // Register the last fingers' movement time
   }
  Serial.println(analogRead(A0));  // Print emg status
  
  delay(10);                  // Delay for stability
}
