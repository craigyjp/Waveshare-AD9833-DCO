# Waveshare Zero controlling two AD9833 function generators to create a dual DCO voice core.

Using the RP2040 based Waveshare Zero board I'm controlling the pitch of the AD9833 function generators.

The Zero receives MIDI note and CC information to control aspects of the frequency etc.

Midi Note On (by channel)- sets the pitch of the note according to a lookup table

MIDI Pitchbend (Channel 1) - creates an octave bend in each direction.

MIDI CC 18 (0-127) sets the detune for the second AD9833

MIDI CC 17 (0-127) sets the octave of DCO1 ( -1, 0 and +1 )

MIDI CC 19 (0-127) sets the octave of DCO2 ( -1, 0 and +1 )

Currently using a Triangle output and waveshaping to create the basic requirements, sawtooth, pulse width, triangle and a sub oscillator.

So far created the Triangle and pulse width successfully

# TODO:

Try with a squarewave core output

Implement modulation.

Implement glide.
