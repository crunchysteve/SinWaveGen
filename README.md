## SineWaveGen

SinWaveGen is a synchronised sinewave generator that takes a
square input on an Arduino Uno, Nano, etc digital pin and
outputs a loosely synchronised sinusoid wave as opposite
polarity PWM signals on pins 5 (+ve) and 6 (-ve).

It's intended to test the timings and reliability when
generating a sychronised sinewave at frequencies equal to
the first 2 octaves of a bass guitar and whether it's 
feasable as a tone generator for "top secret" guitar pedal. 
It would probably be used in conjunction with an analog VCA
and Attack/Decay circuit as I'm not sure at this stage if an
AT328p has the bandwidth to do that digitally, without 
writing the sketch entirely in assembly code. I'm pretty
sure that option is beyond me at this stage.

My aim is to create this in pure C/C++ code, in order to 
make it compatible with almost any microcontroller.

Before making public...
ToDos:  Turn off output when input timing is null
        Create proper C++ class with header and source

©2023 [Crunchysteve bandmassa@gmail.com](bandmassa@gmail.com) 
Modified MIT licence, commercial developers should negotiate 
a paid licence with the above author.
