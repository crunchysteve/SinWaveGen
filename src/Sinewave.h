//  SinWaveGen Sinewave Class Header (ToDo: separate into header, source files & 
//  custom library folder)

#ifndef Sinewave_h
  #define Sinewave_h
  class Sinewave{
    public:
      float incrementReturn = 0;                //  public access to new phase angle
      float sample = 0;                         //  public access to new amplitude

      //  Public function generates sine wave at "radians" steps
      float calcSample(float currentIncrement,  //  local variable takes previous phase angle
                       float scale,             //    "       "      "   bitrate (opt)
                       float level,             //    "       "      "   max amplitude
                       float radians){          //    "       "      "   phase step value (rads)
        if(currentIncrement < 2 * PI){
          //  scales sample to 12 bit amplitude (0 to 4095)
          sample = (sinf(currentIncrement) * scale * level) + scale;
          //  increments phase angle
          incrementReturn = currentIncrement + radians;
        } else if (currentIncrement >= 2 * PI){
          //  resets phase angle after 2π Radians (360°)
          currentIncrement = 0.0;
        }
        return sample;    //  return current sample
      }

      //  Public function calculates sinewave period from input squarewave
      float getWavelength(int PIN){
        return (float)(pulseIn(PIN,HIGH) + pulseIn(PIN,LOW));        //  Measure Hi/Lo pulses,
                                                                     //  return as float
      }
  };
#endif