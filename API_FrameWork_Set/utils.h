#pragma once

#define DEG_TO_RAD 0.017435 //��׸� 1��(���Ȱ�)

#define PI 3.141592654f
#define PI2 PI * 2


#define PI_2	(PI / 2)
#define PI_4	(PI / 4)
#define PI_8	(PI / 8)
#define PI_16	(PI / 16)
#define PI_32	(PI / 32)
namespace UTIL
{

	//�Ÿ� �������� �Լ�
	float getDistance(float startX, float startY, float endX, float endY);

	//���� �������� �Լ�
	float getAngle(float x1, float y1, float x2, float y2);



}

