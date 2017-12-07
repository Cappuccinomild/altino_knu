#define _CRT_SECURE_NO_WARNINGS
#include "Altino.h"
#include <stdio.h>
#define distancetillwalls2 225 //2번센서 벽까지 거리 
#define distancetillwalls3 153 //3번 센서 벽까지 거리
#define backdistancewall2 700 //후진시 2번센서 거리
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
		Go(350, 350);
		
		dsensor = dsensor - data.IRSensor[3];
		if (data.IRSensor[3] < distancetillwalls3 /* 3번센서가 벽 밖으로 나감 */) {
				printf("%d %d %d \n", data.IRSensor[2], data.IRSensor[3], dsensor);
				Steering(1);
				Go(-400, -400);
				delay(500);
			
		}
		
		if (data.IRSensor[2] > backdistancewall2 /* 2번센서가 벽과 충돌 */) {
				printf("%d %d %d \n", data.IRSensor[2], data.IRSensor[3], dsensor);
				Steering(3);
				Go(-400, -400);
				delay(500);
			
		}
		
		printf("%d %d %d \n",data.IRSensor[2], data.IRSensor[3], dsensor);
		if (data.IRSensor[2] > distancetillwalls2) {
			if (data.IRSensor[3] <= 350)
				Steering(1);
			if (data.IRSensor[3] > 350)
				Steering(3);
		}
		else {
			Go(350, 350);
			Steering(3);
		}
		dsensor = data.IRSensor[3];
	}
	Steering(2);
	Go(0, 0);
	Close();
	return 0;
}
