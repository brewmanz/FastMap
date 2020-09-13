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

test(T1136Multiply8ByFixedPointFraction88_5DivM9_Neg) {
  int16_t FPF;
  Ratio8ToFixedPointFraction88(5, -9, nullptr, &FPF);
  assertEqual(Multiply8ByFixedPointFraction88(0, FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction88(-1, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(-2, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(-3, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(-4, FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction88(-5, FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction88(-6, FPF), 4);
  assertEqual(Multiply8ByFixedPointFraction88(-7, FPF), 4);
  assertEqual(Multiply8ByFixedPointFraction88(-8, FPF), 5);
  assertEqual(Multiply8ByFixedPointFraction88(-9, FPF), 5);

  assertEqual(Multiply8ByFixedPointFraction88(-10, FPF), 6);
  assertEqual(Multiply8ByFixedPointFraction88(-100, FPF), 56);
}

test(T1135Multiply8ByFixedPointFraction88_5DivM9_Pos) {
  int16_t FPF;
  Ratio8ToFixedPointFraction88(5, -9, &FPF, nullptr);
  assertEqual(Multiply8ByFixedPointFraction88(0, FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction88(1, FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction88(2, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(3, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(4, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(5, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(6, FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction88(7, FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction88(8, FPF), -4);
  assertEqual(Multiply8ByFixedPointFraction88(9, FPF), -5);

  assertEqual(Multiply8ByFixedPointFraction88(10, FPF), -5);
  assertEqual(Multiply8ByFixedPointFraction88(100, FPF), -55);
}
test(T1131Multiply8ByFixedPointFraction88_5Div9_Neg) {
  int16_t FPF;
  Ratio8ToFixedPointFraction88(5, 9, nullptr, &FPF);
  assertEqual(Multiply8ByFixedPointFraction88(0, FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction88(-1, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(-2, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(-3, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(-4, FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction88(-5, FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction88(-6, FPF), -4);
  assertEqual(Multiply8ByFixedPointFraction88(-7, FPF), -4);
  assertEqual(Multiply8ByFixedPointFraction88(-8, FPF), -5);
  assertEqual(Multiply8ByFixedPointFraction88(-9, FPF), -5);

  assertEqual(Multiply8ByFixedPointFraction88(-10, FPF), -6);
  assertEqual(Multiply8ByFixedPointFraction88(-100, FPF), -56);
}
test(T1130Multiply8ByFixedPointFraction88_5Div9_Pos) {
  int16_t FPF;
  Ratio8ToFixedPointFraction88(5, 9, &FPF, nullptr);
  assertEqual(Multiply8ByFixedPointFraction88(0, FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction88(1, FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction88(2, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(3, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(4, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(5, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(6, FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction88(7, FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction88(8, FPF), 4);
  assertEqual(Multiply8ByFixedPointFraction88(9, FPF), 5);

  assertEqual(Multiply8ByFixedPointFraction88(10, FPF), 5);
  assertEqual(Multiply8ByFixedPointFraction88(100, FPF), 55);
}

test(T1126Multiply8ByFixedPointFraction88_1DivM3_Neg) {
  int16_t FPF;
  Ratio8ToFixedPointFraction88(1, -3, nullptr, &FPF);
  assertEqual(Multiply8ByFixedPointFraction88(0, FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction88(-1, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(-2, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(-3, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(-4, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(-5, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(-6, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(-7, FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction88(-8, FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction88(-9, FPF), 3);

  assertEqual(Multiply8ByFixedPointFraction88(-10, FPF), 4);
  assertEqual(Multiply8ByFixedPointFraction88(-100, FPF), 34);
}
test(T1125Multiply8ByFixedPointFraction88_1DivM3_Pos) {
  int16_t FPF;
  Ratio8ToFixedPointFraction88(1, -3, &FPF, nullptr);
  assertEqual(Multiply8ByFixedPointFraction88(0, FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction88(1, FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction88(2, FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction88(3, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(4, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(5, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(6, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(7, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(8, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(9, FPF), -3);

  assertEqual(Multiply8ByFixedPointFraction88(10, FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction88(100, FPF), -33);
}
test(T1121Multiply8ByFixedPointFraction88_1Div3_Neg) {
  int16_t FPF;
  Ratio8ToFixedPointFraction88(1, 3, nullptr, &FPF);
  assertEqual(Multiply8ByFixedPointFraction88(0, FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction88(-1, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(-2, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(-3, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(-4, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(-5, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(-6, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(-7, FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction88(-8, FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction88(-9, FPF), -3);

  assertEqual(Multiply8ByFixedPointFraction88(-10, FPF), -4);
  assertEqual(Multiply8ByFixedPointFraction88(-100, FPF), -34);
}
test(T1120Multiply8ByFixedPointFraction88_1Div3_Pos) {
  int16_t FPF;
  Ratio8ToFixedPointFraction88(1, 3, &FPF, nullptr);
  assertEqual(Multiply8ByFixedPointFraction88(0, FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction88(1, FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction88(2, FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction88(3, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(4, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(5, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(6, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(7, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(8, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(9, FPF), 3);

  assertEqual(Multiply8ByFixedPointFraction88(10, FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction88(100, FPF), 33);
}

test(T1116Multiply8ByFixedPointFraction88_1DivM4_Neg) {
  int16_t FPF;
  Ratio8ToFixedPointFraction88(1, -4, nullptr, &FPF);
  assertEqual(Multiply8ByFixedPointFraction88(0, FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction88(-1, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(-2, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(-3, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(-4, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(-5, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(-6, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(-7, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(-8, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(-9, FPF), 3);

  assertEqual(Multiply8ByFixedPointFraction88(-10, FPF), 3);
  assertEqual(Multiply8ByFixedPointFraction88(-100, FPF), 25);
}
test(T1115Multiply8ByFixedPointFraction88_1DivM4_Pos) {
  int16_t FPF;
  Ratio8ToFixedPointFraction88(1, -4, &FPF, nullptr);
  assertEqual(Multiply8ByFixedPointFraction88(0, FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction88(1, FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction88(2, FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction88(3, FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction88(4, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(5, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(6, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(7, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(8, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(9, FPF), -2);

  assertEqual(Multiply8ByFixedPointFraction88(10, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(100, FPF), -25);
}
test(T1111Multiply8ByFixedPointFraction88_1Div4_Neg) {
  int16_t FPF;
  Ratio8ToFixedPointFraction88(1, 4, nullptr, &FPF);
  assertEqual(Multiply8ByFixedPointFraction88(0, FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction88(-1, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(-2, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(-3, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(-4, FPF), -1);
  assertEqual(Multiply8ByFixedPointFraction88(-5, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(-6, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(-7, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(-8, FPF), -2);
  assertEqual(Multiply8ByFixedPointFraction88(-9, FPF), -3);

  assertEqual(Multiply8ByFixedPointFraction88(-10, FPF), -3);
  assertEqual(Multiply8ByFixedPointFraction88(-100, FPF), -25);
}
test(T1110Multiply8ByFixedPointFraction88_1Div4_Pos) {
  int16_t FPF;
  Ratio8ToFixedPointFraction88(1, 4, &FPF, nullptr);
  assertEqual(Multiply8ByFixedPointFraction88(0, FPF), 0);

  assertEqual(Multiply8ByFixedPointFraction88(1, FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction88(2, FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction88(3, FPF), 0);
  assertEqual(Multiply8ByFixedPointFraction88(4, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(5, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(6, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(7, FPF), 1);
  assertEqual(Multiply8ByFixedPointFraction88(8, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(9, FPF), 2);

  assertEqual(Multiply8ByFixedPointFraction88(10, FPF), 2);
  assertEqual(Multiply8ByFixedPointFraction88(100, FPF), 25);
}

test(T1100Ratio8ToFixedPointFraction88) {
  int16_t fpfP, fpfN;

  // handling of 0
  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(0, 0, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfN, (int16_t)0 * 0x100 + 0x00);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(0, 8, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfN, (int16_t)0 * 0x100 + 0x00);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(8, 0, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)0 * 0x100 + 0x00);
  assertEqual(fpfN, (int16_t)0 * 0x100 + 0x00);

  // equal ratios
  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(1, 1, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfN, (int16_t)1 * 0x100 + 0x00);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(12, 12, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfN, (int16_t)1 * 0x100 + 0x00);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-2, 2, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-1 * 0x100 + 0x00);
  assertEqual(fpfN, (int16_t)-1 * 0x100 + 0x00);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(3, -3, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-1 * 0x100 + 0x00);
  assertEqual(fpfN, (int16_t)-1 * 0x100 + 0x00);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-4, -4, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)1 * 0x100 + 0x00);
  assertEqual(fpfN, (int16_t)1 * 0x100 + 0x00);

  // exact ratios
  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(8, 2, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)4 * 0x100 + 0x00);
  assertEqual(fpfN, (int16_t)4 * 0x100 + 0x00);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-12, 4, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-3 * 0x100 + 0x00);
  assertEqual(fpfN, (int16_t)-3 * 0x100 + 0x00);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(30, -5, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-6 * 0x100 + 0x00);
  assertEqual(fpfN, (int16_t)-6 * 0x100 + 0x00);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-56, -7, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)8 * 0x100 + 0x00);
  assertEqual(fpfN, (int16_t)8 * 0x100 + 0x00);

  // theoretical exact ratios
  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(1, 3, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)0 * 0x100 + 0x56);
  assertEqual(fpfN, (int16_t)0 * 0x100 + 0x55);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-1, 3, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-1 * 0x100 + 0xAA);
  assertEqual(fpfN, (int16_t)-1 * 0x100 + 0xAB);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(1, -3, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-1 * 0x100 + 0xAA);
  assertEqual(fpfN, (int16_t)-1 * 0x100 + 0xAB);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-1, -3, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)0 * 0x100 + 0x56);
  assertEqual(fpfN, (int16_t)0 * 0x100 + 0x55);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(2, 3, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)0 * 0x100 + 0xAB);
  assertEqual(fpfN, (int16_t)0 * 0x100 + 0xAA);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-2, 3, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-1 * 0x100 + 0x55);
  assertEqual(fpfN, (int16_t)-1 * 0x100 + 0x56);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(2, -3, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-1 * 0x100 + 0x55);
  assertEqual(fpfN, (int16_t)-1 * 0x100 + 0x56);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-2, -3, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)0 * 0x100 + 0xAB);
  assertEqual(fpfN, (int16_t)0 * 0x100 + 0xAA);

  // binary fraction
  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(1, 2, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)0 * 0x100 + 0x80);
  assertEqual(fpfN, (int16_t)0 * 0x100 + 0x80);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-3, 4, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-1 * 0x100 + 0x40);
  assertEqual(fpfN, (int16_t)-1 * 0x100 + 0x40);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(3, -8, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-1 * 0x100 + 0xA0);
  assertEqual(fpfN, (int16_t)-1 * 0x100 + 0xA0);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-3, -16, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)0 * 0x100 + 0x30);
  assertEqual(fpfN, (int16_t)0 * 0x100 + 0x30);

  // binary vulgar fraction
  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(3, 2, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)1 * 0x100 + 0x80);
  assertEqual(fpfN, (int16_t)1 * 0x100 + 0x80);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-7, 4, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-2 * 0x100 + 0x40);
  assertEqual(fpfN, (int16_t)-2 * 0x100 + 0x40);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(11, -8, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-2 * 0x100 + 0xA0);
  assertEqual(fpfN, (int16_t)-2 * 0x100 + 0xA0);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-19, -16, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)1 * 0x100 + 0x30);
  assertEqual(fpfN, (int16_t)1 * 0x100 + 0x30);

  // inexact fraction
  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(5, 9, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)0 * 0x100 + 0x8F);
  assertEqual(fpfN, (int16_t)0 * 0x100 + 0x8E);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-5, 9, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-1 * 0x100 + 0x71);
  assertEqual(fpfN, (int16_t)-1 * 0x100 + 0x72);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(5, -9, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-1 * 0x100 + 0x71);
  assertEqual(fpfN, (int16_t)-1 * 0x100 + 0x72);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-5, -9, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)0 * 0x100 + 0x8F);
  assertEqual(fpfN, (int16_t)0 * 0x100 + 0x8E);

  // inexact vulgar fraction
  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(9, 5, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)1 * 0x100 + 0xCD);
  assertEqual(fpfN, (int16_t)1 * 0x100 + 0xCC);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-9, 5, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-2 * 0x100 + 0x33);
  assertEqual(fpfN, (int16_t)-2 * 0x100 + 0x34);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(9, -5, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)-2 * 0x100 + 0x33);
  assertEqual(fpfN, (int16_t)-2 * 0x100 + 0x34);

  fpfP = fpfN = -2468; Ratio8ToFixedPointFraction88(-9, -5, &fpfP, &fpfN);
  assertEqual(fpfP, (int16_t)1 * 0x100 + 0xCD);
  assertEqual(fpfN, (int16_t)1 * 0x100 + 0xCC);
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
