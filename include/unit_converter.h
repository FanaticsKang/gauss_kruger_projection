#pragma once
#include <math.h>
class UnitConverter {
 public:
  // Degree to rad
  static double Degree2Rad(const double degree) {
    return degree * M_PI / 180.0;
  }

  static double Rad2Degree(const double degree) {
    return degree * 180.0 / M_PI;
  }

  // Degree miniute second(DMS) to Rad
  static double Dms2Rad(double dms) {
    const int sign = (dms >= 0 ? 1 : -1);
    dms = fabs(dms);
    const double degree = floor(dms);
    const double miniute = floor(fmod(dms * 100.0, 100.0));
    const double second = fmod(dms * 10000.0, 100.0);
    return sign * (degree + miniute / 60.0 + second / 3600.0) * M_PI / 180.0;
  }

  // Rad to degree miniute second(DMS)
  static double Rad2Dms(double rad) {
    const int sign = (rad >= 0 ? 1 : -1);
    rad = fabs(Rad2Degree(rad));
    const double degree = floor(rad);
    const double miniute = floor(fmod(rad * 60.0, 60.0));
    const double second = fmod(rad * 3600.0, 60.0);
    return sign * (degree + miniute / 100.0 + second / 10000.0);
  }
};