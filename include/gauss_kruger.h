#ifndef _COORTRANS_H_INCLUDED
#define _COORTRANS_H_INCLUDED
#include <iostream>

class PrjPoint
{
   public:
    double L0; // 中央子午线经度
    double B, L; // 大地坐标
    double x, y; // 高斯投影平面坐标
    public:
    bool BL2xy();
    bool xy2BL();
    protected:
    double a, f, e2, e12; // 基本椭球参数
    double A1, A2, A3, A4; // 用于计算X的椭球参数

   public:
    bool SetL0(double dL0);
    bool SetBL(double dB, double dL);
    bool GetBL(double *dB, double *dL);
    bool Setxy(double dx, double dy);
    bool Getxy(double *dx, double *dy);
};

class PrjPoint_Krasovsky : virtual public PrjPoint
{
   public:
    PrjPoint_Krasovsky();
    ~PrjPoint_Krasovsky();
};

class PrjPoint_IUGG1975 : virtual public PrjPoint
{
   public:
    PrjPoint_IUGG1975();
    ~PrjPoint_IUGG1975();
};

#endif /* ndef _COORTRANS_H_INCLUDED */