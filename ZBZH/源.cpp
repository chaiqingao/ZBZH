#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926//圆周率
#define pre 1.0e-08//计算大地纬度B时的精度
double a = 6378137;//长半径
double f = 1 / 298.257222101;//扁率
double b = a - f * a;//短半径
double e2 = (a*a - b * b) / (a*a);//e为第一偏心率
void LBHtoXYZ(void);
void XYZtoLBH(void);
double BB(double X,double Y,double Z);
int main()
{
	int n;
	while (1)
	{
		printf("功能1：大地坐标转换为空间直角坐标；\n功能2：空间直角坐标转换为大地坐标。\n请输入需要执行的功能（若输入其他，则退出程序）：");
		scanf_s("%d", &n);
		if (n==1)
		{
			LBHtoXYZ();
		}
		else if (n==2)
		{
			XYZtoLBH();
		}
		else break;
	}
	system("pause");
	return 0;
}
//大地坐标系转换为空间坐标系
void LBHtoXYZ(void)
{
	int l1, l2, b1, b2;
	double l3, b3, L, B, H, X, Y, Z, N;
	
	printf("请依次输入经度、维度、高程（角度符号以“'”来替代）：");
	scanf_s("%d'%d'%lf',%d'%d'%lf',%lf", &l1, &l2, &l3, &b1, &b2, &b3, &H);
	L = (l1 + l2 / 60 + l3 / 3600) / 180 * PI;
	B = (b1 + b2 / 60 + b3 / 3600) / 180 * PI;
	N = a / sqrt(1 - e2 * sin(B)*sin(B));
	X = (N + H)*cos(B)*cos(L);
	Y = (N + H)*cos(B)*sin(L);
	Z = (N*(1 - e2) + H)*sin(B);
	printf("空间直角坐标为（%lf,%lf,%lf）\n\n\n", X, Y, Z);
}
//空间坐标系转换为大地坐标系
void XYZtoLBH(void)
{
	int l1, l2, b1, b2;
	double X, Y, Z, L, B, H, N, l3, b3;
	
	printf("请依次输入X，Y，Z的值：");
	scanf_s("%lf,%lf,%lf", &X, &Y, &Z);
	L = atan(Y / X);
	B = BB(X,Y,Z);
	N = a / sqrt(1 - e2 * sin(B)*sin(B));
	H = sqrt(X*X + Y*Y) / cos(B) - N;
	//弧度转换为角度
	L = L * 180 / PI;
	B = B * 180 / PI;
	if (L < 0) L += 180;
	l1 = (int)L;
	l2 = (int)((L - l1) * 60);
	l3 = L - l1 - l2;
	b1 = (int)B;
	b2 = (int)((B - b1) * 60);
	b3 = B - b1 - b2;
	printf("大地坐标为（%d°%d'%lf\",%d°%d'%lf\",%lf）\n\n\n",l1,l2,l3,b1,b2,b3,H);
}
//利用迭代法求出B的值
double BB(double X,double Y,double Z)
{
	double b1, b2, N;
	b2 = atan(Z / sqrt(X*X + Y*Y));
	while (1)
	{
		b1 = b2;
		N = a / sqrt(1 - e2 * sin(b1)*sin(b1));
		b2 = atan((Z + N * e2*sin(b1)) / sqrt(X*X + Y*Y));
		if (fabs(b2 - b1) < pre) break;
	}
	return b2;
}