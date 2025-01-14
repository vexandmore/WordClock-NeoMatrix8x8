/*
   WORD CLOCK - 8x8 NeoPixel Desktop Edition
   by Andy Doro

   A word clock using NeoPixel RGB LEDs for a color shift effect.

   Hardware:
   - Trinket Pro 5V (should work with other Arduino-compatibles with minor modifications)
   - DS1307 RTC breakout
   - NeoPixel NeoMatrix 8x8


   Software:

   This code requires the following libraries:

   - RTClib https://github.com/adafruit/RTClib
   - DST_RTC https://github.com/andydoro/DST_RTC
   - Adafruit_GFX https://github.com/adafruit/Adafruit-GFX-Library
   - Adafruit_NeoPixel https://github.com/adafruit/Adafruit_NeoPixel
   - Adafruit_NeoMatrix https://github.com/adafruit/Adafruit_NeoMatrix


   Wiring:
   - Solder DS1307 breakout to Trinket Pro, A2 to GND, A3 to PWR, A4 to SDA, A5 to SCL
   If you leave off / clip the unused SQW pin on the RTC breakout, the breakout can sit right on top of the Trinket Pro
   for a compact design! It'll be difficult to reach the Trinket Pro reset button, but you can activate the bootloader by
   plugging in the USB.
   - Solder NeoMatrix 5V to Trinket 5V, GND to GND, DIN to Trinket Pro pin 8.


   grid pattern

    A T W E N T Y D
    Q U A R T E R Y
    F I V E H A L F
    D P A S T O R O
    F I V E I G H T
    S I X T H R E E
    T W E L E V E N
    F O U R N I N E


    Acknowledgements:
    - Thanks Dano for faceplate / 3D models & project inspiration!

*/

// include the library code:
#include <Wire.h>
#include <RTClib.h>
#include <DST_RTC.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "functions.h"
#include "config.h"

// define how to write each of the words

// 64-bit "mask" for each pixel in the matrix- is it on or off?
uint64_t mask;

// define masks for each word. we add them with "bitwise or" to generate a mask for the entire "phrase".
#define MFIVE    mask |= 0xF00000000000        // these are in hexadecimal
#define MTEN     mask |= 0x5800000000000000
#define AQUARTER mask |= 0x80FE000000000000
#define TWENTY   mask |= 0x7E00000000000000
#define HALF     mask |= 0xF0000000000
#define PAST     mask |= 0x7800000000
#define TO       mask |= 0xC00000000
#define ONE      mask |= 0x43
#define TWO      mask |= 0xC040
#define THREE    mask |= 0x1F0000
#define FOUR     mask |= 0xF0
#define FIVE     mask |= 0xF0000000
#define SIX      mask |= 0xE00000
#define SEVEN    mask |= 0x800F00
#define EIGHT    mask |= 0x1F000000
#define NINE     mask |= 0xF
#define TEN      mask |= 0x1010100
#define ELEVEN   mask |= 0x3F00
#define TWELVE   mask |= 0xF600
#define ANDYDORO mask |= 0x8901008700000000
// These masks are extra for the day-of-month
#define TEEN     mask |= 0x1030202
#define FIF      mask |= 0xC10000000000
#define THIR     mask |= 0x8080008040000
#define DAY_INDICATOR mask |= 0x100000000000000
// These masks are extra for year
#define YEAR_INDICATOR mask |= 0x200000000000000


// define pins
#define NEOPIN 8  // connect to DIN on NeoMatrix 8x8
#define RTCGND A2 // use this as DS1307 breakout ground 
#define RTCPWR A3 // use this as DS1307 breakout power

RTC_DS1307 RTC; // Establish clock object
DST_RTC dst_rtc; // DST object

// Define US or EU rules for DST comment out as required. see config.h
// More countries could be added with different rules in DST_RTC.cpp
const char rulesDST[] = RULES_DST;

DateTime theTime; // Holds current clock time

int j;   // an integer for the color shifting effect


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//Adafruit_NeoPixel matrix = Adafruit_NeoPixel(64, NEOPIN, NEO_GRB + NEO_KHZ800);

// configure for 8x8 neopixel matrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, NEOPIN,
                            NEO_MATRIX_TOP  + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB         + NEO_KHZ800);


// These variables are for switching between the time and moon phase
class State {
  public:
  State(void (*callback) (void), unsigned long timeOnThisState): callback(callback), timeOnThisState(timeOnThisState){}
  void (*callback) (void);
  unsigned long timeOnThisState;
};

unsigned long timeStateStarted;
int displayState = 0;
State states[] = {State(&displayTime, SHOW_TIME_DURATION), State(&mode_moon, SHOW_MOON_DURATION), State(&displayDay, SHOW_DAY_DURATION),
                        State(&displayMonth, SHOW_MONTH_DURATION), State(&displayYear, SHOW_YEAR_DURATION)};


void setup() {
  // put your setup code here, to run once:

  //Serial for debugging
  //Serial.begin(9600);

  // set pinmodes
  pinMode(NEOPIN, OUTPUT);

  // set analog pins to power DS1307 breakout!
  pinMode(RTCGND, OUTPUT); // analog 2
  pinMode(RTCPWR, OUTPUT); // analog 3

  // set them going!
  digitalWrite(RTCGND, LOW);  // GND for RTC
  digitalWrite(RTCPWR, HIGH); // PWR for RTC

  // start clock
  Wire.begin();  // Begin I2C
  RTC.begin();   // begin clock

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
    // DST? If we're in it, let's subtract an hour from the RTC time to keep our DST calculation correct. This gives us
    // Standard Time which our DST check will add an hour back to if we're in DST.
    DateTime standardTime = RTC.now();
    if (dst_rtc.checkDST(standardTime) == true) { // check whether we're in DST right now. If we are, subtract an hour.
      standardTime = standardTime.unixtime() - 3600;
    }
    RTC.adjust(standardTime);
  }


  matrix.begin();
  matrix.setBrightness(DAYBRIGHTNESS);
  matrix.fillScreen(0); // Initialize all pixels to 'off'
  matrix.show();

  // startup sequence... do colorwipe?
  // delay(500);
  // rainbowCycle(20);
  delay(500);
  flashWords(); // briefly flash each word in sequence
  delay(500);
  timeStateStarted = millis();
}

void loop() {
  updateTime();
  adjustBrightness();
  updateDisplay();
  changeDisplayIfNeeded();
}

void updateTime() {
  // get the time
  theTime = dst_rtc.calculateTime(RTC.now()); // takes into account DST
  // add 2.5 minutes to get better estimates
  theTime = theTime.unixtime() + 150;
}

void updateDisplay() {
  if (displayState < sizeof(states)) {
    State currentState = states[displayState];
    // run function for current state
    currentState.callback(); 
  }
}

void changeDisplayIfNeeded() {
  if (displayState < sizeof(states)) {
    State currentState = states[displayState];
    // Advance to next state if needed
    if (millis() - timeStateStarted > currentState.timeOnThisState) {
      displayState = displayState + 1;
      // loop over
      displayState = displayState % (sizeof(states)/sizeof(states[0]));
      timeStateStarted = millis();
    }
  }
}
