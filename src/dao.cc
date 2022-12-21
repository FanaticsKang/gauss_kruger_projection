#include <math.h>

int main() {
  double sinL = sin(L);
  double cosL = cos(L);
  const double R = 6378137.0;
  const double f = 1 / 298.257223563;
  const double e2 = f * (2 - f);
  const double temp = sqrt(1 - e2 * sinL * sinL);
  const double temp3 = temp * temp * temp;
  const double Rn = R * (1 - e2) / temp3;
  const double Re = R / temp;

  // 高
  const double RnhX=Rn+Data.INSData.pos(InsTsMin:InsTsMax,3);
  const double RehX=(Re+Data.INSData.pos(InsTsMin:InsTsMax,3))*cosL;
  const double InsLon=(Data.INSData.pos(InsTsMin:InsTsMax,2)-lon0)/180*pi.*RehX;
  const double InsLat=(Data.INSData.pos(InsTsMin:InsTsMax,1)-lat0)/180*pi.*RnhX;
}