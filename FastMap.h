#pragma once
//
//    FILE: FastMap.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: class with fast map function - library for Arduino
//     URL: https://github.com/RobTillaart/FastMap
//
// HISTORY:
// see FastMap.cpp file
//

#include <Arduino.h>

#define FASTMAP_LIB_VERSION (F("0.3.1"))
#define STRING2(x) #x
#define STRING(x) STRING2(x)

class FastMap
{
public:
    FastMap();

    void init(const float in_min, const float in_max, const float out_min, const float out_max);

    float inline map (const float value)  { return _base + value * _factor; }
    float inline back (const float value) { return _backbase + value * _backfactor; }

    float constrainedMap(const float value);
    float lowerConstrainedMap(const float value);
    float upperConstrainedMap(const float value);

private:
    float _in_min, _in_max, _out_min, _out_max;
    float _factor, _base;
    float _backfactor, _backbase;
};


class FastMapDouble
{
public:
    FastMapDouble();
    void init(const double in_min, const double in_max, const double out_min, const double out_max);

    double inline map (const double value)  { return _base + value * _factor; }
    double inline back (const double value) { return _backbase + value * _backfactor; }

    double constrainedMap(const double value);
    double lowerConstrainedMap(const double value);
    double upperConstrainedMap(const double value);

private:
    double _in_min, _in_max, _out_min, _out_max;
    double _factor, _base;
    double _backfactor, _backbase;
};


struct FixedPointFraction16_t {
  int16_t TheFraction;
  int16_t BitsToShift;
  void Dump(Print* pPrint);
};
struct FixedPointFraction32_t {
  int32_t TheFraction;
  int16_t BitsToShift;
  void Dump(Print* pPrint);
};
struct FixedPointFraction64_t {
  int64_t TheFraction;
  int16_t BitsToShift;
  void Dump(Print* pPrint);
};
// fixedPointFraction is often a 8.8 number
int8_t Multiply8ByFixedPointFraction16(int8_t factor, const FixedPointFraction16_t* pFixedPointFraction);
// fixedPointFraction is often a 16.16 number
int16_t Multiply16ByFixedPointFraction32(int16_t factor, const FixedPointFraction32_t* pFixedPointFraction);
// fixedPointFraction is often a 32.32 number
int32_t Multiply32ByFixedPointFraction64(int32_t factor, const FixedPointFraction64_t* pFixedPointFraction);
// COMPROMISE until int128_t defined // fixedPointFraction is often a 32.32 number
int64_t Multiply64ByFixedPointFraction64(int64_t factor, const FixedPointFraction64_t* pFixedPointFraction);

// we need two fractions, depending on whether we're multiplying a +ve or -ve factor later
void Ratio8ToFixedPointFraction16(int8_t numerator, int8_t denominator, FixedPointFraction16_t* poutFixedPointFraction_Pos, FixedPointFraction16_t* poutFixedPointFraction_Neg);
void Ratio16ToFixedPointFraction32(int16_t numerator, int16_t denominator, FixedPointFraction32_t* poutFixedPointFraction_Pos, FixedPointFraction32_t* poutFixedPointFraction_Neg);
void Ratio32ToFixedPointFraction64(int32_t numerator, int32_t denominator, FixedPointFraction64_t* poutFixedPointFraction_Pos, FixedPointFraction64_t* poutFixedPointFraction_Neg);
// COMPROMISE until int128_t defined // Ratio64ToFixedPointFraction3232
void Ratio64ToFixedPointFraction64(int64_t numerator, int64_t denominator, FixedPointFraction64_t* poutFixedPointFraction_Pos, FixedPointFraction64_t* poutFixedPointFraction_Neg);

// Calculate Greatest Common Denominator
long CalcGCD(long A, long B);

class FastMapInt
{
public:
    FastMapInt();

    void init(const int in_min_incl, const int in_max_excl, const int out_min_incl, const int out_max_excl);
    int inline map (const int val, int* pCalcInfo = nullptr) {
      int calcInfo = 0;
      int inXS = val - _in_min_incl;
      int absXS = abs(inXS);
      int ratioPart;
      if(absXS == 0){
        calcInfo |= 1;
        ratioPart = 0;
      } else if(absXS < _d_FactorToMax8){
        calcInfo |= 2;
        ratioPart = Multiply8ByFixedPointFraction16(inXS, inXS >= 0 ? &_fixedPoint16Fraction_Pos : &_fixedPoint16Fraction_Neg);
      } else if(absXS < _d_FactorToMax16){
        calcInfo |= 4;
        ratioPart = Multiply16ByFixedPointFraction32(inXS, inXS >= 0 ? &_fixedPoint32Fraction_Pos : &_fixedPoint32Fraction_Neg);
      } else if(absXS < _d_FactorToMax32){
        calcInfo |= 8;
        ratioPart = Multiply32ByFixedPointFraction64(inXS, inXS >= 0 ? &_fixedPoint64Fraction_Pos : &_fixedPoint64Fraction_Neg);
      } else {
        calcInfo |= 32;
        ratioPart = ((long)inXS * _d_out - (inXS >= 0 ? 0 : _d_in_less1)) / _d_in;
      }
//Serial.print("cI=");Serial.print(calcInfo, DEC);Serial.print(", rP=");Serial.println(ratioPart, DEC);

      if(pCalcInfo) { *pCalcInfo = calcInfo; } // pass back calc info, if wanted
      return ( _out_min_incl + ratioPart);
    }
    int inline back (const int val) {
      int outXS = val - _out_min_incl;
      return ( _in_min_incl + ((long)outXS * _d_in - (outXS >= 0 ? 0 : _d_out_less1) ) / _d_out);
    }
    int constrainedMap(const int val);
    int lowerConstrainedMap(const int val);
    int upperConstrainedMap(const int val);

    void Dump(Print* pPrint);
private:
    int _in_min_incl, _in_max_excl, _out_min_incl, _out_max_excl;
    int _d_in, _d_out, _d_GCF;
    int _d_in_less1, _d_out_less1;
    int _d_FactorToMax8, _d_FactorToMax16, _d_FactorToMax32; // used to see if we can reduce size of calculaton
    FixedPointFraction16_t _fixedPoint16Fraction_Pos, _fixedPoint16Fraction_Neg;
    FixedPointFraction32_t _fixedPoint32Fraction_Pos, _fixedPoint32Fraction_Neg;
    FixedPointFraction64_t _fixedPoint64Fraction_Pos, _fixedPoint64Fraction_Neg;
};

class FastMapLong
{
public:
    FastMapLong();

    void init(const long in_min_incl, const long in_max_excl, const long out_min_incl, const long out_max_excl);
    long inline map (const long val, int* pCalcInfo = nullptr) {
      long calcInfo = 0;
      long inXS = val - _in_min_incl;
      long absXS = abs(inXS);
      long ratioPart;
      if(absXS == 0){
        calcInfo |= 1;
        ratioPart = 0;
      } else if(absXS < _d_FactorToMax8){
        calcInfo |= 2;
        ratioPart = Multiply8ByFixedPointFraction16(inXS, inXS >= 0 ? &_fixedPoint16Fraction_Pos : &_fixedPoint16Fraction_Neg);
      } else if(absXS < _d_FactorToMax16){
        calcInfo |= 4;
        ratioPart = Multiply16ByFixedPointFraction32(inXS, inXS >= 0 ? &_fixedPoint32Fraction_Pos : &_fixedPoint32Fraction_Neg);
      } else if(absXS < _d_FactorToMax32){
        calcInfo |= 8;
        ratioPart = Multiply32ByFixedPointFraction64(inXS, inXS >= 0 ? &_fixedPoint64Fraction_Pos : &_fixedPoint64Fraction_Neg);
      } else {
        calcInfo |= 32;
        ratioPart = ((long long)inXS * _d_out - (inXS >= 0 ? 0 : _d_in_less1)) / _d_in;
      }
//Serial.print("cI=");Serial.print(calcInfo, DEC);Serial.print(", rP=");Serial.println(ratioPart, DEC);

      if(pCalcInfo) { *pCalcInfo = calcInfo; } // pass back calc info, if wanted
      return ( _out_min_incl + ratioPart);
    }
    long inline back (const long val) {
      long outXS = val - _out_min_incl;
      return ( _in_min_incl + ((long long)outXS * _d_in - (outXS >= 0 ? 0 : _d_out_less1) ) / _d_out);
    }
    long constrainedMap(const long val);
    long lowerConstrainedMap(const long val);
    long upperConstrainedMap(const long val);

    void Dump(Print* pPrint);
private:
    long _in_min_incl, _in_max_excl, _out_min_incl, _out_max_excl;
    long _d_in, _d_out, _d_GCF;
    long _d_in_less1, _d_out_less1;
    long _d_FactorToMax8, _d_FactorToMax16, _d_FactorToMax32; // used to see if we can reduce size of calculaton
    FixedPointFraction16_t _fixedPoint16Fraction_Pos, _fixedPoint16Fraction_Neg;
    FixedPointFraction32_t _fixedPoint32Fraction_Pos, _fixedPoint32Fraction_Neg;
    FixedPointFraction64_t _fixedPoint64Fraction_Pos, _fixedPoint64Fraction_Neg;
};
// -- END OF FILE --
