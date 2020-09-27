//
//    FILE: fastMapInteger16ArithmeticTestA.ino
//  AUTHOR: Brewmanz (Bryan White)
// VERSION: 0.1.1
// PURPOSE: Test of FastMapInt(16) helper functions
//    DATE: 2020-09-08
//     URL: https://github.com/RobTillaart/FastMap

//#include <AUnitVerbose.h> // too much for Nano!
#include <AUnit.h>
#include <FastMap.h>

volatile int i, j;

test(T1150Ratio16ToFixedPointFraction32) {
  FixedPointFraction32_t  fpfP, fpfN;
#if FULL_DEBUG || 1
  Print* pPrintDebug = &Serial;
#else
  Print* pPrintDebug = nullptr;
#endif

  fpfP = fpfN = {-2468, 97, -42};
  assertEqual(fpfP.TheFraction, (long)-2468);
  assertEqual(fpfN.TheFraction, (long)-2468);
  assertEqual(fpfP.BitsToShift, 97);
  assertEqual(fpfN.BitsToShift, 97);
  assertEqual(fpfP.MaxInput, -42);
  assertEqual(fpfN.MaxInput, -42);

  // handling of 0
  Ratio16ToFixedPointFraction32(0, 0, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)0 * 0x10000 + 0x0000);
  assertEqual(fpfN.TheFraction, (long)0 * 0x10000 + 0x0000);
  assertEqual(fpfP.BitsToShift, 0);
  assertEqual(fpfN.BitsToShift, 0);
  assertEqual(fpfP.MaxInput, 0);
  assertEqual(fpfN.MaxInput, 0);

  Ratio16ToFixedPointFraction32(0, 8, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)0 * 0x10000 + 0x0000);
  assertEqual(fpfN.TheFraction, (long)0 * 0x10000 + 0x0000);
  assertEqual(fpfP.BitsToShift, 0);
  assertEqual(fpfN.BitsToShift, 0);
  assertEqual(fpfP.MaxInput, 0);
  assertEqual(fpfN.MaxInput, 0);

  Ratio16ToFixedPointFraction32(8, 0, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)0 * 0x10000 + 0x0000);
  assertEqual(fpfN.TheFraction, (long)0 * 0x10000 + 0x0000);
  assertEqual(fpfP.BitsToShift, 0);
  assertEqual(fpfN.BitsToShift, 0);
  assertEqual(fpfP.MaxInput, 0);
  assertEqual(fpfN.MaxInput, 0);

  // equal ratios
  Ratio16ToFixedPointFraction32(1, 1, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x0000);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x0000);
  assertEqual(fpfP.BitsToShift, 16 + 0);
  assertEqual(fpfN.BitsToShift, 16 + 0);
  assertEqual(fpfP.MaxInput, 32767 / 1);
  assertEqual(fpfN.MaxInput, 32767);

  Ratio16ToFixedPointFraction32(12, 12, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x0000);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x0000);
  assertEqual(fpfP.BitsToShift, 16 + 0);
  assertEqual(fpfN.BitsToShift, 16 + 0);
  assertEqual(fpfP.MaxInput, 32767 / 1);
  assertEqual(fpfN.MaxInput, 32767);

  Ratio16ToFixedPointFraction32(-2, 2, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-1 * 0x10000 + 0x0000);
  assertEqual(fpfN.TheFraction, (long)-1 * 0x10000 + 0x0000);
  assertEqual(fpfP.BitsToShift, 16 + 0);
  assertEqual(fpfN.BitsToShift, 16 + 0);
  assertEqual(fpfP.MaxInput, 32767 / 1);
  assertEqual(fpfN.MaxInput, 32767);

  Ratio16ToFixedPointFraction32(3, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-1 * 0x10000 + 0x0000);
  assertEqual(fpfN.TheFraction, (long)-1 * 0x10000 + 0x0000);
  assertEqual(fpfP.BitsToShift, 16 + 0);
  assertEqual(fpfN.BitsToShift, 16 + 0);
  assertEqual(fpfP.MaxInput, 32767 / 1);
  assertEqual(fpfN.MaxInput, 32767);

  Ratio16ToFixedPointFraction32(-4, -4, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x0000);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x0000);
  assertEqual(fpfP.BitsToShift, 16 + 0);
  assertEqual(fpfN.BitsToShift, 16 + 0);
  assertEqual(fpfP.MaxInput, 32767 / 1);
  assertEqual(fpfN.MaxInput, 32767);

  // exact ratios
  Ratio16ToFixedPointFraction32(8, 2, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x0000);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x0000);
  assertEqual(fpfP.BitsToShift, 16 - 2);
  assertEqual(fpfN.BitsToShift, 16 - 2);
  assertEqual(fpfP.MaxInput, 32767 / 4);
  assertEqual(fpfN.MaxInput, 8191);

  Ratio16ToFixedPointFraction32(-12, 4, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-2 * 0x10000 + 0x8000);
  assertEqual(fpfN.TheFraction, (long)-2 * 0x10000 + 0x8000);
  assertEqual(fpfP.BitsToShift, 16 - 1);
  assertEqual(fpfN.BitsToShift, 16 - 1);
  assertEqual(fpfP.MaxInput, 32767 / 3);
  assertEqual(fpfN.MaxInput, 10922);

  Ratio16ToFixedPointFraction32(30, -5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-2 * 0x10000 + 0x8000);
  assertEqual(fpfN.TheFraction, (long)-2 * 0x10000 + 0x8000);
  assertEqual(fpfP.BitsToShift, 16 - 2);
  assertEqual(fpfN.BitsToShift, 16 - 2);
  assertEqual(fpfP.MaxInput, 32767 / 6);
  assertEqual(fpfN.MaxInput, 5461);

  Ratio16ToFixedPointFraction32(-56, -7, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x0000);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x0000);
  assertEqual(fpfP.BitsToShift, 16 - 3);
  assertEqual(fpfN.BitsToShift, 16 - 3);
  assertEqual(fpfP.MaxInput, 32767 / 8);
  assertEqual(fpfN.MaxInput, 4095);

  // theoretical exact ratios
  Ratio16ToFixedPointFraction32(1, 3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x5556);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x5555);
  assertEqual(fpfP.BitsToShift, 16 + 2);
  assertEqual(fpfN.BitsToShift, 16 + 2);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 3 / 4));
  assertEqual(fpfN.MaxInput, 24575);

  Ratio16ToFixedPointFraction32(-1, 3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-2 * 0x10000 + 0xAAAA);
  assertEqual(fpfN.TheFraction, (long)-2 * 0x10000 + 0xAAAB);
  assertEqual(fpfP.BitsToShift, 16 + 2);
  assertEqual(fpfN.BitsToShift, 16 + 2);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 3 / 4));
  assertEqual(fpfN.MaxInput, 24575);

  Ratio16ToFixedPointFraction32(1, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-2 * 0x10000 + 0xAAAA);
  assertEqual(fpfN.TheFraction, (long)-2 * 0x10000 + 0xAAAB);
  assertEqual(fpfP.BitsToShift, 16 + 2);
  assertEqual(fpfN.BitsToShift, 16 + 2);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 3 / 4));
  assertEqual(fpfN.MaxInput, 24575);

  Ratio16ToFixedPointFraction32(-1, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x5556);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x5555);
  assertEqual(fpfP.BitsToShift, 16 + 2);
  assertEqual(fpfN.BitsToShift, 16 + 2);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 3 / 4));
  assertEqual(fpfN.MaxInput, 24575);

  Ratio16ToFixedPointFraction32(2, 3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x5556);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x5555);
  assertEqual(fpfP.BitsToShift, 16 + 1);
  assertEqual(fpfN.BitsToShift, 16 + 1);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 3 / 4));
  assertEqual(fpfN.MaxInput, 24575);

  Ratio16ToFixedPointFraction32(-2, 3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-2 * 0x10000 + 0xAAAA);
  assertEqual(fpfN.TheFraction, (long)-2 * 0x10000 + 0xAAAB);
  assertEqual(fpfP.BitsToShift, 16 + 1);
  assertEqual(fpfN.BitsToShift, 16 + 1);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 3 / 4));
  assertEqual(fpfN.MaxInput, 24575);

  Ratio16ToFixedPointFraction32(2, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-2 * 0x10000 + 0xAAAA);
  assertEqual(fpfN.TheFraction, (long)-2 * 0x10000 + 0xAAAB);
  assertEqual(fpfP.BitsToShift, 16 + 1);
  assertEqual(fpfN.BitsToShift, 16 + 1);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 3 / 4));
  assertEqual(fpfN.MaxInput, 24575);

  Ratio16ToFixedPointFraction32(-2, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x5556);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x5555);
  assertEqual(fpfP.BitsToShift, 16 + 1);
  assertEqual(fpfN.BitsToShift, 16 + 1);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 3 / 4));
  assertEqual(fpfN.MaxInput, 24575);

  // binary fraction
  Ratio16ToFixedPointFraction32(1, 2, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x0000);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x0000);
  assertEqual(fpfP.BitsToShift, 16 + 1);
  assertEqual(fpfN.BitsToShift, 16 + 1);
  assertEqual(fpfP.MaxInput, 32767);
  assertEqual(fpfN.MaxInput, 32767);

  Ratio16ToFixedPointFraction32(-3, 4, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-2 * 0x10000 + 0x8000);
  assertEqual(fpfN.TheFraction, (long)-2 * 0x10000 + 0x8000);
  assertEqual(fpfP.BitsToShift, 16 + 1);
  assertEqual(fpfN.BitsToShift, 16 + 1);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 2 / 3));
  assertEqual(fpfN.MaxInput, 21844);

  Ratio16ToFixedPointFraction32(3, -8, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-2 * 0x10000 + 0x8000);
  assertEqual(fpfN.TheFraction, (long)-2 * 0x10000 + 0x8000);
  assertEqual(fpfP.BitsToShift, 16 + 2);
  assertEqual(fpfN.BitsToShift, 16 + 2);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 2 / 3));
  assertEqual(fpfN.MaxInput, 21844);

  Ratio16ToFixedPointFraction32(-3, -16, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x8000);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x8000);
  assertEqual(fpfP.BitsToShift, 16 + 3);
  assertEqual(fpfN.BitsToShift, 16 + 3);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 2 / 3));
  assertEqual(fpfN.MaxInput, 21844);

  // binary vulgar fraction
  Ratio16ToFixedPointFraction32(3, 2, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x8000);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x8000);
  assertEqual(fpfP.BitsToShift, 16);
  assertEqual(fpfN.BitsToShift, 16);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 2 / 3));
  assertEqual(fpfN.MaxInput, 21844);

  Ratio16ToFixedPointFraction32(-7, 4, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-2 * 0x10000 + 0x4000);
  assertEqual(fpfN.TheFraction, (long)-2 * 0x10000 + 0x4000);
  assertEqual(fpfP.BitsToShift, 16);
  assertEqual(fpfN.BitsToShift, 16);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 4 / 7));
  assertEqual(fpfN.MaxInput, 18724);

  Ratio16ToFixedPointFraction32(11, -8, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-2 * 0x10000 + 0xA000);
  assertEqual(fpfN.TheFraction, (long)-2 * 0x10000 + 0xA000);
  assertEqual(fpfP.BitsToShift, 16);
  assertEqual(fpfN.BitsToShift, 16);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 8 / 11));
  assertEqual(fpfN.MaxInput, 23830);

  Ratio16ToFixedPointFraction32(-19, -16, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x3000);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x3000);
  assertEqual(fpfP.BitsToShift, 16);
  assertEqual(fpfN.BitsToShift, 16);
  assertEqual(fpfP.MaxInput, (int)((long)32767 * 16 / 19));
  assertEqual(fpfN.MaxInput, 27593);

  // inexact fraction
  Ratio16ToFixedPointFraction32(5, 9, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x1C72);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x1C71);
  assertEqual(fpfP.BitsToShift, 16 + 1);
  assertEqual(fpfN.BitsToShift, 16 + 1);
  assertNear((double)fpfP.MaxInput, (int)((long)32767 * 9 / 10) + 0.5, 0.6); // 'usual' shortcut, but returns 29490 rather than actual 29491
  assertEqual(fpfP.MaxInput, (int)((long)0x7FFF0000 /((long)5 * 0x10000 / 9)/2)); // actual calculation
  assertEqual(fpfN.MaxInput, 29491);

  Ratio16ToFixedPointFraction32(-5, 9, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-2 * 0x10000 + 0xE38E);
  assertEqual(fpfN.TheFraction, (long)-2 * 0x10000 + 0xE38F);
  assertEqual(fpfP.BitsToShift, 16 + 1);
  assertEqual(fpfN.BitsToShift, 16 + 1);
  assertEqual(fpfP.MaxInput, (int)((long)0x7FFF0000 /((long)5 * 0x10000 / 9)/2));
  assertEqual(fpfN.MaxInput, 29491);

  Ratio16ToFixedPointFraction32(5, -9, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-2 * 0x10000 + 0xE38E);
  assertEqual(fpfN.TheFraction, (long)-2 * 0x10000 + 0xE38F);
  assertEqual(fpfP.BitsToShift, 16 + 1);
  assertEqual(fpfN.BitsToShift, 16 + 1);
  assertEqual(fpfP.MaxInput, (int)((long)0x7FFF0000 /((long)5 * 0x10000 / 9)/2));
  assertEqual(fpfN.MaxInput, 29491);

  Ratio16ToFixedPointFraction32(-5, -9, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0x1C72);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0x1C71);
  assertEqual(fpfP.BitsToShift, 16 + 1);
  assertEqual(fpfN.BitsToShift, 16 + 1);
  assertEqual(fpfP.MaxInput, (int)((long)0x7FFF0000 /((long)5 * 0x10000 / 9)/2));
  assertEqual(fpfN.MaxInput, 29491);

  // inexact vulgar fraction
  Ratio16ToFixedPointFraction32(9, 5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0xCCCD);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0xCCCC);
  assertEqual(fpfP.BitsToShift, 16);
  assertEqual(fpfN.BitsToShift, 16);
  assertNear((double)fpfP.MaxInput, (int)((long)32767 * 5 / 9) + 0.5, 0.6); // 'usual' shortcut, but returns 18203 rather than actual 18204
  assertEqual(fpfP.MaxInput, (int)((long)0x7FFF0000 /((long)9 * 0x10000 / 5))); // actual calculation
  assertEqual(fpfN.MaxInput, 18204);

  Ratio16ToFixedPointFraction32(-9, 5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-2 * 0x10000 + 0x3333);
  assertEqual(fpfN.TheFraction, (long)-2 * 0x10000 + 0x3334);
  assertEqual(fpfP.BitsToShift, 16);
  assertEqual(fpfN.BitsToShift, 16);
  assertEqual(fpfP.MaxInput, (int)((long)0x7FFF0000 /((long)9 * 0x10000 / 5))); // actual calculation
  assertEqual(fpfN.MaxInput, 18204);

  Ratio16ToFixedPointFraction32(9, -5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)-2 * 0x10000 + 0x3333);
  assertEqual(fpfN.TheFraction, (long)-2 * 0x10000 + 0x3334);
  assertEqual(fpfP.BitsToShift, 16);
  assertEqual(fpfN.BitsToShift, 16);
  assertEqual(fpfP.MaxInput, (int)((long)0x7FFF0000 /((long)9 * 0x10000 / 5))); // actual calculation
  assertEqual(fpfN.MaxInput, 18204);

  Ratio16ToFixedPointFraction32(-9, -5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); pPrintDebug->flush(); }
  assertEqual(fpfP.TheFraction, (long)1 * 0x10000 + 0xCCCD);
  assertEqual(fpfN.TheFraction, (long)1 * 0x10000 + 0xCCCC);
  assertEqual(fpfP.BitsToShift, 16);
  assertEqual(fpfN.BitsToShift, 16);
  assertEqual(fpfP.MaxInput, (int)((long)0x7FFF0000 /((long)9 * 0x10000 / 5))); // actual calculation
  assertEqual(fpfN.MaxInput, 18204);
}

void setup() {
  delay(1000); // wait for stability on some boards to prevent garbage Serial
  Serial.begin(115200); // The baudrate of Serial monitor is set
  while(!Serial); // for the Arduino Leonardo/Micro only
  Serial.println(F(__DATE__ " @ " __TIME__));
  Serial.println(F(__FILE__));
}

void loop() {
  aunit::TestRunner::run();
}
