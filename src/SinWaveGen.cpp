//  SinWaveGen is a synchronised sinewave generator that takes a
//  square input on an Arduino Uno, Nano, etc digital pin and
//  outputs a loosely synchronised sinusoid wave as opposite
//  polarity PWM signals on pins 5 (+ve) and 6 (-ve).
//  
//  It's intended to test the timings and reliability when
//  generating a sychronised sinewave at frequencies equal to
//  the first 2 octaves of a bass guitar and whether it's feasable
//  as a tone generator for the Dan the Bass Man guitar pedal. 
//  It would probably be used in conjunction with an analog VCA
//  and Attack/Decay circuit as I'm not sure at this stage if it
//  has the bandwidth to do that digitally, without writing the
//  sketch entirely in assembly code.
//  
//  ©2023 Crunchysteve bandmassa@gmail.com Modified MIT licence,
//  commercial developers should negotiate a paid licence with
//  the above author.

#include "Arduino.h"                            //  Remove for use with ArduinoIDE (PIO only)
#include "Sinewave.h"                           //  uses the custom Sinewave class
#include "Settings.h"                           //  include file containing constants and variables
#include <Chrono.h>                             //  uses the Chrono class by 
#include <math.h>                               //  uses the system math class for sinf (floating point sin)

Chrono sampleTimer(Chrono::MICROS);             //  instantiate class of Chrono to time sample output
Sinewave sine;                                  //  instantiate class of sine to generate output samples

void setup(){
  // Serial.begin(9600);                        //  Serial output for debugging

  // Set PWM carrier frequency
  TCCR0B = TCCR0B & B11111000 | B00000001;      // set to 62500.00 Hz

  //  set fast analogRead (1uS) (analogRead() to be used for trigger velocity when added)
  ADCSRA &= ~bit (ADPS0) | bit (ADPS1) | bit (ADPS2);   
                                                //  ^ clear analogRead() default timing of 104uS
  ADCSRA |= bit (ADPS0);                        //  set analogRead() default timing to 1.5uS


  pinMode(INPUT_PIN,INPUT);                     //  set INPUT_PIN as an input
  pinMode(LO_OUT_PIN,OUTPUT);                   //  set LO_OUT_PIN as an output 
  pinMode(HI_OUT_PIN,OUTPUT);                   //  set HI_OUT_PIN as an output (for bilateral output)
  sampleTimer.start();                          //  start Chrono::sampleTimer
}

void loop(){
  //  get wavelength in uS
  if(sine.getWavelength(INPUT_PIN) != 0){
    otPtWvLn = 2 * sine.getWavelength(INPUT_PIN);
                                                //  drop sinewave by one octave
  } else {
    otPtWvLn = 0.0;                             //  or not output anything if no input
  }
  
  //  generate synchronised sinewave
  if(otPtWvLn != 0.0 && sampleTimer.hasPassed(smplWvLn)){
                                                //  if the sampleTimer returns true
    sampleTimer.restart();                      //  restart the timer
    float samplesWidth = 2 * PI * smplWvLn / otPtWvLn;
    float output = sine.calcSample(newIncrement, bitscale, amplitude, samplesWidth);
    newIncrement = sine.incrementReturn;
    analogWrite(LO_OUT_PIN,(unsigned long)output >> 8);
    analogWrite(HI_OUT_PIN,255 - ((unsigned long)output >> 8));
  }
}
