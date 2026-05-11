# STM32 Firmware to log and send via USART current GPS Coordinates and all three axis accaleromtere data in real -time.
For testing purposes the GPS coordinates have been fixed and being defined a constant in the main.c file. All axis data i.e x, y and Z and GPS lat/long are being send over uart.
GNU Octave code opens up COM port and acquires data , its buffer size is fixed to 200 bytes and can be increased but it create more latency and graph would be displayed after some delay.

