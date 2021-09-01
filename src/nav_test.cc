#include <iomanip>
#include <iostream>
#include <vector>

#include "navinfo_projection.h"

int main() {
  NaviProjection* test = NaviProjection::MakeNaviProjection();
  std::vector<Eigen::Vector2d> parr = {{106.759007, 29.642845},
                                       {106.759007, 29.6428347},
                                       {106.7600459, 29.6428347},
                                       {106.7599744, 29.6428329}};
  test->SetOrigin(parr[0] * DEG_TO_RAD);
  for (auto &tmp : parr) {
    Eigen::Vector2d origin = tmp;
    origin *= DEG_TO_RAD;
    Eigen::Vector2d ground = test->ToGround(origin);
    std::cout << std::setprecision(10);
    std::cout << "Ground localization: " << ground.transpose() << std::endl;

    Eigen::Vector2d local = test->ToLocal(origin);
    std::cout << "Local : " << local.transpose() << std::endl;

    Eigen::Vector2d wgs84 = test->ToWGS84(ground);
    wgs84 *= RAD_TO_DEG;

    std::cout << "WGS84 localization: " << wgs84.transpose() << std::endl;
  }
}