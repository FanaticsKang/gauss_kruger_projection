#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "proj_api.h"

int main() {
  // 定义WGS84坐标系
  // +a 地球半径
  // +rf 椭球体扁平程度倒数
  // +lat_0 中央纬线
  // +lon_0 中央经线
  // +lat_1,2 第一，第二标准纬线
  // +x_0, +y_0 水平位置偏移
  // +units 单位
  const char* wgs84_config =
      "+proj=longlat +towgs84=0.0000,0.0000,0.0000 +a=6378245.0000 +rf=298.3 "
      "+lat_0=0.00000000 +lon_0=104.000000000 +lat_1=24.000000000 "
      "+lat_2=40.000000000 +x_0=0.000 +y_0=0.000 +units=m +no_defs";

  projPJ wgs84_projection = pj_init_plus(wgs84_config);

  // 定义一个横轴墨卡托投影坐标系
  // +k=1.0 比例
  // +ellps 椭球类型
  const char* ground_config =
      "+proj=tmerc +ellps=krass +lat_1=25n +lat_2=47n +lon_0=105e "
      "+x_0=20500000 +y_0=0 +units=m +k=1.0";
  // 创建高斯-克吕格投影
  projPJ ground_projection = pj_init_plus(ground_config);
  // 初始化投影对象
  if (ground_projection == nullptr || wgs84_projection == nullptr) {
    exit(-1);
  }

  // 待转换的坐标,wgs84
  std::vector<projUV> parr = {{106.759007, 29.642845},
                              {106.759007, 29.6428347},
                              {106.7600459, 29.6428347},
                              {106.7599744, 29.6428329}};

  // 逐点转换
  double pre_point[3];
  for (int i = 0; i < parr.size(); i++) {
    printf("\n--------------转换第%d点---------------\n", i + 1);
    // from degree to rad
    double x, y, z;
    x = parr[i].u * DEG_TO_RAD;
    y = parr[i].v * DEG_TO_RAD;
    z = 0;
    pj_transform(wgs84_projection, ground_projection, 1, 1, &x, &y, &z);

    printf("投影坐标:%10lf,%10lf\n", x, y);

    pj_transform(ground_projection, wgs84_projection, 1, 1, &x, &y, &z);
    printf("地球坐标:%10lf,%10lf\n", x * RAD_TO_DEG, y * RAD_TO_DEG);
  }

  // 释放投影对象内存
  pj_free(wgs84_projection);
  pj_free(ground_projection);
  return 0;
}