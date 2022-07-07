
#define  ENCODER_OPTIMIZE_INTERRUPTS //エンコーダノイズ対策
#include <Wire.h>
#include <Encoder.h>

Encoder myEnc(18, 19);//ロータリーエンコーダライブラリ用
float oldPosition1  = -999;//ロータリーエンコーダライブラリ用
float newPosition1  = -999;
float oldPosition2  = -999;//ロータリーエンコーダライブラリ用
float newPosition2  = -999;
float oldPosition3  = -999;//ロータリーエンコーダライブラリ用
float newPosition3  = -999;
float oldPosition4  = -999;//ロータリーエンコーダライブラリ用
float newPosition4  = -999;
float oldPosition5  = -999;//ロータリーエンコーダライブラリ用
float newPosition5  = -999;
float oldPosition6  = -999;//ロータリーエンコーダライブラリ用
float newPosition6  = -999;
float oldPosition7  = -999;//ロータリーエンコーダライブラリ用
float newPosition7  = -999;
float oldPosition8  = -999;//ロータリーエンコーダライブラリ用
float newPosition8  = -999;
float oldPosition9  = -999;//ロータリーエンコーダライブラリ用
float newPosition9  = -999;
float oldPosition10  = -999;//ロータリーエンコーダライブラリ用
float newPosition10  = -999;
float oldPosition11  = -999;//ロータリーエンコーダライブラリ用
float newPosition11  = -999;
float oldPosition12  = -999;//ロータリーエンコーダライブラリ用
float newPosition12  = -999;
float oldPosition13  = -999;//ロータリーエンコーダライブラリ用
float newPosition13  = -999;
float oldPosition14  = -999;//ロータリーエンコーダライブラリ用
float newPosition14  = -999;
float oldPosition15  = -999;//ロータリーエンコーダライブラリ用
float newPosition15  = -999;
float oldPosition16  = -999;//ロータリーエンコーダライブラリ用
float newPosition16  = -999;
float oldPosition17  = -999;//ロータリーエンコーダライブラリ用
float newPosition17  = -999;
float oldPosition18  = -999;//ロータリーエンコーダライブラリ用
float newPosition18  = -999;
float oldPosition19  = -999;//ロータリーエンコーダライブラリ用
float newPosition19  = -999;

byte enc_switch_in = 0;
unsigned long enc_switch_timer = 0;
bool enc_switch_latch = false;
byte enc_switch_counter = 0;
byte enc_switch = 0;
byte toggle_switch = 0;//0=EXT,1=ON
static int DOUBLE_CLICK_TIME = 500;


//////////////

#include <ezButton.h>

///////////
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

////////////
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

struct midiKeyTable
{
  int keyPin;
  int midiNote;
} midiKeys[] = {
  { 52,  0},  // Pin, MIDI note - C
  { 50,  1},  // C#-1
  { 48,  2},  // D -1
  { 46,  3},  // D#-1
  { 44,  4},  // E -1
  { 42,  5},  // F -1
  { 40,  6},  // F#-1
  { 38,  7},  // G -1
  { 36,  8},  // G#-1
  { 34,  9},  // A -1
  { 32,  10}, // A#-1
  { 30,  11}, // B -1
  { 28,  12}, //C0
  { 26,  13}, //C#
  { 24,  14}, //D0
  { 22,  15}, //D#0
  { 53,  16}, //E0
  { 51,  17}, //F0
  { 49,  18}, //F#0
  { 47,  19}, //G0
  { 45,  20}, //G#0
  { 43,  21}, //A0
  { 41,  22}, //A#0
  { 39,  23}, //B0
  { 37,  24}, //C1
  { 35,  25}, //C#1
  { 33,  26}, //D1
  { 31,  27}, //D#1
  { 29,  28}, //E1
  { 27,  29}, //F1
  { 25,  30}, //F#1
  { 23,  31}, //G1
  { 69,  32}, //G#1
  { 68,  33}, //A1
  { 67,  34}, //A#1
  { 66,  35}, //B1
  { 65,  36}, //C2
};


// C    0, 12, 24,36,
// C#   1, 13, 25,
// D    2, 14, 26,
// D#   3, 15, 27,
// E    4, 16, 28,
// F    5, 17, 29,
// F#   6, 18, 30,
// G    7, 19, 31,
// G#   8, 20, 32,
// A    9, 21, 33,
// A#   10, 22, 34,
// B    11, 23, 35,

///////////////

ezButton octRangeup(6);
ezButton octRangeDown(5);

int menu = 0;
int menu2 = 0;
int menu3 = 0;
int playbackMenu = 0;

int invD = 0;

float BPM = 100.0;
float delayPerBeat = 0.0;
float msPerMin = 1000.0 * 60.0; //1000ms x 60s = 60,000ms per min

float bpmDelay = 0.0;

// constants won't change. Used here to set a pin number:
const int ledPin =  LED_BUILTIN;// the number of the LED pin

// Variables will change:
int clockState = LOW;             // clockState used to set the LED


// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousTime = 0;        // will store last time LED was updated

int bpmClock = 1;

int keyPin = 0;

int octRange = 0;
int octave = 0;

int pitchBend = 0;
int lastpitchBend = 0;

int modWheel = 0;

int select = 0;
int entered = -1;

int arpLength = 1;
int arpRange = 100;
int scale = 0;
int arpDirection = 0;

int teachMenu = 0;
int teachLength = 10;
int teachScale = 0;
int go = 0;

float correctCounter = 0.0;   // counter for the number of correct key presses
float incorrectCounter = 0.0;   // counter for the number of incorrect key presses
float total = 0.0;
float correctPercent = 0.0;
float incorrectPercent = 0.0;

static int lastKeyState[37] = {0};
int keyState = 0;         // current state of a key
int currentNote = 0;

int x = 64;
int y = 32;

int xSpeed = random(1, 4);
int ySpeed = random(1, 4);

bool isRunning = false;
int currentStep;
unsigned long startTime;

bool previousKeyStatus;
bool currentKeyStatus = true;
unsigned long currentTime;

int song = 0;
signed int playbackOct = 0;
float bpmPerc = 100.0;
signed int playTrans = 0;

int screenSaver = 1;

struct playbackTable
{
  const int timestamp;
  const int statusByte;
  const int dataByte1;
  const int dataByte2;
}
midiData[] = {

  {0,   144, 55, 95},
  {268, 128, 55, 80},
  {536, 144, 58, 95},
  {804, 128, 58, 80},
  {1071, 144, 60, 95},
  {1607, 128, 60, 80},
  {1875, 144, 55, 95},
  {2143, 128, 55, 80},
  {2411, 144, 58, 95},
  {2679, 128, 58, 80},
  {2946, 144, 61, 95},
  {3214, 128, 61, 80},
  {3214, 144, 60, 95},
  {3750, 128, 60, 80},
  {4286, 144, 55, 95},
  {4554, 128, 55, 80},
  {4821, 144, 58, 95},
  {5089, 128, 58, 80},
  {5357, 144, 60, 95},
  {5893, 128, 60, 80},
  {6161, 144, 58, 95},
  {6429, 128, 58, 80},
  {6696, 144, 55, 95},
  {8036, 128, 55, 80},

};


const int CMajor[] = {0, 2, 4, 5, 7, 9, 11, 12}; //R W W H W W W H
const int CMinor[] = {0, 2, 3, 5, 7, 9, 10, 12}; //R W H W W W H W

const int CSMajor[] = {1, 3, 5, 6, 8, 10, 12, 13}; //R W W H W W W H
const int CSMinor[] = {1, 3, 4, 6, 8, 10, 11, 13}; //R W H W W W H W

const int DMajor[] = {2, 4, 6, 7, 9, 11, 13, 14}; //R W W H W W W H
const int DMinor[] = {2, 4, 5, 7, 9, 11, 12, 14}; //R W H W W W H W

const int DSMajor[] = {3, 5, 7, 8, 10, 12, 14, 15}; //R W W H W W W H
const int DSMinor[] = {3, 5, 6, 8, 10, 12, 13, 15}; //R W H W W W H W

const int EMajor[] = {4, 6, 8, 9, 11, 13, 15, 16}; //R W W H W W W H
const int EMinor[] = {4, 6, 7, 9, 11, 13, 14, 16}; //R W H W W W H W

const int FMajor[] = {5, 7, 9, 10, 12, 14, 16, 17}; //R W W H W W W H
const int FMinor[] = {5, 7, 8, 10, 12, 14, 15, 17}; //R W H W W W H W

const int FSMajor[] = {6, 8, 10, 11, 13, 15, 17, 18}; //R W W H W W W H
const int FSMinor[] = {6, 8, 9,  11, 13, 15, 16, 18}; //R W H W W W H W

const int GMajor[] = {7, 9, 11, 12, 14, 16, 18, 19}; //R W W H W W W H
const int GMinor[] = {7, 9, 10, 12, 14, 16, 17, 19}; //R W H W W W H W

const int GSMajor[] = {8, 10, 12, 13, 15, 17, 19, 20}; //R W W H W W W H
const int GSMinor[] = {8, 10, 11, 13, 15, 17, 18, 20}; //R W H W W W H W

const int AMajor[] = {9, 11, 13, 14, 16, 18, 20, 21}; //R W W H W W W H
const int AMinor[] = {9, 11, 12, 14, 16, 18, 19, 21}; //R W H W W W H W

const int ASMajor[] = {10, 12, 14, 15, 17, 19, 21, 22}; //R W W H W W W H
const int ASMinor[] = {10, 12, 13, 15, 17, 19, 20, 22}; //R W H W W W H W

const int BMajor[] = {11, 13, 15, 16, 18, 20, 22, 23}; //R W W H W W W H
const int BMinor[] = {11, 13, 14, 16, 18, 20, 21, 23}; //R W H W W W H W


const int fullArrraySize = 21;

const int CMajorFull[] = {0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 24, 26, 28, 29, 31, 33, 35, 36};
const int CMinorFull[] = {0, 2, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19, 20, 22, 24, 26, 27, 29, 31, 32, 34, 36};

const int CSMajorFull[] = {0, 1, 3, 5, 6, 8, 10, 12, 13, 15, 17, 18, 20, 22, 24, 25, 27, 29, 30, 32, 34, 36};
const int CSMinorFull[] = {1, 3, 4, 6, 8, 9, 11, 13, 15, 16, 18, 20, 21, 23, 25, 27, 28, 30, 32, 33, 35};

const int DMajorFull[] = {1, 2, 4, 6, 7, 9, 11, 13, 14, 16, 18, 19, 21, 23, 25, 26, 28, 30, 31, 33, 35};
const int DMinorFull[] = {0, 2, 4, 5, 7, 9, 10, 12, 14, 16, 17, 19, 21, 22, 24, 26, 28, 29, 31, 33, 34, 36};

const int DSMajorFull[] = {0, 2, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19, 20, 22, 24, 26, 27, 29, 31, 32, 34, 36};
const int DSMinorFull[] = {1, 3, 5, 6, 8, 10, 11, 13, 15, 17, 18, 20, 22, 23, 25, 27, 29, 30, 32, 34, 35};

const int EMajorFull[] = {1, 3, 4, 6, 8, 9, 11, 13, 15, 16, 18, 20, 21, 23, 25, 27, 28, 30, 32, 33, 35};
const int EMinorFull[] = {0, 2, 4, 6, 7, 9, 11, 12, 14, 16, 18, 19, 21, 23, 24, 26, 28, 30, 31, 33, 35, 36};

const int FMajorFull[] = {0, 2, 4, 5, 7, 9, 10, 12, 14, 16, 17, 19, 21, 22, 24, 26, 28, 29, 31, 33, 34, 36};
const int FMinorFull[] = {0, 1, 3, 5, 7, 8, 10, 12, 13, 15, 17, 19, 20, 22, 24, 25, 27, 29, 31, 32, 34, 36};

const int FSMajorFull[] = {1, 3, 5, 6, 8, 10, 11, 13, 15, 17, 18, 20, 22, 23, 25, 27, 29, 30, 32, 34, 35};
const int FSMinorFull[] = {1, 2, 4, 6, 8, 9, 11, 13, 14, 16, 18, 20, 21, 23, 25, 26, 28, 30, 32, 33, 35};

const int GMajorFull[] = {0, 2, 4, 6, 7, 9, 11, 12, 14, 16, 18, 19, 21, 23, 24, 26, 28, 30, 31, 33, 35, 36};
const int GMinorFull[] = {1, 3, 4, 6, 8, 10, 11, 13, 15, 16, 18, 20, 22, 23, 25, 27, 28, 30, 32, 34, 35};

const int GSMajorFull[] = {0, 1, 3, 5, 7, 8, 10, 12, 13, 15, 17, 19, 20, 22, 24, 25, 27, 29, 31, 32, 34, 36};
const int GSMinorFull[] = {1, 3, 4, 6, 8, 10, 11, 13, 15, 16, 18, 20, 22, 23, 25, 27, 28, 30, 32, 34, 35};

const int AMajorFull[] = {1, 2, 4, 6, 8, 9, 11, 13, 14, 16, 18, 20, 21, 23, 25, 26, 28, 30, 32, 33, 35};
const int AMinorFull[] = {0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 24, 26, 28, 29, 31, 33, 35, 36};

const int ASMajorFull[] = {0, 2, 3, 5, 7, 9, 10, 12, 14, 15, 17, 19, 21, 22, 24, 26, 27, 29, 31, 33, 34, 36};
const int ASMinorFull[] = { 0, 1, 3, 5, 6, 8, 10, 12, 13, 15, 17, 18, 20, 22, 24, 25, 27, 29, 30, 32, 34, 36};

const int BMajorFull[] = {1, 3, 4, 6, 8, 10, 11, 13, 15, 16, 18, 20, 22, 23, 25, 27, 28, 30, 32, 34, 35};
const int BMinorFull[] = {1, 2, 4, 6, 7, 9, 11, 13, 14, 16, 18, 19, 21, 23, 25, 26, 28, 30, 31, 33, 35};


const int numKeys = 37; //Create Read-Only constant numKeys
bool keyStates[numKeys] = {0}; //Create boolean array keyStates the same size as numKeys and fill with all 0's
////////////////////

int redLED = 8;
int greenLED = 9;
int blueLED = 10;

int redLEDValue = 0;
int greenLEDValue = 0;
int blueLEDValue = 0;

unsigned long activity = 0;        // will store last time any activity from encoder/buttons etc has happened


/////////////////

void setup() {
  MIDI.begin();

  Serial.begin(31250); //SERIAL COMM. & MIDI CANNOT BE RAN AT SAME TIME!!!!

  // Loop through the map of keys and set them all to INPUT_PULLUP
  // Means the pin is in input mode with an internal pull up resistor, so it is waiting to receive ground to do something

  for (int i = 0; i < numKeys; i++)
  {
    pinMode(midiKeys[i].keyPin, INPUT_PULLUP);
    //Also initialise the state for the current key so that it is marked as 'OFF'
    keyStates[i] = false;
  }

  pinMode(redLED, OUTPUT); //Color_LED_R
  pinMode(greenLED, OUTPUT); //Color_LED_G
  pinMode(blueLED, OUTPUT); //Color_LED_B

  pinMode(7, INPUT_PULLUP); //Encoder Button

  octRangeup.setDebounceTime(50);
  octRangeDown.setDebounceTime(50);

  display.begin(i2c_Address, true); // Address 0x3C default
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);

  randomSeed(analogRead(A0)); //RANDOM SEED FOR RANDOM FUNCTIONS

  // oLEDStart();

  pinMode(ledPin, OUTPUT);

}




void loop() {
  currentTime = millis();

  menuAdjust(); //CHECK ENCODER/OCT BUTTONS/PITCH & MOD WHEELS/MENU ITEMS
  staticMenu(); //UPDATE OLED DISPLAY
  display.clearDisplay(); //CLEAR DISPLAY
  rgbLED(); //UPDATE RGB LED
  midiControl(); //UPDATE MIDI COMMANDS


  if (bpmClock == 1) { //IF BPM CLOCK IS SET TO "ON" IN "OPTIONS" MENU
    //UPDATE BPM CLOCK OUT
    bpmDelay = (msPerMin / BPM) / 2;

    if (currentTime - previousTime >= bpmDelay) {

      // save the last time you blinked the LED
      previousTime = currentTime;

      // if the LED is off turn it on and vice-versa:
      if (clockState == LOW) {
        clockState = HIGH;
      }

      else {
        clockState = LOW;
      }

      // set the LED with the clockState of the variable:
      digitalWrite(ledPin, clockState);
    }
  }

  else if (bpmClock == 0) { //IF BPM CLOCK IS SET TO "OFF", SET CLOCK OUTPUT LOW
    // set the LED with the clockState of the variable:
    digitalWrite(ledPin, LOW);
  }

}


void menuAdjust() {

  octRangeup.loop(); // MUST call the loop() function first
  octRangeDown.loop();

  if (octRangeup.isPressed()) {
    octRange = octRange + 36;
  }

  if (octRangeup.isReleased()) {
    octRange = octRange;
  }

  if (octRangeDown.isPressed()) {
    octRange = octRange - 36;
  }

  if (octRangeDown.isReleased()) {
    octRange = octRange;
  }

  if ( octRange < 0) {
    octRange = 108;
  }
  else if ( octRange >= 109 ) {
    octRange = 0;
  }



  pitchBend = analogRead(A1) - 512;
  if ( abs(pitchBend - lastpitchBend) > 1)  { // have we moved enough to avoid analog jitter?
    if ( abs(pitchBend) > 6) { // are we out of the central dead zone?
      MIDI.sendPitchBend(16 * pitchBend, 1); // or -16 depending which way you want to go up and down
      lastpitchBend = pitchBend;
    }
  }

  modWheel = map(analogRead(A2), 0, 1023, 0, 127); //MAP FROM 0 - 1023 TO 0 - 127
  MIDI.sendControlChange(1, modWheel , 1); //CC number, CC value, Channel //MOD DEPTH


  enc_switch_in  = !digitalRead(7);


  if ((enc_switch_in == true) && (enc_switch_latch == false)) {  //Count Times Button Pressed
    enc_switch_counter++;
    enc_switch_timer = millis();
    enc_switch_latch = true;
  }
  else if (enc_switch_in == false) {
    enc_switch_latch = false;
  }


  if ((millis() >= enc_switch_timer + DOUBLE_CLICK_TIME) && (enc_switch_in == false)) {  //Reset Count when no Button Pressed
    enc_switch_counter = 0;
  }


  if ((enc_switch_in == true) && (enc_switch_counter == 1)) {
    enc_switch = 1;
    activity = millis();
    x = 64;
    y = 32;
  }

  else if ((enc_switch_in == true) && (enc_switch_counter >= 2)) {
    enc_switch = 2;
    activity = millis();
    x = 64;
    y = 32;
  }

  else if ((enc_switch_counter == 0) && (enc_switch_in == false)) {
    enc_switch = 0;
  }



  if ( select == 0) { //MAIN MENU ADJUST
    newPosition1 = myEnc.read();
    if ( (newPosition1 - 3) / 4  > oldPosition1 / 4) {
      oldPosition1 = newPosition1;
      oldPosition2 = newPosition1;
      oldPosition3 = newPosition1;
      oldPosition4 = newPosition1;
      oldPosition5 = newPosition1;
      oldPosition6 = newPosition1;
      oldPosition7 = newPosition1;
      oldPosition8 = newPosition1;
      oldPosition9 = newPosition1;
      oldPosition10 = newPosition1;
      oldPosition11 = newPosition1;
      oldPosition12 = newPosition1;
      oldPosition13 = newPosition1;
      oldPosition14 = newPosition1;
      oldPosition15 = newPosition1;
      oldPosition16 = newPosition1;
      menu = menu - 1;
      activity = millis();
      x = 64;
      y = 32;
    }

    else if ( (newPosition1 + 3) / 4  < oldPosition1 / 4 ) {
      oldPosition1 = newPosition1;
      oldPosition2 = newPosition1;
      oldPosition3 = newPosition1;
      oldPosition4 = newPosition1;
      oldPosition5 = newPosition1;
      oldPosition6 = newPosition1;
      oldPosition7 = newPosition1;
      oldPosition8 = newPosition1;
      oldPosition9 = newPosition1;
      oldPosition10 = newPosition1;
      oldPosition11 = newPosition1;
      oldPosition12 = newPosition1;
      oldPosition13 = newPosition1;
      oldPosition14 = newPosition1;
      oldPosition15 = newPosition1;
      oldPosition16 = newPosition1;
      menu = menu + 1;
      activity = millis();
      x = 64;
      y = 32;
    }

    if ( menu < 0) {
      menu = 5;
    }
    else if ( menu >= 6 ) {
      menu = 0;
    }

    if (enc_switch == 1) { //Enter selection
      select = 1;
    }

  }

  if (enc_switch  == 1 && menu == 5 ) {//GLOBAL BPM

    newPosition2 = myEnc.read();
    if ( (newPosition2 - 3) / 4  > oldPosition2 / 4) {
      oldPosition1 = newPosition2;
      oldPosition2 = newPosition2;
      oldPosition3 = newPosition2;
      oldPosition4 = newPosition2;
      oldPosition5 = newPosition2;
      oldPosition6 = newPosition2;
      oldPosition7 = newPosition2;
      oldPosition8 = newPosition2;
      oldPosition9 = newPosition2;
      oldPosition10 = newPosition2;
      oldPosition11 = newPosition2;
      oldPosition12 = newPosition2;
      oldPosition13 = newPosition2;
      oldPosition14 = newPosition2;
      oldPosition15 = newPosition2;
      oldPosition16 = newPosition2;
      BPM = BPM - 10;
    }

    else if ( (newPosition2 + 3) / 4  < oldPosition2 / 4 ) {
      oldPosition1 = newPosition2;
      oldPosition2 = newPosition2;
      oldPosition3 = newPosition2;
      oldPosition4 = newPosition2;
      oldPosition5 = newPosition2;
      oldPosition6 = newPosition2;
      oldPosition7 = newPosition2;
      oldPosition8 = newPosition2;
      oldPosition9 = newPosition2;
      oldPosition10 = newPosition2;
      oldPosition11 = newPosition2;
      oldPosition12 = newPosition2;
      oldPosition13 = newPosition2;
      oldPosition14 = newPosition2;
      oldPosition15 = newPosition2;
      oldPosition16 = newPosition2;
      BPM = BPM + 10;
    }

    if ( BPM < 60) {
      BPM = 160;
    }
    else if ( BPM >= 161 ) {
      BPM = 60;
    }
  }


  if ( menu == 1 && select == 1) { //ARP
    if (enc_switch == 0) {
      newPosition3 = myEnc.read();
      if ( (newPosition3 - 3) / 4  > oldPosition3 / 4) {
        oldPosition1 = newPosition3;
        oldPosition2 = newPosition3;
        oldPosition3 = newPosition3;
        oldPosition4 = newPosition3;
        oldPosition5 = newPosition3;
        oldPosition6 = newPosition3;
        oldPosition7 = newPosition3;
        oldPosition8 = newPosition3;
        oldPosition9 = newPosition3;
        oldPosition10 = newPosition3;
        oldPosition11 = newPosition3;
        oldPosition12 = newPosition3;
        oldPosition13 = newPosition3;
        oldPosition14 = newPosition3;
        oldPosition15 = newPosition3;
        oldPosition16 = newPosition3;
        menu2 = menu2 - 1;
      }

      else if ( (newPosition3 + 3) / 4  < oldPosition3 / 4 ) {
        oldPosition1 = newPosition3;
        oldPosition2 = newPosition3;
        oldPosition3 = newPosition3;
        oldPosition4 = newPosition3;
        oldPosition5 = newPosition3;
        oldPosition6 = newPosition3;
        oldPosition7 = newPosition3;
        oldPosition8 = newPosition3;
        oldPosition9 = newPosition3;
        oldPosition10 = newPosition3;
        oldPosition11 = newPosition3;
        oldPosition12 = newPosition3;
        oldPosition13 = newPosition3;
        oldPosition14 = newPosition3;
        oldPosition15 = newPosition3;
        oldPosition16 = newPosition3;
        menu2 = menu2 + 1;
      }

      if ( menu2 < 0) {
        menu2 = 3;
      }
      else if ( menu2 >= 4 ) {
        menu2 = 0;
      }
    }

    if (enc_switch == 1 && menu2 == 0) {
      newPosition4 = myEnc.read();
      if ( (newPosition4 - 3) / 4  > oldPosition4 / 4) {
        oldPosition1 = newPosition4;
        oldPosition2 = newPosition4;
        oldPosition3 = newPosition4;
        oldPosition4 = newPosition4;
        oldPosition5 = newPosition4;
        oldPosition6 = newPosition4;
        oldPosition7 = newPosition4;
        oldPosition8 = newPosition4;
        oldPosition9 = newPosition4;
        oldPosition10 = newPosition4;
        oldPosition11 = newPosition4;
        oldPosition12 = newPosition4;
        oldPosition13 = newPosition4;
        oldPosition14 = newPosition4;
        oldPosition15 = newPosition4;
        oldPosition16 = newPosition4;
        arpRange = arpRange - 1;
      }

      else if ( (newPosition4 + 3) / 4  < oldPosition4 / 4 ) {
        oldPosition1 = newPosition4;
        oldPosition2 = newPosition4;
        oldPosition3 = newPosition4;
        oldPosition4 = newPosition4;
        oldPosition5 = newPosition4;
        oldPosition6 = newPosition4;
        oldPosition7 = newPosition4;
        oldPosition8 = newPosition4;
        oldPosition9 = newPosition4;
        oldPosition10 = newPosition4;
        oldPosition11 = newPosition4;
        oldPosition12 = newPosition4;
        oldPosition13 = newPosition4;
        oldPosition14 = newPosition4;
        oldPosition15 = newPosition4;
        oldPosition16 = newPosition4;
        arpRange = arpRange + 1;
      }


      if ( arpRange < 0) {
        arpRange = 8;
      }
      else if ( arpRange >= 9) {
        arpRange = 0;
      }

    }

    else if (enc_switch == 1 && menu2 == 1) {

      newPosition5 = myEnc.read();
      if ( (newPosition5 - 3) / 4  > oldPosition5 / 4) {
        oldPosition1 = newPosition5;
        oldPosition2 = newPosition5;
        oldPosition3 = newPosition5;
        oldPosition4 = newPosition5;
        oldPosition5 = newPosition5;
        oldPosition6 = newPosition5;
        oldPosition7 = newPosition5;
        oldPosition8 = newPosition5;
        oldPosition9 = newPosition5;
        oldPosition10 = newPosition5;
        oldPosition11 = newPosition5;
        oldPosition12 = newPosition5;
        oldPosition13 = newPosition5;
        oldPosition14 = newPosition5;
        oldPosition15 = newPosition5;
        oldPosition16 = newPosition5;
        arpLength = arpLength * 2;
      }

      else if ( (newPosition5 + 3) / 4  < oldPosition5 / 4 ) {
        oldPosition1 = newPosition5;
        oldPosition2 = newPosition5;
        oldPosition3 = newPosition5;
        oldPosition4 = newPosition5;
        oldPosition5 = newPosition5;
        oldPosition6 = newPosition5;
        oldPosition7 = newPosition5;
        oldPosition8 = newPosition5;
        oldPosition9 = newPosition5;
        oldPosition10 = newPosition5;
        oldPosition11 = newPosition5;
        oldPosition12 = newPosition5;
        oldPosition13 = newPosition5;
        oldPosition14 = newPosition5;
        oldPosition15 = newPosition5;
        oldPosition16 = newPosition5;
        arpLength = arpLength * 2;
      }

      if ( arpLength < 1) {
        arpLength = 8;
      }
      else if ( arpLength >= 9 ) {
        arpLength = 1;
      }
    }

    else if (enc_switch == 1 && menu2 == 2) {

      newPosition6 = myEnc.read();
      if ( (newPosition6 - 3) / 4  > oldPosition6 / 4) {
        oldPosition1 = newPosition6;
        oldPosition2 = newPosition6;
        oldPosition3 = newPosition6;
        oldPosition4 = newPosition6;
        oldPosition5 = newPosition6;
        oldPosition6 = newPosition6;
        oldPosition7 = newPosition6;
        oldPosition8 = newPosition6;
        oldPosition9 = newPosition6;
        oldPosition10 = newPosition6;
        oldPosition11 = newPosition6;
        oldPosition12 = newPosition6;
        oldPosition13 = newPosition6;
        oldPosition14 = newPosition6;
        oldPosition15 = newPosition6;
        oldPosition16 = newPosition6;
        scale = scale - 1;
      }

      else if ( (newPosition6 + 3) / 4  < oldPosition6 / 4 ) {
        oldPosition1 = newPosition6;
        oldPosition2 = newPosition6;
        oldPosition3 = newPosition6;
        oldPosition4 = newPosition6;
        oldPosition5 = newPosition6;
        oldPosition6 = newPosition6;
        oldPosition7 = newPosition6;
        oldPosition8 = newPosition6;
        oldPosition9 = newPosition6;
        oldPosition10 = newPosition6;
        oldPosition11 = newPosition6;
        oldPosition12 = newPosition6;
        oldPosition13 = newPosition6;
        oldPosition14 = newPosition6;
        oldPosition15 = newPosition6;
        oldPosition16 = newPosition6;
        scale = scale + 1;
      }

      if ( scale < 0) {
        scale = 1;
      }
      else if ( scale >= 2 ) {
        scale = 0;
      }
    }

    else if (enc_switch == 1 && menu2 == 3) {

      newPosition7 = myEnc.read();
      if ( (newPosition7 - 3) / 4  > oldPosition7 / 4) {
        oldPosition1 = newPosition7;
        oldPosition2 = newPosition7;
        oldPosition3 = newPosition7;
        oldPosition4 = newPosition7;
        oldPosition5 = newPosition7;
        oldPosition6 = newPosition7;
        oldPosition7 = newPosition7;
        oldPosition8 = newPosition7;
        oldPosition9 = newPosition7;
        oldPosition10 = newPosition7;
        oldPosition11 = newPosition7;
        oldPosition12 = newPosition7;
        oldPosition13 = newPosition7;
        oldPosition14 = newPosition7;
        oldPosition15 = newPosition7;
        oldPosition16 = newPosition7;
        arpDirection = arpDirection - 1;
      }

      else if ( (newPosition7 + 3) / 4  < oldPosition7 / 4 ) {
        oldPosition1 = newPosition7;
        oldPosition2 = newPosition7;
        oldPosition3 = newPosition7;
        oldPosition4 = newPosition7;
        oldPosition5 = newPosition7;
        oldPosition6 = newPosition7;
        oldPosition7 = newPosition7;
        oldPosition8 = newPosition7;
        oldPosition9 = newPosition7;
        oldPosition10 = newPosition7;
        oldPosition11 = newPosition7;
        oldPosition12 = newPosition7;
        oldPosition13 = newPosition7;
        oldPosition14 = newPosition7;
        oldPosition15 = newPosition7;
        oldPosition16 = newPosition7;
        arpDirection = arpDirection + 1;
      }

      if ( arpDirection < 0) {
        arpDirection = 4;
      }
      else if ( arpDirection >= 5 ) {
        arpDirection = 0;
      }
    }

    else if (enc_switch == 2) { //Go back to start menu
      select = 0;
    }

  }


  else if (menu == 2  && select == 1) { //TEACH MODE

    if (enc_switch == 0) {
      newPosition8 = myEnc.read();
      if ( (newPosition8 - 3) / 4  > oldPosition8 / 4) {
        oldPosition1 = newPosition8;
        oldPosition2 = newPosition8;
        oldPosition3 = newPosition8;
        oldPosition4 = newPosition8;
        oldPosition5 = newPosition8;
        oldPosition6 = newPosition8;
        oldPosition7 = newPosition8;
        oldPosition8 = newPosition8;
        oldPosition9 = newPosition8;
        oldPosition10 = newPosition8;
        oldPosition11 = newPosition8;
        oldPosition12 = newPosition8;
        oldPosition13 = newPosition8;
        oldPosition14 = newPosition8;
        oldPosition15 = newPosition8;
        oldPosition16 = newPosition8;
        teachMenu = teachMenu - 1;
      }

      else if ( (newPosition8 + 3) / 4  < oldPosition8 / 4 ) {
        oldPosition1 = newPosition8;
        oldPosition2 = newPosition8;
        oldPosition3 = newPosition8;
        oldPosition4 = newPosition8;
        oldPosition5 = newPosition8;
        oldPosition6 = newPosition8;
        oldPosition7 = newPosition8;
        oldPosition8 = newPosition8;
        oldPosition9 = newPosition8;
        oldPosition10 = newPosition8;
        oldPosition11 = newPosition8;
        oldPosition12 = newPosition8;
        oldPosition13 = newPosition8;
        oldPosition14 = newPosition8;
        oldPosition15 = newPosition8;
        oldPosition16 = newPosition8;
        teachMenu = teachMenu + 1;
      }

      if ( teachMenu < 0) {
        teachMenu = 2;
      }
      else if ( teachMenu >= 3  ) {
        teachMenu = 0;
      }
    }

    else if (teachMenu == 0 && enc_switch == 1) {
      newPosition9 = myEnc.read();
      if ( (newPosition9 - 3) / 4  > oldPosition9 / 4) {
        oldPosition1 = newPosition9;
        oldPosition2 = newPosition9;
        oldPosition3 = newPosition9;
        oldPosition4 = newPosition9;
        oldPosition5 = newPosition9;
        oldPosition6 = newPosition9;
        oldPosition7 = newPosition9;
        oldPosition8 = newPosition9;
        oldPosition9 = newPosition9;
        oldPosition10 = newPosition9;
        oldPosition11 = newPosition9;
        oldPosition12 = newPosition9;
        oldPosition13 = newPosition9;
        oldPosition14 = newPosition9;
        oldPosition15 = newPosition9;
        oldPosition16 = newPosition9;
        teachScale = teachScale - 1;
      }

      else if ( (newPosition9 + 3) / 4  < oldPosition9 / 4 ) {
        oldPosition1 = newPosition9;
        oldPosition2 = newPosition9;
        oldPosition3 = newPosition9;
        oldPosition4 = newPosition9;
        oldPosition5 = newPosition9;
        oldPosition6 = newPosition9;
        oldPosition7 = newPosition9;
        oldPosition8 = newPosition9;
        oldPosition9 = newPosition9;
        oldPosition10 = newPosition9;
        oldPosition11 = newPosition9;
        oldPosition12 = newPosition9;
        oldPosition13 = newPosition9;
        oldPosition14 = newPosition9;
        oldPosition15 = newPosition9;
        oldPosition16 = newPosition9;
        teachScale = teachScale + 1;
      }

      if ( teachScale < 0) {
        teachScale = 23;
      }
      else if ( teachScale >= 24 ) {
        teachScale = 0;
      }
    }

    else if (teachMenu == 1 && enc_switch == 1) {
      newPosition10 = myEnc.read();
      if ( (newPosition10 - 3) / 4  > oldPosition10 / 4) {
        oldPosition1 = newPosition10;
        oldPosition2 = newPosition10;
        oldPosition3 = newPosition10;
        oldPosition4 = newPosition10;
        oldPosition5 = newPosition10;
        oldPosition6 = newPosition10;
        oldPosition7 = newPosition10;
        oldPosition8 = newPosition10;
        oldPosition9 = newPosition10;
        oldPosition10 = newPosition10;
        oldPosition11 = newPosition10;
        oldPosition12 = newPosition10;
        oldPosition13 = newPosition10;
        oldPosition14 = newPosition10;
        oldPosition15 = newPosition10;
        oldPosition16 = newPosition10;
        teachLength = teachLength - 10;
      }

      else if ( (newPosition10 + 3) / 4  < oldPosition10 / 4 ) {
        oldPosition1 = newPosition10;
        oldPosition2 = newPosition10;
        oldPosition3 = newPosition10;
        oldPosition4 = newPosition10;
        oldPosition5 = newPosition10;
        oldPosition6 = newPosition10;
        oldPosition7 = newPosition10;
        oldPosition8 = newPosition10;
        oldPosition9 = newPosition10;
        oldPosition10 = newPosition10;
        oldPosition11 = newPosition10;
        oldPosition12 = newPosition10;
        oldPosition13 = newPosition10;
        oldPosition14 = newPosition10;
        oldPosition15 = newPosition10;
        oldPosition16 = newPosition10;
        teachLength = teachLength + 10;
      }

      if ( teachLength < 0) {
        teachLength = 100;
      }
      else if ( teachLength >= 101 ) {
        teachLength = 10;
      }
    }

    else if (teachMenu == 2 && enc_switch == 1) {

      go = 1;

    }

    else if (enc_switch == 2) { //Go back to start menu
      select = 0;
      correctCounter = 0.0;
      incorrectCounter = 0.0;
      total = 0.0;
      correctPercent = 0.0;
      incorrectPercent = 0.0;
      go = 0;
    }

  }


  else if (menu == 3  && select == 1) { //OPTIONS
    if (enc_switch == 0) {
      newPosition11 = myEnc.read();
      if ( (newPosition11 - 3) / 4  > oldPosition11 / 4) {
        oldPosition1 = newPosition11;
        oldPosition2 = newPosition11;
        oldPosition3 = newPosition11;
        oldPosition4 = newPosition11;
        oldPosition5 = newPosition11;
        oldPosition6 = newPosition11;
        oldPosition7 = newPosition11;
        oldPosition8 = newPosition11;
        oldPosition9 = newPosition11;
        oldPosition10 = newPosition11;
        oldPosition11 = newPosition11;
        oldPosition12 = newPosition11;
        oldPosition13 = newPosition11;
        oldPosition14 = newPosition11;
        oldPosition15 = newPosition11;
        oldPosition16 = newPosition11;
        menu3 = menu3 - 1;
      }

      else if ( (newPosition11 + 3) / 4  < oldPosition11 / 4 ) {
        oldPosition1 = newPosition11;
        oldPosition2 = newPosition11;
        oldPosition3 = newPosition11;
        oldPosition4 = newPosition11;
        oldPosition5 = newPosition11;
        oldPosition6 = newPosition11;
        oldPosition7 = newPosition11;
        oldPosition8 = newPosition11;
        oldPosition9 = newPosition11;
        oldPosition10 = newPosition11;
        oldPosition11 = newPosition11;
        oldPosition12 = newPosition11;
        oldPosition13 = newPosition11;
        oldPosition14 = newPosition11;
        oldPosition15 = newPosition11;
        oldPosition16 = newPosition11;
        menu3 = menu3 + 1;
      }

      if ( menu3 < 0) {
        menu3 = 2;
      }
      else if ( menu3 >= 3 ) {
        menu3 = 0;
      }
    }

    if (enc_switch == 1 && menu3 == 0) { //INVERT DISPLAY

      newPosition12 = myEnc.read();
      if ( (newPosition12 - 3) / 4  > oldPosition12 / 4) {
        oldPosition1 = newPosition12;
        oldPosition2 = newPosition12;
        oldPosition3 = newPosition12;
        oldPosition4 = newPosition12;
        oldPosition5 = newPosition12;
        oldPosition6 = newPosition12;
        oldPosition7 = newPosition12;
        oldPosition8 = newPosition12;
        oldPosition9 = newPosition12;
        oldPosition10 = newPosition12;
        oldPosition11 = newPosition12;
        oldPosition12 = newPosition12;
        oldPosition13 = newPosition12;
        oldPosition14 = newPosition12;
        oldPosition15 = newPosition12;
        oldPosition16 = newPosition12;
        invD = invD - 1;
      }

      else if ( (newPosition12 + 3) / 4  < oldPosition12 / 4 ) {
        oldPosition1 = newPosition12;
        oldPosition2 = newPosition12;
        oldPosition3 = newPosition12;
        oldPosition4 = newPosition12;
        oldPosition5 = newPosition12;
        oldPosition6 = newPosition12;
        oldPosition7 = newPosition12;
        oldPosition8 = newPosition12;
        oldPosition9 = newPosition12;
        oldPosition10 = newPosition12;
        oldPosition11 = newPosition12;
        oldPosition12 = newPosition12;
        oldPosition13 = newPosition12;
        oldPosition14 = newPosition12;
        oldPosition15 = newPosition12;
        oldPosition16 = newPosition12;
        invD = invD + 1;
      }

      if ( invD < 0) {
        invD = 1;
      }
      else if ( invD >= 2 ) {
        invD = 0;
      }
    }


    if (enc_switch == 1 && menu3 == 1) { //SCREENSAVER ON/OFF

      newPosition17 = myEnc.read();
      if ( (newPosition17 - 3) / 4  > oldPosition17 / 4) {
        oldPosition1 = newPosition17;
        oldPosition2 = newPosition17;
        oldPosition3 = newPosition17;
        oldPosition4 = newPosition17;
        oldPosition5 = newPosition17;
        oldPosition6 = newPosition17;
        oldPosition7 = newPosition17;
        oldPosition8 = newPosition17;
        oldPosition9 = newPosition17;
        oldPosition10 = newPosition17;
        oldPosition11 = newPosition17;
        oldPosition12 = newPosition17;
        oldPosition13 = newPosition17;
        oldPosition14 = newPosition17;
        oldPosition15 = newPosition17;
        oldPosition16 = newPosition17;
        oldPosition17 = newPosition17;
        screenSaver = screenSaver - 1;
      }

      else if ( (newPosition17 + 3) / 4  < oldPosition17 / 4 ) {
        oldPosition1 = newPosition17;
        oldPosition2 = newPosition17;
        oldPosition3 = newPosition17;
        oldPosition4 = newPosition17;
        oldPosition5 = newPosition17;
        oldPosition6 = newPosition17;
        oldPosition7 = newPosition17;
        oldPosition8 = newPosition17;
        oldPosition9 = newPosition17;
        oldPosition10 = newPosition17;
        oldPosition11 = newPosition17;
        oldPosition12 = newPosition17;
        oldPosition13 = newPosition17;
        oldPosition14 = newPosition17;
        oldPosition15 = newPosition17;
        oldPosition16 = newPosition17;
        oldPosition17 = newPosition17;
        screenSaver = screenSaver + 1;
      }

      if ( screenSaver < 0) {
        screenSaver = 1;
      }
      else if ( screenSaver >= 2 ) {
        screenSaver = 0;
      }
    }

    if (enc_switch == 1 && menu3 == 2) { //BPM CLOCK ON/OFF
      newPosition19 = myEnc.read();
      if ( (newPosition19 - 3) / 4  > oldPosition19 / 4) {
        oldPosition1 = newPosition19;
        oldPosition2 = newPosition19;
        oldPosition3 = newPosition19;
        oldPosition4 = newPosition19;
        oldPosition5 = newPosition19;
        oldPosition6 = newPosition19;
        oldPosition7 = newPosition19;
        oldPosition8 = newPosition19;
        oldPosition9 = newPosition19;
        oldPosition10 = newPosition19;
        oldPosition11 = newPosition19;
        oldPosition12 = newPosition19;
        oldPosition13 = newPosition19;
        oldPosition14 = newPosition19;
        oldPosition15 = newPosition19;
        oldPosition16 = newPosition19;
        oldPosition17 = newPosition19;
        oldPosition18 = newPosition19;
        oldPosition19 = newPosition19;
        bpmClock = bpmClock - 1;
      }

      else if ( (newPosition19 + 3) / 4  < oldPosition19 / 4 ) {
        oldPosition1 = newPosition19;
        oldPosition2 = newPosition19;
        oldPosition3 = newPosition19;
        oldPosition4 = newPosition19;
        oldPosition5 = newPosition19;
        oldPosition6 = newPosition19;
        oldPosition7 = newPosition19;
        oldPosition8 = newPosition19;
        oldPosition9 = newPosition19;
        oldPosition10 = newPosition19;
        oldPosition11 = newPosition19;
        oldPosition12 = newPosition19;
        oldPosition13 = newPosition19;
        oldPosition14 = newPosition19;
        oldPosition15 = newPosition19;
        oldPosition16 = newPosition19;
        oldPosition17 = newPosition19;
        oldPosition18 = newPosition19;
        oldPosition19 = newPosition19;
        bpmClock = bpmClock + 1;
      }

      if ( bpmClock < 0) {
        bpmClock = 1;
      }
      else if ( bpmClock >= 2 ) {
        bpmClock = 0;
      }
    }

    else if (enc_switch == 2) { //Go back to start menu
      select = 0;
    }

  }

  else if (menu == 4  && select == 1) { //MIDI PLAYBACK
    if (enc_switch == 0) {
      newPosition13 = myEnc.read();
      if ( (newPosition13 - 3) / 4  > oldPosition13 / 4) {
        oldPosition1 = newPosition13;
        oldPosition2 = newPosition13;
        oldPosition3 = newPosition13;
        oldPosition4 = newPosition13;
        oldPosition5 = newPosition13;
        oldPosition6 = newPosition13;
        oldPosition7 = newPosition13;
        oldPosition8 = newPosition13;
        oldPosition9 = newPosition13;
        oldPosition10 = newPosition13;
        oldPosition11 = newPosition13;
        oldPosition12 = newPosition13;
        oldPosition13 = newPosition13;
        oldPosition14 = newPosition13;
        oldPosition15 = newPosition13;
        oldPosition16 = newPosition13;
        playbackMenu = playbackMenu - 1;
      }

      else if ( (newPosition13 + 3) / 4  < oldPosition13 / 4 ) {
        oldPosition1 = newPosition13;
        oldPosition2 = newPosition13;
        oldPosition3 = newPosition13;
        oldPosition4 = newPosition13;
        oldPosition5 = newPosition13;
        oldPosition6 = newPosition13;
        oldPosition7 = newPosition13;
        oldPosition8 = newPosition13;
        oldPosition9 = newPosition13;
        oldPosition10 = newPosition13;
        oldPosition11 = newPosition13;
        oldPosition12 = newPosition13;
        oldPosition13 = newPosition13;
        oldPosition14 = newPosition13;
        oldPosition15 = newPosition13;
        oldPosition16 = newPosition13;
        playbackMenu = playbackMenu + 1;
      }

      if ( playbackMenu < 0) {
        playbackMenu = 4;
      }
      else if ( playbackMenu >= 5 ) {
        playbackMenu = 0;
      }
    }


    else if (enc_switch == 1 && playbackMenu == 0) { //SONG SELECT
      newPosition17 = myEnc.read();
      if ( (newPosition17 - 3) / 4  > oldPosition17 / 4) {
        oldPosition1 = newPosition17;
        oldPosition2 = newPosition17;
        oldPosition3 = newPosition17;
        oldPosition4 = newPosition17;
        oldPosition5 = newPosition17;
        oldPosition6 = newPosition17;
        oldPosition7 = newPosition17;
        oldPosition8 = newPosition17;
        oldPosition9 = newPosition17;
        oldPosition10 = newPosition17;
        oldPosition11 = newPosition17;
        oldPosition12 = newPosition17;
        oldPosition13 = newPosition17;
        oldPosition14 = newPosition17;
        oldPosition15 = newPosition17;
        oldPosition16 = newPosition17;
        oldPosition17 = newPosition17;
        song = song - 1;
      }

      else if ( (newPosition17 + 3) / 4  < oldPosition17 / 4 ) {
        oldPosition1 = newPosition17;
        oldPosition2 = newPosition17;
        oldPosition3 = newPosition17;
        oldPosition4 = newPosition17;
        oldPosition5 = newPosition17;
        oldPosition6 = newPosition17;
        oldPosition7 = newPosition17;
        oldPosition8 = newPosition17;
        oldPosition9 = newPosition17;
        oldPosition10 = newPosition17;
        oldPosition11 = newPosition17;
        oldPosition12 = newPosition17;
        oldPosition13 = newPosition17;
        oldPosition14 = newPosition17;
        oldPosition15 = newPosition17;
        oldPosition16 = newPosition17;
        oldPosition17 = newPosition17;
        song = song + 1;
      }

      if ( song < 0) {
        song = 4;
      }
      else if ( song >= 5 ) {
        song = 0;
      }
    }

    else if (enc_switch == 1 && playbackMenu == 1) { //OCT RANGE DECREASE/INCREASE

      newPosition14 = myEnc.read();
      if ( (newPosition14 - 3) / 4  > oldPosition14 / 4) {
        oldPosition1 = newPosition14;
        oldPosition2 = newPosition14;
        oldPosition3 = newPosition14;
        oldPosition4 = newPosition14;
        oldPosition5 = newPosition14;
        oldPosition6 = newPosition14;
        oldPosition7 = newPosition14;
        oldPosition8 = newPosition14;
        oldPosition9 = newPosition14;
        oldPosition10 = newPosition14;
        oldPosition11 = newPosition14;
        oldPosition12 = newPosition14;
        oldPosition13 = newPosition14;
        oldPosition14 = newPosition14;
        oldPosition15 = newPosition14;
        oldPosition16 = newPosition14;
        playbackOct = playbackOct - 12;
      }

      else if ( (newPosition14 + 3) / 4  < oldPosition14 / 4 ) {
        oldPosition1 = newPosition14;
        oldPosition2 = newPosition14;
        oldPosition3 = newPosition14;
        oldPosition4 = newPosition14;
        oldPosition5 = newPosition14;
        oldPosition6 = newPosition14;
        oldPosition7 = newPosition14;
        oldPosition8 = newPosition14;
        oldPosition9 = newPosition14;
        oldPosition10 = newPosition14;
        oldPosition11 = newPosition14;
        oldPosition12 = newPosition14;
        oldPosition13 = newPosition14;
        oldPosition14 = newPosition14;
        oldPosition15 = newPosition14;
        oldPosition16 = newPosition14;
        playbackOct = playbackOct + 12;
      }

      if ( playbackOct < -37) {
        playbackOct = 36;
      }
      else if ( playbackOct >= 37 ) {
        playbackOct = -36;
      }
    }

    else if (enc_switch == 1 && playbackMenu == 2) { //BPM % DECREASE/INCREASE

      newPosition15 = myEnc.read();
      if ( (newPosition15 - 3) / 4  > oldPosition15 / 4) {
        oldPosition1 = newPosition15;
        oldPosition2 = newPosition15;
        oldPosition3 = newPosition15;
        oldPosition4 = newPosition15;
        oldPosition5 = newPosition15;
        oldPosition6 = newPosition15;
        oldPosition7 = newPosition15;
        oldPosition8 = newPosition15;
        oldPosition9 = newPosition15;
        oldPosition10 = newPosition15;
        oldPosition11 = newPosition15;
        oldPosition12 = newPosition15;
        oldPosition13 = newPosition15;
        oldPosition14 = newPosition15;
        oldPosition15 = newPosition15;
        oldPosition16 = newPosition15;;
        bpmPerc = bpmPerc - 0.05;
      }

      else if ( (newPosition15 + 3) / 4  < oldPosition15 / 4 ) {
        oldPosition1 = newPosition15;
        oldPosition2 = newPosition15;
        oldPosition3 = newPosition15;
        oldPosition4 = newPosition15;
        oldPosition5 = newPosition15;
        oldPosition6 = newPosition15;
        oldPosition7 = newPosition15;
        oldPosition8 = newPosition15;
        oldPosition9 = newPosition15;
        oldPosition10 = newPosition15;
        oldPosition11 = newPosition15;
        oldPosition12 = newPosition15;
        oldPosition13 = newPosition15;
        oldPosition14 = newPosition15;
        oldPosition15 = newPosition15;
        oldPosition16 = newPosition15;
        bpmPerc = bpmPerc + 0.05;
      }

      if ( bpmPerc < 0.05) {
        bpmPerc = 2.0;
      }
      else if ( bpmPerc >= 2.01 ) {
        bpmPerc = 0.05;
      }
    }

    else if (enc_switch == 1 && playbackMenu == 3) { //KEY TRANSPOSE

      newPosition16 = myEnc.read();
      if ( (newPosition16 - 3) / 4  > oldPosition16 / 4) {
        oldPosition1 = newPosition16;
        oldPosition2 = newPosition16;
        oldPosition3 = newPosition16;
        oldPosition4 = newPosition16;
        oldPosition5 = newPosition16;
        oldPosition6 = newPosition16;
        oldPosition7 = newPosition16;
        oldPosition8 = newPosition16;
        oldPosition9 = newPosition16;
        oldPosition10 = newPosition16;
        oldPosition11 = newPosition16;
        oldPosition12 = newPosition16;
        oldPosition13 = newPosition16;
        oldPosition14 = newPosition16;
        oldPosition15 = newPosition16;
        oldPosition16 = newPosition16;
        playTrans = playTrans - 1;
      }

      else if ( (newPosition16 + 3) / 4  < oldPosition16 / 4 ) {
        oldPosition1 = newPosition16;
        oldPosition2 = newPosition16;
        oldPosition3 = newPosition16;
        oldPosition4 = newPosition16;
        oldPosition5 = newPosition16;
        oldPosition6 = newPosition16;
        oldPosition7 = newPosition16;
        oldPosition8 = newPosition16;
        oldPosition9 = newPosition16;
        oldPosition10 = newPosition16;
        oldPosition11 = newPosition16;
        oldPosition12 = newPosition16;
        oldPosition13 = newPosition16;
        oldPosition14 = newPosition16;
        oldPosition15 = newPosition16;
        oldPosition16 = newPosition16;
        playTrans = playTrans + 1;
      }

      if ( playTrans < -11) {
        playTrans = 11;
      }
      else if ( playTrans >= 12 ) {
        playTrans = -11;
      }
    }



    else if (enc_switch == 2) { //Go back to start menu
      select = 0;
      isRunning = false;
      Serial.write(176); //ALL NOTES OFF
      Serial.write(123);
      Serial.write(0);
    }
  }


  else if (enc_switch == 2) { //Go back to start menu
    select = 0;
  }

}

void staticMenu() {

  if (select == 0) { //MAIN MENU
    display.clearDisplay();
    display.setTextColor(SH110X_WHITE);
    display.setCursor(10, 0);
    display.println("PLAY");

    display.setCursor(10, 10);
    display.println("ARP");

    display.setCursor(10, 20);
    display.println("TEACH");

    display.setCursor(10, 30);
    display.println("OPTIONS");

    display.setCursor(10, 40);
    display.println("MIDI PLAYBACK");

    display.setCursor(10, 50);
    display.println("BPM:");

    display.setCursor(32, 50);
    display.println(BPM);

    display.setCursor(0, menu * 10);
    display.println(">");



    if (screenSaver == 1) {

      if (millis() - activity > 30000 && millis() - activity < 60000) { //ACTIVITY TIMEOUT/SCREENSAVER - 30 SECS

        display.clearDisplay();

        x = x + xSpeed;
        y = y + ySpeed;

        // Check for ball bounce
        if ( x <= 0 || x  >= 103) {
          xSpeed = xSpeed * -1; // reverse x direction

          analogWrite(redLED, random(0, 255));
          analogWrite(greenLED, random(0, 255));
          analogWrite(blueLED, random(0, 255));

          int randomNote = random(0, 7);

          MIDI.sendNoteOn(CMajor[randomNote] + 48, 127, 1);
          MIDI.sendNoteOff(CMajor[randomNote] + 48, 127, 1);
        }

        if ( y <= 0 || y >= 57) {
          ySpeed = ySpeed * -1; // reverse y direction

          analogWrite(redLED, random(0, 255));
          analogWrite(greenLED, random(0, 255));
          analogWrite(blueLED, random(0, 255));

          int randomNote = random(0, 7);

          MIDI.sendNoteOn(CMajor[randomNote] + 48, 127, 1);
          MIDI.sendNoteOff(CMajor[randomNote] + 48, 127, 1);

        }

        display.setCursor(x, y);
        display.println("MIDI");
        display.display();

      }


      if (millis() - activity >= 60000) { //ACTIVITY TIMEOUT/SCREENSAVER - 90 SECS

        display.clearDisplay();

        x = x + xSpeed;
        y = y + ySpeed;

        // Check for ball bounce
        if ( x <= 0 || x  >= 103) {
          xSpeed = xSpeed * -1; // reverse x direction

          analogWrite(redLED, random(0, 255));
          analogWrite(greenLED, random(0, 255));
          analogWrite(blueLED, random(0, 255));
        }

        if ( y <= 0 || y >= 57) {
          ySpeed = ySpeed * -1; // reverse y direction

          analogWrite(redLED, random(0, 255));
          analogWrite(greenLED, random(0, 255));
          analogWrite(blueLED, random(0, 255));
        }

        display.setCursor(x, y);
        display.println("MIDI");
        display.display();

      }
    }
  }

  else  if ( menu == 5 && select == 1) { //BPM
    display.clearDisplay();
    display.setTextColor(SH110X_WHITE);
    display.setCursor(10, 0);
    display.println("PLAY");

    display.setCursor(10, 10);
    display.println("ARP");

    display.setCursor(10, 20);
    display.println("TEACH");

    display.setCursor(10, 30);
    display.println("OPTIONS");

    display.setCursor(10, 40);
    display.println("MIDI PLAYBACK");

    display.setCursor(10, 50);
    display.println("BPM:");

    display.setCursor(32, 50);
    display.println(BPM);


    display.setCursor(0, menu * 10);
    display.println(">");

  }



  if (menu == 0  && select == 1) { //PLAY

    //DRAW PIANO KEYS
    display.drawRect(10,  0, 10, 30, SH110X_WHITE); // x, y, width, height, colour C
    display.fillRect(20, 0, 8,  20, SH110X_WHITE); // x, y, width, height, colour C#
    display.drawRect(28, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour D
    display.fillRect(38, 0, 8,  20, SH110X_WHITE); // x, y, width, height, colour D#
    display.drawRect(46, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour E
    display.drawRect(55, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour F
    display.fillRect(64, 0, 8,  20, SH110X_WHITE); // x, y, width, height, colour F#
    display.drawRect(72, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour G
    display.fillRect(82, 0, 8,  20, SH110X_WHITE); // x, y, width, height, colour G#
    display.drawRect(90, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour A
    display.fillRect(99, 0, 8,  20, SH110X_WHITE); // x, y, width, height, colour A#
    display.drawRect(107, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour B


    if ((midiKeys[0].keyPin = 52) && (keyStates[0] == true) || (midiKeys[12].keyPin = 28) && (keyStates[12] == true)
        || (midiKeys[24].keyPin = 37) && (keyStates[24] == true ) || (midiKeys[36].keyPin = 65) && (keyStates[36] == true )) {
      display.fillRect(10,  0, 10, 30, SH110X_WHITE); // x, y, width, height, colour C
      display.setCursor(12, 35);
      display.println("C");
    }

    else if ((midiKeys[1].keyPin = 50) && (keyStates[1] == true) || (midiKeys[13].keyPin = 26) && (keyStates[13] == true) || (midiKeys[25].keyPin = 35) && (keyStates[25] == true))  {
      display.drawRect(20, 0, 8,  20, SH110X_BLACK); // x, y, width, height, colour C#
      display.setCursor(22, 35);
      display.println("C");
      display.setCursor(22, 45);
      display.println("#");
    }

    else if ((midiKeys[2].keyPin = 48) && (keyStates[2] == true) || (midiKeys[14].keyPin = 24) && (keyStates[14] == true) || (midiKeys[26].keyPin = 33) && (keyStates[26] == true)) {
      display.fillRect(28, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour D
      display.setCursor(30, 35);
      display.println("D");
    }

    else if ((midiKeys[3].keyPin = 46) && (keyStates[3] == true) || (midiKeys[15].keyPin = 22) && (keyStates[15] == true) || (midiKeys[27].keyPin = 31) && (keyStates[27] == true)) {
      display.drawRect(38, 0, 8,  20, SH110X_BLACK); // x, y, width, height, colour D#
      display.setCursor(40, 35);
      display.println("D");
      display.setCursor(40, 45);
      display.println("#");
    }

    else if ((midiKeys[4].keyPin = 44) && (keyStates[4] == true) || (midiKeys[16].keyPin = 53) && (keyStates[16] == true) || (midiKeys[28].keyPin = 29) && (keyStates[28] == true)) {
      display.fillRect(46, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour E
      display.setCursor(48, 35);
      display.println("E");
    }

    else if ((midiKeys[5].keyPin = 42) && (keyStates[5] == true) || (midiKeys[17].keyPin = 51) && (keyStates[17] == true) || (midiKeys[29].keyPin = 27) && (keyStates[29] == true)) {
      display.fillRect(55, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour F
      display.setCursor(57, 35);
      display.println("F");
    }

    else if ((midiKeys[6].keyPin = 40) && (keyStates[6] == true)  || (midiKeys[18].keyPin = 49) && (keyStates[18] == true) || (midiKeys[30].keyPin = 25) && (keyStates[30] == true)) {
      display.drawRect(64, 0, 8,  20, SH110X_BLACK); // x, y, width, height, colour F#
      display.setCursor(66, 35);
      display.println("F");
      display.setCursor(66, 45);
      display.println("#");

    }

    else if ((midiKeys[7].keyPin = 38) && (keyStates[7] == true) || (midiKeys[19].keyPin = 47) && (keyStates[19] == true) || (midiKeys[31].keyPin = 23) && (keyStates[31] == true)) {
      display.fillRect(72, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour G
      display.setCursor(78, 35);
      display.println("G");
    }

    else if ((midiKeys[8].keyPin = 36) && (keyStates[8] == true) || (midiKeys[20].keyPin = 45) && (keyStates[20] == true) || (midiKeys[32].keyPin = 69) && (keyStates[32] == true)) {
      display.drawRect(82, 0, 8,  20, SH110X_BLACK); // x, y, width, height, colour G#
      display.setCursor(84, 35);
      display.println("G");
      display.setCursor(84, 45);
      display.println("#");
    }


    else if ((midiKeys[9].keyPin = 34) && (keyStates[9] == true) || (midiKeys[21].keyPin = 43) && (keyStates[21] == true) || (midiKeys[33].keyPin = 68) && (keyStates[33] == true)) {
      display.fillRect(90, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour A
      display.setCursor(92, 35);
      display.println("A");
    }

    else if ((midiKeys[10].keyPin = 32) && (keyStates[10] == true) || (midiKeys[22].keyPin = 41) && (keyStates[22] == true) || (midiKeys[34].keyPin = 67) && (keyStates[34] == true)) {
      display.drawRect(99, 0, 8,  20, SH110X_BLACK); // x, y, width, height, colour A#
      display.setCursor(101, 35);
      display.println("A");
      display.setCursor(101, 45);
      display.println("#");
    }

    else if ((midiKeys[11].keyPin = 30) && (keyStates[11] == true) || (midiKeys[23].keyPin = 39) && (keyStates[23] == true) || (midiKeys[35].keyPin = 66) && (keyStates[35] == true)) {
      display.fillRect(107, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour B
      display.setCursor(109, 35);
      display.println("B");
    }

    display.setCursor(0, 55);
    display.println("OCT RANGE:");

    if (octRange == 0) {
      display.setCursor(65, 55);
      display.println("0-2");
    }

    else if (octRange == 36) {
      display.setCursor(65, 55);
      display.println("3-5");
    }

    else if (octRange == 72) {
      display.setCursor(65, 55);
      display.println("6-8");
    }

    else if (octRange == 108) {
      display.setCursor(65, 55);
      display.println("9-11");
    }
  }


  else if (menu == 1  && select == 1) { //ARP
    display.clearDisplay();

    display.setCursor(10, 0);
    display.println("RANGE:");

    if (arpRange == 0) {
      display.setCursor(50, 0);
      display.println("4 BARS");
    }

    else if (arpRange == 1) {
      display.setCursor(50, 0);
      display.println("2 BARS");
    }

    else if (arpRange == 2) {
      display.setCursor(50, 0);
      display.println("WHOLE NOTE");
    }

    else if (arpRange == 3) {
      display.setCursor(50, 0);
      display.println("1/2 NOTE");
    }

    else if (arpRange == 4) {
      display.setCursor(50, 0);
      display.println("1/4 NOTE");
    }

    else if (arpRange == 5) {
      display.setCursor(50, 0);
      display.println("1/8 NOTE");
    }

    else if (arpRange == 6) {
      display.setCursor(50, 0);
      display.println("1/16 NOTE");
    }

    else if (arpRange == 7) {
      display.setCursor(50, 0);
      display.println("1/32 NOTE");
    }

    else if (arpRange == 8) {
      display.setCursor(50, 0);
      display.println("RANDOM");
    }


    display.setCursor(10, 10);
    display.println("LENGTH:");

    display.setCursor(52, 10);
    display.println(arpLength);

    display.setCursor(60, 10);
    display.println("NOTES");

    display.setCursor(10, 20);
    display.println("SCALE:");

    if (scale == 0) {
      display.setCursor(50, 20);
      display.println("MAJOR");

    }

    else if (scale == 1) {
      display.setCursor(50, 20);
      display.println("MINOR");
    }

    display.setCursor(10, 30);
    display.println("DIRECTION:");

    if (arpDirection == 0) {
      display.setCursor(70, 30);
      display.println("UP");
    }

    else if (arpDirection == 1) {
      display.setCursor(70, 30);
      display.println("DOWN");
    }

    else if (arpDirection == 2) {
      display.setCursor(70, 30);
      display.println("RANDOM");
    }

    else if (arpDirection == 3) {
      display.setCursor(70, 30);
      display.println("UP/DOWN");
    }

    else if (arpDirection == 4) {
      display.setCursor(70, 30);
      display.println("DOWN/UP");
    }

    display.setCursor(0, menu2 * 10);
    display.println(">");


  }


  else if (menu == 2  && select == 1) { //TEACHER

    if (go == 0) {

      display.clearDisplay();
      display.setCursor(10, 0);
      display.println("WELCOME TO YOUR");
      display.setCursor(10, 10);
      display.println("PIANO LESSON!");

      display.setCursor(10, 30);
      display.println("SCALE:");


      switch (teachScale) {

        case 0:
          display.setCursor(45, 30);
          display.println("C MAJOR");
          break;

        case 1:
          display.setCursor(45, 30);
          display.println("C MINOR");
          break;

        case 2:
          display.setCursor(45, 30);
          display.println("C# MAJOR");
          break;

        case 3:
          display.setCursor(45, 30);
          display.println("C# MINOR");
          break;

        case 4:
          display.setCursor(45, 30);
          display.println("D MAJOR");
          break;

        case 5:
          display.setCursor(45, 30);
          display.println("D MINOR");
          break;

        case 6:
          display.setCursor(45, 30);
          display.println("D# MAJOR");
          break;

        case 7:
          display.setCursor(45, 30);
          display.println("D# MINOR");
          break;

        case 8:
          display.setCursor(45, 30);
          display.println("E MAJOR");
          break;

        case 9:
          display.setCursor(45, 30);
          display.println("E MINOR");
          break;

        case 10:
          display.setCursor(45, 30);
          display.println("F MAJOR");
          break;

        case 11:
          display.setCursor(45, 30);
          display.println("F MINOR");
          break;

        case 12:
          display.setCursor(45, 30);
          display.println("F# MAJOR");
          break;

        case 13:
          display.setCursor(45, 30);
          display.println("F# MINOR");
          break;

        case 14:
          display.setCursor(45, 30);
          display.println("G MAJOR");
          break;

        case 15:
          display.setCursor(45, 30);
          display.println("G MINOR");
          break;

        case 16:
          display.setCursor(45, 30);
          display.println("G# MAJOR");
          break;

        case 17:
          display.setCursor(45, 30);
          display.println("G# MINOR");
          break;

        case 18:
          display.setCursor(45, 30);
          display.println("A MAJOR");
          break;

        case 19:
          display.setCursor(45, 30);
          display.println("A MINOR");
          break;

        case 20:
          display.setCursor(45, 30);
          display.println("A# MAJOR");
          break;

        case 21:
          display.setCursor(45, 30);
          display.println("A# MINOR");
          break;

        case 22:
          display.setCursor(45, 30);
          display.println("B MAJOR");
          break;

        case 23:
          display.setCursor(45, 30);
          display.println("B MINOR");
          break;

        default:
          display.setCursor(45, 30);
          display.println("DEFAULT");
          break;
      }

      display.setCursor(10, 40);
      display.println("NOTES:");
      display.setCursor(45, 40);
      display.println(teachLength);

      display.setCursor(10, 50);
      display.println("BEGIN!");


      display.setCursor(0, ((teachMenu * 10) + 30));
      display.println(">");

    }

    else if (go == 1) {
      if (total != teachLength) {

        display.clearDisplay();

        //DRAW PIANO KEYS
        display.drawRect(10,  0, 10, 30, SH110X_WHITE); // x, y, width, height, colour C
        display.fillRect(20, 0, 8,  20, SH110X_WHITE); // x, y, width, height, colour C#
        display.drawRect(28, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour D
        display.fillRect(38, 0, 8,  20, SH110X_WHITE); // x, y, width, height, colour D#
        display.drawRect(46, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour E
        display.drawRect(55, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour F
        display.fillRect(64, 0, 8,  20, SH110X_WHITE); // x, y, width, height, colour F#
        display.drawRect(72, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour G
        display.fillRect(82, 0, 8,  20, SH110X_WHITE); // x, y, width, height, colour G#
        display.drawRect(90, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour A
        display.fillRect(99, 0, 8,  20, SH110X_WHITE); // x, y, width, height, colour A#
        display.drawRect(107, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour B

        if ((midiKeys[0].keyPin = 52) && (keyStates[0] == true) || (midiKeys[12].keyPin = 28) && (keyStates[12] == true)
            || (midiKeys[24].keyPin = 37) && (keyStates[24] == true ) || (midiKeys[36].keyPin = 65) && (keyStates[36] == true )) {
          display.fillRect(10,  0, 10, 30, SH110X_WHITE); // x, y, width, height, colour C
        }

        else if ((midiKeys[1].keyPin = 50) && (keyStates[1] == true) || (midiKeys[13].keyPin = 26) && (keyStates[13] == true) || (midiKeys[25].keyPin = 35) && (keyStates[25] == true)) {
          display.drawRect(20, 0, 8,  20, SH110X_BLACK); // x, y, width, height, colour C#
        }

        else if ((midiKeys[2].keyPin = 48) && (keyStates[2] == true) || (midiKeys[14].keyPin = 24) && (keyStates[14] == true) || (midiKeys[26].keyPin = 33) && (keyStates[26] == true)) {
          display.fillRect(28, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour D
        }

        else if ((midiKeys[3].keyPin = 46) && (keyStates[3] == true) || (midiKeys[15].keyPin = 22) && (keyStates[15] == true) || (midiKeys[27].keyPin = 31) && (keyStates[27] == true)) {
          display.drawRect(38, 0, 8,  20, SH110X_BLACK); // x, y, width, height, colour D#
        }

        else if ((midiKeys[4].keyPin = 44) && (keyStates[4] == true) || (midiKeys[16].keyPin = 53) && (keyStates[16] == true) || (midiKeys[28].keyPin = 29) && (keyStates[28] == true)) {
          display.fillRect(46, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour E
        }

        else if ((midiKeys[5].keyPin = 42) && (keyStates[5] == true) || (midiKeys[17].keyPin = 51) && (keyStates[17] == true) || (midiKeys[29].keyPin = 27) && (keyStates[29] == true)) {
          display.fillRect(55, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour F
        }

        else if ((midiKeys[6].keyPin = 40) && (keyStates[6] == true)  || (midiKeys[18].keyPin = 49) && (keyStates[18] == true) || (midiKeys[30].keyPin = 25) && (keyStates[30] == true)) {
          display.drawRect(64, 0, 8,  20, SH110X_BLACK); // x, y, width, height, colour F#
        }

        else if ((midiKeys[7].keyPin = 38) && (keyStates[7] == true) || (midiKeys[19].keyPin = 47) && (keyStates[19] == true) || (midiKeys[31].keyPin = 23) && (keyStates[31] == true)) {
          display.fillRect(72, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour G
        }

        else if ((midiKeys[8].keyPin = 36) && (keyStates[8] == true) || (midiKeys[20].keyPin = 45) && (keyStates[20] == true) || (midiKeys[32].keyPin = 69) && (keyStates[32] == true)) {
          display.drawRect(82, 0, 8,  20, SH110X_BLACK); // x, y, width, height, colour G#
        }

        else if ((midiKeys[9].keyPin = 34) && (keyStates[9] == true) || (midiKeys[21].keyPin = 43) && (keyStates[21] == true) || (midiKeys[33].keyPin = 68) && (keyStates[33] == true)) {
          display.fillRect(90, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour A
        }

        else if ((midiKeys[10].keyPin = 32) && (keyStates[10] == true) || (midiKeys[22].keyPin = 41) && (keyStates[22] == true) || (midiKeys[34].keyPin = 67) && (keyStates[34] == true)) {
          display.drawRect(99, 0, 8,  20, SH110X_BLACK); // x, y, width, height, colour A#
        }

        else if ((midiKeys[11].keyPin = 30) && (keyStates[11] == true) || (midiKeys[23].keyPin = 39) && (keyStates[23] == true) || (midiKeys[35].keyPin = 66) && (keyStates[35] == true)) {
          display.fillRect(107, 0, 10, 30, SH110X_WHITE); // x, y, width, height, colour B
        }


        switch (teachScale) {

          case 0:
            display.setCursor(35, 55);
            display.println("C MAJOR");

            display.setCursor(12, 35);
            display.println("C");

            display.setCursor(30, 35);
            display.println("D");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(57, 35);
            display.println("F");

            display.setCursor(74, 35);
            display.println("G");

            display.setCursor(92, 35);
            display.println("A");

            display.setCursor(109, 35);
            display.println("B");
            break;

          case 1:
            display.setCursor(35, 55);
            display.println("C MINOR");

            display.setCursor(12, 35);
            display.println("C");

            display.setCursor(30, 35);
            display.println("D");

            display.setCursor(40, 35);
            display.println("D");
            display.setCursor(40, 45);
            display.println("#");

            display.setCursor(57, 35);
            display.println("F");

            display.setCursor(74, 35);
            display.println("G");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(101, 35);
            display.println("A");
            display.setCursor(101, 45);
            display.println("#");
            break;

          case 2:
            display.setCursor(35, 55);
            display.println("C# MAJOR");

            display.setCursor(12, 35);
            display.println("C");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(40, 35);
            display.println("D");
            display.setCursor(40, 45);
            display.println("#");

            display.setCursor(57, 35);
            display.println("F");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(101, 35);
            display.println("A");
            display.setCursor(101, 45);
            display.println("#");
            break;

          case 3:
            display.setCursor(35, 55);
            display.println("C# MINOR");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(40, 35);
            display.println("D");
            display.setCursor(40, 45);
            display.println("#");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(92, 35);
            display.println("A");

            display.setCursor(109, 35);
            display.println("B");
            break;

          case 4:
            display.setCursor(35, 55);
            display.println("D MAJOR");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(30, 35);
            display.println("D");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(74, 35);
            display.println("G");

            display.setCursor(92, 35);
            display.println("A");

            display.setCursor(109, 35);
            display.println("B");
            break;

          case 5:
            display.setCursor(35, 55);
            display.println("D MINOR");

            display.setCursor(12, 35);
            display.println("C");

            display.setCursor(30, 35);
            display.println("D");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(57, 35);
            display.println("F");

            display.setCursor(74, 35);
            display.println("G");

            display.setCursor(92, 35);
            display.println("A");

            display.setCursor(101, 35);
            display.println("A");
            display.setCursor(101, 45);
            display.println("#");
            break;

          case 6:
            display.setCursor(35, 55);
            display.println("D# MAJOR");

            display.setCursor(12, 35);
            display.println("C");

            display.setCursor(30, 35);
            display.println("D");

            display.setCursor(40, 35);
            display.println("D");
            display.setCursor(40, 45);
            display.println("#");

            display.setCursor(57, 35);
            display.println("F");

            display.setCursor(74, 35);
            display.println("G");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(101, 35);
            display.println("A");
            display.setCursor(101, 45);
            display.println("#");
            break;

          case 7:
            display.setCursor(35, 55);
            display.println("D# MINOR");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(40, 35);
            display.println("D");
            display.setCursor(40, 45);
            display.println("#");

            display.setCursor(57, 35);
            display.println("F");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(101, 35);
            display.println("A");
            display.setCursor(101, 45);
            display.println("#");

            display.setCursor(109, 35);
            display.println("B");
            break;

          case 8:
            display.setCursor(35, 55);
            display.println("E MAJOR");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(40, 35);
            display.println("D");
            display.setCursor(40, 45);
            display.println("#");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(92, 35);
            display.println("A");

            display.setCursor(109, 35);
            display.println("B");
            break;

          case 9:
            display.setCursor(35, 55);
            display.println("E MINOR");

            display.setCursor(12, 35);
            display.println("C");

            display.setCursor(30, 35);
            display.println("D");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(74, 35);
            display.println("G");

            display.setCursor(92, 35);
            display.println("A");

            display.setCursor(109, 35);
            display.println("B");
            break;

          case 10:
            display.setCursor(35, 55);
            display.println("F MAJOR");

            display.setCursor(12, 35);
            display.println("C");

            display.setCursor(30, 35);
            display.println("D");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(57, 35);
            display.println("F");

            display.setCursor(74, 35);
            display.println("G");

            display.setCursor(92, 35);
            display.println("A");

            display.setCursor(101, 35);
            display.println("A");
            display.setCursor(101, 45);
            display.println("#");
            break;

          case 11:
            display.setCursor(35, 55);
            display.println("F MINOR");

            display.setCursor(12, 35);
            display.println("C");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(40, 35);
            display.println("D");
            display.setCursor(40, 45);
            display.println("#");

            display.setCursor(57, 35);
            display.println("F");

            display.setCursor(74, 35);
            display.println("G");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(101, 35);
            display.println("A");
            display.setCursor(101, 45);
            display.println("#");
            break;


          case 12:
            display.setCursor(35, 55);
            display.println("F# MAJOR");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(40, 35);
            display.println("D");
            display.setCursor(40, 45);
            display.println("#");

            display.setCursor(57, 35);
            display.println("F");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(101, 35);
            display.println("A");
            display.setCursor(101, 45);
            display.println("#");

            display.setCursor(109, 35);
            display.println("B");
            break;

          case 13:
            display.setCursor(35, 55);
            display.println("F# MINOR");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(30, 35);
            display.println("D");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(92, 35);
            display.println("A");

            display.setCursor(109, 35);
            display.println("B");
            break;

          case 14:
            display.setCursor(35, 55);
            display.println("G MAJOR");

            display.setCursor(12, 35);
            display.println("C");

            display.setCursor(30, 35);
            display.println("D");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(74, 35);
            display.println("G");

            display.setCursor(92, 35);
            display.println("A");

            display.setCursor(109, 35);
            display.println("B");
            break;

          case 15:
            display.setCursor(35, 55);
            display.println("G MINOR");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(40, 35);
            display.println("D");
            display.setCursor(40, 45);
            display.println("#");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(101, 35);
            display.println("A");
            display.setCursor(101, 45);
            display.println("#");

            display.setCursor(109, 35);
            display.println("B");
            break;

          case 16:
            display.setCursor(35, 55);
            display.println("G# MAJOR");

            display.setCursor(12, 35);
            display.println("C");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(40, 35);
            display.println("D");
            display.setCursor(40, 45);
            display.println("#");

            display.setCursor(57, 35);
            display.println("F");

            display.setCursor(74, 35);
            display.println("G");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(101, 35);
            display.println("A");
            display.setCursor(101, 45);
            display.println("#");
            break;

          case 17:
            display.setCursor(35, 55);
            display.println("G# MINOR");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(40, 35);
            display.println("D");
            display.setCursor(40, 45);
            display.println("#");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(101, 35);
            display.println("A");
            display.setCursor(101, 45);
            display.println("#");

            display.setCursor(109, 35);
            display.println("B");
            break;

          case 18:
            display.setCursor(35, 55);
            display.println("A MAJOR");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(30, 35);
            display.println("D");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(92, 35);
            display.println("A");

            display.setCursor(109, 35);
            display.println("B");
            break;

          case 19:
            display.setCursor(35, 55);
            display.println("A MINOR");

            display.setCursor(12, 35);
            display.println("C");

            display.setCursor(30, 35);
            display.println("D");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(57, 35);
            display.println("F");

            display.setCursor(74, 35);
            display.println("G");

            display.setCursor(92, 35);
            display.println("A");

            display.setCursor(109, 35);
            display.println("B");
            break;

          case 20:
            display.setCursor(35, 55);
            display.println("A# MAJOR");

            display.setCursor(12, 35);
            display.println("C");

            display.setCursor(30, 35);
            display.println("D");

            display.setCursor(40, 35);
            display.println("D");
            display.setCursor(40, 45);
            display.println("#");

            display.setCursor(57, 35);
            display.println("F");

            display.setCursor(74, 35);
            display.println("G");

            display.setCursor(92, 35);
            display.println("A");

            display.setCursor(101, 35);
            display.println("A");
            display.setCursor(101, 45);
            display.println("#");
            break;

          case 21:
            display.setCursor(35, 55);
            display.println("A# MINOR");

            display.setCursor(12, 35);
            display.println("C");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(40, 35);
            display.println("D");
            display.setCursor(40, 45);
            display.println("#");

            display.setCursor(57, 35);
            display.println("F");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(101, 35);
            display.println("A");
            display.setCursor(101, 45);
            display.println("#");
            break;

          case 22:
            display.setCursor(35, 55);
            display.println("B MAJOR");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(40, 35);
            display.println("D");
            display.setCursor(40, 45);
            display.println("#");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(84, 35);
            display.println("G");
            display.setCursor(84, 45);
            display.println("#");

            display.setCursor(101, 35);
            display.println("A");
            display.setCursor(101, 45);
            display.println("#");

            display.setCursor(109, 35);
            display.println("B");
            break;

          case 23:
            display.setCursor(35, 55);
            display.println("B MINOR");

            display.setCursor(22, 35);
            display.println("C");
            display.setCursor(22, 45);
            display.println("#");

            display.setCursor(30, 35);
            display.println("D");

            display.setCursor(48, 35);
            display.println("E");

            display.setCursor(66, 35);
            display.println("F");
            display.setCursor(66, 45);
            display.println("#");

            display.setCursor(74, 35);
            display.println("G");

            display.setCursor(92, 35);
            display.println("A");

            display.setCursor(109, 35);
            display.println("B");
            break;

          default:
            display.setCursor(35, 55);
            display.println("DEFAULT");
            break;
        }




        bool isCorrect = false;
        for (int i = 0; i < numKeys; i++) {
          keyState = digitalRead(midiKeys[i].keyPin);
          currentNote = midiKeys[i].midiNote;

          // compare the keyState to its previous state
          if (keyState != lastKeyState[i]) {

            if (keyState == LOW) {

              for (int j = 0; j < 20; j++) {

                switch (teachScale) {

                  case 0:
                    if (currentNote == CMajorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 1:
                    if (currentNote == CMinorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 2:
                    if (currentNote == CSMajorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 3:
                    if (currentNote == CSMinorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 4:
                    if (currentNote == DMajorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 5:
                    if (currentNote == DMinorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 6:
                    if (currentNote == DSMajorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 7:
                    if (currentNote == DSMinorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 8:
                    if (currentNote == EMajorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 9:
                    if (currentNote == EMinorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 10:
                    if (currentNote == FMajorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 11:
                    if (currentNote == FMinorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 12:
                    if (currentNote == FSMajorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 13:
                    if (currentNote == FSMinorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 14:
                    if (currentNote == GMajorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 15:
                    if (currentNote == GMinorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 16:
                    if (currentNote == GSMajorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 17:
                    if (currentNote == GSMinorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 18:
                    if (currentNote == AMajorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 19:
                    if (currentNote == AMinorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 20:
                    if (currentNote == ASMajorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 21:
                    if (currentNote == ASMinorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 22:
                    if (currentNote == BMajorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  case 23:
                    if (currentNote == BMinorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                  default:
                    if (currentNote == CMajorFull[j]) {
                      // if the current state is LOW then the key
                      //            // went from off to on (active low key).
                      isCorrect = true;
                      break;
                    }
                    break;

                }
              }

              if (isCorrect == true) {
                correctCounter++;
              }

              else {
                incorrectCounter++;
              }
            }
          }
          delay(1);
          // save the current state of this key as the last state,
          //for next time through the loop
          lastKeyState[i] = keyState;
        }

        total = correctCounter + incorrectCounter;
      }


      else if (total == teachLength) {


        correctPercent = ((correctCounter / total) * 100);
        incorrectPercent = ((incorrectCounter / total) * 100);

        display.clearDisplay();

        display.setCursor(0, 0);
        display.println("CORRECT:");
        display.setCursor(50, 0);
        display.println(correctPercent);
        display.setCursor(82, 0);
        display.println("%");

        display.setCursor(0, 10);
        display.println("INCORRECT:");
        display.setCursor(60, 10);
        display.println(incorrectPercent);
        display.setCursor(92, 10);
        display.println("%");

        if (correctPercent >= incorrectPercent) {
          display.setCursor(0, 40);
          display.println("WELL DONE!");

        }

        else if (incorrectPercent >= correctPercent) {
          display.setCursor(0, 40);
          display.println("YOU NEED");
          display.setCursor(0, 50);
          display.println("MORE PRACTISE!");
        }

      }


    }
  }

  else if (menu == 3  && select == 1) { //OPTIONS

    display.clearDisplay();

    display.setCursor(10, 0);
    display.println("INVERT:");


    if (invD == 0) {
      display.setCursor(52, 0);
      display.println("OFF");
      display.invertDisplay(false);

    }

    else if (invD == 1) {
      display.setCursor(52, 0);
      display.println("ON");
      display.invertDisplay(true);
    }

    display.setCursor(10, 10);
    display.println("SCREENSAVER:");

    if (screenSaver == 0) {
      display.setCursor(82, 10);
      display.println("OFF");
    }

    else if (screenSaver == 1) {
      display.setCursor(82, 10);
      display.println("ON");
    }

    display.setCursor(10, 20);
    display.println("BPM CLOCK:");

    if (bpmClock == 0) {
      display.setCursor(70, 20);
      display.println("OFF");
    }

    else if (bpmClock == 1) {
      display.setCursor(70, 20);
      display.println("ON");
    }

    display.setCursor(0, menu3 * 10);
    display.println(">");

  }

  if (menu == 4  && select == 1) { //MIDI PLAYBACK

    display.clearDisplay();

    display.setCursor(10, 0);
    display.println("SONG:");

    display.setCursor(50, 0);
    display.println(song);

    display.setCursor(10, 10);
    display.println("OCTAVE RANGE:");


    if (playbackOct == -36) {
      display.setCursor(87, 10);
      display.println("-3");
    }

    else if (playbackOct == -24) {
      display.setCursor(87, 10);
      display.println("-2");
    }

    else if (playbackOct == -12) {
      display.setCursor(87, 10);
      display.println("-1");
    }

    if (playbackOct == 0) {
      display.setCursor(87, 10);
      display.println("OG");
    }

    else if (playbackOct == 12) {
      display.setCursor(87, 10);
      display.println("+1");
    }

    else if (playbackOct == 24) {
      display.setCursor(87, 10);
      display.println("+2");
    }

    else if (playbackOct == 36) {
      display.setCursor(87, 10);
      display.println("+3");
    }


    display.setCursor(10, 20);
    display.println("BPM x");

    display.setCursor(45, 20);
    display.println(bpmPerc * 100);

    display.setCursor(85, 20);
    display.println("%");

    display.setCursor(10, 30);
    display.println("TRANSPOSE:");

    display.setCursor(75, 30);
    display.println(playTrans);

    display.setCursor(10, 40);
    display.println("PLAY!");

    display.setCursor(0, playbackMenu * 10);
    display.println(">");


  }

  display.display();
}




/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
void midiControl() {



  if (menu == 0  && select == 1) { //PLAY

    for (int i = 0; i < numKeys; i++) {

      int keyStatus = digitalRead(midiKeys[i].keyPin); //Create int variable keyStatus and read the status of each key
      if ((keyStatus == LOW) && (keyStates[i] == false)) { //If keyStatus = LOW (ie - key ON) AND current keyState = FALSE

        MIDI.sendNoteOn(midiKeys[i].midiNote + octRange, 127, 1); //Turn midi note ON: velocity 127, midi channel 1.
        //Mark the button  state as TRUE, since the button is now ON
        keyStates[i] = true;
      }

      else if ((keyStatus == HIGH) && (keyStates[i] == true)) //Else if keyStatus = HIGH (ie - key OFF) AND current keyState = TRUE
      {
        MIDI.sendNoteOff(midiKeys[i].midiNote + octRange, 0, 1); //turn midi note off, midi channel 1.
        //Mark the button  state as FALSE, since the button is now OFF
        keyStates[i] = false;
      }
    }
  }



  if (menu == 1  && select == 1) { //ARP


    if (arpRange == 0) {
      delayPerBeat = (msPerMin / BPM) * 16.0;//4 BARS
    }

    else  if (arpRange == 1) {
      delayPerBeat = (msPerMin / BPM) * 8.0;//2 BARS
    }

    else  if (arpRange == 2) {
      delayPerBeat = (msPerMin / BPM) * 4.0;//1 BAR
    }

    else  if (arpRange == 3) {
      delayPerBeat = (msPerMin / BPM) * 2.0;//1/2 NOTE
    }

    else  if (arpRange == 4) {
      delayPerBeat = (msPerMin / BPM);//1/4 NOTE
    }

    else  if (arpRange == 5) {
      delayPerBeat = (msPerMin / BPM) / 2.0;//1/8 NOTE
    }

    else  if (arpRange == 6) {
      delayPerBeat = (msPerMin / BPM) / 4.0;//1/16 NOTE
    }

    else  if (arpRange == 7) {
      delayPerBeat = (msPerMin / BPM) / 8.0; //1/32 NOTE
    }

    else  if (arpRange == 8) {
      randomSeed(analogRead(A0));
      int randLength = random(1, 4);
      switch (randLength) {


        case 1:
          delayPerBeat = (msPerMin / BPM);//1/4 NOTE
          break;

        case 2:
          delayPerBeat = (msPerMin / BPM) / 2;//1/8 NOTE
          break;

        case 3:
          delayPerBeat = (msPerMin / BPM) / 4;//1/16 NOTE
          break;

        case 4:
          delayPerBeat = (msPerMin / BPM) / 8; //1/32 NOTE
          break;

        default:
          delayPerBeat = (msPerMin / BPM);//1/4 NOTE
          break;
      }

    }


    for (int i = 0; i < numKeys; i++) {
      int keyStatus = digitalRead(midiKeys[i].keyPin); //Create int variable keyStatus and read the status of each key
      int keyPin = midiKeys[i].keyPin; //Create int variable keyPin to determine each key pressed

      if (keyStatus == LOW) { //If key pressed

        if (keyPin == 52) { //If C-1 key pressed

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(CMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);


            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(CMajor) / sizeof(CMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL


              switch (randColour) {

                case 1 : //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;

                case 2: //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;

                default: //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;
              }



              MIDI.sendNoteOn(CMajor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(CMajor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(CMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(CMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR
            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(CMinor) / sizeof(CMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;

                case 2: //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;

                default: //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;
              }


              MIDI.sendNoteOn(CMinor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(CMinor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(CMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(CMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 28) { //If C0 key pressed

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(CMajor) / sizeof(CMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL


              switch (randColour) {

                case 1 : //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;

                case 2: //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;

                default: //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;
              }



              MIDI.sendNoteOn(CMajor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CMajor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR
            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(CMinor) / sizeof(CMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;

                case 2: //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;

                default: //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;
              }


              MIDI.sendNoteOn(CMinor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CMinor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }


        if (keyPin == 37) { //If C1 key pressed

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(CMajor) / sizeof(CMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL


              switch (randColour) {

                case 1 : //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;

                case 2: //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;

                default: //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;
              }



              MIDI.sendNoteOn(CMajor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CMajor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR
            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(CMinor) / sizeof(CMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;

                case 2: //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;

                default: //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;
              }


              MIDI.sendNoteOn(CMinor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CMinor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 65) { //If C2 key pressed

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CMajor[i] + octRange + 36, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 36, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMajor[i] + octRange + 36, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 36, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(CMajor) / sizeof(CMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL


              switch (randColour) {

                case 1 : //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;

                case 2: //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;

                default: //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;
              }



              MIDI.sendNoteOn(CMajor[idx] + octRange + 36, 127, 1);
              MIDI.sendNoteOff(CMajor[idx] + octRange + 36, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CMajor[i] + octRange + 36, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 36, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMajor[i] + octRange + 36, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 36, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMajor[i] + octRange + 36, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 36, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CMajor[i] + octRange + 36, 127, 1);
              MIDI.sendNoteOff(CMajor[i] + octRange + 36, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 36, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 36, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 36, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 36, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR
            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(CMinor) / sizeof(CMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;

                case 2: //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;

                default: //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;
              }


              MIDI.sendNoteOn(CMinor[idx] + octRange + 36, 127, 1);
              MIDI.sendNoteOff(CMinor[idx] + octRange + 36, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 36, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 36, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 36, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 36, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 36, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 36, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31 ; //TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CMinor[i] + octRange + 36, 127, 1);
              MIDI.sendNoteOff(CMinor[i] + octRange + 36, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }



        if (keyPin == 50) {  //C#-1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR



            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(CSMajor) / sizeof(CSMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;

                case 2: //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;

                default: //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(CSMajor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(CSMajor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR


            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR
            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(CSMinor) / sizeof(CSMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;

                case 2: //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;

                default: //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;
              }


              MIDI.sendNoteOn(CSMinor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(CSMinor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

          }
        }


        if (keyPin == 26) {  //C#0

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR



            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(CSMajor) / sizeof(CSMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;

                case 2: //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;

                default: //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(CSMajor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CSMajor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR


            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR
            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(CSMinor) / sizeof(CSMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;

                case 2: //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;

                default: //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;
              }


              MIDI.sendNoteOn(CSMinor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CSMinor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

          }
        }

        if (keyPin == 35) {  //C#1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR



            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(CSMajor) / sizeof(CSMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;

                case 2: //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;

                default: //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(CSMajor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CSMajor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR


            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR
            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(CSMinor) / sizeof(CSMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;

                case 2: //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;

                default: //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;
              }


              MIDI.sendNoteOn(CSMinor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CSMinor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(CSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; //TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(CSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(CSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

          }
        }




        if (keyPin == 48) {  //D-1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR


            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(DMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(DMajor) / sizeof(DMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                default: //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(DMajor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(DMajor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(DMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(DMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }




          if (scale == 1 && arpDirection == 0) { //UP, MINOR


            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(DMinor) / sizeof(DMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                default: //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(DMinor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(DMinor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 24) {  //D0

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR


            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(DMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(DMajor) / sizeof(DMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                default: //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(DMajor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DMajor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(DMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(DMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }




          if (scale == 1 && arpDirection == 0) { //UP, MINOR


            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(DMinor) / sizeof(DMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                default: //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(DMinor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DMinor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }


        if (keyPin == 33) {  //D1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR


            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(DMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(DMajor) / sizeof(DMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                default: //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(DMajor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DMajor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(DMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(DMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }




          if (scale == 1 && arpDirection == 0) { //UP, MINOR


            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(DMinor) / sizeof(DMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                default: //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(DMinor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DMinor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }




        if (keyPin == 46) {  //D#-1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 150; //CHARTEUSE
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(DSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(DSMajor) / sizeof(DSMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //CHARTREUSE
                  redLEDValue = 150;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                default: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(DSMajor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(DSMajor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 150; //CHARTEUSE
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(DSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(DSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 150; //CHARTEUSE
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(DSMinor) / sizeof(DSMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //CHARTREUSE
                  redLEDValue = 150;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                default: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(DSMinor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(DSMinor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 150; //CHARTEUSE
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }


        if (keyPin == 22) {  //D#0

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 150; //CHARTEUSE
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(DSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(DSMajor) / sizeof(DSMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //CHARTREUSE
                  redLEDValue = 150;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                default: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(DSMajor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DSMajor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 150; //CHARTEUSE
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(DSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(DSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 150; //CHARTEUSE
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(DSMinor) / sizeof(DSMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //CHARTREUSE
                  redLEDValue = 150;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                default: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(DSMinor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DSMinor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 150; //CHARTEUSE
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 31) {  //D#1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 150; //CHARTEUSE
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(DSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(DSMajor) / sizeof(DSMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //CHARTREUSE
                  redLEDValue = 150;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                default: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(DSMajor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DSMajor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 150; //CHARTEUSE
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(DSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(DSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 150; //CHARTEUSE
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(DSMinor) / sizeof(DSMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //CHARTREUSE
                  redLEDValue = 150;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                default: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(DSMinor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DSMinor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 150; //CHARTEUSE
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(DSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(DSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }



        if (keyPin == 44) {  //E-1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(EMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(EMajor) / sizeof(EMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;

                  break;

                default: //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(EMajor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(EMajor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(EMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(EMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(EMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(EMinor) / sizeof(EMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;

                  break;

                default: //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(EMinor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(EMinor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(EMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(EMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 53) {  //E0

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(EMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(EMajor) / sizeof(EMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;

                  break;

                default: //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(EMajor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(EMajor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(EMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(EMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(EMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(EMinor) / sizeof(EMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;

                  break;

                default: //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(EMinor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(EMinor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(EMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(EMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 29) {  //E1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(EMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(EMajor) / sizeof(EMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;

                  break;

                default: //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(EMajor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(EMajor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(EMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(EMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(EMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(EMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(EMinor) / sizeof(EMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                case 2: //MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;

                  break;

                default: //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;
              }

              MIDI.sendNoteOn(EMinor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(EMinor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(EMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(EMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(EMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(EMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }



        if (keyPin == 42) {  //F-1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(FMajor) / sizeof(FMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;

                case 2: //ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;

                default: //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;
              }


              MIDI.sendNoteOn(FMajor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(FMajor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(FMinor) / sizeof(FMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;

                case 2: //ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;

                default: //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;
              }

              MIDI.sendNoteOn(FMinor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(FMinor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

        }

        if (keyPin == 51) {  //F0

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(FMajor) / sizeof(FMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;

                case 2: //ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;

                default: //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;
              }


              MIDI.sendNoteOn(FMajor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FMajor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(FMinor) / sizeof(FMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;

                case 2: //ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;

                default: //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;
              }

              MIDI.sendNoteOn(FMinor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FMinor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 27) {  //F1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(FMajor) / sizeof(FMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;

                case 2: //ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;

                default: //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;
              }


              MIDI.sendNoteOn(FMajor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FMajor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(FMinor) / sizeof(FMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;

                case 2: //ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;

                default: //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;
              }

              MIDI.sendNoteOn(FMinor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FMinor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 6;

              MIDI.sendNoteOn(FMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(FMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }



        if (keyPin == 40) { //F#-1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(FSMajor) / sizeof(FSMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;

                case 2: //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;

                default: //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(FSMajor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(FSMajor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(FSMinor) / sizeof(FSMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;

                case 2: //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;

                default: //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(FSMinor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(FSMinor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 49) { //F#0

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(FSMajor) / sizeof(FSMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;

                case 2: //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;

                default: //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(FSMajor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FSMajor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(FSMinor) / sizeof(FSMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;

                case 2: //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;

                default: //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(FSMinor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FSMinor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 25) { //F#1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(FSMajor) / sizeof(FSMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;

                case 2: //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;

                default: //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(FSMajor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FSMajor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(FSMinor) / sizeof(FSMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;

                case 2: //RED
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 0;
                  break;

                default: //CYAN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(FSMinor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FSMinor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //RED
            greenLEDValue = 0;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //CYAN
            greenLEDValue = 255;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO RED
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO CYAN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(FSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(FSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }


        if (keyPin == 38) {  //G

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(GMajor) / sizeof(GMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;

                case 2: //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;

                default: //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(GMajor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(GMajor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 0) { //UP, MINOR


            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(GMinor) / sizeof(GMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;

                case 2: //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;

                default: //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(GMinor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(GMinor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(GMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 47) {  //G0

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(GMajor) / sizeof(GMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;

                case 2: //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;

                default: //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(GMajor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GMajor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 0) { //UP, MINOR


            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(GMinor) / sizeof(GMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;

                case 2: //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;

                default: //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(GMinor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GMinor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(GMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 23) {  //G1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(GMajor) / sizeof(GMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;

                case 2: //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;

                default: //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(GMajor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GMajor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 0) { //UP, MINOR


            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(GMinor) / sizeof(GMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;

                case 2: //ORANGE
                  redLEDValue = 255;
                  greenLEDValue = 150;
                  blueLEDValue = 0;
                  break;

                default: //AZURE
                  redLEDValue = 0;
                  greenLEDValue = 150;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(GMinor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GMinor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //ORANGE
            greenLEDValue = 150;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;


              MIDI.sendNoteOn(GMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //AZURE
            greenLEDValue = 150;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ORANGE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AZURE
              greenLEDValue = greenLEDValue;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }



        if (keyPin == 36) {  //G#-1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR


            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(GSMajor) / sizeof(GSMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(GSMajor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(GSMajor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(GSMinor) / sizeof(GSMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(GSMinor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(GSMinor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 45) {  //G#0

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR


            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(GSMajor) / sizeof(GSMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(GSMajor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GSMajor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(GSMinor) / sizeof(GSMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(GSMinor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GSMinor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 69) {  //G#1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR


            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(GSMajor) / sizeof(GSMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(GSMajor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GSMajor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GSMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(GSMinor) / sizeof(GSMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 : //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //YELLOW
                  redLEDValue = 255;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //BLUE
                  redLEDValue = 0;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(GSMinor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GSMinor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 255; //YELLOW
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 0; //BLUE
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO YELLOW
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO BLUE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(GSMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(GSMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }



        if (keyPin == 34) {  //A-1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(AMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 150; //CHARTREUSE
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(AMajor) / sizeof(AMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 ://VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //CHARTREUSE
                  redLEDValue = 150;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(AMajor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(AMajor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(AMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }



            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 150; //CHARTREUSE
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(AMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR


            redLEDValue = 150; //CHARTREUSE
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(AMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(AMinor) / sizeof(AMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 ://VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //CHARTREUSE
                  redLEDValue = 150;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(AMinor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(AMinor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 150; //CHARTREUSE
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(AMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(AMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 43) {  //A0

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(AMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 150; //CHARTREUSE
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(AMajor) / sizeof(AMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 ://VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //CHARTREUSE
                  redLEDValue = 150;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(AMajor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(AMajor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(AMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }



            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 150; //CHARTREUSE
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(AMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR


            redLEDValue = 150; //CHARTREUSE
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(AMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(AMinor) / sizeof(AMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 ://VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //CHARTREUSE
                  redLEDValue = 150;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(AMinor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(AMinor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 150; //CHARTREUSE
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(AMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(AMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 68) {  //A1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(AMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 150; //CHARTREUSE
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(AMajor) / sizeof(AMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 ://VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //CHARTREUSE
                  redLEDValue = 150;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(AMajor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(AMajor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(AMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }



            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR

            redLEDValue = 150; //CHARTREUSE
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;


              MIDI.sendNoteOn(AMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(AMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR


            redLEDValue = 150; //CHARTREUSE
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(AMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(AMinor) / sizeof(AMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL

              switch (randColour) {

                case 1 ://VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //CHARTREUSE
                  redLEDValue = 150;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //VIOLET
                  redLEDValue = 150;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(AMinor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(AMinor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR

            redLEDValue = 150; //CHARTREUSE
            greenLEDValue = 255;
            blueLEDValue = 0;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(AMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 150; //VIOLET
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue; // TO CHARTREUSE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(AMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue; // TO VIOLET
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(AMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(AMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }


        if (keyPin == 32) {  //A#-1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(ASMajor) / sizeof(ASMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL
              switch (randColour) {

                case 1 ://MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(ASMajor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(ASMajor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }



            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

          }
          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR


            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(ASMinor) / sizeof(ASMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL
              switch (randColour) {

                case 1 ://MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(ASMinor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(ASMinor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR


            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 41) {  //A#0

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(ASMajor) / sizeof(ASMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL
              switch (randColour) {

                case 1 ://MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(ASMajor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(ASMajor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }



            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

          }
          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR


            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(ASMinor) / sizeof(ASMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL
              switch (randColour) {

                case 1 ://MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(ASMinor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(ASMinor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR


            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 67) {  //A#1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(ASMajor) / sizeof(ASMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL
              switch (randColour) {

                case 1 ://MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }


              MIDI.sendNoteOn(ASMajor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(ASMajor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }



            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

          }
          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR


            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(ASMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(ASMinor) / sizeof(ASMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL
              switch (randColour) {

                case 1 ://MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;

                case 2: //GREEN
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 0;
                  break;

                default: //MAGENTA
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 255;
                  break;
              }

              MIDI.sendNoteOn(ASMinor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(ASMinor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR


            redLEDValue = 0; //GREEN
            greenLEDValue = 255;
            blueLEDValue = 0;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //MAGENTA
            greenLEDValue = 0;
            blueLEDValue = 255;

            for (int i = arpLength - 1; i >= 0; i--)
            {
              redLEDValue = redLEDValue - 31; // TO GREEN
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue - 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO MAGENTA
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue + 31;

              MIDI.sendNoteOn(ASMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(ASMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }



        if (keyPin == 30) {  //B-1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR


            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(BMajor) / sizeof(BMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL
              switch (randColour) {

                case 1 ://ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;

                case 2: //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;

                default: //ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;
              }

              MIDI.sendNoteOn(BMajor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(BMajor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }



            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR


            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(BMinor) / sizeof(BMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL
              switch (randColour) {

                case 1 ://ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;

                case 2: //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;

                default: //ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;
              }

              MIDI.sendNoteOn(BMinor[idx] + octRange, 127, 1);
              MIDI.sendNoteOff(BMinor[idx] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR


            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 39) {  //B0

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR


            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(BMajor) / sizeof(BMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL
              switch (randColour) {

                case 1 ://ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;

                case 2: //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;

                default: //ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;
              }

              MIDI.sendNoteOn(BMajor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(BMajor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }



            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR


            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(BMinor) / sizeof(BMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL
              switch (randColour) {

                case 1 ://ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;

                case 2: //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;

                default: //ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;
              }

              MIDI.sendNoteOn(BMinor[idx] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(BMinor[idx] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR


            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange + 12, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange + 12, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }

        if (keyPin == 66) {  //B1

          if (scale == 0 && arpDirection == 0) { //UP, MAJOR


            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 1) {// DOWN, MAJOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 2) {// RANDOM, MAJOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(BMajor) / sizeof(BMajor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL
              switch (randColour) {

                case 1 ://ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;

                case 2: //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;

                default: //ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;
              }

              MIDI.sendNoteOn(BMajor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(BMajor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 3) {// UP/DOWN, MAJOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }



            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 0 && arpDirection == 4) {// DOWN/UP, MAJOR


            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMajor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(BMajor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 0) { //UP, MINOR

            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 1) { //DOWN, MINOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }


          if (scale == 1 && arpDirection == 2) {// RANDOM, MINOR

            for (int i = 0; i < arpLength; i++)
            { randomSeed(analogRead(A0));
              int idx = random(sizeof(BMinor) / sizeof(BMinor[0]));
              int randColour = random(1, 3); //DOESN'T LIKE TO BE BETWEEN 1 & 2, DUNNO WHY LOL
              switch (randColour) {

                case 1 ://ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;

                case 2: //AQUAMARINE
                  redLEDValue = 0;
                  greenLEDValue = 255;
                  blueLEDValue = 150;
                  break;

                default: //ROSE
                  redLEDValue = 255;
                  greenLEDValue = 0;
                  blueLEDValue = 150;
                  break;
              }

              MIDI.sendNoteOn(BMinor[idx] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(BMinor[idx] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 3) {// UP/DOWN, MINOR


            redLEDValue = 0; //AQUAMARINE
            greenLEDValue = 255;
            blueLEDValue = 150;


            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }


            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }

          if (scale == 1 && arpDirection == 4) {// DOWN/UP, MINOR

            redLEDValue = 255; //ROSE
            greenLEDValue = 0;
            blueLEDValue = 150;

            for (int i = arpLength - 1; i >= 0; i--)
            {

              redLEDValue = redLEDValue - 31; // TO AQUAMARINE
              greenLEDValue = greenLEDValue + 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }

            for (int i = 0; i < arpLength; i++)
            {

              redLEDValue = redLEDValue + 31; // TO ROSE
              greenLEDValue = greenLEDValue - 31;
              blueLEDValue = blueLEDValue;

              MIDI.sendNoteOn(BMinor[i] + octRange + 24, 127, 1);
              MIDI.sendNoteOff(BMinor[i] + octRange + 24, 0, 1);

              analogWrite(redLED, redLEDValue);
              analogWrite(greenLED, greenLEDValue);
              analogWrite(blueLED, blueLEDValue);

              delay(delayPerBeat);
            }
          }
        }


      }
    }

  }



  if (menu == 2  && select == 1) { //TEACH


    if (go == 1) {
      for (int i = 0; i < numKeys; i++) {

        int keyStatus = digitalRead(midiKeys[i].keyPin); //Create int variable keyStatus and read the status of each key
        if ((keyStatus == LOW) && (keyStates[i] == false)) { //If keyStatus = LOW (ie - key ON) AND current keyState = FALSE

          MIDI.sendNoteOn(midiKeys[i].midiNote + octRange, 127, 1); //Turn midi note ON: velocity 127, midi channel 1.
          //Mark the button  state as TRUE, since the button is now ON
          keyStates[i] = true;
        }

        else if ((keyStatus == HIGH) && (keyStates[i] == true)) //Else if keyStatus = HIGH (ie - key OFF) AND current keyState = TRUE
        {
          MIDI.sendNoteOff(midiKeys[i].midiNote + octRange, 0, 1); //turn midi note off, midi channel 1.
          //Mark the button  state as FALSE, since the button is now OFF
          keyStates[i] = false;
        }
      }

    }

    else if (go == 0) {

    }
  }


  if (menu == 4 && select == 1) { //MIDI PLAYBACK



    if (playbackMenu == 4 && enc_switch == 1) {

      isRunning = true;
      currentStep = 0;
      startTime = currentTime;

    }

    if (isRunning) {

      // check if the next timestamp has been reached
      while ((currentTime - startTime) >= (midiData[currentStep].timestamp / bpmPerc)) {


        switch (playTrans) {


          case -11:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct - 11); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case -10:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct - 10); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case -9:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct - 9); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case -8:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct - 8); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case -7:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct - 7); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case -6:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct - 6); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case -5:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct - 5); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case -4:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct - 4); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case -3:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct - 3); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case -2:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct - 2); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case -1:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct - 1); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;


          case 0:
            // play the note
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case 1:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct + 1); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case 2:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct + 2); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case 3:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct + 3); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case 4:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct + 4); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case 5:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct + 5); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case 6:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct + 6); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case 7:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct + 7); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case 8:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct + 8); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case 9:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct + 9); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case 10:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct + 10); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          case 11:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct + 11); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;

          default:
            Serial.write(midiData[currentStep].statusByte); //NOTE ON/OFF CH. 1
            Serial.write(midiData[currentStep].dataByte1 + playbackOct - 11); //NOTE
            Serial.write(midiData[currentStep].dataByte2); //VELOCITY
            break;
        }

        // move on to the next step
        currentStep ++;

        // end the sequence
        if (currentStep == (sizeof(midiData) / sizeof(midiData[0]))) {
          isRunning = false;
          break;
        }
      }
    }

  }
}



void oLEDStart() {

  display.setCursor(0, 0);

  for ( int i = 0; i < 64; i++) {
    display.setCursor(i, i);
    display.clearDisplay();
    display.println("MIDI CONTROLLER V1");
    display.display();
  }

  display.clearDisplay();
  display.display();
}






void rgbLED() {


  if (select == 0) { //MAIN MENU

    analogWrite(redLED,     255); //MAGENTA
    analogWrite(greenLED, 0);
    analogWrite(blueLED,  255);
  }




  if (menu == 0  && select == 1) { //PLAY

    analogWrite(redLED,     255); //RED
    analogWrite(greenLED, 0);
    analogWrite(blueLED,  0);

    if ((midiKeys[0].keyPin = 52) && (keyStates[0] == true) || (midiKeys[12].keyPin = 28) && (keyStates[12] == true)
        || (midiKeys[24].keyPin = 37) && (keyStates[24] == true ) || (midiKeys[36].keyPin = 65) && (keyStates[36] == true )) { //C
      analogWrite(redLED, 255);
      analogWrite(greenLED, 0);
      analogWrite(blueLED, 0);
    }

    else if ((midiKeys[1].keyPin = 50) && (keyStates[1] == true) || (midiKeys[13].keyPin = 26) && (keyStates[13] == true) || (midiKeys[25].keyPin = 35) && (keyStates[25] == true)) { //C#
      analogWrite(redLED, 255);
      analogWrite(greenLED, 150);
      analogWrite(blueLED, 0);
    }

    else if ((midiKeys[2].keyPin = 48) && (keyStates[2] == true) || (midiKeys[14].keyPin = 24) && (keyStates[14] == true) || (midiKeys[26].keyPin = 33) && (keyStates[26] == true)) {//D
      analogWrite(redLED, 255);
      analogWrite(greenLED, 255);
      analogWrite(blueLED, 0);
    }

    else if ((midiKeys[3].keyPin = 46) && (keyStates[3] == true) || (midiKeys[15].keyPin = 22) && (keyStates[15] == true) || (midiKeys[27].keyPin = 31) && (keyStates[27] == true)) { //D#
      analogWrite(redLED, 150);
      analogWrite(greenLED, 255);
      analogWrite(blueLED, 0);
    }

    else if ((midiKeys[4].keyPin = 44) && (keyStates[4] == true) || (midiKeys[16].keyPin = 53) && (keyStates[16] == true) || (midiKeys[28].keyPin = 29) && (keyStates[28] == true)) { // E
      analogWrite(redLED, 0);
      analogWrite(greenLED, 255);
      analogWrite(blueLED, 0);
    }

    else if ((midiKeys[5].keyPin = 42) && (keyStates[5] == true) || (midiKeys[17].keyPin = 51) && (keyStates[17] == true) || (midiKeys[29].keyPin = 27) && (keyStates[29] == true)) { //F
      analogWrite(redLED, 0);
      analogWrite(greenLED, 255);
      analogWrite(blueLED, 150);
    }

    else if ((midiKeys[6].keyPin = 40) && (keyStates[6] == true)  || (midiKeys[18].keyPin = 49) && (keyStates[18] == true) || (midiKeys[30].keyPin = 25) && (keyStates[30] == true)) { //F#
      analogWrite(redLED, 0);
      analogWrite(greenLED, 255);
      analogWrite(blueLED, 255);
    }

    else if ((midiKeys[7].keyPin = 38) && (keyStates[7] == true) || (midiKeys[19].keyPin = 47) && (keyStates[19] == true) || (midiKeys[31].keyPin = 23) && (keyStates[31] == true)) { //G
      analogWrite(redLED, 0);
      analogWrite(greenLED, 150);
      analogWrite(blueLED, 255);
    }

    else if ((midiKeys[8].keyPin = 36) && (keyStates[8] == true) || (midiKeys[20].keyPin = 45) && (keyStates[20] == true) || (midiKeys[32].keyPin = 69) && (keyStates[32] == true)) { //G#
      analogWrite(redLED, 0);
      analogWrite(greenLED, 0);
      analogWrite(blueLED, 255);
    }


    else if ((midiKeys[9].keyPin = 34) && (keyStates[9] == true) || (midiKeys[21].keyPin = 43) && (keyStates[21] == true) || (midiKeys[33].keyPin = 68) && (keyStates[33] == true)) { //A
      analogWrite(redLED, 150);
      analogWrite(greenLED, 0);
      analogWrite(blueLED, 255);
    }

    else if ((midiKeys[10].keyPin = 32) && (keyStates[10] == true) || (midiKeys[22].keyPin = 41) && (keyStates[22] == true) || (midiKeys[34].keyPin = 67) && (keyStates[34] == true)) { //A#
      analogWrite(redLED, 255);
      analogWrite(greenLED, 0);
      analogWrite(blueLED, 255);
    }

    else if ((midiKeys[11].keyPin = 30) && (keyStates[11] == true) || (midiKeys[23].keyPin = 39) && (keyStates[23] == true) || (midiKeys[35].keyPin = 66) && (keyStates[35] == true)) { //B
      analogWrite(redLED, 255);
      analogWrite(greenLED, 0);
      analogWrite(blueLED, 150);
    }
  }



  else if (menu == 1  && select == 1) { //ARP
    analogWrite(redLED, 0); //MAGENTA
    analogWrite(greenLED, 255);
    analogWrite(blueLED, 255);

  }


  else  if (menu == 2  && select == 1) { //TEACH

    if (total == 0) {
      analogWrite(redLED, 0);
      analogWrite(greenLED, 0);
      analogWrite(blueLED, 255); //BLUE
    }

    else  if (correctCounter > incorrectCounter) {
      analogWrite(redLED, 0);
      analogWrite(greenLED, 255);
      analogWrite(blueLED, 0);
    }

    else if (incorrectCounter > correctCounter) {
      analogWrite(redLED, 255);
      analogWrite(greenLED, 0);
      analogWrite(blueLED, 0);
    }

    else if (incorrectCounter == correctCounter) {
      analogWrite(redLED, 255);
      analogWrite(greenLED, 255);
      analogWrite(blueLED, 0);
    }
  }

  else  if (menu == 3  && select == 1) { //OPTIONS

    if (invD == 0) {
      analogWrite(redLED, 0);
      analogWrite(greenLED, 0);
      analogWrite(blueLED, 0);

    }

    else if (invD == 1) {
      analogWrite(redLED, 255);
      analogWrite(greenLED, 255);
      analogWrite(blueLED, 255);

    }

  }

  else if (menu == 4  && select == 1) { //MIDI PLAYBACK
    analogWrite(redLED, 0); //AZURE
    analogWrite(greenLED, 150);
    analogWrite(blueLED, 255);

  }




}
