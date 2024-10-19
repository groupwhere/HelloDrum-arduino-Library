/*
  EXAMPLE - MUX Sensing

  With this sample code, you can make 4 pads with a 74HC4052. 
  https://github.com/RyoKosaka/HelloDrum-arduino-Library
*/

///////////////////////////////   SETTING VALUE   ///////////////////////////////////

//Determine the setting value.
//By changing the number in this array you can set sensitivity, threshold and so on.

byte PAD1[5] = {
    100, //sensitivity
    10,  //threshold
    10,  //scan time
    30,  //mask time
    38   //note
};

byte PAD2[5] = {
    100, //sensitivity
    10,  //threshold
    10,  //scan time
    30,  //mask time
    36   //note
};

byte PAD3[5] = {
    100, //sensitivity
    10,  //threshold
    10,  //scan time
    30,  //mask time
    41   //note
};

byte PAD4[5] = {
    100, //sensitivity
    10,  //threshold
    10,  //scan time
    30,  //mask time
    46   //note
};

/////////////////////////////////////////////////////////////////////////////////////

#include <hellodrum.h>

//Using MIDI Library. If you want to use USB-MIDI, comment out the next two lines.
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

//Uncomment the next two lines for using USB-MIDI with atmega32u4 or Teensy
//#include <USB-MIDI.h>
//USBMIDI_CREATE_DEFAULT_INSTANCE();

/*
Mux Breakout ----------- Arduino
S0 ------------------- 2
S1 ------------------- 3
Z -------------------- A0
 */
//Define MUX Pins
HelloDrumMUX_4052 mux(2, 3, 0); //D2, D3, A0

HelloDrum pad1(0); //mux pin
HelloDrum pad2(1); //mux pin
HelloDrum pad3(2); //mux pin
HelloDrum pad4(3); //mux pin

void setup()
{
  //If you use Hairless MIDI, you have to comment out the next line.
  MIDI.begin(10);

  //And uncomment the next two lines.
  //MIDI.begin();
  //Serial.begin(38400);
}

void loop()
{
  //scanning 8 piezos.
  mux.scan();

  //Piezo sensing is done in this line. And it is returned as a velocity of 127 stages.
  //For each piezo, one line is required.
  pad1.singlePiezoMUX(PAD1[0], PAD1[1], PAD1[2], PAD1[3]);
  pad2.singlePiezoMUX(PAD2[0], PAD2[1], PAD2[2], PAD2[3]);
  pad3.singlePiezoMUX(PAD3[0], PAD3[1], PAD3[2], PAD3[3]);
  pad4.singlePiezoMUX(PAD4[0], PAD4[1], PAD4[2], PAD4[3]);

  if (pad1.hit == true)
  {
    MIDI.sendNoteOn(PAD1[4], pad1.velocity, 10); //(note, velocity, channel)
    MIDI.sendNoteOff(PAD1[4], 0, 10);
  }

  if (pad2.hit == true)
  {
    MIDI.sendNoteOn(PAD2[4], pad2.velocity, 10); //(note, velocity, channel)
    MIDI.sendNoteOff(PAD2[4], 0, 10);
  }

  if (pad3.hit == true)
  {
    MIDI.sendNoteOn(PAD3[4], pad3.velocity, 10); //(note, velocity, channel)
    MIDI.sendNoteOff(PAD3[4], 0, 10);
  }

  if (pad4.hit == true)
  {
    MIDI.sendNoteOn(PAD4[4], pad4.velocity, 10); //(note, velocity, channel)
    MIDI.sendNoteOff(PAD4[4], 0, 10);
  }
}
