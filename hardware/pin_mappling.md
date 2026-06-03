# Hardware Pin Mapping

## Arduino Uno Pin Assignments

| Pin       | Component             | Signal Type    | Notes                                     |
| --------- | --------------------- | -------------- | ----------------------------------------- |
| A0        | AD8232 ECG OUTPUT     | Analog input   | ECG waveform (0–1024 ADC range)           |
| A1        | PulseSensor SIGNAL    | Analog input   | Purple wire. Optical heart rate sensor    |
| A2        | LM35 OUTPUT           | Analog input   | Backup analog temperature sensor          |
| D5 (PWM)  | Pulse Fade LED        | PWM output     | Do NOT use D9 or D10 — conflicts with ISR |
| D10       | AD8232 LO+            | Digital input  | Lead-off detection positive               |
| D11       | AD8232 LO-            | Digital input  | Lead-off detection negative               |
| D13 (LED) | Pulse Blink Indicator | Digital output | Built-in LED blinks on each heartbeat     |
| SDA       | MLX90614 SDA          | I2C data       | Default I2C address: 0x5A                 |
| SCL       | MLX90614 SCL          | I2C clock      | —                                         |
| TX (D1)   | ESP8266 RX            | UART           | 3.3V logic — use voltage divider          |
| RX (D0)   | ESP8266 TX            | UART           | 3.3V logic                                |

## Power Requirements

| Component   | Voltage | Current (max) |
| ----------- | ------- | ------------- |
| Arduino Uno | 5V USB  | 500mA         |
| AD8232      | 3.3V    | 3.5mA         |
| ESP8266     | 3.3V    | 250mA (peak)  |
| MLX90614    | 3.3V    | 2.5mA         |
| PulseSensor | 5V      | 4mA           |
