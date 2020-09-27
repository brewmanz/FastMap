//
//    FILE: fastMapInteger16ArithmeticTest.ino
//  AUTHOR: Brewmanz (Bryan White)
// VERSION: 0.1.1
// PURPOSE: Test of FastMapInt(16) helper functions
//    DATE: 2020-09-08
//     URL: https://github.com/RobTillaart/FastMap

//#include <AUnitVerbose.h> // too much for Nano!
#include <AUnit.h>
#include <FastMap.h>

volatile int i, j;
const char* spinner[] = {"\b|", "\b/", "\b-", "\b\\" };

test(T1186Multiply16ByFixedPointFraction32_5DivM9_Neg) {
  FixedPointFraction32_t FPF;
  Ratio16ToFixedPointFraction32(5, -9, nullptr, &FPF);
  FPF.Dump(&Serial); Serial.println();
  assertEqual(FPF.MaxInput, (int)((long)0x7FFF0000 /((long)5 * 0x10000 / 9)/2));
  assertEqual(Multiply16ByFixedPointFraction32(0, &FPF), 0);

  assertEqual(Multiply16ByFixedPointFraction32(-1, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(-2, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(-3, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(-4, &FPF), 3);
  assertEqual(Multiply16ByFixedPointFraction32(-5, &FPF), 3);
  assertEqual(Multiply16ByFixedPointFraction32(-6, &FPF), 4);
  assertEqual(Multiply16ByFixedPointFraction32(-7, &FPF), 4);
  assertEqual(Multiply16ByFixedPointFraction32(-8, &FPF), 5);
  assertEqual(Multiply16ByFixedPointFraction32(-9, &FPF), 5);

  assertEqual(Multiply16ByFixedPointFraction32(-10, &FPF), 6);
  assertEqual(Multiply16ByFixedPointFraction32(-100, &FPF), 56);
  assertEqual(Multiply16ByFixedPointFraction32(-1000, &FPF), 556);

  assertEqual(Multiply16ByFixedPointFraction32(-2000, &FPF), 1112);
  assertEqual(Multiply16ByFixedPointFraction32(-3000, &FPF), 1667);
  assertEqual(Multiply16ByFixedPointFraction32(-4000, &FPF), 2223);
  assertEqual(Multiply16ByFixedPointFraction32(-5000, &FPF), 2778);
  assertEqual(Multiply16ByFixedPointFraction32(-6000, &FPF), 3334);
  assertEqual(Multiply16ByFixedPointFraction32(-7000, &FPF), 3889);
  assertEqual(Multiply16ByFixedPointFraction32(-8000, &FPF), 4445);
  assertEqual(Multiply16ByFixedPointFraction32(-9000, &FPF), 5000);

  long failed = 0;
  Serial.print(F("@"));Serial.print(__LINE__);Serial.print(F(": FPF.MaxInput="));Serial.print(FPF.MaxInput);Serial.println(F("..."));
  for(int32_t ix = 0; ix >= -FPF.MaxInput; --ix){
    if(ix%256 == 0) { Serial.print(spinner[abs((ix/256)%4)]); }

    int16_t expVal = -(((ix * 5L) - 8) / 9);
    int16_t actVal = Multiply16ByFixedPointFraction32(ix, &FPF);
    if(expVal != actVal){
      ++failed;
      if(failed < 20) {
        Serial.print(F("ix="));Serial.print(ix);
        Serial.print(F("\texp="));Serial.print(expVal);
        Serial.print(F("\tact="));Serial.print(actVal);
        Serial.print(F("\tdiff="));Serial.print(actVal - expVal);
        Serial.println();
      }
    }
  }
  Serial.println();
  assertEqual(failed, 0L);
}
test(T1185Multiply16ByFixedPointFraction32_5DivM9_Pos) {
  FixedPointFraction32_t FPF;
  Ratio16ToFixedPointFraction32(5, -9, &FPF, nullptr);
  assertEqual(FPF.MaxInput, (int)((long)0x7FFF0000 /((long)5 * 0x10000 / 9)/2));
  assertEqual(Multiply16ByFixedPointFraction32(0, &FPF), 0);

  assertEqual(Multiply16ByFixedPointFraction32(1, &FPF), 0);
  assertEqual(Multiply16ByFixedPointFraction32(2, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(3, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(4, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(5, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(6, &FPF), -3);
  assertEqual(Multiply16ByFixedPointFraction32(7, &FPF), -3);
  assertEqual(Multiply16ByFixedPointFraction32(8, &FPF), -4);
  assertEqual(Multiply16ByFixedPointFraction32(9, &FPF), -5);

  assertEqual(Multiply16ByFixedPointFraction32(10, &FPF), -5);
  assertEqual(Multiply16ByFixedPointFraction32(100, &FPF), -55);
  assertEqual(Multiply16ByFixedPointFraction32(1000, &FPF), -555);

  assertEqual(Multiply16ByFixedPointFraction32(2000, &FPF), -1111);
  assertEqual(Multiply16ByFixedPointFraction32(3000, &FPF), -1666);
  assertEqual(Multiply16ByFixedPointFraction32(4000, &FPF), -2222);
  assertEqual(Multiply16ByFixedPointFraction32(5000, &FPF), -2777);
  assertEqual(Multiply16ByFixedPointFraction32(6000, &FPF), -3333);
  assertEqual(Multiply16ByFixedPointFraction32(7000, &FPF), -3888);
  assertEqual(Multiply16ByFixedPointFraction32(8000, &FPF), -4444);
  assertEqual(Multiply16ByFixedPointFraction32(9000, &FPF), -5000);

  long failed = 0;
  Serial.print(F("@"));Serial.print(__LINE__);Serial.print(F(": FPF.MaxInput="));Serial.print(FPF.MaxInput);Serial.println(F("..."));
  for(int32_t ix = 0; ix - 1 < FPF.MaxInput; ++ix){
    if(ix%256 == 0) { Serial.print(spinner[abs((ix/256)%4)]); }

    int16_t expVal = -(((ix * 5L) - 0) / 9);
    int16_t actVal = Multiply16ByFixedPointFraction32(ix, &FPF);
    if(expVal != actVal){
      ++failed;
      if(failed < 20) {
        Serial.print(F("ix="));Serial.print(ix);
        Serial.print(F("\texp="));Serial.print(expVal);
        Serial.print(F("\tact="));Serial.print(actVal);
        Serial.print(F("\tdiff="));Serial.print(actVal - expVal);
        Serial.println();
      }
    }
  }
  Serial.println();
  assertEqual(failed, 0L);
}
test(T1181Multiply16ByFixedPointFraction32_5Div9_Neg) {
  FixedPointFraction32_t FPF;
  Ratio16ToFixedPointFraction32(5, 9, nullptr, &FPF, &Serial); Serial.println();
  FPF.Dump(&Serial); Serial.println();
  assertEqual(FPF.MaxInput, (int)((long)0x7FFF0000 /((long)5 * 0x10000 / 9)/2));
  assertEqual(Multiply16ByFixedPointFraction32(0, &FPF), 0);

  assertEqual(Multiply16ByFixedPointFraction32(-1, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(-2, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(-3, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(-4, &FPF), -3);
  assertEqual(Multiply16ByFixedPointFraction32(-5, &FPF), -3);
  assertEqual(Multiply16ByFixedPointFraction32(-6, &FPF), -4);
  assertEqual(Multiply16ByFixedPointFraction32(-7, &FPF), -4);
  assertEqual(Multiply16ByFixedPointFraction32(-8, &FPF), -5);
  assertEqual(Multiply16ByFixedPointFraction32(-9, &FPF), -5);

  assertEqual(Multiply16ByFixedPointFraction32(-10, &FPF), -6);
  assertEqual(Multiply16ByFixedPointFraction32(-100, &FPF), -56);
  assertEqual(Multiply16ByFixedPointFraction32(-1000, &FPF), -556);

  assertEqual(Multiply16ByFixedPointFraction32(-2000, &FPF), -1112);
  assertEqual(Multiply16ByFixedPointFraction32(-3000, &FPF), -1667);
  assertEqual(Multiply16ByFixedPointFraction32(-4000, &FPF), -2223);
  assertEqual(Multiply16ByFixedPointFraction32(-5000, &FPF), -2778);
  assertEqual(Multiply16ByFixedPointFraction32(-6000, &FPF), -3334);
  assertEqual(Multiply16ByFixedPointFraction32(-7000, &FPF), -3889);
  assertEqual(Multiply16ByFixedPointFraction32(-8000, &FPF), -4445);
  assertEqual(Multiply16ByFixedPointFraction32(-9000, &FPF), -5000);

  assertEqual(Multiply16ByFixedPointFraction32(-18720, &FPF), -10400-0);
  assertEqual(Multiply16ByFixedPointFraction32(-18721, &FPF), -10400-1);
  assertEqual(Multiply16ByFixedPointFraction32(-18722, &FPF, &Serial), -10400-2); Serial.println();
  assertEqual(Multiply16ByFixedPointFraction32(-18723, &FPF), -10400-2);
  assertEqual(Multiply16ByFixedPointFraction32(-18724, &FPF), -10400-3);
  assertEqual(Multiply16ByFixedPointFraction32(-18725, &FPF), -10400-3);
  assertEqual(Multiply16ByFixedPointFraction32(-18726, &FPF), -10400-4);
  assertEqual(Multiply16ByFixedPointFraction32(-18727, &FPF), -10400-4);
  assertEqual(Multiply16ByFixedPointFraction32(-18728, &FPF), -10400-5);

  assertEqual(Multiply16ByFixedPointFraction32(-18729, &FPF), -10405-0);
  assertEqual(Multiply16ByFixedPointFraction32(-18730, &FPF), -10405-1);
  assertEqual(Multiply16ByFixedPointFraction32(-18731, &FPF, &Serial), -10405-2); Serial.println(); // fails
  assertEqual(Multiply16ByFixedPointFraction32(-18732, &FPF), -10405-2);
  assertEqual(Multiply16ByFixedPointFraction32(-18733, &FPF), -10405-3);
  assertEqual(Multiply16ByFixedPointFraction32(-18734, &FPF), -10405-3);
  assertEqual(Multiply16ByFixedPointFraction32(-18735, &FPF), -10405-4);
  assertEqual(Multiply16ByFixedPointFraction32(-18736, &FPF), -10405-4);
  assertEqual(Multiply16ByFixedPointFraction32(-18737, &FPF), -10405-5);

  assertEqual(Multiply16ByFixedPointFraction32(-18738, &FPF), -10410-0);
  assertEqual(Multiply16ByFixedPointFraction32(-18739, &FPF), -10410-1);
  assertEqual(Multiply16ByFixedPointFraction32(-18740, &FPF, &Serial), -10410-2); Serial.println(); // fails
  assertEqual(Multiply16ByFixedPointFraction32(-18741, &FPF), -10410-2);
  assertEqual(Multiply16ByFixedPointFraction32(-18742, &FPF), -10410-3);
  assertEqual(Multiply16ByFixedPointFraction32(-18743, &FPF), -10410-3);
  assertEqual(Multiply16ByFixedPointFraction32(-18744, &FPF), -10410-4);
  assertEqual(Multiply16ByFixedPointFraction32(-18745, &FPF), -10410-4);
  assertEqual(Multiply16ByFixedPointFraction32(-18746, &FPF), -10410-5);

  assertEqual(Multiply16ByFixedPointFraction32(-18747, &FPF), -10415-0);
  assertEqual(Multiply16ByFixedPointFraction32(-18748, &FPF), -10415-1);
  assertEqual(Multiply16ByFixedPointFraction32(-18749, &FPF, &Serial), -10415-2); Serial.println(); // fails
  assertEqual(Multiply16ByFixedPointFraction32(-18750, &FPF), -10415-2);
  assertEqual(Multiply16ByFixedPointFraction32(-18751, &FPF), -10415-3);
  assertEqual(Multiply16ByFixedPointFraction32(-18752, &FPF), -10415-3);
  assertEqual(Multiply16ByFixedPointFraction32(-18753, &FPF), -10415-4);
  assertEqual(Multiply16ByFixedPointFraction32(-18754, &FPF), -10415-4);
  assertEqual(Multiply16ByFixedPointFraction32(-18755, &FPF), -10415-5);
 
  long failed = 0;
  Serial.print(F("@"));Serial.print(__LINE__);Serial.print(F(": FPF.MaxInput="));Serial.print(FPF.MaxInput);Serial.println(F("..."));
  for(int32_t ix = 0; ix >= -FPF.MaxInput; --ix){
    if(ix%256 == 0) { Serial.print(spinner[abs((ix/256)%4)]); }

    int16_t expVal = (((ix * 5L) - 8) / 9);
    int16_t actVal = Multiply16ByFixedPointFraction32(ix, &FPF);
    if(expVal != actVal){
      ++failed;
      if(failed < 20) {
        Serial.print(F("ix="));Serial.print(ix);
        Serial.print(F("\texp="));Serial.print(expVal);
        Serial.print(F("\tact="));Serial.print(actVal);
        Serial.print(F("\tdiff="));Serial.print(actVal - expVal);
        Serial.println();
      }
    }
  }
  Serial.println();
  assertEqual(failed, 0L);
}
test(T1180Multiply16ByFixedPointFraction32_5Div9_Pos) {
  FixedPointFraction32_t FPF;
  Ratio16ToFixedPointFraction32(5, 9, &FPF, nullptr);
  assertEqual(FPF.MaxInput, (int)((long)0x7FFF0000 /((long)5 * 0x10000 / 9)/2));
  assertEqual(Multiply16ByFixedPointFraction32(0, &FPF), 0);

  assertEqual(Multiply16ByFixedPointFraction32(1, &FPF), 0);
  assertEqual(Multiply16ByFixedPointFraction32(2, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(3, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(4, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(5, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(6, &FPF), 3);
  assertEqual(Multiply16ByFixedPointFraction32(7, &FPF), 3);
  assertEqual(Multiply16ByFixedPointFraction32(8, &FPF), 4);
  assertEqual(Multiply16ByFixedPointFraction32(9, &FPF), 5);

  assertEqual(Multiply16ByFixedPointFraction32(10, &FPF), 5);
  assertEqual(Multiply16ByFixedPointFraction32(100, &FPF), 55);
  assertEqual(Multiply16ByFixedPointFraction32(1000, &FPF), 555);

  assertEqual(Multiply16ByFixedPointFraction32(2000, &FPF), 1111);
  assertEqual(Multiply16ByFixedPointFraction32(3000, &FPF), 1666);
  assertEqual(Multiply16ByFixedPointFraction32(4000, &FPF), 2222);
  assertEqual(Multiply16ByFixedPointFraction32(5000, &FPF), 2777);
  assertEqual(Multiply16ByFixedPointFraction32(6000, &FPF), 3333);
  assertEqual(Multiply16ByFixedPointFraction32(7000, &FPF), 3888);
  assertEqual(Multiply16ByFixedPointFraction32(8000, &FPF), 4444);
  assertEqual(Multiply16ByFixedPointFraction32(9000, &FPF), 5000);

  long failed = 0;
  Serial.print(F("@"));Serial.print(__LINE__);Serial.print(F(": FPF.MaxInput="));Serial.print(FPF.MaxInput);Serial.println(F("..."));
  for(int32_t ix = 0; ix - 1 < FPF.MaxInput; ++ix){
    if(ix%256 == 0) { Serial.print(spinner[abs((ix/256)%4)]); }

    int16_t expVal = (((ix * 5L) - 0) / 9);
    int16_t actVal = Multiply16ByFixedPointFraction32(ix, &FPF);
    if(expVal != actVal){
      ++failed;
      if(failed < 20) {
        Serial.print(F("ix="));Serial.print(ix);
        Serial.print(F("\texp="));Serial.print(expVal);
        Serial.print(F("\tact="));Serial.print(actVal);
        Serial.print(F("\tdiff="));Serial.print(actVal - expVal);
        Serial.println();
      }
    }
  }
  Serial.println();
  assertEqual(failed, 0L);
}

test(T1176Multiply16ByFixedPointFraction32_1DivM3_Neg) {
  FixedPointFraction32_t FPF;
  Ratio16ToFixedPointFraction32(1, -3, nullptr, &FPF);
  assertEqual(FPF.MaxInput, (int)((long)32767 * 3 / 4));
  assertEqual(Multiply16ByFixedPointFraction32(0, &FPF), 0);

  assertEqual(Multiply16ByFixedPointFraction32(-1, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(-2, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(-3, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(-4, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(-5, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(-6, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(-7, &FPF), 3);
  assertEqual(Multiply16ByFixedPointFraction32(-8, &FPF), 3);
  assertEqual(Multiply16ByFixedPointFraction32(-9, &FPF), 3);

  assertEqual(Multiply16ByFixedPointFraction32(-10, &FPF), 4);
  assertEqual(Multiply16ByFixedPointFraction32(-100, &FPF), 34);
  assertEqual(Multiply16ByFixedPointFraction32(-1000, &FPF), 334);

  assertEqual(Multiply16ByFixedPointFraction32(-2000, &FPF), 667);
  assertEqual(Multiply16ByFixedPointFraction32(-3000, &FPF), 1000);
  assertEqual(Multiply16ByFixedPointFraction32(-4000, &FPF), 1334);
  assertEqual(Multiply16ByFixedPointFraction32(-5000, &FPF), 1667);
  assertEqual(Multiply16ByFixedPointFraction32(-6000, &FPF), 2000);
  assertEqual(Multiply16ByFixedPointFraction32(-7000, &FPF), 2334);
  assertEqual(Multiply16ByFixedPointFraction32(-8000, &FPF), 2667);
  assertEqual(Multiply16ByFixedPointFraction32(-9000, &FPF), 3000);

  long failed = 0;
  Serial.print(F("@"));Serial.print(__LINE__);Serial.print(F(": FPF.MaxInput="));Serial.print(FPF.MaxInput);Serial.println(F("..."));
  for(int32_t ix = 0; ix >= -FPF.MaxInput; --ix){
    if(ix%256 == 0) { Serial.print(spinner[abs((ix/256)%4)]); }

    int16_t expVal = -(((ix * 1L) - 2) / 3);
    int16_t actVal = Multiply16ByFixedPointFraction32(ix, &FPF);
    if(expVal != actVal){
      ++failed;
      if(failed < 20) {
        Serial.print(F("ix="));Serial.print(ix);
        Serial.print(F("\texp="));Serial.print(expVal);
        Serial.print(F("\tact="));Serial.print(actVal);
        Serial.print(F("\tdiff="));Serial.print(actVal - expVal);
        Serial.println();
      }
    }
  }
  Serial.println();
  assertEqual(failed, 0L);
}
test(T1175Multiply16ByFixedPointFraction32_1DivM3_Pos) {
  FixedPointFraction32_t FPF;
  Ratio16ToFixedPointFraction32(1, -3, &FPF, nullptr);
  assertEqual(FPF.MaxInput, (int)((long)32767 * 3 / 4));
  assertEqual(Multiply16ByFixedPointFraction32(0, &FPF), 0);

  assertEqual(Multiply16ByFixedPointFraction32(1, &FPF), 0);
  assertEqual(Multiply16ByFixedPointFraction32(2, &FPF), 0);
  assertEqual(Multiply16ByFixedPointFraction32(3, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(4, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(5, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(6, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(7, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(8, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(9, &FPF), -3);

  assertEqual(Multiply16ByFixedPointFraction32(10, &FPF), -3);
  assertEqual(Multiply16ByFixedPointFraction32(100, &FPF), -33);
  assertEqual(Multiply16ByFixedPointFraction32(1000, &FPF), -333);

  assertEqual(Multiply16ByFixedPointFraction32(2000, &FPF), -666);
  assertEqual(Multiply16ByFixedPointFraction32(3000, &FPF), -1000);
  assertEqual(Multiply16ByFixedPointFraction32(4000, &FPF), -1333);
  assertEqual(Multiply16ByFixedPointFraction32(5000, &FPF), -1666);
  assertEqual(Multiply16ByFixedPointFraction32(6000, &FPF), -2000);
  assertEqual(Multiply16ByFixedPointFraction32(7000, &FPF), -2333);
  assertEqual(Multiply16ByFixedPointFraction32(8000, &FPF), -2666);
  assertEqual(Multiply16ByFixedPointFraction32(9000, &FPF), -3000);

  long failed = 0;
  Serial.print(F("@"));Serial.print(__LINE__);Serial.print(F(": FPF.MaxInput="));Serial.print(FPF.MaxInput);Serial.println(F("..."));
  for(int32_t ix = 0; ix - 1 < FPF.MaxInput; ++ix){
    if(ix%256 == 0) { Serial.print(spinner[abs((ix/256)%4)]); }

    int16_t expVal = -(((ix * 1) - 0) / 3);
    int16_t actVal = Multiply16ByFixedPointFraction32(ix, &FPF);
    if(expVal != actVal){
      ++failed;
      if(failed < 20) {
        Serial.print(F("ix="));Serial.print(ix);
        Serial.print(F("\texp="));Serial.print(expVal);
        Serial.print(F("\tact="));Serial.print(actVal);
        Serial.print(F("\tdiff="));Serial.print(actVal - expVal);
        Serial.println();
      }
    }
  }
  Serial.println();
  assertEqual(failed, 0L);
}
test(T1171Multiply16ByFixedPointFraction32_1Div3_Neg) {
  FixedPointFraction32_t FPF;
  Ratio16ToFixedPointFraction32(1, 3, nullptr, &FPF);
  assertEqual(FPF.MaxInput, (int)((long)32767 * 3 / 4));
  assertEqual(Multiply16ByFixedPointFraction32(0, &FPF), 0);

  assertEqual(Multiply16ByFixedPointFraction32(-1, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(-2, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(-3, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(-4, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(-5, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(-6, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(-7, &FPF), -3);
  assertEqual(Multiply16ByFixedPointFraction32(-8, &FPF), -3);
  assertEqual(Multiply16ByFixedPointFraction32(-9, &FPF), -3);

  assertEqual(Multiply16ByFixedPointFraction32(-10, &FPF), -4);
  assertEqual(Multiply16ByFixedPointFraction32(-100, &FPF), -34);
  assertEqual(Multiply16ByFixedPointFraction32(-1000, &FPF), -334);

  assertEqual(Multiply16ByFixedPointFraction32(-2000, &FPF), -667);
  assertEqual(Multiply16ByFixedPointFraction32(-3000, &FPF), -1000);
  assertEqual(Multiply16ByFixedPointFraction32(-4000, &FPF), -1334);
  assertEqual(Multiply16ByFixedPointFraction32(-5000, &FPF), -1667);
  assertEqual(Multiply16ByFixedPointFraction32(-6000, &FPF), -2000);
  assertEqual(Multiply16ByFixedPointFraction32(-7000, &FPF), -2334);
  assertEqual(Multiply16ByFixedPointFraction32(-8000, &FPF), -2667);
  assertEqual(Multiply16ByFixedPointFraction32(-9000, &FPF), -3000);

  long failed = 0;
  Serial.print(F("@"));Serial.print(__LINE__);Serial.print(F(": FPF.MaxInput="));Serial.print(FPF.MaxInput);Serial.println(F("..."));
  for(int32_t ix = 0; ix >= -FPF.MaxInput; --ix){
    if(ix%256 == 0) { Serial.print(spinner[abs((ix/256)%4)]); }

    int16_t expVal = (((ix * 1L) - 2) / 3);
    int16_t actVal = Multiply16ByFixedPointFraction32(ix, &FPF);
    if(expVal != actVal){
      ++failed;
      if(failed < 20) {
        Serial.print(F("ix="));Serial.print(ix);
        Serial.print(F("\texp="));Serial.print(expVal);
        Serial.print(F("\tact="));Serial.print(actVal);
        Serial.print(F("\tdiff="));Serial.print(actVal - expVal);
        Serial.println();
      }
    }
  }
  Serial.println();
  assertEqual(failed, 0L);
}
test(T1170Multiply16ByFixedPointFraction32_1Div3_Pos) {
  FixedPointFraction32_t FPF;
  Ratio16ToFixedPointFraction32(1, 3, &FPF, nullptr);
  assertEqual(FPF.MaxInput, (int)((long)32767 * 3 / 4));
  assertEqual(Multiply16ByFixedPointFraction32(0, &FPF), 0);

  assertEqual(Multiply16ByFixedPointFraction32(1, &FPF), 0);
  assertEqual(Multiply16ByFixedPointFraction32(2, &FPF), 0);
  assertEqual(Multiply16ByFixedPointFraction32(3, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(4, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(5, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(6, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(7, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(8, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(9, &FPF), 3);

  assertEqual(Multiply16ByFixedPointFraction32(10, &FPF), 3);
  assertEqual(Multiply16ByFixedPointFraction32(100, &FPF), 33);
  assertEqual(Multiply16ByFixedPointFraction32(1000, &FPF), 333);

  assertEqual(Multiply16ByFixedPointFraction32(2000, &FPF), 666);
  assertEqual(Multiply16ByFixedPointFraction32(3000, &FPF), 1000);
  assertEqual(Multiply16ByFixedPointFraction32(4000, &FPF), 1333);
  assertEqual(Multiply16ByFixedPointFraction32(5000, &FPF), 1666);
  assertEqual(Multiply16ByFixedPointFraction32(6000, &FPF), 2000);
  assertEqual(Multiply16ByFixedPointFraction32(7000, &FPF), 2333);
  assertEqual(Multiply16ByFixedPointFraction32(8000, &FPF), 2666);
  assertEqual(Multiply16ByFixedPointFraction32(9000, &FPF), 3000);

  long failed = 0;
  Serial.print(F("@"));Serial.print(__LINE__);Serial.print(F(": FPF.MaxInput="));Serial.print(FPF.MaxInput);Serial.println(F("..."));
  for(int32_t ix = 0; ix - 1 < FPF.MaxInput; ++ix){
    if(ix%256 == 0) { Serial.print(spinner[abs((ix/256)%4)]); }

    int16_t expVal = (((ix * 1) - 0) / 3);
    int16_t actVal = Multiply16ByFixedPointFraction32(ix, &FPF);
    if(expVal != actVal){
      ++failed;
      if(failed < 20) {
        Serial.print(F("ix="));Serial.print(ix);
        Serial.print(F("\texp="));Serial.print(expVal);
        Serial.print(F("\tact="));Serial.print(actVal);
        Serial.print(F("\tdiff="));Serial.print(actVal - expVal);
        Serial.println();
      }
    }
  }
  Serial.println();
  assertEqual(failed, 0L);
}

test(T1166Multiply16ByFixedPointFraction32_1DivM4_Neg) {
  FixedPointFraction32_t FPF;
  Ratio16ToFixedPointFraction32(1, -4, nullptr, &FPF);
  assertEqual(FPF.MaxInput, 32767);
  assertEqual(Multiply16ByFixedPointFraction32(0, &FPF), 0);

  assertEqual(Multiply16ByFixedPointFraction32(-1, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(-2, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(-3, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(-4, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(-5, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(-6, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(-7, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(-8, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(-9, &FPF), 3);

  assertEqual(Multiply16ByFixedPointFraction32(-10, &FPF), 3);
  assertEqual(Multiply16ByFixedPointFraction32(-100, &FPF), 25);
  assertEqual(Multiply16ByFixedPointFraction32(-1000, &FPF), 250);

  assertEqual(Multiply16ByFixedPointFraction32(-2000, &FPF), 500);
  assertEqual(Multiply16ByFixedPointFraction32(-3000, &FPF), 750);
  assertEqual(Multiply16ByFixedPointFraction32(-4000, &FPF), 1000);
  assertEqual(Multiply16ByFixedPointFraction32(-5000, &FPF), 1250);
  assertEqual(Multiply16ByFixedPointFraction32(-6000, &FPF), 1500);
  assertEqual(Multiply16ByFixedPointFraction32(-7000, &FPF), 1750);
  assertEqual(Multiply16ByFixedPointFraction32(-8000, &FPF), 2000);
  assertEqual(Multiply16ByFixedPointFraction32(-9000, &FPF), 2250);

  long failed = 0;
  Serial.print(F("@"));Serial.print(__LINE__);Serial.print(F(": FPF.MaxInput="));Serial.print(FPF.MaxInput);Serial.println(F("..."));
  for(int32_t ix = 0; ix >= -FPF.MaxInput; --ix){
    if(ix%256 == 0) { Serial.print(spinner[abs((ix/256)%4)]); }

    int16_t expVal = -(((ix * 1L) - 3) / 4);
    int16_t actVal = Multiply16ByFixedPointFraction32(ix, &FPF);
    if(expVal != actVal){
      ++failed;
      if(failed < 20) {
        Serial.print(F("ix="));Serial.print(ix);
        Serial.print(F("\texp="));Serial.print(expVal);
        Serial.print(F("\tact="));Serial.print(actVal);
        Serial.print(F("\tdiff="));Serial.print(actVal - expVal);
        Serial.println();
      }
    }
  }
  Serial.println();
  assertEqual(failed, 0L);
}
test(T1165Multiply16ByFixedPointFraction32_1DivM4_Pos) {
  FixedPointFraction32_t FPF;
  Ratio16ToFixedPointFraction32(1, -4, &FPF, nullptr);
  assertEqual(FPF.MaxInput, 32767);
  assertEqual(Multiply16ByFixedPointFraction32(0, &FPF), 0);

  assertEqual(Multiply16ByFixedPointFraction32(1, &FPF), 0);
  assertEqual(Multiply16ByFixedPointFraction32(2, &FPF), 0);
  assertEqual(Multiply16ByFixedPointFraction32(3, &FPF), 0);
  assertEqual(Multiply16ByFixedPointFraction32(4, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(5, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(6, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(7, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(8, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(9, &FPF), -2);

  assertEqual(Multiply16ByFixedPointFraction32(10, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(100, &FPF), -25);
  assertEqual(Multiply16ByFixedPointFraction32(1000, &FPF), -250);

  assertEqual(Multiply16ByFixedPointFraction32(2000, &FPF), -500);
  assertEqual(Multiply16ByFixedPointFraction32(3000, &FPF), -750);
  assertEqual(Multiply16ByFixedPointFraction32(4000, &FPF), -1000);
  assertEqual(Multiply16ByFixedPointFraction32(5000, &FPF), -1250);
  assertEqual(Multiply16ByFixedPointFraction32(6000, &FPF), -1500);
  assertEqual(Multiply16ByFixedPointFraction32(7000, &FPF), -1750);
  assertEqual(Multiply16ByFixedPointFraction32(8000, &FPF), -2000);
  assertEqual(Multiply16ByFixedPointFraction32(9000, &FPF), -2250);

  long failed = 0;
  Serial.print(F("@"));Serial.print(__LINE__);Serial.print(F(": FPF.MaxInput="));Serial.print(FPF.MaxInput);Serial.println(F("..."));
  for(int32_t ix = 0; ix - 1 < FPF.MaxInput; ++ix){
    if(ix%256 == 0) { Serial.print(spinner[abs((ix/256)%4)]); }

    int16_t expVal = -(((ix * 1) - 0) / 4);
    int16_t actVal = Multiply16ByFixedPointFraction32(ix, &FPF);
    if(expVal != actVal){
      ++failed;
      if(failed < 20) {
        Serial.print(F("ix="));Serial.print(ix);
        Serial.print(F("\texp="));Serial.print(expVal);
        Serial.print(F("\tact="));Serial.print(actVal);
        Serial.print(F("\tdiff="));Serial.print(actVal - expVal);
        Serial.println();
      }
    }
  }
  Serial.println();
  assertEqual(failed, 0L);
}
test(T1161Multiply16ByFixedPointFraction32_1Div4_Neg) {
  FixedPointFraction32_t FPF;
  Ratio16ToFixedPointFraction32(1, 4, nullptr, &FPF);
  assertEqual(FPF.MaxInput, 32767);
  assertEqual(Multiply16ByFixedPointFraction32(0, &FPF), 0);

  assertEqual(Multiply16ByFixedPointFraction32(-1, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(-2, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(-3, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(-4, &FPF), -1);
  assertEqual(Multiply16ByFixedPointFraction32(-5, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(-6, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(-7, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(-8, &FPF), -2);
  assertEqual(Multiply16ByFixedPointFraction32(-9, &FPF), -3);

  assertEqual(Multiply16ByFixedPointFraction32(-10, &FPF), -3);
  assertEqual(Multiply16ByFixedPointFraction32(-100, &FPF), -25);
  assertEqual(Multiply16ByFixedPointFraction32(-1000, &FPF), -250);

  assertEqual(Multiply16ByFixedPointFraction32(-2000, &FPF), -500);
  assertEqual(Multiply16ByFixedPointFraction32(-3000, &FPF), -750);
  assertEqual(Multiply16ByFixedPointFraction32(-4000, &FPF), -1000);
  assertEqual(Multiply16ByFixedPointFraction32(-5000, &FPF), -1250);
  assertEqual(Multiply16ByFixedPointFraction32(-6000, &FPF), -1500);
  assertEqual(Multiply16ByFixedPointFraction32(-7000, &FPF), -1750);
  assertEqual(Multiply16ByFixedPointFraction32(-8000, &FPF), -2000);
  assertEqual(Multiply16ByFixedPointFraction32(-9000, &FPF), -2250);

  long failed = 0;
  Serial.print(F("@"));Serial.print(__LINE__);Serial.print(F(": FPF.MaxInput="));Serial.print(FPF.MaxInput);Serial.println(F("..."));
  for(int32_t ix = 0; ix >= -FPF.MaxInput; --ix){
    if(ix%256 == 0) { Serial.print(spinner[abs((ix/256)%4)]); }

    int16_t expVal = (((ix * 1L) - 3) / 4);
    int16_t actVal = Multiply16ByFixedPointFraction32(ix, &FPF);
    if(expVal != actVal){
      ++failed;
      if(failed < 20) {
        Serial.print(F("ix="));Serial.print(ix);
        Serial.print(F("\texp="));Serial.print(expVal);
        Serial.print(F("\tact="));Serial.print(actVal);
        Serial.print(F("\tdiff="));Serial.print(actVal - expVal);
        Serial.println();
      }
    }
  }
  Serial.println();
  assertEqual(failed, 0L);
}
test(T1160Multiply16ByFixedPointFraction32_1Div4_Pos) {
  FixedPointFraction32_t FPF;
  Ratio16ToFixedPointFraction32(1, 4, &FPF, nullptr);
  assertEqual(FPF.MaxInput, 32767);
  assertEqual(Multiply16ByFixedPointFraction32(0, &FPF), 0);

  assertEqual(Multiply16ByFixedPointFraction32(1, &FPF), 0);
  assertEqual(Multiply16ByFixedPointFraction32(2, &FPF), 0);
  assertEqual(Multiply16ByFixedPointFraction32(3, &FPF), 0);
  assertEqual(Multiply16ByFixedPointFraction32(4, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(5, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(6, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(7, &FPF), 1);
  assertEqual(Multiply16ByFixedPointFraction32(8, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(9, &FPF), 2);

  assertEqual(Multiply16ByFixedPointFraction32(10, &FPF), 2);
  assertEqual(Multiply16ByFixedPointFraction32(100, &FPF), 25);
  assertEqual(Multiply16ByFixedPointFraction32(1000, &FPF), 250);

  assertEqual(Multiply16ByFixedPointFraction32(2000, &FPF), 500);
  assertEqual(Multiply16ByFixedPointFraction32(3000, &FPF), 750);
  assertEqual(Multiply16ByFixedPointFraction32(4000, &FPF), 1000);
  assertEqual(Multiply16ByFixedPointFraction32(5000, &FPF), 1250);
  assertEqual(Multiply16ByFixedPointFraction32(6000, &FPF), 1500);
  assertEqual(Multiply16ByFixedPointFraction32(7000, &FPF), 1750);
  assertEqual(Multiply16ByFixedPointFraction32(8000, &FPF), 2000);
  assertEqual(Multiply16ByFixedPointFraction32(9000, &FPF), 2250);

  long failed = 0;
  Serial.print(F("@"));Serial.print(__LINE__);Serial.print(F(": FPF.MaxInput="));Serial.print(FPF.MaxInput);Serial.println(F("..."));
  for(int32_t ix = 0; ix - 1 < FPF.MaxInput; ++ix){
    if(ix%256 == 0) { Serial.print(spinner[abs((ix/256)%4)]); }

    int16_t expVal = (((ix * 1L) - 0) / 4);
    int16_t actVal = Multiply16ByFixedPointFraction32(ix, &FPF);
    if(expVal != actVal){
      ++failed;
      if(failed < 20) {
        Serial.print(F("ix="));Serial.print(ix);
        Serial.print(F("\texp="));Serial.print(expVal);
        Serial.print(F("\tact="));Serial.print(actVal);
        Serial.print(F("\tdiff="));Serial.print(actVal - expVal);
        Serial.println();
      }
    }
  }
  Serial.println();
  assertEqual(failed, 0L);
}

void setup() {
  delay(1000); // wait for stability on some boards to prevent garbage Serial
  Serial.begin(115200); // The baudrate of Serial monitor is set
  while(!Serial); // for the Arduino Leonardo/Micro only
  Serial.println(F(__DATE__ " @ " __TIME__));
  Serial.println(F(__FILE__));

  int toSecs = 256;
  Serial.print(F("Setting aunit::TestRunner::setTimeout to ")); Serial.println(toSecs);
  aunit::TestRunner::setTimeout(toSecs); // 0 = infinite
}

void loop() {
  aunit::TestRunner::run();
}
