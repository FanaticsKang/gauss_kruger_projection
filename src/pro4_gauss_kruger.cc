#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "proj_api.h"

int main() {
  // 定义一个横轴墨卡托投影坐标系
  // +proj=tmerc 投影类型：横轴墨卡托投影
  // +ellps=krass 克拉索夫斯基椭球
  // +lon_0=115 中央经度为东经117度, 为高斯投影6°带
  // +x_0=0 X轴(东)方向偏移量, 书上建议500km
  // +y_0=0 Y轴(北)方向偏移量
  // +units=m 单位
  // +k_0=1.0 比率

  const char* gauss_kruger_config =
      "+proj=tmerc +lat_0=0 +lon_0=111 +x_0=0000000 +y_0=0 +ellps=krass "
      "+units=m +k_0=1";
  // 创建高斯-克吕格投影
  projPJ gauss_kruger_projection = pj_init_plus(gauss_kruger_config);
  // 初始化投影对象
  if (gauss_kruger_projection == nullptr) {
    exit(-1);
  }

  // 待转换的坐标(投影坐标)
  // 最后一个坐标摘自孔祥元的大地测量学基础P176，
  // 经度114.3333，纬度30.5，中央经线111, 投影坐标(320089.9761, 3380330.773)
  std::vector<projUV> parr = {{106.759007, 29.642845},
                              {106.759007, 29.6428347},
                              {106.7600459, 29.6428347},
                              {106.7599744, 29.6428329},
                              {114.3333333, 30.5}};

  // 逐点转换
  projUV pre_point;
  for (int i = 0; i < parr.size(); i++) {
    printf("\n--------------转换第%d点---------------\n", i + 1);
    // from degree to rad
    parr[i].u *= DEG_TO_RAD;
    parr[i].v *= DEG_TO_RAD;

    // 投影正变换(经纬度坐标转投影坐标)
    projUV point = pj_fwd(parr[i], gauss_kruger_projection);
    printf("Gauss Kruger 投影坐标:%10lf,%10lf\n", point.u, point.v);
    if (i > 0) {
      std::cout << "delta: " << point.u - pre_point.u << ", "
                << point.v - pre_point.v << std::endl;
    }
    pre_point = point;
    // 投影逆变换(投影坐标转经纬度坐标)
    point = pj_inv(point, gauss_kruger_projection);

    // 输出的时候，将弧度转换为度
    printf("Gauss Kruger 经纬度坐标:%10lf,%10lf\n", point.u / DEG_TO_RAD,
           point.v / DEG_TO_RAD);
  }

  // 释放投影对象内存
  pj_free(gauss_kruger_projection);
  return 0;
}