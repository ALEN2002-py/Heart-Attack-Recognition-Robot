
float val;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  val = analogRead(A2);
  val = val * 0.48828125;
  //float farh = (cel*9)/5 + 32;
  Serial.print("TEMPRATURE = ");
  Serial.print(val);
  Serial.print("*C");
  Serial.println();
  delay(1000);
/* uncomment this to get temperature in farenhite
Serial.print("TEMPRATURE = ");
Serial.print(farh);
Serial.print("*F");
Serial.println();
*/
}
