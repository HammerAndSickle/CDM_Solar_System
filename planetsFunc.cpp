#include "solarsysHeader.h"

//Ű���� �ݹ鿡�� ����� �ؽ�Ʈ ���(solarsys.cpp�� ��ġ) ����
extern bool TextToggle;	


//�༺���� �׸���.
void drawSolarSystem(struct planet* planets)
{
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	
	for(int i = 0; i < PLANET_NUM; i++)
	{
		glPushMatrix();
			glRotatef(planets[i].direction, 0.0, 1.0, 0.0);		//ȸ�� �� �̵� - ����
			glTranslatef(planets[i].distance, 0.0, 0.0);
			if(TextToggle) printNames(planets[i]);				//�༺ ���� �̸� ���
			glRotatef(planets[i].self_rot_deg, 1.0, 0.0, 0.0);	//�̵� �� ȸ�� - ����
			drawPlanet(planets[i]);								//�༺ �׸���
		glPopMatrix();
	}

}

//�־��� �༺�� �׸���.
void drawPlanet(struct planet& planet)
{
	//�־��� ���� �༺ �������� �̿��� ���� �׸���.
	drawSphere(planet.rad, 45, 40, planet.color1, planet.color2);
	
	//�伺�� �찡 �ʿ��ϴ�. �츦 �׸����� �Ѵ�.
	if(strcmp(planet.name, "SATURN") == 0)
	{
		glColor3f(0.35, 0.35, 0.2);
		glutSolidTorus(0.1, planet.rad + 0.2, 30, 30);
	}

}

//�༺ �̸��� ����Ѵ�.
void printNames(struct planet& planet)
{
	//�༺ ������ �� 2.0 ����(+y) ��ġ�� ��� ����
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3d(0.0, 2.0, 0.0);

	for(int i = 0; i < strlen(planet.name); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, planet.name[i]);

}

//�༺�� �׷��ش�.
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

			
			//�༺�� ���� �����ϱ� ���� �κ�
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
