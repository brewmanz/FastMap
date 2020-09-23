//
//    FILE: fastMapInteger64ArithmeticTest.ino
//  AUTHOR: Brewmanz (Bryan White)
// VERSION: 0.1.1
// PURPOSE: Test of FastMapInt(64) helper functions
//        : N.B. needs refactoring to properly handle int128_t
//    DATE: 2020-09-08
//     URL: https://github.com/RobTillaart/FastMap

//#include <AUnitVerbose.h> // too much for Nano!
#include <AUnit.h>
#include <FastMap.h>

volatile int i, j;

test(T1300Ratio64ToFixedPointFraction64) {
  FixedPointFraction64_t fpfP, fpfN;

  // handling of 0
  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(0, 0, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)0 * 0x100000000 + 0x00000000);
  assertEqual(fpfN.TheFraction, (int64_t)0 * 0x100000000 + 0x00000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(0, 8, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)0 * 0x100000000 + 0x00000000);
  assertEqual(fpfN.TheFraction, (int64_t)0 * 0x100000000 + 0x00000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(8, 0, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)0 * 0x100000000 + 0x00000000);
  assertEqual(fpfN.TheFraction, (int64_t)0 * 0x100000000 + 0x00000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  // equal ratios
  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(1, 1, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)1 * 0x100000000 + 0x00000000);
  assertEqual(fpfN.TheFraction, (int64_t)1 * 0x100000000 + 0x00000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(12, 12, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)1 * 0x100000000 + 0x00000000);
  assertEqual(fpfN.TheFraction, (int64_t)1 * 0x100000000 + 0x00000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-2, 2, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-1 * 0x100000000 + 0x00000000);
  assertEqual(fpfN.TheFraction, (int64_t)-1 * 0x100000000 + 0x00000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(3, -3, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-1 * 0x100000000 + 0x00000000);
  assertEqual(fpfN.TheFraction, (int64_t)-1 * 0x100000000 + 0x00000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-4, -4, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)1 * 0x100000000 + 0x00000000);
  assertEqual(fpfN.TheFraction, (int64_t)1 * 0x100000000 + 0x00000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  // exact ratios
  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(8, 2, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)4 * 0x100000000 + 0x00000000);
  assertEqual(fpfN.TheFraction, (int64_t)4 * 0x100000000 + 0x00000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-12, 4, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-3 * 0x100000000 + 0x00000000);
  assertEqual(fpfN.TheFraction, (int64_t)-3 * 0x100000000 + 0x00000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(30, -5, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-6 * 0x100000000 + 0x00000000);
  assertEqual(fpfN.TheFraction, (int64_t)-6 * 0x100000000 + 0x00000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-56, -7, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)8 * 0x100000000 + 0x00000000);
  assertEqual(fpfN.TheFraction, (int64_t)8 * 0x100000000 + 0x00000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  // theoretical exact ratios
  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(1, 3, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)0 * 0x100000000 + 0x55555556);
  assertEqual(fpfN.TheFraction, (int64_t)0 * 0x100000000 + 0x55555555);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-1, 3, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-1 * 0x100000000 + 0xAAAAAAAA);
  assertEqual(fpfN.TheFraction, (int64_t)-1 * 0x100000000 + 0xAAAAAAAB);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(1, -3, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-1 * 0x100000000 + 0xAAAAAAAA);
  assertEqual(fpfN.TheFraction, (int64_t)-1 * 0x100000000 + 0xAAAAAAAB);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-1, -3, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)0 * 0x100000000 + 0x55555556);
  assertEqual(fpfN.TheFraction, (int64_t)0 * 0x100000000 + 0x55555555);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(2, 3, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)0 * 0x100000000 + 0xAAAAAAAB);
  assertEqual(fpfN.TheFraction, (int64_t)0 * 0x100000000 + 0xAAAAAAAA);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-2, 3, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-1 * 0x100000000 + 0x55555555);
  assertEqual(fpfN.TheFraction, (int64_t)-1 * 0x100000000 + 0x55555556);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(2, -3, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-1 * 0x100000000 + 0x55555555);
  assertEqual(fpfN.TheFraction, (int64_t)-1 * 0x100000000 + 0x55555556);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-2, -3, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)0 * 0x100000000 + 0xAAAAAAAB);
  assertEqual(fpfN.TheFraction, (int64_t)0 * 0x100000000 + 0xAAAAAAAA);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  // binary fraction
  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(1, 2, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)0 * 0x100000000 + 0x80000000);
  assertEqual(fpfN.TheFraction, (int64_t)0 * 0x100000000 + 0x80000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-3, 4, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-1 * 0x100000000 + 0x40000000);
  assertEqual(fpfN.TheFraction, (int64_t)-1 * 0x100000000 + 0x40000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(3, -8, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-1 * 0x100000000 + 0xA0000000);
  assertEqual(fpfN.TheFraction, (int64_t)-1 * 0x100000000 + 0xA0000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-3, -16, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)0 * 0x100000000 + 0x30000000);
  assertEqual(fpfN.TheFraction, (int64_t)0 * 0x100000000 + 0x30000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  // binary vulgar fraction
  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(3, 2, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)1 * 0x100000000 + 0x80000000);
  assertEqual(fpfN.TheFraction, (int64_t)1 * 0x100000000 + 0x80000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-7, 4, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-2 * 0x100000000 + 0x40000000);
  assertEqual(fpfN.TheFraction, (int64_t)-2 * 0x100000000 + 0x40000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(11, -8, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-2 * 0x100000000 + 0xA0000000);
  assertEqual(fpfN.TheFraction, (int64_t)-2 * 0x100000000 + 0xA0000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-19, -16, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)1 * 0x100000000 + 0x30000000);
  assertEqual(fpfN.TheFraction, (int64_t)1 * 0x100000000 + 0x30000000);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  // inexact fraction
  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(5, 9, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)0 * 0x100000000 + 0x8E38E38F); // 32 = 0x8E39
  assertEqual(fpfN.TheFraction, (int64_t)0 * 0x100000000 + 0x8E38E38E); // 32 = 0x8E38
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-5, 9, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-1 * 0x100000000 + 0x71C71C71); // 32 = 0x71C7
  assertEqual(fpfN.TheFraction, (int64_t)-1 * 0x100000000 + 0x71C71C72); // 32 = 0x71C8
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(5, -9, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-1 * 0x100000000 + 0x71C71C71); // 32 = 0x71C7
  assertEqual(fpfN.TheFraction, (int64_t)-1 * 0x100000000 + 0x71C71C72); // 32 = 0x71C8
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-5, -9, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)0 * 0x100000000 + 0x8E38E38F); // 32 = 0x8E39
  assertEqual(fpfN.TheFraction, (int64_t)0 * 0x100000000 + 0x8E38E38E); // 32 = 0x8E38
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  // inexact vulgar fraction
  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(9, 5, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)1 * 0x100000000 + 0xCCCCCCCD);
  assertEqual(fpfN.TheFraction, (int64_t)1 * 0x100000000 + 0xCCCCCCCC);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-9, 5, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-2 * 0x100000000 + 0x33333333);
  assertEqual(fpfN.TheFraction, (int64_t)-2 * 0x100000000 + 0x33333334);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(9, -5, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)-2 * 0x100000000 + 0x33333333);
  assertEqual(fpfN.TheFraction, (int64_t)-2 * 0x100000000 + 0x33333334);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);

  fpfP = fpfN = {-2468, 97}; Ratio64ToFixedPointFraction64(-9, -5, &fpfP, &fpfN);
  assertEqual(fpfP.TheFraction, (int64_t)1 * 0x100000000 + 0xCCCCCCCD);
  assertEqual(fpfN.TheFraction, (int64_t)1 * 0x100000000 + 0xCCCCCCCC);
  assertEqual(fpfP.BitsToShift, 32);
  assertEqual(fpfN.BitsToShift, 32);
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
