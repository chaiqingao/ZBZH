#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926//Բ����
#define pre 1.0e-08//������γ��Bʱ�ľ���
double a = 6378137;//���뾶
double f = 1 / 298.257222101;//����
double b = a - f * a;//�̰뾶
double e2 = (a*a - b * b) / (a*a);//eΪ��һƫ����
void LBHtoXYZ(void);
void XYZtoLBH(void);
double BB(double X,double Y,double Z);
int main()
{
	int n;
	while (1)
	{
		printf("����1���������ת��Ϊ�ռ�ֱ�����ꣻ\n����2���ռ�ֱ������ת��Ϊ������ꡣ\n��������Ҫִ�еĹ��ܣ����������������˳����򣩣�");
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
//�������ϵת��Ϊ�ռ�����ϵ
void LBHtoXYZ(void)
{
	int l1, l2, b1, b2;
	double l3, b3, L, B, H, X, Y, Z, N;
	
	printf("���������뾭�ȡ�ά�ȡ��̣߳��Ƕȷ����ԡ�'�����������");
	scanf_s("%d'%d'%lf',%d'%d'%lf',%lf", &l1, &l2, &l3, &b1, &b2, &b3, &H);
	L = (l1 + l2 / 60 + l3 / 3600) / 180 * PI;
	B = (b1 + b2 / 60 + b3 / 3600) / 180 * PI;
	N = a / sqrt(1 - e2 * sin(B)*sin(B));
	X = (N + H)*cos(B)*cos(L);
	Y = (N + H)*cos(B)*sin(L);
	Z = (N*(1 - e2) + H)*sin(B);
	printf("�ռ�ֱ������Ϊ��%lf,%lf,%lf��\n\n\n", X, Y, Z);
}
//�ռ�����ϵת��Ϊ�������ϵ
void XYZtoLBH(void)
{
	int l1, l2, b1, b2;
	double X, Y, Z, L, B, H, N, l3, b3;
	
	printf("����������X��Y��Z��ֵ��");
	scanf_s("%lf,%lf,%lf", &X, &Y, &Z);
	L = atan(Y / X);
	B = BB(X,Y,Z);
	N = a / sqrt(1 - e2 * sin(B)*sin(B));
	H = sqrt(X*X + Y*Y) / cos(B) - N;
	//����ת��Ϊ�Ƕ�
	L = L * 180 / PI;
	B = B * 180 / PI;
	if (L < 0) L += 180;
	l1 = (int)L;
	l2 = (int)((L - l1) * 60);
	l3 = L - l1 - l2;
	b1 = (int)B;
	b2 = (int)((B - b1) * 60);
	b3 = B - b1 - b2;
	printf("�������Ϊ��%d��%d'%lf\",%d��%d'%lf\",%lf��\n\n\n",l1,l2,l3,b1,b2,b3,H);
}
//���õ��������B��ֵ
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