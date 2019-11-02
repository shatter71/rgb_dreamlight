    /****************************************
    Code from Adafruit and ctbaker
    ****************************************/

    #include <Adafruit_NeoPixel.h>
     
    #define DATA_PIN      3 // Data pin to communicate with the LEDs
    #define NUM_LEDS      64 // Number of LEDs to control
    const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
    unsigned int sample;
    double baseValue = 0.11; // Ambient noise level voltage value
    double peakValue = 0.25; // When volts is this value or higher, all LEDs will be lit up
    double voltsMax = peakValue;
    int numSegments = 8; // Number of segments for spectrum analyzer
    int i = 0;
    double volts = 0;
    int maxBright = 200;
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);
    // Set the segmentation values for when each color band is lit
    double seg1 = ((peakValue - baseValue)*1/numSegments) + baseValue;
    double seg2 = ((peakValue - baseValue)*2/numSegments) + baseValue;
    double seg3 = ((peakValue - baseValue)*3/numSegments) + baseValue;
    double seg4 = ((peakValue - baseValue)*4/numSegments) + baseValue;
    double seg5 = ((peakValue - baseValue)*5/numSegments) + baseValue;
    double seg6 = ((peakValue - baseValue)*6/numSegments) + baseValue;
    double seg7 = ((peakValue - baseValue)*7/numSegments) + baseValue;
    double seg8 = ((peakValue - baseValue)*8/numSegments) + baseValue;
    uint32_t black = strip.Color(0, 0, 0);
    uint32_t red = strip.Color(255, 0, 0);
    uint32_t green = strip.Color(0, 255, 0);
    uint32_t blue = strip.Color(0, 0, 255);
    uint32_t yellow = strip.Color(255, 255, 0);
    uint32_t orange = strip.Color(255, 128, 0);
    uint32_t purple = strip.Color(128, 0, 255);
    uint32_t white = strip.Color(255, 255, 255);
    uint32_t cyan = strip.Color(0, 255, 255);
    void setup() 
    {
       strip.begin();
       strip.setBrightness(maxBright);
       strip.clear();
       delay(1000);
    }
          
    void loop() 
    {   
       unsigned long startMillis= millis();  // Start of sample window
       unsigned int peakToPeak = 0;   // peak-to-peak level
     
       unsigned int signalMax = 0;
       unsigned int signalMin = 1024;
     
       // collect data for 50 mS
       while (millis() - startMillis < sampleWindow)
       {
          sample = analogRead(1);
          if (sample < 1024)  // toss out spurious readings
          {
             if (sample > signalMax)
             {
                signalMax = sample;  // save just the max levels
             }
             else if (sample < signalMin)
             {
                signalMin = sample;  // save just the min levels
             }
          }
       }
       peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
       double volts = (peakToPeak * 5.0) / 1024;  // convert to volts 1024

// Set a new maximum value for voltage and rescale based on the new max value
// This will dampen over driven audio when compared to starting maximum expected
// audio level
      if (i <= 20 && peakValue < ((signalMax * 5.0) / 1024))
      {
        peakValue = (signalMax * 5.0) / 1024;  // convert maximum signal value to volts
      }
      if (i > 20)
      {
        i = 0;
        // Set the segmentation values for when each color band is lit
        double seg1 = ((peakValue - baseValue)*1/numSegments) + baseValue;
        double seg2 = ((peakValue - baseValue)*2/numSegments) + baseValue;
        double seg3 = ((peakValue - baseValue)*3/numSegments) + baseValue;
        double seg4 = ((peakValue - baseValue)*4/numSegments) + baseValue;
        double seg5 = ((peakValue - baseValue)*5/numSegments) + baseValue;
        double seg6 = ((peakValue - baseValue)*6/numSegments) + baseValue;
        double seg7 = ((peakValue - baseValue)*7/numSegments) + baseValue;
        double seg8 = ((peakValue - baseValue)*8/numSegments) + baseValue;
        peakValue = voltsMax;
      }
      i = i + 1;

//        diagStrips(volts, seg1, seg2, seg3, seg4, seg5, seg6, seg7, seg8);
        diagInsideOut(volts, seg1, seg2, seg3, seg4, seg5, seg6, seg7, seg8);
//        oneColor();
//        multiColor(volts, seg1, seg2, seg3, seg4, seg5, seg6, seg7, seg8);
//        vertStrips(volts, seg1, seg2, seg3, seg4, seg5, seg6, seg7, seg8);
//        ringsOutToIn(volts, seg1, seg2, seg3, seg4, seg5, seg6, seg7, seg8);
//        ringsInToOut(volts, seg1, seg2, seg3, seg4, seg5, seg6, seg7, seg8);
//        variBright(volts, maxBright, numSegments, seg1, seg2, seg3, seg4, seg5, seg6, seg7, seg8);
        strip.show();
        strip.clear();
    }

    //
    //Write to RGB LED Matrix based on value of volts
    //
    
    void diagStrips(double volts, double seg1, double seg2, double seg3, double seg4, double seg5, double seg6, double seg7, double seg8) // Display diagonal strips of light across the 8x8 matrix
    {
       if (volts < seg1)
       {
            strip.clear();
       }
       if (volts >= seg1)
       {
          strip.setPixelColor(0, 127, 0, 255); // Purple
          strip.setPixelColor(1, 127, 0, 255); // Purple
          strip.setPixelColor(8, 127, 0, 255); // Purple
       }
       if (volts >= seg2)
       {
          strip.setPixelColor(2, 0, 0, 255); // Blue
          strip.setPixelColor(3, 0, 0, 255); // Blue
          strip.setPixelColor(9, 0, 0, 255); // Blue
          strip.setPixelColor(10, 0, 0, 255); // Blue
          strip.setPixelColor(16, 0, 0, 255); // Blue
          strip.setPixelColor(17, 0, 0, 255); // Blue
          strip.setPixelColor(24, 0, 0, 255); // Blue
       }
       if (volts >= seg3)
       {
          strip.setPixelColor(4, 0, 255, 255); // Cyan
          strip.setPixelColor(5, 0, 255, 255); // Cyan
          strip.setPixelColor(11, 0, 255, 255); // Cyan
          strip.setPixelColor(12, 0, 255, 255); // Cyan
          strip.setPixelColor(18, 0, 255, 255); // Cyan
          strip.setPixelColor(19, 0, 255, 255); // Cyan
          strip.setPixelColor(25, 0, 255, 255); // Cyan
          strip.setPixelColor(26, 0, 255, 255); // Cyan
          strip.setPixelColor(32, 0, 255, 255); // Cyan
          strip.setPixelColor(33, 0, 255, 255); // Cyan
          strip.setPixelColor(40, 0, 255, 255); // Cyan
       }
       if (volts >= seg4)
       {
          strip.setPixelColor(6, 0, 255, 0); // Green
          strip.setPixelColor(7, 0, 255, 0); // Green
          strip.setPixelColor(13, 0, 255, 0); // Green
          strip.setPixelColor(14, 0, 255, 0); // Green
          strip.setPixelColor(20, 0, 255, 0); // Green
          strip.setPixelColor(21, 0, 255, 0); // Green
          strip.setPixelColor(27, 0, 255, 0); // Green
          strip.setPixelColor(28, 0, 255, 0); // Green
          strip.setPixelColor(34, 0, 255, 0); // Green
          strip.setPixelColor(35, 0, 255, 0); // Green
          strip.setPixelColor(41, 0, 255, 0); // Green
          strip.setPixelColor(42, 0, 255, 0); // Green
          strip.setPixelColor(48, 0, 255, 0); // Green
          strip.setPixelColor(49, 0, 255, 0); // Green
          strip.setPixelColor(56, 0, 255, 0); // Green
        }
       if (volts >= seg5)
       {
          strip.setPixelColor(15, 255, 255, 0); // Yellow
          strip.setPixelColor(22, 255, 255, 0); // Yellow
          strip.setPixelColor(23, 255, 255, 0); // Yellow
          strip.setPixelColor(29, 255, 255, 0); // Yellow
          strip.setPixelColor(30, 255, 255, 0); // Yellow
          strip.setPixelColor(36, 255, 255, 0); // Yellow
          strip.setPixelColor(37, 255, 255, 0); // Yellow
          strip.setPixelColor(43, 255, 255, 0); // Yellow
          strip.setPixelColor(44, 255, 255, 0); // Yellow
          strip.setPixelColor(50, 255, 255, 0); // Yellow
          strip.setPixelColor(51, 255, 255, 0); // Yellow
          strip.setPixelColor(57, 255, 255, 0); // Yellow
          strip.setPixelColor(58, 255, 255, 0); // Yellow
       }
       if (volts >= seg6)
       {
          strip.setPixelColor(31, 255, 128, 0); // Orange
          strip.setPixelColor(38, 255, 128, 0); // Orange
          strip.setPixelColor(39, 255, 128, 0); // Orange
          strip.setPixelColor(45, 255, 128, 0); // Orange
          strip.setPixelColor(46, 255, 128, 0); // Orange
          strip.setPixelColor(52, 255, 128, 0); // Orange
          strip.setPixelColor(53, 255, 128, 0); // Orange
          strip.setPixelColor(59, 255, 128, 0); // Orange
          strip.setPixelColor(60, 255, 128, 0); // Orange
       }
       if (volts >= seg7)
       {
          strip.setPixelColor(47, 255, 0, 0); // Red
          strip.setPixelColor(54, 255, 0, 0); // Red
          strip.setPixelColor(55, 255, 0, 0); // Red
          strip.setPixelColor(61, 255, 0, 0); // Red
          strip.setPixelColor(62, 255, 0, 0); // Red
       }
       if (volts >= seg8)
       {
          strip.setPixelColor(63, 255, 255, 255); // White
       }
    }

    void diagInsideOut(double volts, double seg1, double seg2, double seg3, double seg4, double seg5, double seg6, double seg7, double seg8) // Display diagonal strips of light across the 8x8 matrix
    {
       if (volts < seg1)
       {
            strip.clear();
       }
       if (volts >= seg1)
       {
          strip.setPixelColor(0, 127, 0, 255); // Purple
          strip.setPixelColor(9, 127, 0, 255); // Purple
          strip.setPixelColor(18, 127, 0, 255); // Purple
          strip.setPixelColor(27, 127, 0, 255); // Purple
          strip.setPixelColor(36, 127, 0, 255); // Purple
          strip.setPixelColor(45, 127, 0, 255); // Purple
          strip.setPixelColor(54, 127, 0, 255); // Purple
          strip.setPixelColor(63, 127, 0, 255); // Purple
       }
       if (volts >= seg2)
       {
          strip.setPixelColor(1, 0, 0, 255); // Blue
          strip.setPixelColor(10, 0, 0, 255); // Blue
          strip.setPixelColor(19, 0, 0, 255); // Blue
          strip.setPixelColor(28, 0, 0, 255); // Blue
          strip.setPixelColor(37, 0, 0, 255); // Blue
          strip.setPixelColor(46, 0, 0, 255); // Blue
          strip.setPixelColor(55, 0, 0, 255); // Blue
          strip.setPixelColor(8, 0, 0, 255); // Blue
          strip.setPixelColor(17, 0, 0, 255); // Blue
          strip.setPixelColor(26, 0, 0, 255); // Blue
          strip.setPixelColor(35, 0, 0, 255); // Blue
          strip.setPixelColor(44, 0, 0, 255); // Blue
          strip.setPixelColor(53, 0, 0, 255); // Blue
          strip.setPixelColor(62, 0, 0, 255); // Blue
       }
       if (volts >= seg3)
       {
          strip.setPixelColor(2, 0, 255, 255); // Cyan
          strip.setPixelColor(11, 0, 255, 255); // Cyan
          strip.setPixelColor(20, 0, 255, 255); // Cyan
          strip.setPixelColor(29, 0, 255, 255); // Cyan
          strip.setPixelColor(38, 0, 255, 255); // Cyan
          strip.setPixelColor(47, 0, 255, 255); // Cyan
          strip.setPixelColor(16, 0, 255, 255); // Cyan
          strip.setPixelColor(25, 0, 255, 255); // Cyan
          strip.setPixelColor(34, 0, 255, 255); // Cyan
          strip.setPixelColor(43, 0, 255, 255); // Cyan
          strip.setPixelColor(52, 0, 255, 255); // Cyan
          strip.setPixelColor(61, 0, 255, 255); // Cyan
       }
       if (volts >= seg4)
       {
          strip.setPixelColor(3, 0, 255, 0); // Green
          strip.setPixelColor(12, 0, 255, 0); // Green
          strip.setPixelColor(21, 0, 255, 0); // Green
          strip.setPixelColor(30, 0, 255, 0); // Green
          strip.setPixelColor(39, 0, 255, 0); // Green
          strip.setPixelColor(24, 0, 255, 0); // Green
          strip.setPixelColor(33, 0, 255, 0); // Green
          strip.setPixelColor(42, 0, 255, 0); // Green
          strip.setPixelColor(51, 0, 255, 0); // Green
          strip.setPixelColor(60, 0, 255, 0); // Green
        }
       if (volts >= seg5)
       {
          strip.setPixelColor(4, 255, 255, 0); // Yellow
          strip.setPixelColor(13, 255, 255, 0); // Yellow
          strip.setPixelColor(22, 255, 255, 0); // Yellow
          strip.setPixelColor(31, 255, 255, 0); // Yellow
          strip.setPixelColor(32, 255, 255, 0); // Yellow
          strip.setPixelColor(41, 255, 255, 0); // Yellow
          strip.setPixelColor(50, 255, 255, 0); // Yellow
          strip.setPixelColor(59, 255, 255, 0); // Yellow
       }
       if (volts >= seg6)
       {
          strip.setPixelColor(5, 255, 128, 0); // Orange
          strip.setPixelColor(14, 255, 128, 0); // Orange
          strip.setPixelColor(23, 255, 128, 0); // Orange
          strip.setPixelColor(40, 255, 128, 0); // Orange
          strip.setPixelColor(49, 255, 128, 0); // Orange
          strip.setPixelColor(58, 255, 128, 0); // Orange
       }
       if (volts >= seg7)
       {
          strip.setPixelColor(6, 255, 0, 0); // Red
          strip.setPixelColor(15, 255, 0, 0); // Red
          strip.setPixelColor(48, 255, 0, 0); // Red
          strip.setPixelColor(57, 255, 0, 0); // Red
       }
       if (volts >= seg8)
       {
          strip.setPixelColor(7, 255, 255, 255); // White
          strip.setPixelColor(56, 255, 255, 255); // White
       }
    }

    void vertStrips(double volts, double seg1, double seg2, double seg3, double seg4, double seg5, double seg6, double seg7, double seg8)
    {
       if (volts < seg1)
       {
            strip.clear();
       }
       if (volts >= seg1)
       {
          strip.fill(purple, 0, 8); // Purple
       }
       if (volts >= seg2)
       {
        strip.fill(blue, 8, 8); // Blue
       }
       if (volts >= seg3)
       {
          strip.fill(green, 16, 8); // Green
       }
       if (volts >= seg4)
       {
          strip.fill(yellow, 24, 8); // Yellow
        }
       if (volts >= seg5)
       {
          strip.fill(orange, 32, 8); // Orange
       }
       if (volts >= seg6)
       {
          strip.fill(red, 40, 8); // Red
       }
       if (volts >= seg7)
       {
          strip.fill(white, 48, 8); // White
       }
       if (volts >= seg8)
       {
          strip.fill(cyan, 56, 8); // Cyan
       }
    }

   void ringsOutToIn(double volts, double seg1, double seg2, double seg3, double seg4, double seg5, double seg6, double seg7, double seg8)
    {
       if (volts < seg1)
       {
            strip.clear();
       }
       if (volts >= seg1)
       {
          strip.fill(purple, 0, 8); // Purple
          strip.fill(purple, 56, 8); // Purple
          strip.setPixelColor(8, 127, 0, 255); // Purple
          strip.setPixelColor(16, 127, 0, 255); // Purple
          strip.setPixelColor(24, 127, 0, 255); // Purple
          strip.setPixelColor(32, 127, 0, 255); // Purple
          strip.setPixelColor(40, 127, 0, 255); // Purple
          strip.setPixelColor(48, 127, 0, 255); // Purple
          strip.setPixelColor(15, 127, 0, 255); // Purple
          strip.setPixelColor(23, 127, 0, 255); // Purple
          strip.setPixelColor(31, 127, 0, 255); // Purple
          strip.setPixelColor(39, 127, 0, 255); // Purple
          strip.setPixelColor(47, 127, 0, 255); // Purple
          strip.setPixelColor(55, 127, 0, 255); // Purple
       }
       if (volts >= seg3)
       {
          strip.fill(blue, 9, 6); // Blue
          strip.fill(blue, 49, 6); // Blue
          strip.setPixelColor(17, 0, 0, 255); // Blue
          strip.setPixelColor(25, 0, 0, 255); // Blue
          strip.setPixelColor(33, 0, 0, 255); // Blue
          strip.setPixelColor(41, 0, 0, 255); // Blue
          strip.setPixelColor(22, 0, 0, 255); // Blue
          strip.setPixelColor(30, 0, 0, 255); // Blue
          strip.setPixelColor(38, 0, 0, 255); // Blue
          strip.setPixelColor(46, 0, 0, 255); // Blue
       }
       if (volts >= seg5)
       {
          strip.fill(cyan, 18, 4); // Cyan
          strip.fill(cyan, 42, 4); // Cyan
          strip.setPixelColor(26, 0, 255, 255); // Cyan
          strip.setPixelColor(34, 0, 255, 255); // Cyan
          strip.setPixelColor(29, 0, 255, 255); // Cyan
          strip.setPixelColor(37, 0, 255, 255); // Cyan
       }
       if (volts >= seg7)
       {
          strip.fill(green, 27, 2); // Green
          strip.fill(green, 35, 2); // Green
        }
    }

       void ringsInToOut(double volts, double seg1, double seg2, double seg3, double seg4, double seg5, double seg6, double seg7, double seg8)
    {
       if (volts < seg1)
       {
            strip.clear();
       }
       if (volts >= seg1)
       {
          strip.fill(green, 27, 2); // Green
          strip.fill(green, 35, 2); // Green
       }
       if (volts >= seg3)
       {
          strip.fill(cyan, 18, 4); // Cyan
          strip.fill(cyan, 42, 4); // Cyan
          strip.setPixelColor(26, 0, 255, 255); // Cyan
          strip.setPixelColor(34, 0, 255, 255); // Cyan
          strip.setPixelColor(29, 0, 255, 255); // Cyan
          strip.setPixelColor(37, 0, 255, 255); // Cyan
               }
       if (volts >= seg5)
       {
          strip.fill(blue, 9, 6); // Blue
          strip.fill(blue, 49, 6); // Blue
          strip.setPixelColor(17, 0, 0, 255); // Blue
          strip.setPixelColor(25, 0, 0, 255); // Blue
          strip.setPixelColor(33, 0, 0, 255); // Blue
          strip.setPixelColor(41, 0, 0, 255); // Blue
          strip.setPixelColor(22, 0, 0, 255); // Blue
          strip.setPixelColor(30, 0, 0, 255); // Blue
          strip.setPixelColor(38, 0, 0, 255); // Blue
          strip.setPixelColor(46, 0, 0, 255); // Blue
       }
       if (volts >= seg7)
       {
          strip.fill(purple, 0, 8); // Purple
          strip.fill(purple, 56, 8); // Purple
          strip.setPixelColor(8, 127, 0, 255); // Purple
          strip.setPixelColor(16, 127, 0, 255); // Purple
          strip.setPixelColor(24, 127, 0, 255); // Purple
          strip.setPixelColor(32, 127, 0, 255); // Purple
          strip.setPixelColor(40, 127, 0, 255); // Purple
          strip.setPixelColor(48, 127, 0, 255); // Purple
          strip.setPixelColor(15, 127, 0, 255); // Purple
          strip.setPixelColor(23, 127, 0, 255); // Purple
          strip.setPixelColor(31, 127, 0, 255); // Purple
          strip.setPixelColor(39, 127, 0, 255); // Purple
          strip.setPixelColor(47, 127, 0, 255); // Purple
          strip.setPixelColor(55, 127, 0, 255); // Purple
        }
    }

        void oneColor()
        {
          strip.fill(purple, 0, 63); // Purple
        }

        void multiColor(double volts, double seg1, double seg2, double seg3, double seg4, double seg5, double seg6, double seg7, double seg8)
        {
          if (volts < seg1)
          {
              strip.clear();
          }
          if (volts >= seg1)
          {
              strip.fill(purple, 0, 63); // Purple
          }
          if (volts >= seg2)
          {
            strip.fill(blue, 0, 63); // Blue
          }
          if (volts >= seg3)
          {
              strip.fill(green, 0, 63); // Green
          }
          if (volts >= seg4)
          {
              strip.fill(yellow, 0, 63); // Yellow
          }
          if (volts >= seg5)
          {
              strip.fill(orange, 0, 63); // Orange
          }
          if (volts >= seg6)
          {
              strip.fill(red, 0, 63); // Red
          }
          if (volts >= seg7)
          {
              strip.fill(white, 0, 63); // White
          }
          if (volts >= seg8)
          {
              strip.fill(cyan, 0, 63); // Cyan
          }
        }

        void variBright(double volts, int maxBright, int numSegments, double seg1, double seg2, double seg3, double seg4, double seg5, double seg6, double seg7, double seg8)
        {
          if (volts < seg1)
          {
            strip.setBrightness(maxBright*1/numSegments);
          }
          if (volts >= seg1)
          {
            strip.setBrightness(maxBright*1/numSegments);
          }
          if (volts >= seg2)
          {
            strip.setBrightness(maxBright*2/numSegments);
          }
          if (volts >= seg3)
          {
            strip.setBrightness(maxBright*3/numSegments);
          }
          if (volts >= seg4)
          {
            strip.setBrightness(maxBright*4/numSegments);
          }
          if (volts >= seg5)
          {
            strip.setBrightness(maxBright*5/numSegments);
          }
          if (volts >= seg6)
          {
            strip.setBrightness(maxBright*6/numSegments);
          }
          if (volts >= seg7)
          {
            strip.setBrightness(maxBright*7/numSegments);
          }
          if (volts >= seg8)
          {
            strip.setBrightness(maxBright*8/numSegments);
          }
        }
