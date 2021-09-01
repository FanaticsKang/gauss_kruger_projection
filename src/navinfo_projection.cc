#include "navinfo_projection.h"

#include <stdio.h>
#include <iostream>

NaviProjection* NaviProjection::data_ = nullptr;
NaviProjection::NaviProjection(const double central_meridian,
                               const double earth_radius,
                               const double flattening)
    : central_meridian_(central_meridian),
      earth_radius_(earth_radius),
      flattening_(flattening) {
  std::cout << "\033[032m--------Navi Projection Initialization--------\033[0m"
            << std::endl;
  SetWGS84Config(earth_radius, flattening);
  SetGroundConfig(central_meridian);

  if (wgs84_projection_ == nullptr || ground_projection_ == nullptr) {
    std::cout << "\033[031m"
              << "NaviProjection Init Error"
              << "\033[0m" << std::endl;
  }
}

Eigen::Vector2d NaviProjection::ToGround(const Eigen::Vector2d &wgs84) {
  double x = wgs84.x();
  double y = wgs84.y();

  pj_transform(wgs84_projection_, ground_projection_, 1, 1, &x, &y, NULL);
  return Eigen::Vector2d(x, y);
}

Eigen::Vector2d NaviProjection::ToWGS84(const Eigen::Vector2d &ground) {
  double x = ground.x();
  double y = ground.y();

  pj_transform(ground_projection_, wgs84_projection_, 1, 1, &x, &y, NULL);
  return Eigen::Vector2d(x, y);
}

void NaviProjection::SetWGS84Config(const double earth_radius,
                                    const double flattening) {
  earth_radius_ = earth_radius;
  flattening_ = flattening;

  char wgs84_config[500];
  // set earth_radius and flattening
  sprintf(wgs84_config,
          "+proj=longlat +towgs84=0.0000,0.0000,0.0000 +a=%.3f +rf=%.3f "
          "+lat_0=0.00000000 +lon_0=104.000000000 +lat_1=24.000000000 "
          "+lat_2=40.000000000 +x_0=0.000 +y_0=0.000 +units=m +no_defs",
          earth_radius_, flattening_);
  std::cout << "wgs84 config: " << wgs84_config << std::endl;

  // Set WGS84 coordinate system, longitude and latitude
  wgs84_projection_ = pj_init_plus(wgs84_config);
}

void NaviProjection::SetGroundConfig(const double central_meridian) {
  central_meridian_ = central_meridian;
  char ground_config[500];
  // set central_meridian
  sprintf(ground_config,
          "+proj=tmerc +ellps=krass +lat_1=25n +lat_2=47n +lon_0=%.1fe "
          "+x_0=2050000 +y_0=0 +units=m +k=1.0",
          central_meridian_);

  std::cout << "ground config: " << ground_config << std::endl;

  // set gauss kruger projection
  ground_projection_ = pj_init_plus(ground_config);
}

void NaviProjection::SetOrigin(const Eigen::Vector2d &wgs84) {
  wgs84_origin_ = wgs84;
  ground_origin_ = ToGround(wgs84);
}

Eigen::Vector2d NaviProjection::ToLocal(const Eigen::Vector2d &wgs84) {
  Eigen::Vector2d ground = ToGround(wgs84);
  return ground - ground_origin_;
}

NaviProjection::~NaviProjection() {
  if (wgs84_projection_ != nullptr) {
    pj_free(wgs84_projection_);
  }
  if (ground_projection_ != nullptr) {
    pj_free(ground_projection_);
  }
}

NaviProjection* NaviProjection::MakeNaviProjection(
    const double central_meridian, const double earth_radius,
    const double flattening) {
  if (data_ == nullptr) {
    data_ = new NaviProjection(central_meridian, earth_radius, flattening);
  }
  return data_;
}