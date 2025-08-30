#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ST7789.h>
#include <XPT2046_Touchscreen.h>

const uint8_t TWI_ADDR = 0x10;


const uint8_t PIN_T_CS = PIN_PA4;
const uint8_t PIN_CS = PIN_PA5;
const uint8_t PIN_DC = PIN_PA6;
const uint8_t PIN_PIN_BTN = PIN_PA7;
const uint8_t PIN_DISP_LED = PIN_PB5;

Adafruit_ST7789 tft = Adafruit_ST7789(PIN_CS, PIN_DC, -1);
XPT2046_Touchscreen ts(PIN_T_CS);

const uint16_t BOTTOM = 400;
const uint16_t LEFT = 410;
const uint16_t TOP = 3875;
const uint16_t RIGHT = 3739;

const uint16_t SCREEN_WIDTH = 320;
const uint16_t SCREEN_HEIGHT = 240;


uint32_t lastUpdate = 0;

void requestEvent(){
	
	Wire.write('3');
	Serial.println("Got req event");
}

void receiveEvent( uint16_t howMany ){

	char buf[howMany+1];
	uint16_t i = 0;
	while( Wire.available() > 0 ){
		buf[i] = Wire.read();
		++i;
	}
	buf[howMany] = '\0';

	tft.setCursor(0,SCREEN_HEIGHT/2);
	tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
	tft.setTextSize(2);
	tft.print(buf);
	Serial.println(buf);

}

void setup(){

	//Serial.swap(1);
	Serial.begin(115200);

	pinMode(PIN_DISP_LED, OUTPUT);
	
	tft.init(240,320);
	tft.setRotation(1);
	tft.invertDisplay(false);

	ts.begin();
	delay(50);
	tft.fillScreen(ST77XX_BLACK);
	delay(100);
	Serial.println("IT BEGINS!");

	Wire.begin(TWI_ADDR);
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);


}

bool led = false;
void loop(){

	if( millis()-lastUpdate > 500 ){
		lastUpdate = millis();
		led = !led;
		digitalWrite(PIN_DISP_LED, led);
		
	}

	if( ts.touched() ){

		TS_Point p = ts.getPoint();
		const uint16_t TOTAL_WIDTH = RIGHT-LEFT;
		const uint16_t TOTAL_HEIGHT = TOP-BOTTOM;

		int16_t xPos = p.x-LEFT;
		int16_t yPos = p.y-BOTTOM;
		if( xPos < -10 || xPos > TOTAL_WIDTH+10 || yPos < -10 || yPos > TOTAL_HEIGHT+10 )
			return;
		xPos = max(min(xPos, TOTAL_WIDTH), 0);
		yPos = max(min(yPos, TOTAL_HEIGHT), 0);
		
			
		xPos = SCREEN_WIDTH-map(xPos, 0, TOTAL_WIDTH, 0, SCREEN_WIDTH);					//  Cast to pixels
		yPos = SCREEN_HEIGHT-map(yPos, 0, TOTAL_HEIGHT, 0, SCREEN_HEIGHT); // Cast to pixels
		
		Serial.printf("X: %i, Y: %i\n", xPos, yPos);
		delay(100);

	}

	
}

