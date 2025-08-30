#include <Wire.h>

uint8_t TWI_ADDR_START = 0x10;

uint16_t ticks = 0;

uint32_t lastWrite = 0;

void setup(){

	Serial.begin(115200);
	Wire.begin(2,1);

}

void loop(){

	const uint32_t ms = millis();
	if( ms-lastWrite > 1e3 ){
		lastWrite = ms;
		
		Wire.beginTransmission(TWI_ADDR_START);
		char out[32] = "Test: ";
		char num[8];
		itoa(ticks, num, 10); 
		strcat(out, num);
		Serial.println(out);
		Wire.write((uint8_t*)out, strlen(out));
		Wire.endTransmission();
		
		
		delay(100); // Have to wait for it to update the display

		Serial.println("Requesting...");
		Wire.requestFrom(TWI_ADDR_START, 1, true);
		
		++ticks;


	}

	while( Wire.available() > 0 ) 
		Serial.write(Wire.read());

}

