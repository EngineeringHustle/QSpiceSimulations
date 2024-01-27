// Automatically generated C++ file on Fri Aug  4 21:24:03 2023
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD pwm.cpp kernel32.lib

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

int counter = 0;
int counterMAX = 99;
int lastTick = 0;

// #undef pin names lest they collide with names in any header file(s) you might include.
#undef IN
#undef PWM
#undef tick


extern "C" __declspec(dllexport) void pwm(void **opaque, double t, union uData *data)
{
   int   IN   = data[0].i; // input
   bool  tick = data[1].b; // input
   bool &PWM  = data[2].b; // output

// Implement module evaluation code here:

   if(tick == 1 && lastTick == 0)
   {

      if(counter < counterMAX)
      {
         counter++;
      }
      else
      {
         counter = 0;
      }

      if(IN > counter)
      {
         PWM = 1;
      }
      else
      {
         PWM = 0;
      }

   }
   lastTick = tick;

}

