const int SINE = 0x2000;                    // Define AD9833's waveform register value.
const int SQUARE = 0x2028;                  // When we update the frequency, we need to
const int TRIANGLE = 0x2002;                // define the waveform when we end writing.    

int wave = 0;
int waveType = SINE;
int wavePin = 8;

const float refFreq = 25000000.0;           // On-board crystal reference frequency

unsigned long freq = 880;               // Set initial frequency.
unsigned long freqOld = freq;

unsigned long incr = 1;
unsigned long oldIncr = 1;

boolean glidesw = false;
int glidetime = 0;
int detune = 0;
int noteVal = 0;
int type, channel, d1, d2;
byte noteon = 36;
double factor = 0.0001;
float newbend = 0.01;
unsigned long frequency1 = 1;
unsigned long frequency2 = 1;

// Global variables for portamento
int prevNoteVal = 0;
float current_freq = 0;
float target_freq = 0;
float glide_rate = 0;
unsigned long lastGlideTime = 0;
const int minGlideTime = 0; // Minimum glide time in milliseconds
const int maxGlideTime = 4000; // Maximum glide time in milliseconds
float exponent = 2.0; // Change this value as needed
boolean osc2 = true;

int k = 1;
float AM_mod = 1;  //AM modulation rate
float f = 0;
int slice_num = 0;
float osc_freq = 0;
float mod = 0;
int wavetable[256];        //1024 resolution , 256 rate
float mod_wavetable[256];  //1st modulated wavetable
int mod2_wavetable[256];   //2nd modulated wavetable
float calb = 1.142;        //calibration for reduce resistance error
int freq_pot, fm_input, oct_sel1, oct_sel2, mode, pb_input;
int waveform = 0;
float oct_sw1 = 1.00;
float oct_sw2 = 1.00;

// Set up the MIDI codes to respond to by listing the lowest note
#define MIDI_NOTE_START 23   // B0

// Set the notes to be played by each key
int notes[] = {
  NOTE_B0,
  NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_F1, NOTE_FS1, NOTE_G1, NOTE_GS1, NOTE_A1, NOTE_AS1, NOTE_B1,
  NOTE_C2, NOTE_CS2, NOTE_D2, NOTE_DS2, NOTE_E2, NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_GS2, NOTE_A2, NOTE_AS2, NOTE_B2,
  NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3,
  NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
  NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
  NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
  NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7,
  NOTE_C8, NOTE_CS8, NOTE_D8, NOTE_DS8
};
int numnotes;