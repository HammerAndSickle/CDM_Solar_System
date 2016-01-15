#include "solarsysHeader.h"

//키보드 콜백에서 사용할 텍스트 토글(solarsys.cpp에 위치) 변수
extern bool TextToggle;	


//행성들을 그린다.
void drawSolarSystem(struct planet* planets)
{
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	
	for(int i = 0; i < PLANET_NUM; i++)
	{
		glPushMatrix();
			glRotatef(planets[i].direction, 0.0, 1.0, 0.0);		//회전 후 이동 - 공전
			glTranslatef(planets[i].distance, 0.0, 0.0);
			if(TextToggle) printNames(planets[i]);				//행성 위에 이름 출력
			glRotatef(planets[i].self_rot_deg, 1.0, 0.0, 0.0);	//이동 후 회전 - 자전
			drawPlanet(planets[i]);								//행성 그리기
		glPopMatrix();
	}

}

//주어진 행성을 그린다.
void drawPlanet(struct planet& planet)
{
	//주어진 색과 행성 반지름을 이용해 구를 그린다.
	drawSphere(planet.rad, 45, 40, planet.color1, planet.color2);
	
	//토성은 띠가 필요하다. 띠를 그리도록 한다.
	if(strcmp(planet.name, "SATURN") == 0)
	{
		glColor3f(0.35, 0.35, 0.2);
		glutSolidTorus(0.1, planet.rad + 0.2, 30, 30);
	}

}

//행성 이름을 출력한다.
void printNames(struct planet& planet)
{
	//행성 위에서 약 2.0 정도(+y) 위치에 출력 가정
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3d(0.0, 2.0, 0.0);

	for(int i = 0; i < strlen(planet.name); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, planet.name[i]);

}

//행성을 그려준다.
void drawSphere(GLdouble r, GLint lats, GLint longs, GLfloat* color1, GLfloat* color2) 
{
	bool toggle = false;

	int i, j;
	for(i = 0; i <= lats; i++) {
		GLdouble lat0 = M_PI * (-0.5 + (GLdouble) (i - 1) / lats);
		GLdouble z0  = r * sin(lat0);
		GLdouble zr0 = r * cos(lat0);

		GLdouble lat1 = M_PI * (-0.5 + (GLdouble) i / lats);
		GLdouble z1 = r * sin(lat1);
		GLdouble zr1 = r * cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for(j = 0; j <= longs; j++) {
			GLdouble lng = 2 * M_PI * (GLdouble) (j - 1) / longs;
			GLdouble x = cos(lng);
			GLdouble y = sin(lng);

			
			//행성의 색을 설정하기 위한 부분
			if(toggle)	{
				if(j%2 == 0)
					glColor3f(color1[0], color1[1], color1[2]);
				else
					glColor3f(color2[0], color2[1], color2[2]);
			}
			else		{
				if(j%2 == 0)
					glColor3f(color2[0], color2[1], color2[2]);
				else
					glColor3f(color1[0], color1[1], color1[2]);
			}

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(x * zr0, y * zr0, z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(x * zr1, y * zr1, z1);

			toggle = (toggle)? false : true;
		}
		glEnd();
	}
}
