#ifndef    __STDIO_H       
#define    __STDIO_H  

#include <iostream>
#include "glut.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cmath>

#define M_PI 3.14159

//행성의 수 (태양-수성-금성-지구-화성-목성-토성-천왕성-해왕성)
#define PLANET_NUM 9

//가시면 부피의 길이
#define LIMIT 40
#define LIMIT_FLOAT ((GLfloat)LIMIT)

//태양의 거리와 반지르음
#define SUN_DISTANCE 0
#define SUN_RADIUS 2

//열거형
enum PLANET_NAMES
{
	SUN, MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE
};


//각 행성의 정보를 담는 구조체
struct planet
{
	char name[64];				//행성 이름
	GLfloat distance;			//태양에서의 거리
	GLfloat direction;			//태양 기준에서의 방향(degree)
	GLfloat self_rot_deg;		//자전하는 각도
	GLfloat rad;				//반지름
	GLfloat color1[3];			//두 개씩의 색을 가진다.
	GLfloat color2[3];
};

//---종합 그리기 함수
void entireDrawing();

//---행성 함수
void initializePlanets();
void drawSolarSystem(struct planet* planets);

void drawSphere(GLdouble r, GLint lats, GLint longs, GLfloat* color1, GLfloat* color2);
void drawPlanet(struct planet& planet);
void printNames(struct planet& planet);


//---궤도/격자 그리기
void drawOrbit();
void drawGrid();


//void static MyReshape(int width, int height);
//void static MyDisplay();


#endif