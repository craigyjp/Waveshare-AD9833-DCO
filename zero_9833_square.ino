/*
AD9833 Waveform Module 
*/

#include <SPI.h>
#include "pitches.h"
#include "Parameters.h"
#include <MIDI.h>
#include "AD9833.h"

#define MIDI_CHANNEL 1

AD9833 AD(5, 3, 6);   //  SW SPI over the HW SPI pins (UNO);
AD9833 AD1(9, 3, 6);  //  SW SPI over the HW SPI pins (UNO);

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void setup() {


  MIDI.begin(0);
  MIDI.setHandleControlChange(myControlChange);
  MIDI.setHandleNoteOn(DinHandleNoteOn);
  MIDI.setHandleNoteOff(DinHandleNoteOff);
  MIDI.setHandlePitchBend(myPitchBend);

  SPI.begin();

  AD.begin();
  AD1.begin();

  AD.setWave(AD9833_SQUARE1);
  AD.setFrequency(880.0, 0);
  AD.setFrequencyChannel(0);
  AD1.setWave(AD9833_SQUARE1);
  AD1.setFrequency(880.0, 0);
  AD1.setFrequencyChannel(0);

  numnotes = sizeof(notes) / sizeof(notes[0]);


  factor = 1;

  delay(2000);
}

void myControlChange(byte channel, byte control, byte value) {
  switch (control) {
    case 5:
      glidetime = map(value, 0, 127, 0, 4000);
      break;
    case 16:
      mode = value;
      break;
    case 65:
      glidesw = map(value, 0, 1, 1, 0);
      break;
    case 70:
      waveform = value;
      break;
    case 71:
      waveform = value;
      break;
    case 18:
      detune = map(value, 0, 127, 0, 15);
      break;
    case 17:
      oct_sel1 = map(value, 0, 127, 0, 2);
      switch (oct_sel1) {
        case 0:
          oct_sw1 = 0.5;
          break;
        case 1:
          oct_sw1 = 1;
          break;
        case 2:
          oct_sw1 = 2;
          break;
      }
      break;
    case 19:
      oct_sel2 = map(value, 0, 127, 0, 2);
      switch (oct_sel2) {
        case 0:
          oct_sw2 = 0.5;
          break;
        case 1:
          oct_sw2 = 1;
          break;
        case 2:
          oct_sw2 = 2;
          break;
      }
      break;
  }
}

void DinHandleNoteOn(byte channel, byte pitch, byte velocity) {

  if (channel == MIDI_CHANNEL) {

    if (velocity == 0) {
      // Handle this as a "note off" event
      DinHandleNoteOff(channel, pitch, velocity);
      return;
    }

    noteon = pitch;
  }
}

void DinHandleNoteOff(byte channel, byte note, byte velocity) {
  if (channel == MIDI_CHANNEL) {
  }
}

void myPitchBend(byte channel, int bend) {

    if (bend >= 0) {
        // Increase frequency until it's twice the original at maximum positive bend
        factor = 1.0 + bend / 8192.0;
    } else {
        // Decrease frequency until it's half the original at maximum negative bend
        factor = 1.0 / (1.0 - bend / 8192.0);
    }
    
}

void loop() {

  //------------------- handle the MIDI --------------------------
  MIDI.read();

  // and AD9833 updates.
    frequency1 = notes[(noteon - MIDI_NOTE_START)];
    frequency1 = (frequency1 * oct_sw1);
    frequency1 = (frequency1 * factor);
    AD.setFrequency(frequency1, 0);
    int frequency2 = notes[(noteon - MIDI_NOTE_START)];
    frequency2 = (frequency2 * oct_sw2);
    frequency2 = (frequency2 * factor);
    frequency2 = (frequency2 - detune);
    AD1.setFrequency(frequency2, 0);
}
