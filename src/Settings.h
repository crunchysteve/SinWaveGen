//  SinWaveGen Declarations and Variables Settings Header

#ifndef Settings_h
  #define Settings_h
    #define INPUT_PIN  2
    #define LO_OUT_PIN 5
    #define HI_OUT_PIN 6

    const float smplRate = 31250;               //  deault playback rate (31250 is half PWM carrier)
    const float smplWvLn = 1000000 / smplRate;  //  sample rate wavelength in uS
    float newIncrement = 0.0;
    float otPtWvLn = 0.0;                       //  output wavelength in uS
    float inc = 2 * PI * smplWvLn / otPtWvLn;   //  radians increment per sample
    float i = 0.0;                              //  increment counter by 'inc' radians
    float bitscale = 32767.0;                   //  peak amplitude sine factor
    float amplitude = 0.701;                    //  default amplitude with 3dB headroom (0.5 for 6dB headroom)
#endif