// Automatically generated C++ file on Wed Aug  9 23:10:22 2023
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD pwmgatedriver.cpp kernel32.lib

union uData
{
   bool b;
   char c;
   unsigned char uc;
   short s;
   unsigned short us;
   int i;
   unsigned int ui;
   float f;
   double d;
   long long int i64;
   unsigned long long int ui64;
   char *str;
   unsigned char *bytes;
};

// int DllMain() must exist and return 1 for a process to load the .DLL
// See https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain for more information.
int __stdcall DllMain(void *module, unsigned int reason, void *reserved) { return 1; }

// #undef pin names lest they collide with names in any header file(s) you might include.
#undef Vref
#undef tick
#undef PWMh
#undef PWMl

#define Fosc 64000000
#define ClkPrescaler 0        //values from 0 to 65538
#define UpCounting 1
#define DownCounting 0
#define PwmOutputPolarity 1   //output polarity negative when equal to 1

int lastClk = 0;
int prescalerCounter = 0;
int counter = 0;
bool counterEnable = 1;   //PWM counter stops when equal to 0
bool pwmEnable = 1;
bool pwmNEnable = 1;

#if (DownCounting == 1 && UpCounting == 0)
bool counterDir = 1;    //0=Up; 1=Down
#else
bool counterDir = 0;
#endif

int counterMax = 639;        //16-bit value, 65 536
int deadTimeRisingEdge = 5;   //10-bit value
int deadTimeFallingEdge = 5;  //10-bit value
int deadTimeCounter = 0;

struct pwm
{
   bool pwmOutH;
   bool pwmOutL;
};

void CounterModule()
{
      if(counter >= counterMax && counterDir == 0)
      {
         if(DownCounting)
         {
            counterDir = 1;
         }
         else
         {
            counter = 0;
         }
      }

      else if(counter <= 0 && counterDir == 1)
      {
         if(UpCounting)
         {
            counterDir = 0;
         }
         else
         {
            counter = counterMax;
         }

      }
      else
      {
         if(counterDir == 0)
         {
            counter++;
         }
         else
         {
            counter--;
         }
      }
}

struct pwm PwmModule(int duty)
{
   struct pwm pwmOut;

   if( duty > counter)
   {
#if(PwmOutputPolarity == 0)
      pwmOut.pwmOutL = 0;
      pwmOut.pwmOutH = 0;
#else
      pwmOut.pwmOutL = 1;
      pwmOut.pwmOutH = 1;
#endif

      if(deadTimeCounter >= deadTimeRisingEdge)
      {
#if(PwmOutputPolarity == 0)
         pwmOut.pwmOutH = 1;
#else
         pwmOut.pwmOutH = 0;
#endif

         deadTimeCounter = deadTimeFallingEdge;
      }
      else
      {
         deadTimeCounter++;
      }

   }
   else
   {
#if(PwmOutputPolarity == 0)
      pwmOut.pwmOutH = 0;
      pwmOut.pwmOutL = 0;
#else
      pwmOut.pwmOutH = 1;
      pwmOut.pwmOutL = 1;
#endif


      if(deadTimeCounter <= 0)
      {
#if(PwmOutputPolarity == 0)
         pwmOut.pwmOutL = 1;
#else
         pwmOut.pwmOutL = 0;
#endif

      }
      else
      {
         deadTimeCounter--;
      }
   }

   return pwmOut;

}

extern "C" __declspec(dllexport) void pwmgatedriver(void **opaque, double t, union uData *data)
{
   int   duty = data[0].i; // input
   bool  clk  = data[1].b; // input
   bool &PWMh = data[2].b; // output
   bool &PWMl = data[3].b; // output

// Implement module evaluation code here:


   struct pwm output;

   if(lastClk == 0 && clk == 1)
   {

   if(counterEnable)
   {
      prescalerCounter++;
      if(prescalerCounter > ClkPrescaler)
      {
         prescalerCounter = 0;

         CounterModule();
         //cnt = counter;
         output = PwmModule(duty);

         if(pwmEnable == 1)
         {
            PWMh = output.pwmOutH;
         }
         else
         {
            PWMh = 0;
         }

         if(pwmNEnable == 1)
         {
            PWMl = output.pwmOutL;
         }
         else
         {
            PWMl = 0;
         }

      }

   }



   }
   lastClk = clk;

}
