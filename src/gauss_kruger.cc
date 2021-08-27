#include "gauss_kruger.h"

#include <math.h>

#include "unit_converter.h"

///////////////////////////////////////////////////
// Definition of PrjPoint
///////////////////////////////////////////////////
bool PrjPoint::BL2xy() {
  double X, N, t, t2, m, m2, ng2;
  double sinB, cosB;
  X = A1 * B * 180.0 / M_PI + A2 * sin(2 * B) + A3 * sin(4 * B) +
      A4 * sin(6 * B);
  sinB = sin(B);
  printf("sinB = %.10f\n", sinB);
  cosB = cos(B);
  printf("cosB = %.10f\n", cosB);
  t = tan(B);
  t2 = t * t;
  N = a / sqrt(1 - e2 * sinB * sinB);
  m = cosB * (L - L0);
  m2 = m * m;
  ng2 = cosB * cosB * e2 / (1 - e2);
  x = X + N * t *
              ((0.5 + ((5 - t2 + 9 * ng2 + 4 * ng2 * ng2) / 24.0 +
                       (61 - 58 * t2 + t2 * t2) * m2 / 720.0) *
                          m2) *
               m2);
  y = N * m *
      (1 +
       m2 * ((1 - t2 + ng2) / 6.0 +
             m2 * (5 - 18 * t2 + t2 * t2 + 14 * ng2 - 58 * ng2 * t2) / 120.0));

  y += 500000;
  printf("x = %.10f\ny = %.10f\n", x, y);
  return true;
}

bool PrjPoint::xy2BL() {
  double sinB, cosB, t, t2, N, ng2, V, yN;
  double preB0, B0;
  double eta;
  y -= 500000;
  B0 = x / A1;
  do {
    preB0 = B0;
    B0 = B0 * M_PI / 180.0;
    B0 = (x - (A2 * sin(2 * B0) + A3 * sin(4 * B0) + A4 * sin(6 * B0))) / A1;
    eta = fabs(B0 - preB0);
  } while (eta > 0.000000001);
  B0 = B0 * M_PI / 180.0;
  B = UnitConverter::Rad2Dms(B0);
  sinB = sin(B0);
  cosB = cos(B0);
  t = tan(B0);
  t2 = t * t;
  N = a / sqrt(1 - e2 * sinB * sinB);
  ng2 = cosB * cosB * e2 / (1 - e2);
  V = sqrt(1 + ng2);
  yN = y / N;
  B = B0 -
      (yN * yN - (5 + 3 * t2 + ng2 - 9 * ng2 * t2) * yN * yN * yN * yN / 12.0 +
       (61 + 90 * t2 + 45 * t2 * t2) * yN * yN * yN * yN * yN * yN / 360.0) *
          V * V * t / 2;
  L = L0 + (yN - (1 + 2 * t2 + ng2) * yN * yN * yN / 6.0 +
            (5 + 28 * t2 + 24 * t2 * t2 + 6 * ng2 + 8 * ng2 * t2) * yN * yN *
                yN * yN * yN / 120.0) /
               cosB;
  printf("B = %.10f\nL = %.10f\n", B * 180 / M_PI, L * 180 / M_PI);

  return true;
}

bool PrjPoint::SetL0(double dL0) {
  L0 = UnitConverter::Dms2Rad(dL0);
  return true;
}

bool PrjPoint::SetBL(double dB, double dL) {
  // B = UnitConverter::Dms2Rad(dB);
  // L = UnitConverter::Dms2Rad(dL);
  B = UnitConverter::Degree2Rad(dB);
  L = UnitConverter::Degree2Rad(dL);
  BL2xy();
  return true;
}

bool PrjPoint::GetBL(double *dB, double *dL) {
  *dB = UnitConverter::Rad2Dms(B);
  *dL = UnitConverter::Rad2Dms(L);
  return true;
}

bool PrjPoint::Setxy(double dx, double dy) {
  x = dx;
  y = dy;
  xy2BL();
  return true;
}

bool PrjPoint::Getxy(double *dx, double *dy) {
  *dx = x;
  *dy = y;
  return true;
}
///////////////////////////////////////////////////
// Definition of PrjPoint_IUGG1975
///////////////////////////////////////////////////
PrjPoint_IUGG1975::PrjPoint_IUGG1975() {
  printf("prjpoint_IUGG1975\n");
  a = 6378140;
  f = 298.257;
  e2 = 1 - ((f - 1) / f) * ((f - 1) / f);
  e12 = (f / (f - 1)) * (f / (f - 1)) - 1;
  A1 = 111133.0047;
  A2 = -16038.5282;
  A3 = 16.8326;
  A4 = -0.0220;
}
PrjPoint_IUGG1975::~PrjPoint_IUGG1975() {}
///////////////////////////////////////////////////
// Definition of PrjPoint_Krasovsky
///////////////////////////////////////////////////
PrjPoint_Krasovsky::PrjPoint_Krasovsky() {
  printf("prjpoint_krasovsky\n");
  a = 6378245;
  f = 298.3;
  e2 = 1 - ((f - 1) / f) * ((f - 1) / f);
  e12 = (f / (f - 1)) * (f / (f - 1)) - 1;
  A1 = 111134.8611;
  A2 = -16036.4803;
  A3 = 16.8281;
  A4 = -0.0220;
}
PrjPoint_Krasovsky::~PrjPoint_Krasovsky() {}