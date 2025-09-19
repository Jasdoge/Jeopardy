#include <Arduino.h>
#include "../SerialHelper.h"

uint16_t ticks = 0;

uint32_t lastWrite = 0;

void setup(){

	Serial.begin(115200);
	Serial2.begin(115200, SERIAL_8N1, 17,18);

}

void loop(){
	
	const uint32_t ms = millis();
	if( ms-lastWrite > 1e3 ){
		lastWrite = ms;
		

		size_t len = 256;
		char out[len] = {0};
		SerialHelper::cmdSetText( ADDR_ALL, 0, 0, 1, "Hello", out, len );
		Serial.print("Sending: ");
		Serial.printf("Addr %i, Com %i, Size %i, Clr %i, Font %i, %s\n", out[0], out[1], out[2], out[3], out[4], out+5);
		Serial2.println(out);

		++ticks;

	}
	
	while( Serial2.available() > 0 ){
		Serial.write(Serial2.read());
	}
	
	// Todo: serial receive


}

