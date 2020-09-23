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
  pPrint->print(F(", B:"));pPrint->println(BitsToShift, DEC);
  pPrint->print(F(">"));
  //pPrint->print(F("[8]_fixedPoint64Fraction_Pos: 0x"));pPrint->print((int32_t)(_fixedPoint64Fraction_Pos / 0x1000000000000), HEX);pPrint->print(F(" "));pPrint->print((int32_t)(_fixedPoint64Fraction_Pos % 0x1000000000000), HEX);
  //pPrint->print(F(", Neg: 0x"));pPrint->print((int32_t)(_fixedPoint64Fraction_Neg / 0x1000000000000), HEX);pPrint->print(F(" "));pPrint->print((int32_t)(_fixedPoint64Fraction_Neg % 0x1000000000000), HEX);
}
void FixedPointFraction32_t::Dump(Print* pPrint){
  pPrint->print(F("FixedPointFraction32_t Dump:<"));
  pPrint->print(F("F:"));pPrint->print(TheFraction, DEC);pPrint->print(F("=0x"));pPrint->print(TheFraction, HEX);
  pPrint->print(F(", B:"));pPrint->println(BitsToShift, DEC);
  pPrint->print(F(">"));
  //pPrint->print(F("[8]_fixedPoint64Fraction_Pos: 0x"));pPrint->print((int32_t)(_fixedPoint64Fraction_Pos / 0x1000000000000), HEX);pPrint->print(F(" "));pPrint->print((int32_t)(_fixedPoint64Fraction_Pos % 0x1000000000000), HEX);
  //pPrint->print(F(", Neg: 0x"));pPrint->print((int32_t)(_fixedPoint64Fraction_Neg / 0x1000000000000), HEX);pPrint->print(F(" "));pPrint->print((int32_t)(_fixedPoint64Fraction_Neg % 0x1000000000000), HEX);
}
void FixedPointFraction64_t::Dump(Print* pPrint){
  pPrint->print(F("FixedPointFraction64_t Dump:<"));
  pPrint->print(F("F:=0x"));pPrint->print((int32_t)(TheFraction / 0x1000000000000), HEX);pPrint->print(F(" "));pPrint->print((int32_t)(TheFraction % 0x1000000000000), HEX);
  pPrint->print(F(", B:"));pPrint->println(BitsToShift, DEC);
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

#if 0 // DEBUG help
Serial.print("_d_in=");Serial.print(_d_in, DEC);Serial.print(", _d_out=");Serial.print(_d_out, DEC);Serial.print(", _d_GCF=");Serial.println(_d_GCF, DEC);
Serial.print("f8=");Serial.print(factor8, 6);Serial.print(", f16=");Serial.print(factor16, 6);Serial.print(", f32=");Serial.println(factor32, 6);
Serial.print("__INT8_MAX__=");Serial.print(__INT8_MAX__, DEC);Serial.print(", __INT16_MAX__=");Serial.print(__INT16_MAX__, DEC);Serial.print(", __INT32_MAX__=");Serial.println(__INT32_MAX__, DEC);
Serial.print("M8=");Serial.print(_d_FactorToMax8, DEC);Serial.print(", M16=");Serial.print(_d_FactorToMax16, DEC);Serial.print(", M32=");Serial.println(_d_FactorToMax32, DEC);
Serial.print("R16P=");Serial.print(_fixedPoint16Fraction_Pos / 256.0, 3);Serial.print(", R16N=");Serial.print(_fixedPoint16Fraction_Neg / 256.0, 3);
Serial.print(", R32P=");Serial.print(_fixedPoint32Fraction_Pos / 65536.0, 3);Serial.print(", R32N=");Serial.print(_fixedPoint32Fraction_Neg / 65536.0, 3);
Serial.print(", R64P=");Serial.print(_fixedPoint64Fraction_Pos / 4294967296.0, 3);Serial.print(", R64N=");Serial.println(_fixedPoint64Fraction_Neg / 4294967296.0, 3);
#endif
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

int8_t Multiply8ByFixedPointFraction16(int8_t factor, const FixedPointFraction16_t* pFixedPointFraction){
  if(factor == 0 || pFixedPointFraction == nullptr || pFixedPointFraction->TheFraction == 0) { return 0; }
  FixedPointFraction16_t fixedPointFraction = *pFixedPointFraction;
  bool bFPFNeg = fixedPointFraction.TheFraction < 0;
  if(bFPFNeg){
    fixedPointFraction.TheFraction = -fixedPointFraction.TheFraction;
  }
  int16_t res = factor;
  res *= fixedPointFraction.TheFraction;
  res >>= fixedPointFraction.BitsToShift;
  return bFPFNeg ? -res : res;
}
int16_t Multiply16ByFixedPointFraction32(int16_t factor, const FixedPointFraction32_t* pFixedPointFraction){
  if(factor == 0 || pFixedPointFraction == nullptr || pFixedPointFraction->TheFraction == 0) { return 0; }
  FixedPointFraction32_t fixedPointFraction = *pFixedPointFraction;
  bool bFPFNeg = fixedPointFraction.TheFraction < 0;
  if(bFPFNeg){
    fixedPointFraction.TheFraction = -fixedPointFraction.TheFraction;
  }
  int32_t res = factor;
  res *= fixedPointFraction.TheFraction;
  res >>= fixedPointFraction.BitsToShift;
  return bFPFNeg ? -res : res;
}
int32_t Multiply32ByFixedPointFraction64(int32_t factor, const FixedPointFraction64_t* pFixedPointFraction){
  if(factor == 0 || pFixedPointFraction == nullptr || pFixedPointFraction->TheFraction == 0) { return 0; }
  FixedPointFraction64_t fixedPointFraction = *pFixedPointFraction;
  bool bFPFNeg = fixedPointFraction.TheFraction < 0;
  if(bFPFNeg){
    fixedPointFraction.TheFraction = -fixedPointFraction.TheFraction;
  }
  int64_t res = factor;
  res *= fixedPointFraction.TheFraction;
  res >>= fixedPointFraction.BitsToShift;
  return bFPFNeg ? -res : res;
}

int64_t Multiply64ByFixedPointFraction64(int64_t factor, const FixedPointFraction64_t* pFixedPointFraction){
  if(factor == 0 || pFixedPointFraction == nullptr || pFixedPointFraction->TheFraction == 0) { return 0; }
  FixedPointFraction64_t fixedPointFraction = *pFixedPointFraction;
  bool bFPFNeg = fixedPointFraction.TheFraction < 0;
  if(bFPFNeg){
    fixedPointFraction.TheFraction = -fixedPointFraction.TheFraction;
  }
  int64_t res = factor;
  res *= fixedPointFraction.TheFraction;
  res >>= fixedPointFraction.BitsToShift;
  return bFPFNeg ? -res : res;
}

// we need two fractions, depending on whether we're multiplying a +ve or -ve factor later
void Ratio8ToFixedPointFraction16(int8_t numerator, int8_t denominator, FixedPointFraction16_t* poutFixedPointFraction_Pos, FixedPointFraction16_t* poutFixedPointFraction_Neg){
  FixedPointFraction16_t resP, resN;
  if(numerator != 0 && denominator != 0) {
    resP.TheFraction = numerator;
    resP.BitsToShift = 8;
    resP.TheFraction <<= resP.BitsToShift;
    resN = resP;
    // round slightly to help truncated fraction for +ve numbers
    int8_t rounding = abs(denominator) - 1;
    resP.TheFraction += resP.TheFraction > 0 ? rounding : -rounding;
    resP.TheFraction /= denominator;
    resN.TheFraction /= denominator; // always need to round down for -ve numbers
  }
  if(poutFixedPointFraction_Pos) { *poutFixedPointFraction_Pos = resP; }
  if(poutFixedPointFraction_Neg) { *poutFixedPointFraction_Neg = resN; }
}

// we need two fractions, depending on whether we're multiplying a +ve or -ve factor later
void Ratio16ToFixedPointFraction32(int16_t numerator, int16_t denominator, FixedPointFraction32_t* poutFixedPointFraction_Pos, FixedPointFraction32_t* poutFixedPointFraction_Neg){
  FixedPointFraction32_t resP, resN;
  if(numerator != 0 && denominator != 0) {
    resP.TheFraction = numerator;
    resP.BitsToShift = 16;
    resP.TheFraction <<= resP.BitsToShift;
    resN = resP;
    // round slightly to help truncated fraction for +ve numbers
    int16_t rounding = abs(denominator) - 1;
    resP.TheFraction += resP.TheFraction > 0 ? rounding : -rounding;
    resP.TheFraction /= denominator;
    resN.TheFraction /= denominator; // always need to round down for -ve numbers
  }
  if(poutFixedPointFraction_Pos) { *poutFixedPointFraction_Pos = resP; }
  if(poutFixedPointFraction_Neg) { *poutFixedPointFraction_Neg = resN; }
}

// we need two fractions, depending on whether we're multiplying a +ve or -ve factor later
void Ratio32ToFixedPointFraction64(int32_t numerator, int32_t denominator, FixedPointFraction64_t* poutFixedPointFraction_Pos, FixedPointFraction64_t* poutFixedPointFraction_Neg){
  FixedPointFraction64_t resP, resN;
  if(numerator != 0 && denominator != 0) {
    resP.TheFraction = numerator;
    resP.BitsToShift = 32;
    resP.TheFraction <<= resP.BitsToShift;
    resN = resP;
    // round slightly to help truncated fraction for +ve numbers
    int32_t rounding = abs(denominator) - 1;
    resP.TheFraction += resP.TheFraction > 0 ? rounding : -rounding;
    resP.TheFraction /= denominator;
    resN.TheFraction /= denominator; // always need to round down for -ve numbers
  }
  if(poutFixedPointFraction_Pos) { *poutFixedPointFraction_Pos = resP; }
  if(poutFixedPointFraction_Neg) { *poutFixedPointFraction_Neg = resN; }
}

// we need two fractions, depending on whether we're multiplying a +ve or -ve factor later
// COMPROMISE s/b Ratio64ToFixedPointFraction6464
void Ratio64ToFixedPointFraction64(int64_t numerator, int64_t denominator, FixedPointFraction64_t* poutFixedPointFraction_Pos, FixedPointFraction64_t* poutFixedPointFraction_Neg){
  FixedPointFraction64_t resP, resN;
  if(numerator != 0 && denominator != 0) {
    resP.TheFraction = numerator;
    resP.BitsToShift = 32;
    resP.TheFraction <<= resP.BitsToShift;
    resN = resP;
    // round slightly to help truncated fraction for +ve numbers
    int32_t rounding = abs(denominator) - 1;
    resP.TheFraction += resP.TheFraction > 0 ? rounding : -rounding;
    resP.TheFraction /= denominator;
    resN.TheFraction /= denominator; // always need to round down for -ve numbers
  }
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
