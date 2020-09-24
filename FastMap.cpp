//
//    FILE: FastMap.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: class with fast map function - library for Arduino
//     URL: https://github.com/RobTillaart/FastMap
//
// HISTORY:
// 0.X.X  2020-09-XX added FastMapInt, FastMapLong by Bryan White (Brewmanz)
// 0.3.1  2020-08-31 updated documentation
// 0.3.0  2020-07-04 added fastMapDouble + test sketch.
// 0.2.1  2020-06-10 fix library.json; rename license
// 0.2.0  2020-03-21 #pragma once; readme.md; license.md
//
// 0.1.8  2017-07-27 revert double to float (issue 33)
// 0.1.7  2017-04-28 cleaned up, get examples working again
// 0.1.06 2015-03-08 replaced float by double (support ARM)
// 0.1.05 2014-11-02 stripped of bit mask experimental code
// 0.1.04 add back() - the inverse map
//        tested with bit mask for constrain code (Perfomance was killed)
// 0.1.03 proper name
// 0.1.02 sqeezed the code (first public version)
// 0.1.01 refactor
// 0.1.00 initial version
//

#include "FastMap.h"

FastMap::FastMap()
{
    init(0, 1, 0, 1);
}

void FastMap::init(float in_min, float in_max, float out_min, float out_max)
{
    _in_min = in_min;
    _in_max = in_max;
    _out_min = out_min;
    _out_max = out_max;

    _factor = (out_max - out_min)/(in_max - in_min);
    _base = out_min - in_min * _factor;

    _backfactor = 1/_factor;
    _backbase = in_min - out_min * _backfactor;
}

float FastMap::constrainedMap(float value)
{
    if (value <= _in_min) return _out_min;
    if (value >= _in_max) return _out_max;
    return this->map(value);
}

float FastMap::lowerConstrainedMap(float value)
{
    if (value <= _in_min) return _out_min;
    return this->map(value);
}

float FastMap::upperConstrainedMap(float value)
{
    if (value >= _in_max) return _out_max;
    return this->map(value);
}

FastMapDouble::FastMapDouble()
{
    init(0, 1, 0, 1);
}

void FastMapDouble::init(double in_min, double in_max, double out_min, double out_max)
{
    _in_min = in_min;
    _in_max = in_max;
    _out_min = out_min;
    _out_max = out_max;

    _factor = (out_max - out_min)/(in_max - in_min);
    _base = out_min - in_min * _factor;

    _backfactor = 1/_factor;
    _backbase = in_min - out_min * _backfactor;
}

double FastMapDouble::constrainedMap(double value)
{
    if (value <= _in_min) return _out_min;
    if (value >= _in_max) return _out_max;
    return this->map(value);
}

double FastMapDouble::lowerConstrainedMap(double value)
{
    if (value <= _in_min) return _out_min;
    return this->map(value);
}

double FastMapDouble::upperConstrainedMap(double value)
{
    if (value >= _in_max) return _out_max;
    return this->map(value);
}

void FixedPointFraction16_t::Dump(Print* pPrint){
  pPrint->print(F("FixedPointFraction16_t Dump:<"));
  pPrint->print(F("F:"));pPrint->print(TheFraction, DEC);pPrint->print(F("=0x"));pPrint->print(TheFraction, HEX);
  pPrint->print(F(", B:"));pPrint->print(BitsToShift, DEC);
  pPrint->print(F(", Mx:"));pPrint->print(MaxInput, DEC);
  pPrint->print(F(">"));
}
void FixedPointFraction32_t::Dump(Print* pPrint){
  pPrint->print(F("FixedPointFraction32_t Dump:<"));
  pPrint->print(F("F:"));pPrint->print(TheFraction, DEC);pPrint->print(F("=0x"));pPrint->print(TheFraction, HEX);
  pPrint->print(F(", B:"));pPrint->print(BitsToShift, DEC);
  pPrint->print(F(", Mx:"));pPrint->print(MaxInput, DEC);
  pPrint->print(F(">"));
}
void FixedPointFraction64_t::Dump(Print* pPrint){
  pPrint->print(F("FixedPointFraction64_t Dump:<"));
  pPrint->print(F("F:=0x"));pPrint->print((int32_t)(TheFraction / 0x1000000000000), HEX);pPrint->print(F(" "));pPrint->print((int32_t)(TheFraction % 0x1000000000000), HEX);
  pPrint->print(F(", B:"));pPrint->print(BitsToShift, DEC);
  pPrint->print(F(", Mx:"));pPrint->print(MaxInput, DEC);
  pPrint->print(F(">"));
}

FastMapInt::FastMapInt()
{
    init(0, 1, 0, 1);
}

void FastMapInt::init(const int in_min_incl, const int in_max_excl, const int out_min_incl, const int out_max_excl)
{
  _in_min_incl = in_min_incl;
  _in_max_excl = in_max_excl;
  _out_min_incl = out_min_incl;
  _out_max_excl = out_max_excl;

  _d_in = in_max_excl - in_min_incl;
  _d_out = out_max_excl - out_min_incl;

  // can we simplify maths? eg in/out of 1024/256 can be refactored as 4/1
  _d_GCF = CalcGCD(_d_in, _d_out);
  if(_d_GCF > 1) {
    _d_in /= _d_GCF;
    _d_out /= _d_GCF;
  }

  _d_in_less1 = _d_in - (_d_in > 0 ? 1 : -1);
  _d_out_less1 = _d_out - (_d_out > 0 ? 1 : -1);

  double theRatio = 1.0 + (1.0 * abs(_d_out) ) / abs(_d_in);

  double factor8 = (__INT8_MAX__) / theRatio;
  if(factor8 > __INT8_MAX__) { factor8 = __INT8_MAX__; }
  if(max(abs(_d_in), abs(_d_out)) > __INT8_MAX__) { factor8 = 0; } // kill factor if numbers too big
  _d_FactorToMax8 = factor8 > __INT_MAX__? __INT_MAX__ : factor8;

  double factor16 = (__INT16_MAX__) / theRatio;
  if(factor16 > __INT16_MAX__) { factor16 = __INT16_MAX__; }
  if(max(abs(_d_in), abs(_d_out)) > __INT16_MAX__) { factor16 = 0; } // kill factor if numbers too big
  _d_FactorToMax16 = factor16 > __INT_MAX__? __INT_MAX__ : factor16;

  double factor32 = (__INT32_MAX__) / theRatio;
  if(factor32 > __INT32_MAX__) { factor32 = __INT32_MAX__; }
  if(max(abs(_d_in), abs(_d_out)) > __INT32_MAX__) { factor32 = 0; } // kill factor if numbers too big
  _d_FactorToMax32 = factor32 > __INT_MAX__? __INT_MAX__ : factor32;

  // some of the following may overflow; no-one cares
  Ratio8ToFixedPointFraction16(_d_out, _d_in, &_fixedPoint16Fraction_Pos, &_fixedPoint16Fraction_Neg);
  Ratio16ToFixedPointFraction32(_d_out, _d_in, &_fixedPoint32Fraction_Pos, &_fixedPoint32Fraction_Neg);
  Ratio32ToFixedPointFraction64(_d_out, _d_in, &_fixedPoint64Fraction_Pos, &_fixedPoint64Fraction_Neg);
}

int FastMapInt::constrainedMap(int value)
{
    if (value <= _in_min_incl) return _out_min_incl;
    if (value >= _in_max_excl) return _out_max_excl - 1;
    return this->map(value);
}

int FastMapInt::lowerConstrainedMap(int value)
{
    if (value <= _in_min_incl) return _out_min_incl;
    return this->map(value);
}

int FastMapInt::upperConstrainedMap(int value)
{
    if (value >= _in_max_excl) return _out_max_excl - 1;
    return this->map(value);
}

void FastMapInt::Dump(Print* pPrint)
{
  pPrint->println(F("FastMapInt Dump:<"));

  pPrint->print(F("_in_min_incl:"));pPrint->print(_in_min_incl);
  pPrint->print(F(", _in_max_excl:"));pPrint->print(_in_max_excl);
  pPrint->print(F(", _out_min_incl:"));pPrint->print(_out_min_incl);
  pPrint->print(F(", _out_max_excl:"));pPrint->print(_out_max_excl);
  pPrint->println();

  pPrint->print(F("_d_in:"));pPrint->print(_d_in);
  pPrint->print(F(", _d_out:"));pPrint->print(_d_out);
  pPrint->print(F(", _d_GCF:"));pPrint->print(_d_GCF);
  pPrint->print(F(", _d_in_less1:"));pPrint->print(_d_in_less1);
  pPrint->print(F(", _d_out_less1:"));pPrint->print(_d_out_less1);
  pPrint->println();

  pPrint->print(F("_d_FactorToMax8:"));pPrint->print(_d_FactorToMax8);
  pPrint->print(F(", _d_FactorToMax16:"));pPrint->print(_d_FactorToMax16);
  pPrint->print(F(", _d_FactorToMax32:"));pPrint->print(_d_FactorToMax32);
  pPrint->println();

  pPrint->print(F("[2]_fixedPoint16Fraction_Pos:"));_fixedPoint16Fraction_Pos.Dump(pPrint);
  pPrint->print(F(", Neg:"));_fixedPoint16Fraction_Neg.Dump(pPrint);
  pPrint->println();

  pPrint->print(F("[4]_fixedPoint32Fraction_Pos:"));_fixedPoint32Fraction_Pos.Dump(pPrint);
  pPrint->print(F(", Neg:"));_fixedPoint32Fraction_Neg.Dump(pPrint);
  pPrint->println();

  pPrint->print(F("[8]_fixedPoint64Fraction_Pos: 0x"));_fixedPoint64Fraction_Pos.Dump(pPrint);
  pPrint->print(F(", Neg: 0x"));_fixedPoint64Fraction_Neg.Dump(pPrint);
  pPrint->println();
  pPrint->println(F(">"));
}

FastMapLong::FastMapLong()
{
    init(0, 1, 0, 1);
}

void FastMapLong::init(const long in_min_incl, const long in_max_excl, const long out_min_incl, const long out_max_excl)
{
  _in_min_incl = in_min_incl;
  _in_max_excl = in_max_excl;
  _out_min_incl = out_min_incl;
  _out_max_excl = out_max_excl;

  _d_in = in_max_excl - in_min_incl;
  _d_out = out_max_excl - out_min_incl;

  // can we simplify maths? eg in/out of 1024/256 can be refactored as 4/1
  _d_GCF = CalcGCD(_d_in, _d_out);
  if(_d_GCF > 1) {
    _d_in /= _d_GCF;
    _d_out /= _d_GCF;
  }

  _d_in_less1 = _d_in - (_d_in > 0 ? 1 : -1);
  _d_out_less1 = _d_out - (_d_out > 0 ? 1 : -1);

  double theRatio = 1.0 + (1.0 * abs(_d_out) ) / abs(_d_in);

  double factor8 = (__INT8_MAX__) / theRatio;
  if(factor8 > __INT8_MAX__) { factor8 = __INT8_MAX__; }
  if(max(abs(_d_in), abs(_d_out)) > __INT8_MAX__) { factor8 = 0; } // kill factor if numbers too big
  _d_FactorToMax8 = factor8 > __INT_MAX__? __INT_MAX__ : factor8;

  double factor16 = (__INT16_MAX__) / theRatio;
  if(factor16 > __INT16_MAX__) { factor16 = __INT16_MAX__; }
  if(max(abs(_d_in), abs(_d_out)) > __INT16_MAX__) { factor16 = 0; } // kill factor if numbers too big
  _d_FactorToMax16 = factor16 > __INT_MAX__? __INT_MAX__ : factor16;

  double factor32 = (__INT32_MAX__) / theRatio;
  if(factor32 > __INT32_MAX__) { factor32 = __INT32_MAX__; }
  if(max(abs(_d_in), abs(_d_out)) > __INT32_MAX__) { factor32 = 0; } // kill factor if numbers too big
  _d_FactorToMax32 = factor32 > __INT_MAX__? __INT_MAX__ : factor32;

  // some of the following may overflow; no-one cares
  Ratio8ToFixedPointFraction16(_d_out, _d_in, &_fixedPoint16Fraction_Pos, &_fixedPoint16Fraction_Neg);
  Ratio16ToFixedPointFraction32(_d_out, _d_in, &_fixedPoint32Fraction_Pos, &_fixedPoint32Fraction_Neg);
  Ratio32ToFixedPointFraction64(_d_out, _d_in, &_fixedPoint64Fraction_Pos, &_fixedPoint64Fraction_Neg);
}

long FastMapLong::constrainedMap(long value)
{
    if (value <= _in_min_incl) return _out_min_incl;
    if (value >= _in_max_excl) return _out_max_excl - 1;
    return this->map(value);
}

long FastMapLong::lowerConstrainedMap(long value)
{
    if (value <= _in_min_incl) return _out_min_incl;
    return this->map(value);
}

long FastMapLong::upperConstrainedMap(long value)
{
    if (value >= _in_max_excl) return _out_max_excl - 1;
    return this->map(value);
}

void FastMapLong::Dump(Print* pPrint)
{
  pPrint->println(F("FastMapLong Dump:"));

  pPrint->print(F("_in_min_incl:"));pPrint->print(_in_min_incl);
  pPrint->print(F(", _in_max_excl:"));pPrint->print(_in_max_excl);
  pPrint->print(F(", _out_min_incl:"));pPrint->print(_out_min_incl);
  pPrint->print(F(", _out_max_excl:"));pPrint->print(_out_max_excl);
  pPrint->println();

  pPrint->print(F("_d_in:"));pPrint->print(_d_in);
  pPrint->print(F(", _d_out:"));pPrint->print(_d_out);
  pPrint->print(F(", _d_GCF:"));pPrint->print(_d_GCF);
  pPrint->print(F(", _d_in_less1:"));pPrint->print(_d_in_less1);
  pPrint->print(F(", _d_out_less1:"));pPrint->print(_d_out_less1);
  pPrint->println();

  pPrint->print(F("_d_FactorToMax8:"));pPrint->print(_d_FactorToMax8);
  pPrint->print(F(", _d_FactorToMax16:"));pPrint->print(_d_FactorToMax16);
  pPrint->print(F(", _d_FactorToMax32:"));pPrint->print(_d_FactorToMax32);
  pPrint->println();

  pPrint->print(F("[2]_fixedPoint16Fraction_Pos:"));_fixedPoint16Fraction_Pos.Dump(pPrint);
  pPrint->print(F(", Neg:"));_fixedPoint16Fraction_Neg.Dump(pPrint);
  pPrint->println();

  pPrint->print(F("[4]_fixedPoint32Fraction_Pos:"));_fixedPoint32Fraction_Pos.Dump(pPrint);
  pPrint->print(F(", Neg:"));_fixedPoint32Fraction_Neg.Dump(pPrint);
  pPrint->println();

  pPrint->print(F("[8]_fixedPoint64Fraction_Pos: 0x"));_fixedPoint64Fraction_Pos.Dump(pPrint);
  pPrint->print(F(", Neg: 0x"));_fixedPoint64Fraction_Neg.Dump(pPrint);
  pPrint->println();
}

int8_t Multiply8ByFixedPointFraction16(int8_t factor, const FixedPointFraction16_t* pFixedPointFraction, Print* pPrintDebug){
  if(factor == 0 || pFixedPointFraction == nullptr || pFixedPointFraction->TheFraction == 0) { return 0; }
  int16_t theFraction = pFixedPointFraction->TheFraction;
  if(pPrintDebug) { pPrintDebug->print(F(",f=")); pPrintDebug->print(factor); pPrintDebug->print(F(",tF=")); pPrintDebug->print(theFraction, DEC); pPrintDebug->print(F("=X")); pPrintDebug->print(theFraction, HEX); pPrintDebug->print(F(",BS=")); pPrintDebug->print(pFixedPointFraction->BitsToShift); }
  bool bFPFNeg = theFraction < 0;
  if(bFPFNeg){
    theFraction = -theFraction;
    if(pPrintDebug) { pPrintDebug->print(F(",-ve")); }
  }
  int16_t res = factor;
  res *= theFraction;
  if(pPrintDebug) { pPrintDebug->print(F(",preBS=")); pPrintDebug->print(res); }
  res >>= pFixedPointFraction->BitsToShift;
  if(pPrintDebug) { pPrintDebug->print(F(",res=")); pPrintDebug->print(res); }
  return bFPFNeg ? -res : res;
}
int16_t Multiply16ByFixedPointFraction32(int16_t factor, const FixedPointFraction32_t* pFixedPointFraction, Print* pPrintDebug){
  if(factor == 0 || pFixedPointFraction == nullptr || pFixedPointFraction->TheFraction == 0) { return 0; }
  int32_t theFraction = pFixedPointFraction->TheFraction;
  bool bFPFNeg = theFraction < 0;
  if(bFPFNeg){
    theFraction = -theFraction;
  }
  int32_t res = factor;
  res *= theFraction;
  res >>= pFixedPointFraction->BitsToShift;
  return bFPFNeg ? -res : res;
}
int32_t Multiply32ByFixedPointFraction64(int32_t factor, const FixedPointFraction64_t* pFixedPointFraction, Print* pPrintDebug){
  if(factor == 0 || pFixedPointFraction == nullptr || pFixedPointFraction->TheFraction == 0) { return 0; }
  int64_t theFraction = pFixedPointFraction->TheFraction;
  bool bFPFNeg = theFraction < 0;
  if(bFPFNeg){
    theFraction = -theFraction;
  }
  int64_t res = factor;
  res *= theFraction;
  res >>= pFixedPointFraction->BitsToShift;
  return bFPFNeg ? -res : res;
}

int64_t Multiply64ByFixedPointFraction64(int64_t factor, const FixedPointFraction64_t* pFixedPointFraction, Print* pPrintDebug){
  if(factor == 0 || pFixedPointFraction == nullptr || pFixedPointFraction->TheFraction == 0) { return 0; }
  int64_t theFraction = pFixedPointFraction->TheFraction;
  bool bFPFNeg = theFraction < 0;
  if(bFPFNeg){
    theFraction = -theFraction;
  }
  int64_t res = factor;
  res *= theFraction;
  res >>= pFixedPointFraction->BitsToShift;
  return bFPFNeg ? -res : res;
}

// we need two fractions, depending on whether we're multiplying a +ve or -ve factor later
void Ratio8ToFixedPointFraction16(int8_t numerator, int8_t denominator, FixedPointFraction16_t* poutFixedPointFraction_Pos, FixedPointFraction16_t* poutFixedPointFraction_Neg, Print* pPrintDebug){
  if(pPrintDebug) { pPrintDebug->print(F(",N="));pPrintDebug->print(numerator);pPrintDebug->print(F(",D="));pPrintDebug->print(denominator);}
  FixedPointFraction16_t resP {0, 0, 0}, resN {0, 0, 0};
  int16_t maxInput = 0;
  if(numerator != 0 && denominator != 0) {
    // look ahead to find bit shift needed
    int16_t lookAhead = numerator;
    resP.BitsToShift = 8;
    lookAhead <<= 8;
    lookAhead /= denominator;

    // work out largest input value
    maxInput = abs(0x7F00 / lookAhead);
    if(pPrintDebug) { pPrintDebug->print(F(",lA=x"));pPrintDebug->print(lookAhead, HEX);pPrintDebug->print(F(", mI="));pPrintDebug->print(maxInput);}

    // ensure TheFraction is between 0x100 & 0x1FF incl
    while(abs(lookAhead) < (int)0x100) {
      if(pPrintDebug) { pPrintDebug->print(F(",SL")); }
      lookAhead <<= 1;
      maxInput >>= 1;
      ++resP.BitsToShift;
    }
    while(abs(lookAhead) > (int)0x1FF) {
      if(pPrintDebug) { pPrintDebug->print(F(",SR")); }
      lookAhead >>= 1;
      --resP.BitsToShift;
    }

    // now do real calculation
    resP.TheFraction = numerator;
    resP.TheFraction <<= resP.BitsToShift;
    // round slightly to help truncated fraction for +ve numbers
    int8_t rounding = abs(denominator) - 1;

    if(maxInput > 127) { Serial.print(F(" !! maxInput>127;=")); Serial.print(maxInput, DEC); }
    resP.MaxInput = maxInput > 127 ? 127 : maxInput;
    resN = resP;
    resP.TheFraction += resP.TheFraction > 0 ? rounding : -rounding;
    resP.TheFraction /= denominator;
    resN.TheFraction /= denominator; // always need to round down for -ve numbers
  }
  if(pPrintDebug) { pPrintDebug->print(F(",+="));resP.Dump(pPrintDebug);pPrintDebug->print(F(",-="));resN.Dump(pPrintDebug); }

  if(poutFixedPointFraction_Pos) { *poutFixedPointFraction_Pos = resP; }
  if(poutFixedPointFraction_Neg) { *poutFixedPointFraction_Neg = resN; }
}

// we need two fractions, depending on whether we're multiplying a +ve or -ve factor later
void Ratio16ToFixedPointFraction32(int16_t numerator, int16_t denominator, FixedPointFraction32_t* poutFixedPointFraction_Pos, FixedPointFraction32_t* poutFixedPointFraction_Neg, Print* pPrintDebug){
  if(pPrintDebug) { pPrintDebug->print(F(",N="));pPrintDebug->print(numerator);pPrintDebug->print(F(",D="));pPrintDebug->print(denominator);}
  FixedPointFraction32_t resP {0, 0}, resN {0, 0};
  if(numerator != 0 && denominator != 0) {
    resP.TheFraction = numerator;
    resP.BitsToShift = 16;
    resP.TheFraction <<= resP.BitsToShift;
    // round slightly to help truncated fraction for +ve numbers
    int16_t rounding = abs(denominator) - 1;

    // wait! Can we squeeze extra bits of precision?
    while(abs(resP.TheFraction) <= 0xFFFF) {
      if(pPrintDebug) { pPrintDebug->print(F(",Shift")); }
      resP.TheFraction <<= 1;
      ++resP.BitsToShift;
    }

    resN = resP;
    resP.TheFraction += resP.TheFraction > 0 ? rounding : -rounding;
    resP.TheFraction /= denominator;
    resN.TheFraction /= denominator; // always need to round down for -ve numbers
  }
  if(pPrintDebug) { pPrintDebug->print(F(",+="));resP.Dump(pPrintDebug);pPrintDebug->print(F(",-="));resN.Dump(pPrintDebug); }

  if(poutFixedPointFraction_Pos) { *poutFixedPointFraction_Pos = resP; }
  if(poutFixedPointFraction_Neg) { *poutFixedPointFraction_Neg = resN; }
}

// we need two fractions, depending on whether we're multiplying a +ve or -ve factor later
void Ratio32ToFixedPointFraction64(int32_t numerator, int32_t denominator, FixedPointFraction64_t* poutFixedPointFraction_Pos, FixedPointFraction64_t* poutFixedPointFraction_Neg, Print* pPrintDebug){
  if(pPrintDebug) { pPrintDebug->print(F(",N="));pPrintDebug->print(numerator);pPrintDebug->print(F(",D="));pPrintDebug->print(denominator);}
  FixedPointFraction64_t resP {0, 0}, resN {0, 0};
  if(numerator != 0 && denominator != 0) {
    resP.TheFraction = numerator;
    resP.BitsToShift = 32;
    resP.TheFraction <<= resP.BitsToShift;
    // round slightly to help truncated fraction for +ve numbers
    int32_t rounding = abs(denominator) - 1;

    // wait! Can we squeeze extra bits of precision?
    while(abs(resP.TheFraction) <= 0xFFFFFFFF) {
      if(pPrintDebug) { pPrintDebug->print(F(",Shift")); }
      resP.TheFraction <<= 1;
      ++resP.BitsToShift;
    }

    resN = resP;
    resP.TheFraction += resP.TheFraction > 0 ? rounding : -rounding;
    resP.TheFraction /= denominator;
    resN.TheFraction /= denominator; // always need to round down for -ve numbers
  }
  if(pPrintDebug) { pPrintDebug->print(F(",+="));resP.Dump(pPrintDebug);pPrintDebug->print(F(",-="));resN.Dump(pPrintDebug); }

  if(poutFixedPointFraction_Pos) { *poutFixedPointFraction_Pos = resP; }
  if(poutFixedPointFraction_Neg) { *poutFixedPointFraction_Neg = resN; }
}

// we need two fractions, depending on whether we're multiplying a +ve or -ve factor later
// COMPROMISE s/b Ratio64ToFixedPointFraction128
void Ratio64ToFixedPointFraction64(int64_t numerator, int64_t denominator, FixedPointFraction64_t* poutFixedPointFraction_Pos, FixedPointFraction64_t* poutFixedPointFraction_Neg, Print* pPrintDebug){
  if(pPrintDebug) { pPrintDebug->print(F(",N32="));pPrintDebug->print((int32_t)numerator);pPrintDebug->print(F(",D32="));pPrintDebug->print((int32_t)denominator);}
  FixedPointFraction64_t resP {0, 0}, resN {0, 0};
  if(numerator != 0 && denominator != 0) {
    resP.TheFraction = numerator;
    resP.BitsToShift = 32;
    resP.TheFraction <<= resP.BitsToShift;
    // round slightly to help truncated fraction for +ve numbers
    int32_t rounding = abs(denominator) - 1;

    // wait! Can we squeeze extra bits of precision?
    while(abs(resP.TheFraction) <= 0xFFFFFFFF) {
      if(pPrintDebug) { pPrintDebug->print(F(",Shift")); }
      resP.TheFraction <<= 1;
      ++resP.BitsToShift;
    }

    resN = resP;
    resP.TheFraction += resP.TheFraction > 0 ? rounding : -rounding;
    resP.TheFraction /= denominator;
    resN.TheFraction /= denominator; // always need to round down for -ve numbers
  }
  if(pPrintDebug) { pPrintDebug->print(F(",+="));resP.Dump(pPrintDebug);pPrintDebug->print(F(",-="));resN.Dump(pPrintDebug); }

  if(poutFixedPointFraction_Pos) { *poutFixedPointFraction_Pos = resP; }
  if(poutFixedPointFraction_Neg) { *poutFixedPointFraction_Neg = resN; }
}

long CalcGCD(long A, long B){
  if(A == 0 || B == 0) { return 0; }
  long res;
  while(B != 0){
    res = abs(B);
    B = A % B;
    A = abs(res);
  }
  return res;
}

// END OF FILE
