//
//    FILE: fastMapInteger8ArithmeticTest.ino
//  AUTHOR: Brewmanz (Bryan White)
// VERSION: 0.1.1
// PURPOSE: Test of FastMapInt(16) helper functions
//    DATE: 2020-09-08
//     URL: https://github.com/RobTillaart/FastMap

//#include <AUnitVerbose.h> // too much for Nano!
#include <AUnit.h>
#include <FastMap.h>

volatile int i, j;

test(T9130FastMapInt_F2C_M40To212) {
  FastMapInt mapper;
  mapper.init(-40, 212, -40, 100);
  mapper.Dump(&Serial);
  bool failed = false;
  int outCalcInfo;
  for(int ix = 0; ix <= 50; ++ix){
    int valExp = (ix + 40 + 90) * 5 / 9 - 50 - 40;
    int valAct = mapper.map(ix, &outCalcInfo);
    if(valExp != valAct){
      failed = true;
      Serial.print(F("ix="));Serial.print(ix);
      Serial.print(F("\texp="));Serial.print(valExp);
      Serial.print(F("\tact="));Serial.print(valAct);
      Serial.print(F("\toCI="));Serial.print(outCalcInfo);
      Serial.println();
    }
  }
  assertEqual(failed, false);
}

test(T1136Multiply8ByFixedPointFraction16_5DivM9_Neg) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(5, -9, nullptr, &FPF);
  assertEqual(Multiply8ByFixedPointFraction16(0, &FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction16(-1, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(-2, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(-3, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(-4, &FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction16(-5, &FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction16(-6, &FPF), 4);
  assertEqual(Multiply8ByFixedPointFraction16(-7, &FPF), 4);
  assertEqual(Multiply8ByFixedPointFraction16(-8, &FPF), 5);
  assertEqual(Multiply8ByFixedPointFraction16(-9, &FPF), 5);

  assertEqual(Multiply8ByFixedPointFraction16(-10, &FPF), 6);
  assertEqual(Multiply8ByFixedPointFraction16(-100, &FPF), 56);
}

test(T1135Multiply8ByFixedPointFraction16_5DivM9_Pos) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(5, -9, &FPF, nullptr);
  assertEqual(Multiply8ByFixedPointFraction16(0, &FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction16(1, &FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction16(2, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(3, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(4, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(5, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(6, &FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction16(7, &FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction16(8, &FPF), -4);
  assertEqual(Multiply8ByFixedPointFraction16(9, &FPF), -5);

  assertEqual(Multiply8ByFixedPointFraction16(10, &FPF), -5);
  assertEqual(Multiply8ByFixedPointFraction16(100, &FPF), -55);
}
test(T1131Multiply8ByFixedPointFraction16_5Div9_Neg) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(5, 9, nullptr, &FPF);
  assertEqual(Multiply8ByFixedPointFraction16(0, &FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction16(-1, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(-2, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(-3, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(-4, &FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction16(-5, &FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction16(-6, &FPF), -4);
  assertEqual(Multiply8ByFixedPointFraction16(-7, &FPF), -4);
  assertEqual(Multiply8ByFixedPointFraction16(-8, &FPF), -5);
  assertEqual(Multiply8ByFixedPointFraction16(-9, &FPF), -5);

  assertEqual(Multiply8ByFixedPointFraction16(-10, &FPF), -6);
  assertEqual(Multiply8ByFixedPointFraction16(-100, &FPF), -56);
}
test(T1130Multiply8ByFixedPointFraction16_5Div9_Pos) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(5, 9, &FPF, nullptr);
  assertEqual(Multiply8ByFixedPointFraction16(0, &FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction16(1, &FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction16(2, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(3, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(4, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(5, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(6, &FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction16(7, &FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction16(8, &FPF), 4);
  assertEqual(Multiply8ByFixedPointFraction16(9, &FPF), 5);

  assertEqual(Multiply8ByFixedPointFraction16(10, &FPF), 5);
  assertEqual(Multiply8ByFixedPointFraction16(100, &FPF), 55);
}

test(T1126Multiply8ByFixedPointFraction16_1DivM3_Neg) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(1, -3, nullptr, &FPF);
  assertEqual(Multiply8ByFixedPointFraction16(0, &FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction16(-1, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(-2, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(-3, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(-4, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(-5, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(-6, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(-7, &FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction16(-8, &FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction16(-9, &FPF), 3);

  assertEqual(Multiply8ByFixedPointFraction16(-10, &FPF), 4);
  assertEqual(Multiply8ByFixedPointFraction16(-100, &FPF), 34);
}
test(T1125Multiply8ByFixedPointFraction16_1DivM3_Pos) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(1, -3, &FPF, nullptr);
  assertEqual(Multiply8ByFixedPointFraction16(0, &FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction16(1, &FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction16(2, &FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction16(3, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(4, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(5, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(6, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(7, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(8, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(9, &FPF), -3);

  assertEqual(Multiply8ByFixedPointFraction16(10, &FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction16(100, &FPF), -33);
}
test(T1121Multiply8ByFixedPointFraction16_1Div3_Neg) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(1, 3, nullptr, &FPF);
  assertEqual(Multiply8ByFixedPointFraction16(0, &FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction16(-1, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(-2, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(-3, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(-4, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(-5, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(-6, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(-7, &FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction16(-8, &FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction16(-9, &FPF), -3);

  assertEqual(Multiply8ByFixedPointFraction16(-10, &FPF), -4);
  assertEqual(Multiply8ByFixedPointFraction16(-100, &FPF), -34);
}
test(T1120Multiply8ByFixedPointFraction16_1Div3_Pos) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(1, 3, &FPF, nullptr);
  assertEqual(Multiply8ByFixedPointFraction16(0, &FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction16(1, &FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction16(2, &FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction16(3, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(4, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(5, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(6, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(7, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(8, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(9, &FPF), 3);

  assertEqual(Multiply8ByFixedPointFraction16(10, &FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction16(100, &FPF), 33);
}

test(T1116Multiply8ByFixedPointFraction16_1DivM4_Neg) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(1, -4, nullptr, &FPF);
  assertEqual(Multiply8ByFixedPointFraction16(0, &FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction16(-1, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(-2, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(-3, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(-4, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(-5, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(-6, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(-7, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(-8, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(-9, &FPF), 3);

  assertEqual(Multiply8ByFixedPointFraction16(-10, &FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction16(-100, &FPF), 25);
}
test(T1115Multiply8ByFixedPointFraction16_1DivM4_Pos) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(1, -4, &FPF, nullptr);
  assertEqual(Multiply8ByFixedPointFraction16(0, &FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction16(1, &FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction16(2, &FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction16(3, &FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction16(4, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(5, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(6, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(7, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(8, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(9, &FPF), -2);

  assertEqual(Multiply8ByFixedPointFraction16(10, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(100, &FPF), -25);
}
test(T1111Multiply8ByFixedPointFraction16_1Div4_Neg) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(1, 4, nullptr, &FPF);
  assertEqual(Multiply8ByFixedPointFraction16(0, &FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction16(-1, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(-2, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(-3, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(-4, &FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction16(-5, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(-6, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(-7, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(-8, &FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction16(-9, &FPF), -3);

  assertEqual(Multiply8ByFixedPointFraction16(-10, &FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction16(-100, &FPF), -25);
}
test(T1110Multiply8ByFixedPointFraction16_1Div4_Pos) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(1, 4, &FPF, nullptr);
  assertEqual(Multiply8ByFixedPointFraction16(0, &FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction16(1, &FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction16(2, &FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction16(3, &FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction16(4, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(5, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(6, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(7, &FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction16(8, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(9, &FPF), 2);

  assertEqual(Multiply8ByFixedPointFraction16(10, &FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction16(100, &FPF), 25);
}

test(T1100Ratio8ToFixedPointFraction16) {
  FixedPointFraction16_t fpfP, fpfN;
#if FULL_DEBUG || 1
  Print* pPrintDebug = &Serial;
#else
  Print* pPrintDebug = nullptr;
#endif

  // handling of 0
  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(0, 0, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 0);
  assertEqual(fpfN.BitsToShift, 0);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(0, 8, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 0);
  assertEqual(fpfN.BitsToShift, 0);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(8, 0, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 0);
  assertEqual(fpfN.BitsToShift, 0);

  // equal ratios
  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(1, 1, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)64 * 1 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)64 * 1 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 6);
  assertEqual(fpfN.BitsToShift, 8 + 6);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(12, 12, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)8 * 1 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)8 * 1 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 3);
  assertEqual(fpfN.BitsToShift, 8 + 3);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-2, 2, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)32 * -1  * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)32 * -1  * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 5);
  assertEqual(fpfN.BitsToShift, 8 + 5);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(3, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)32 * -1 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)32 * -1 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 5);
  assertEqual(fpfN.BitsToShift, 8 + 5);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-4, -4, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)16 * 1 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)16 * 1 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 4);
  assertEqual(fpfN.BitsToShift, 8 + 4);

  // exact ratios
  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(8, 2, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)8 * 4 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)8 * 4 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 3);
  assertEqual(fpfN.BitsToShift, 8 + 3);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-12, 4, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)8 * -3 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)8 * -3 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 3);
  assertEqual(fpfN.BitsToShift, 8 + 3);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(30, -5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)4 * -6 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)4 * -6 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 2);
  assertEqual(fpfN.BitsToShift, 8 + 2);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-56, -7, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)2 * 8 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)2 * 8 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 1);
  assertEqual(fpfN.BitsToShift, 8 + 1);

  // theoretical exact ratios
  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(1, 3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)0 * 0x100 + 0x1556);
  assertEqual(fpfN.TheFraction, (int16_t)0 * 0x100 + 0x1555);
  assertEqual(fpfP.BitsToShift, 8 + 6);
  assertEqual(fpfN.BitsToShift, 8 + 6);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-1, 3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)64 * -1 * 0x100 + 0x2AAA);
  assertEqual(fpfN.TheFraction, (int16_t)64 * -1 * 0x100 + 0x2AAB);
  assertEqual(fpfP.BitsToShift, 8 + 6);
  assertEqual(fpfN.BitsToShift, 8 + 6);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(1, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)64 * -1 * 0x100 + 0x2AAA);
  assertEqual(fpfN.TheFraction, (int16_t)64 * -1 * 0x100 + 0x2AAB);
  assertEqual(fpfP.BitsToShift, 8 + 6);
  assertEqual(fpfN.BitsToShift, 8 + 6);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-1, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)64 * 0 * 0x100 + 0x1556);
  assertEqual(fpfN.TheFraction, (int16_t)64 * 0 * 0x100 + 0x1555);
  assertEqual(fpfP.BitsToShift, 8 + 6);
  assertEqual(fpfN.BitsToShift, 8 + 6);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(2, 3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)32 * 0 * 0x100 + 0x1556);
  assertEqual(fpfN.TheFraction, (int16_t)32 * 0 * 0x100 + 0x1555);
  assertEqual(fpfP.BitsToShift, 8 + 5);
  assertEqual(fpfN.BitsToShift, 8 + 5);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-2, 3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)32 * -1 * 0x100 + 0xAAA);
  assertEqual(fpfN.TheFraction, (int16_t)32 * -1 * 0x100 + 0xAAB);
  assertEqual(fpfP.BitsToShift, 8 + 5);
  assertEqual(fpfN.BitsToShift, 8 + 5);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(2, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)32 * -1 * 0x100 + 0xAAA);
  assertEqual(fpfN.TheFraction, (int16_t)32 * -1 * 0x100 + 0xAAB);
  assertEqual(fpfP.BitsToShift, 8 + 5);
  assertEqual(fpfN.BitsToShift, 8 + 5);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-2, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)32 * 0 * 0x100 + 0x1556);
  assertEqual(fpfN.TheFraction, (int16_t)32 * 0 * 0x100 + 0x1555);
  assertEqual(fpfP.BitsToShift, 8 + 5);
  assertEqual(fpfN.BitsToShift, 8 + 5);

  // binary fraction
  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(1, 2, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)64 * 0 * 0x100 + 0x2000);
  assertEqual(fpfN.TheFraction, (int16_t)64 * 0 * 0x100 + 0x2000);
  assertEqual(fpfP.BitsToShift, 8 + 6);
  assertEqual(fpfN.BitsToShift, 8 + 6);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-3, 4, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)32 * -1 * 0x100 + 0x0800);
  assertEqual(fpfN.TheFraction, (int16_t)32 * -1 * 0x100 + 0x0800);
  assertEqual(fpfP.BitsToShift, 8 + 5);
  assertEqual(fpfN.BitsToShift, 8 + 5);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(3, -8, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)32 * -1 * 0x100 + 0x1400);
  assertEqual(fpfN.TheFraction, (int16_t)32 * -1 * 0x100 + 0x1400);
  assertEqual(fpfP.BitsToShift, 8 + 5);
  assertEqual(fpfN.BitsToShift, 8 + 5);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-3, -16, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)32 * 0 * 0x100 + 0x600);
  assertEqual(fpfN.TheFraction, (int16_t)32 * 0 * 0x100 + 0x600);
  assertEqual(fpfP.BitsToShift, 8 + 5);
  assertEqual(fpfN.BitsToShift, 8 + 5);

  // binary vulgar fraction
  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(3, 2, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)32 * 1 * 0x100 + 0x1000);
  assertEqual(fpfN.TheFraction, (int16_t)32 * 1 * 0x100 + 0x1000);
  assertEqual(fpfP.BitsToShift, 8 + 5);
  assertEqual(fpfN.BitsToShift, 8 + 5);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-7, 4, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)16 * -2 * 0x100 + 0x400);
  assertEqual(fpfN.TheFraction, (int16_t)16 * -2 * 0x100 + 0x400);
  assertEqual(fpfP.BitsToShift, 8 + 4);
  assertEqual(fpfN.BitsToShift, 8 + 4);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(11, -8, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)8 * -2 * 0x100 + 0x500);
  assertEqual(fpfN.TheFraction, (int16_t)8 * -2 * 0x100 + 0x500);
  assertEqual(fpfP.BitsToShift, 8 + 3);
  assertEqual(fpfN.BitsToShift, 8 + 3);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-19, -16, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)4 * 1 * 0x100 + 0xC0);
  assertEqual(fpfN.TheFraction, (int16_t)4 * 1 * 0x100 + 0xC0);
  assertEqual(fpfP.BitsToShift, 8 + 2);
  assertEqual(fpfN.BitsToShift, 8 + 2);

  // inexact fraction
  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(5, 9, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)16 * 0 * 0x100 + 0x8E4);
  assertEqual(fpfN.TheFraction, (int16_t)16 * 0 * 0x100 + 0x8E3);
  assertEqual(fpfP.BitsToShift, 8 + 4);
  assertEqual(fpfN.BitsToShift, 8 + 4);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-5, 9, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)16 * -1 * 0x100 + 0x71C);
  assertEqual(fpfN.TheFraction, (int16_t)16 * -1 * 0x100 + 0x71D);
  assertEqual(fpfP.BitsToShift, 8 + 4);
  assertEqual(fpfN.BitsToShift, 8 + 4);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(5, -9, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)16 * -1 * 0x100 + 0x71C);
  assertEqual(fpfN.TheFraction, (int16_t)16 * -1 * 0x100 + 0x71D);
  assertEqual(fpfP.BitsToShift, 8 + 4);
  assertEqual(fpfN.BitsToShift, 8 + 4);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-5, -9, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)16 * 0 * 0x100 + 0x8E4);
  assertEqual(fpfN.TheFraction, (int16_t)16 * 0 * 0x100 + 0x8E3);
  assertEqual(fpfP.BitsToShift, 8 + 4);
  assertEqual(fpfN.BitsToShift, 8 + 4);

  // inexact vulgar fraction
  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(9, 5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)8 * 1 * 0x100 + 0x667);
  assertEqual(fpfN.TheFraction, (int16_t)8 * 1 * 0x100 + 0x666);
  assertEqual(fpfP.BitsToShift, 8 + 3);
  assertEqual(fpfN.BitsToShift, 8 + 3);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-9, 5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)8 * -2 * 0x100 + 0x199);
  assertEqual(fpfN.TheFraction, (int16_t)8 * -2 * 0x100 + 0x19A);
  assertEqual(fpfP.BitsToShift, 8 + 3);
  assertEqual(fpfN.BitsToShift, 8 + 3);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(9, -5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)8 * -2 * 0x100 + 0x199);
  assertEqual(fpfN.TheFraction, (int16_t)8 * -2 * 0x100 + 0x19A);
  assertEqual(fpfP.BitsToShift, 8 + 3);
  assertEqual(fpfN.BitsToShift, 8 + 3);

  fpfP = fpfN = {-2468, 97}; Ratio8ToFixedPointFraction16(-9, -5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)8 * 1 * 0x100 + 0x667);
  assertEqual(fpfN.TheFraction, (int16_t)8 * 1 * 0x100 + 0x666);
  assertEqual(fpfP.BitsToShift, 8 + 3);
  assertEqual(fpfN.BitsToShift, 8 + 3);
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
