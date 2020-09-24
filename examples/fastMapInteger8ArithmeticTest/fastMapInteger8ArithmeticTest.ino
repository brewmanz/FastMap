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
  int fails = 0;
  int outCalcInfo;
  for(int ix = 0; ix <= 500; ++ix){
    int valExp = (ix + 40 + 90) * 5 / 9 - 50 - 40;
    int valAct = mapper.map(ix, &outCalcInfo);
    if(valExp != valAct){
      ++fails;
      Serial.print(F("ix="));Serial.print(ix);
      Serial.print(F("\texp="));Serial.print(valExp);
      Serial.print(F("\tact="));Serial.print(valAct);
      Serial.print(F("\toCI="));Serial.print(outCalcInfo);
      Serial.println();
    }
  }
  assertEqual(fails, 0);
}

test(T1136Multiply8ByFixedPointFraction16_5DivM9_Neg) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(5, -9, nullptr, &FPF);
  assertEqual(FPF.MaxInput, 114);
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
  assertEqual(FPF.MaxInput, 114);
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
  assertEqual(FPF.MaxInput, 114);
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
  assertEqual(FPF.MaxInput, 114);
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
  assertEqual(FPF.MaxInput, 95);
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
  assertEqual(Multiply8ByFixedPointFraction16(-92, &FPF), 31);  
  assertEqual(Multiply8ByFixedPointFraction16(-93, &FPF), 31);  
  assertEqual(Multiply8ByFixedPointFraction16(-94, &FPF), 32);
  // 95 is max call value for 1/3
  assertEqual(Multiply8ByFixedPointFraction16(-95, &FPF), 32);
}
test(T1125Multiply8ByFixedPointFraction16_1DivM3_Pos) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(1, -3, &FPF, nullptr);
  assertEqual(FPF.MaxInput, 95);
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
  assertEqual(Multiply8ByFixedPointFraction16(92, &FPF), -30);  
  assertEqual(Multiply8ByFixedPointFraction16(93, &FPF), -31);  
  assertEqual(Multiply8ByFixedPointFraction16(94, &FPF), -31);
  // 95 is max call value for 1/3
  assertEqual(Multiply8ByFixedPointFraction16(95, &FPF), -31);
}
test(T1121Multiply8ByFixedPointFraction16_1Div3_Neg) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(1, 3, nullptr, &FPF);
  assertEqual(FPF.MaxInput, 95);
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
  assertEqual(Multiply8ByFixedPointFraction16(-92, &FPF), -31);  
  assertEqual(Multiply8ByFixedPointFraction16(-93, &FPF), -31);  
  assertEqual(Multiply8ByFixedPointFraction16(-94, &FPF), -32);
  // 95 is max call value for 1/3
  assertEqual(Multiply8ByFixedPointFraction16(-95, &FPF), -32);
}
test(T1120Multiply8ByFixedPointFraction16_1Div3_Pos) {
#if FULL_DEBUG
  Print* pPrintDebug = &Serial;
#else
  Print* pPrintDebug = nullptr;
#endif
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(1, 3, &FPF, nullptr);
  assertEqual(FPF.MaxInput, 95);
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
  assertEqual(Multiply8ByFixedPointFraction16(92, &FPF, pPrintDebug), 30);  
  assertEqual(Multiply8ByFixedPointFraction16(93, &FPF, pPrintDebug), 31);  
  assertEqual(Multiply8ByFixedPointFraction16(94, &FPF, pPrintDebug), 31);
  // 95 is max call value for 1/3
  assertEqual(Multiply8ByFixedPointFraction16(95, &FPF, pPrintDebug), 31);
  if(pPrintDebug) { pPrintDebug->println(); }
}

test(T1116Multiply8ByFixedPointFraction16_1DivM4_Neg) {
  FixedPointFraction16_t FPF;
  Ratio8ToFixedPointFraction16(1, -4, nullptr, &FPF);
  assertEqual(FPF.MaxInput, 127);
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
  assertEqual(FPF.MaxInput, 127);
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
  assertEqual(FPF.MaxInput, 127);
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
  assertEqual(FPF.MaxInput, 127);
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
#if FULL_DEBUG
  Print* pPrintDebug = &Serial;
#else
  Print* pPrintDebug = nullptr;
#endif

  fpfP = fpfN = {-2468, 97, -42};
  assertEqual(fpfP.TheFraction, -2468);
  assertEqual(fpfN.TheFraction, -2468);
  assertEqual(fpfP.BitsToShift, 97);
  assertEqual(fpfN.BitsToShift, 97);
  assertEqual(fpfP.MaxInput, -42);
  assertEqual(fpfN.MaxInput, -42);

  // handling of 0
  Ratio8ToFixedPointFraction16(0, 0, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 0);
  assertEqual(fpfN.BitsToShift, 0);
  assertEqual(fpfP.MaxInput, 0);
  assertEqual(fpfN.MaxInput, 0);

  Ratio8ToFixedPointFraction16(0, 8, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 0);
  assertEqual(fpfN.BitsToShift, 0);
  assertEqual(fpfP.MaxInput, 0);
  assertEqual(fpfN.MaxInput, 0);

  Ratio8ToFixedPointFraction16(8, 0, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 0);
  assertEqual(fpfN.BitsToShift, 0);
  assertEqual(fpfP.MaxInput, 0);
  assertEqual(fpfN.MaxInput, 0);

  // equal ratios
  Ratio8ToFixedPointFraction16(1, 1, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 0);
  assertEqual(fpfN.BitsToShift, 8 + 0);
  assertEqual(fpfP.MaxInput, 127);
  assertEqual(fpfN.MaxInput, 127);

  Ratio8ToFixedPointFraction16(12, 12, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 0);
  assertEqual(fpfN.BitsToShift, 8 + 0);
  assertEqual(fpfP.MaxInput, 127);
  assertEqual(fpfN.MaxInput, 127);

  Ratio8ToFixedPointFraction16(-2, 2, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-1  * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)-1  * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 0);
  assertEqual(fpfN.BitsToShift, 8 + 0);
  assertEqual(fpfP.MaxInput, 127);
  assertEqual(fpfN.MaxInput, 127);

  Ratio8ToFixedPointFraction16(3, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-1 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)-1 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 0);
  assertEqual(fpfN.BitsToShift, 8 + 0);
  assertEqual(fpfP.MaxInput, 127);
  assertEqual(fpfN.MaxInput, 127);

  Ratio8ToFixedPointFraction16(-4, -4, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 0);
  assertEqual(fpfN.BitsToShift, 8 + 0);
  assertEqual(fpfP.MaxInput, 127);
  assertEqual(fpfN.MaxInput, 127);

  // exact ratios
  Ratio8ToFixedPointFraction16(8, 2, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 - 2);
  assertEqual(fpfN.BitsToShift, 8 - 2);
  assertEqual(fpfP.MaxInput, 31);
  assertEqual(fpfN.MaxInput, 31);

  Ratio8ToFixedPointFraction16(-12, 4, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-2 * 0x100 + 0x80);
  assertEqual(fpfN.TheFraction, (int16_t)-2 * 0x100 + 0x80);
  assertEqual(fpfP.BitsToShift, 8 - 1);
  assertEqual(fpfN.BitsToShift, 8 - 1);
  assertEqual(fpfP.MaxInput, 42);
  assertEqual(fpfN.MaxInput, 42);

  Ratio8ToFixedPointFraction16(30, -5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-2 * 0x100 + 0x80);
  assertEqual(fpfN.TheFraction, (int16_t)-2 * 0x100 + 0x80);
  assertEqual(fpfP.BitsToShift, 8 - 2);
  assertEqual(fpfN.BitsToShift, 8 - 2);
  assertEqual(fpfP.MaxInput, 21);
  assertEqual(fpfN.MaxInput, 21);

  Ratio8ToFixedPointFraction16(-56, -7, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 - 3);
  assertEqual(fpfN.BitsToShift, 8 - 3);
  assertEqual(fpfP.MaxInput, 15);
  assertEqual(fpfN.MaxInput, 15);

  // theoretical exact ratios
  Ratio8ToFixedPointFraction16(1, 3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x56);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x55);
  assertEqual(fpfP.BitsToShift, 8 + 2);
  assertEqual(fpfN.BitsToShift, 8 + 2);
  assertEqual(fpfP.MaxInput, 95);
  assertEqual(fpfN.MaxInput, 95);

  Ratio8ToFixedPointFraction16(-1, 3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-2 * 0x100 + 0xAA);
  assertEqual(fpfN.TheFraction, (int16_t)-2 * 0x100 + 0xAB);
  assertEqual(fpfP.BitsToShift, 8 + 2);
  assertEqual(fpfN.BitsToShift, 8 + 2);
  assertEqual(fpfP.MaxInput, 95);
  assertEqual(fpfN.MaxInput, 95);

  Ratio8ToFixedPointFraction16(1, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-2 * 0x100 + 0xAA);
  assertEqual(fpfN.TheFraction, (int16_t)-2 * 0x100 + 0xAB);
  assertEqual(fpfP.BitsToShift, 8 + 2);
  assertEqual(fpfN.BitsToShift, 8 + 2);
  assertEqual(fpfP.MaxInput, 95);
  assertEqual(fpfN.MaxInput, 95);

  Ratio8ToFixedPointFraction16(-1, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x56);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x55);
  assertEqual(fpfP.BitsToShift, 8 + 2);
  assertEqual(fpfN.BitsToShift, 8 + 2);
  assertEqual(fpfP.MaxInput, 95);
  assertEqual(fpfN.MaxInput, 95);

  Ratio8ToFixedPointFraction16(2, 3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x56);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x55);
  assertEqual(fpfP.BitsToShift, 8 + 1);
  assertEqual(fpfN.BitsToShift, 8 + 1);
  assertEqual(fpfP.MaxInput, 95);
  assertEqual(fpfN.MaxInput, 95);

  Ratio8ToFixedPointFraction16(-2, 3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-2 * 0x100 + 0xAA);
  assertEqual(fpfN.TheFraction, (int16_t)-2 * 0x100 + 0xAB);
  assertEqual(fpfP.BitsToShift, 8 + 1);
  assertEqual(fpfN.BitsToShift, 8 + 1);
  assertEqual(fpfP.MaxInput, 95);
  assertEqual(fpfN.MaxInput, 95);

  Ratio8ToFixedPointFraction16(2, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-2 * 0x100 + 0xAA);
  assertEqual(fpfN.TheFraction, (int16_t)-2 * 0x100 + 0xAB);
  assertEqual(fpfP.BitsToShift, 8 + 1);
  assertEqual(fpfN.BitsToShift, 8 + 1);
  assertEqual(fpfP.MaxInput, 95);
  assertEqual(fpfN.MaxInput, 95);

  Ratio8ToFixedPointFraction16(-2, -3, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x56);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x55);
  assertEqual(fpfP.BitsToShift, 8 + 1);
  assertEqual(fpfN.BitsToShift, 8 + 1);
  assertEqual(fpfP.MaxInput, 95);
  assertEqual(fpfN.MaxInput, 95);

  // binary fraction
  Ratio8ToFixedPointFraction16(1, 2, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfP.BitsToShift, 8 + 1);
  assertEqual(fpfN.BitsToShift, 8 + 1);
  assertEqual(fpfP.MaxInput, 127);
  assertEqual(fpfN.MaxInput, 127);

  Ratio8ToFixedPointFraction16(-3, 4, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-2 * 0x100 + 0x80);
  assertEqual(fpfN.TheFraction, (int16_t)-2 * 0x100 + 0x80);
  assertEqual(fpfP.BitsToShift, 8 + 1);
  assertEqual(fpfN.BitsToShift, 8 + 1);
  assertEqual(fpfP.MaxInput, 84);
  assertEqual(fpfN.MaxInput, 84);

  Ratio8ToFixedPointFraction16(3, -8, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-2 * 0x100 + 0x80);
  assertEqual(fpfN.TheFraction, (int16_t)-2 * 0x100 + 0x80);
  assertEqual(fpfP.BitsToShift, 8 + 2);
  assertEqual(fpfN.BitsToShift, 8 + 2);
  assertEqual(fpfP.MaxInput, 84);
  assertEqual(fpfN.MaxInput, 84);

  Ratio8ToFixedPointFraction16(-3, -16, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x80);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x80);
  assertEqual(fpfP.BitsToShift, 8 + 3);
  assertEqual(fpfN.BitsToShift, 8 + 3);
  assertEqual(fpfP.MaxInput, 84);
  assertEqual(fpfN.MaxInput, 84);

  // binary vulgar fraction
  Ratio8ToFixedPointFraction16(3, 2, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x80);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x80);
  assertEqual(fpfP.BitsToShift, 8 + 0);
  assertEqual(fpfN.BitsToShift, 8 + 0);
  assertEqual(fpfP.MaxInput, 84);
  assertEqual(fpfN.MaxInput, 84);

  Ratio8ToFixedPointFraction16(-7, 4, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-2 * 0x100 + 0x40);
  assertEqual(fpfN.TheFraction, (int16_t)-2 * 0x100 + 0x40);
  assertEqual(fpfP.BitsToShift, 8 + 0);
  assertEqual(fpfN.BitsToShift, 8 + 0);
  assertEqual(fpfP.MaxInput, 72);
  assertEqual(fpfN.MaxInput, 72);

  Ratio8ToFixedPointFraction16(11, -8, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-2 * 0x100 + 0xA0);
  assertEqual(fpfN.TheFraction, (int16_t)-2 * 0x100 + 0xA0);
  assertEqual(fpfP.BitsToShift, 8 + 0);
  assertEqual(fpfN.BitsToShift, 8 + 0);
  assertEqual(fpfP.MaxInput, 92);
  assertEqual(fpfN.MaxInput, 92);

  Ratio8ToFixedPointFraction16(-19, -16, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x30);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x30);
  assertEqual(fpfP.BitsToShift, 8 + 0);
  assertEqual(fpfN.BitsToShift, 8 + 0);
  assertEqual(fpfP.MaxInput, 106);
  assertEqual(fpfN.MaxInput, 106);

  // inexact fraction
  Ratio8ToFixedPointFraction16(5, 9, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x1D);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x1C);
  assertEqual(fpfP.BitsToShift, 8 + 1);
  assertEqual(fpfN.BitsToShift, 8 + 1);
  assertEqual(fpfP.MaxInput, 114);
  assertEqual(fpfN.MaxInput, 114);

  Ratio8ToFixedPointFraction16(-5, 9, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-2 * 0x100 + 0xE3);
  assertEqual(fpfN.TheFraction, (int16_t)-2 * 0x100 + 0xE4);
  assertEqual(fpfP.BitsToShift, 8 + 1);
  assertEqual(fpfN.BitsToShift, 8 + 1);
  assertEqual(fpfP.MaxInput, 114);
  assertEqual(fpfN.MaxInput, 114);

  Ratio8ToFixedPointFraction16(5, -9, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-2 * 0x100 + 0xE3);
  assertEqual(fpfN.TheFraction, (int16_t)-2 * 0x100 + 0xE4);
  assertEqual(fpfP.BitsToShift, 8 + 1);
  assertEqual(fpfN.BitsToShift, 8 + 1);
  assertEqual(fpfP.MaxInput, 114);
  assertEqual(fpfN.MaxInput, 114);

  Ratio8ToFixedPointFraction16(-5, -9, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0x1D);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0x1C);
  assertEqual(fpfP.BitsToShift, 8 + 1);
  assertEqual(fpfN.BitsToShift, 8 + 1);
  assertEqual(fpfP.MaxInput, 114);
  assertEqual(fpfN.MaxInput, 114);

  // inexact vulgar fraction
  Ratio8ToFixedPointFraction16(9, 5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0xCD);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0xCC);
  assertEqual(fpfP.BitsToShift, 8 + 0);
  assertEqual(fpfN.BitsToShift, 8 + 0);
  assertEqual(fpfP.MaxInput, 70);
  assertEqual(fpfN.MaxInput, 70);

  Ratio8ToFixedPointFraction16(-9, 5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-2 * 0x100 + 0x33);
  assertEqual(fpfN.TheFraction, (int16_t)-2 * 0x100 + 0x34);
  assertEqual(fpfP.BitsToShift, 8 + 0);
  assertEqual(fpfN.BitsToShift, 8 + 0);
  assertEqual(fpfP.MaxInput, 70);
  assertEqual(fpfN.MaxInput, 70);

  Ratio8ToFixedPointFraction16(9, -5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)-2 * 0x100 + 0x33);
  assertEqual(fpfN.TheFraction, (int16_t)-2 * 0x100 + 0x34);
  assertEqual(fpfP.BitsToShift, 8 + 0);
  assertEqual(fpfN.BitsToShift, 8 + 0);
  assertEqual(fpfP.MaxInput, 70);
  assertEqual(fpfN.MaxInput, 70);

  Ratio8ToFixedPointFraction16(-9, -5, &fpfP, &fpfN, pPrintDebug);
  if(pPrintDebug) { pPrintDebug->println(); }
  assertEqual(fpfP.TheFraction, (int16_t)1 * 0x100 + 0xCD);
  assertEqual(fpfN.TheFraction, (int16_t)1 * 0x100 + 0xCC);
  assertEqual(fpfP.BitsToShift, 8 + 0);
  assertEqual(fpfN.BitsToShift, 8 + 0);
  assertEqual(fpfP.MaxInput, 70);
  assertEqual(fpfN.MaxInput, 70);
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
