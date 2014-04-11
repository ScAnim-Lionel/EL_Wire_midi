#include <MIDI.h>
#define BoardNum 1 // Set the board Number here

// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation here: 
// http://arduinomidilib.sourceforge.net/class_m_i_d_i___class.html

byte outelwire = 0;

void HandleNoteOn(byte channel, byte pitch, byte velocity) { 

  // Do whatever you want when you receive a Note On.
  // channel is used for Board Number
  if (channel == BoardNum) {

    // 2 bits left shift, used EL Wire output are from D2 to D6 = PORTD (digital pins 0 to 7)  
    outelwire = pitch <<2;  
    PORTD = outelwire;
  }     
  /*
  if (velocity == 0) {
   // This acts like a NoteOff.
   }  */

  // Try to keep your callbacks short (no delays ect) as the contrary would slow down the loop()
  // and have a bad impact on real-time performance.
}

void setup() {
  // Initiate MIDI communications, listen to all channels
  MIDI.begin(MIDI_CHANNEL_OMNI);    

  // Connect the HandleNoteOn function to the library, so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
  
  DDRD = B11111100;  // sets Arduino pins 2 to 7 as outputs, pin 0 as input
}


void loop() {
  // Call MIDI.read the fastest you can for real-time performance.
  MIDI.read();

  // There is no need to check if there are messages incoming if they are bound to a Callback function.
}
