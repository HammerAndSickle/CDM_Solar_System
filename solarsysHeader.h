#ifndef    __STDIO_H       
#define    __STDIO_H  

#include <iostream>
#include "glut.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cmath>

#define M_PI 3.14159

//�༺�� �� (�¾�-����-�ݼ�-����-ȭ��-��-�伺-õ�ռ�-�ؿռ�)
#define PLANET_NUM 9

//���ø� ������ ����
#define LIMIT 40
#define LIMIT_FLOAT ((GLfloat)LIMIT)

//�¾��� �Ÿ��� ��������
#define SUN_DISTANCE 0
#define SUN_RADIUS 2

//������
enum PLANET_NAMES
{
	SUN, MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE
};


//�� �༺�� ������ ��� ����ü
struct planet
{
	char name[64];				//�༺ �̸�
	GLfloat distance;			//�¾翡���� �Ÿ�
	GLfloat direction;			//�¾� ���ؿ����� ����(degree)
	GLfloat self_rot_deg;		//�����ϴ� ����
	GLfloat rad;				//������
	GLfloat color1[3];			//�� ������ ���� ������.
	GLfloat color2[3];
};

//---���� �׸��� �Լ�
void entireDrawing();

//---�༺ �Լ�
void initializePlanets();
void drawSolarSystem(struct planet* planets);

void drawSphere(GLdouble r, GLint lats, GLint longs, GLfloat* color1, GLfloat* color2);
void drawPlanet(struct planet& planet);
void printNames(struct planet& planet);


//---�˵�/���� �׸���
void drawOrbit();
void drawGrid();


//void static MyReshape(int width, int height);
//void static MyDisplay();


#endif