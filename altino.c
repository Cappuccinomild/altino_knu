#define _CRT_SECURE_NO_WARNINGS
#include "Altino.h"
#include <stdio.h>
#define distancetillwall 225 // 벽까지 거리
int main()
{
	SensorData data;
	//git commit test code
	Open(szPort);
	Sendbuf[21] = 10;
	int dsensor;
	data = Sensor(1);
	dsensor = data.IRSensor[3];

	Steering(2);
	for (int i = 0; i < 200; i++) {
		data = Sensor(1);
		Go(400, 400);

		dsensor = dsensor - data.IRSensor[3];
		printf("%d %d %d \n",data.IRSensor[2], data.IRSensor[3], dsensor);
		if (data.IRSensor[2] > distancetillwall) {
			if (dsensor < 0)
				Steering(1);
			if (dsensor > 0)
				Steering(3);
		}
		else {
			Go(400, 400);
			Steering(3);
		}
		dsensor = data.IRSensor[3];
	}
	Steering(2);
	Go(0, 0);
	Close();
	return 0;
}