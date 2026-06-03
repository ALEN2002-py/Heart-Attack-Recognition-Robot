#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
const int OUTPUT_TYPE = SERIAL_PLOTTER;
const int PULSE_INPUT = A1;
const int PULSE_BLINK = LED_BUILTIN;
const int PULSE_FADE = 5;
const int THRESHOLD = 550;
PulseSensorPlayground pulseSensor;
float val;
int ch;
void setup() {
Serial.begin(115200);
  pulseSensor.analogInput(PULSE_INPUT);
  pulseSensor.blinkOnPulse(PULSE_BLINK);
  pulseSensor.fadeOnPulse(PULSE_FADE);
  pulseSensor.setSerial(Serial);
  pulseSensor.setOutputType(OUTPUT_TYPE);
  pulseSensor.setThreshold(THRESHOLD);
  if (!pulseSensor.begin()) {
    for(;;) {
      // Flash the led to show things didn't work.
      digitalWrite(PULSE_BLINK, LOW);
      delay(50);
      digitalWrite(PULSE_BLINK, HIGH);
      delay(50);
    }
  }
  Serial.begin(9600);
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); 
}
void loop() {
  delay(20);
  pulseSensor.outputSample();
  if (pulseSensor.sawStartOfBeat()) {
    pulseSensor.outputBeat();
  }
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    ch = Serial.print('1');
  }
  else{
    Serial.print(analogRead(A0));
  }
  delay(1);
  val = analogRead(A2);
  val = val * 0.48828125;
  //float farh = (cel*9)/5 + 32;
  delay(1000);
  pulseSensor.outputBeat();
  Serial.print(",");
  Serial.print(ch);
  Serial.print(val); 
  Serial.print(",");
 
}