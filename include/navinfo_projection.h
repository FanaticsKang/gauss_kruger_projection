#pragma
#include <eigen3/Eigen/Core>
#include "proj_api.h"

class NaviProjection {
 public:
  static NaviProjection* MakeNaviProjection(
      const double central_meridian = 105,
      const double earth_radius = 6378245.0, const double flattening = 298.3);
  // from WGS84 to ground by gauss kruger projection
  Eigen::Vector2d ToGround(const Eigen::Vector2d& wgs84);
  Eigen::Vector2d ToWGS84(const Eigen::Vector2d& ground);

  void SetGroundConfig(const double central_meridian);
  void SetWGS84Config(const double earth_radius, const double flattening);

 private:
  NaviProjection(const double central_meridian, const double earth_radius,
                 const double flattening);
  ~NaviProjection();

 private:
  // Singleton core data
  static NaviProjection* data_;

  // two coordinate system
  projPJ wgs84_projection_, ground_projection_;

  double central_meridian_;
  double earth_radius_;
  double flattening_;
};