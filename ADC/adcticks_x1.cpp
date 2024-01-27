// Automatically generated C++ file on Sat Aug  5 09:04:28 2023
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD adcticks_x1.cpp kernel32.lib

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
#undef IN
#undef Vref
#undef tick
#undef OUT

int adcBits = 12;
int lastTick = 0;
int lastOut = 0;

extern "C" __declspec(dllexport) void adcticks_x1(void **opaque, double t, union uData *data)
{
   double IN   = data[0].d; // input
   double Vref = data[1].d; // input
   bool   tick = data[2].b; // input
   int   &OUT  = data[3].i; // output

// Implement module evaluation code here:



   if(lastTick == 0 && tick == 1)
   {
      lastOut = (int) (IN/Vref * (2<<adcBits-1));
      OUT = lastOut;
   }
   else
   {
      OUT = lastOut;
   }


   lastTick = tick;
}
