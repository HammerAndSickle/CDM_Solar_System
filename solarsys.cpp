#include "solarsysHeader.h"

//행성의 정보가 담길 곳이다.
struct planet planets[PLANET_NUM];

bool GridToggle = true;		//격자 그리기 토글 변수
bool OrbitToggle = true;	//궤도 그리기 토글 변수
bool TextToggle = false;	//텍스트 출력 토글 변수
bool TimerToggle = true;	//타이머 토글 변수 (회전)
bool isRotation = true;		//처음엔 회전이다. 아니면 1인칭 시선

GLfloat delta = 0.0;		//타이머의 시간

GLfloat suppresser = 0.005;	//가중치

//[공전] 시간당 각 행성이 움직이는 각(degree)속도. 지구를 1.0으로 보았을 때 기준
GLdouble planets_W[PLANET_NUM] = {0.0, 1.607383, 1.174497, 1.0, 0.808725, 0.439597, 0.322148, 0.228188, 0.181208};

//[자전] 시간당 각 행성이 움직이는 각(degree)속도. 지구를 1.0으로 보았을 때 기준
GLdouble planets_selfRot[PLANET_NUM] = {0.03656, 0.017003, -0.0041033, 1.0, 0.9719707, 2.43177994, 2.340845, -1.3882198, 1.485586};


//카메라, 시점을 다루는 변수
GLfloat view_distance = 1.0;

//회전 용 각도
GLfloat theta = 0.0;
GLfloat pi = 0.0;

//1인칭 시선 용 각도
GLfloat UD = 0.0;
GLfloat LR = 0.0;


GLfloat Xpos = 60.0;
GLfloat Ypos = 60.0;
GLfloat Zpos = 60.0;

GLfloat Xlook = 0.0;
GLfloat Ylook = 0.0;
GLfloat Zlook = 0.0;

//윈도우 가로/세로 크기 값
GLdouble globalW = 900.0;
GLdouble globalH = 900.0;

//Idle 콜백
void static MyIdle()
{
	//타이머 토글이 켜져있을 때만 회전, 꺼지면 멈추고 다시 켜지면 이어서 회전
	if(TimerToggle) 
	{
		delta = delta + 0.001;

		for(int i = 0; i < PLANET_NUM; i++)
		{
			planets[i].direction += (0.01 * planets_W[i]);
			planets[i].self_rot_deg += (0.01 * planets_selfRot[i]);

			//360도를 넘은 건 방향을 0으로 돌려준다.
			if(planets[i].direction >= 360.0) planets[i].direction = 0;

			//자전도 마찬가지이되, 음수 방향으로 도는 것도 처리한다.
			if(planets[i].self_rot_deg >= 360.0) planets[i].self_rot_deg = 0;
			if(planets[i].self_rot_deg < -360.0) planets[i].self_rot_deg = 0;
		}
	}

	glutPostRedisplay();
}

//스페셜 키 콜백
void static MyspecialKey(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_DOWN:
		if(isRotation && theta > -1.55)	theta -= 0.01;
		if(!isRotation) UD += 0.5;
		break;
	case GLUT_KEY_UP:
		if(isRotation && theta < 1.55)	theta += 0.01;
		if(!isRotation) UD -= 0.5;
		break;
	case GLUT_KEY_RIGHT:
		if(isRotation) pi += 0.01;
		else LR += 0.5;
		break;
	case GLUT_KEY_LEFT:
		if(isRotation) pi -= 0.01;
		else LR -= 0.5;
		break;
	default:
		break;
	}

	std::cout<<"theta : "<<theta<<std::endl;

	glutPostRedisplay();
}

//키보드 콜백
void static MyKeyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'o':
	case 'O':
		OrbitToggle = ((OrbitToggle)? false : true);
		break;
	case 'G':
	case 'g':
		GridToggle = ((GridToggle)? false : true);
		break;
	case 's':
	case 'S':
		view_distance += 0.01;
		break;
	case 'w':
	case 'W':
		if(view_distance > 0) view_distance -= 0.01;
		break;
	case 't':
	case 'T':
		TextToggle = ((TextToggle)? false : true);
		break;
	case 'p':
	case 'P':
		TimerToggle = ((TimerToggle)? false : true);
		break;
	case 'c':
	case 'C':
		isRotation = ((isRotation)? false : true);
		break;
	case '+':
		suppresser += 0.01;
		break;
	case '-':
		if(suppresser > 0) suppresser /= 1.01;
		break;
	}

	glutPostRedisplay();
}

//리셰이프 콜백
void static MyReshape(int width, int height)
{
	globalW = width; globalH = height;

	glutPostRedisplay();
}

//화면 출력 준비
void static MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, (GLsizei)globalW, (GLsizei)globalH);

	//투영 관련
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective((view_distance *45), (GLdouble)globalW/(GLdouble)globalH, 0.1, 500);


	//시점 관련
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//회전 용 (Rotation 모드)
	Xpos = (60) * cos(theta) * cos(pi);
	Ypos = (60) * sin(theta);
	Zpos = (60) * (-cos(theta) * sin(pi));
	
	//시선 둘러보기 용(First person 모드)
	glRotatef(LR, 0.0, 1.0, 0.0);
	glRotatef(UD, 1.0, 0.0, 0.0);


	gluLookAt(Xpos, Ypos, Zpos, Xlook, Ylook, Zlook, 0.0, 1.0, 0.0);
	
	//본격적인 출력용 함수
	entireDrawing();

	glFlush();
}

//격자를 그린다.
void drawGrid()
{
	glColor3f(0.4, 0.4, 0.4);

	//1.0 눈금의 격자를 그린다. 
	for(int i = LIMIT; i >= -LIMIT; i -= 2)
	{
		glBegin(GL_LINES);
			glVertex3f(-LIMIT_FLOAT, 0.0, (GLfloat)i);
			glVertex3f(LIMIT_FLOAT, 0.0, (GLfloat)i);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f((GLfloat)i, 0.0, LIMIT_FLOAT);
			glVertex3f((GLfloat)i, 0.0, -LIMIT_FLOAT);
		glEnd();
	}
}

//최종 그리기 함수
void entireDrawing()
{
	if(GridToggle)
		drawGrid();

	if(OrbitToggle)
		drawOrbit();

	drawSolarSystem(planets);


}

//궤도 그리기
void drawOrbit()
{	
	//각 7개(태양 제외) 행성이 가진 반지름 정보를 이용해 그린다.
	for(int i = 1; i < PLANET_NUM; i++)
	{
		//다소 밝은 색으로, LINE_LOOP 모드를 이용해야 원을 그릴 수 있음.
		glColor3f(0.95, 0.95, 0.95);
		glBegin(GL_LINE_LOOP);

		GLint sides = 50;

		//각을 조금씩 증가시켜가며 원을 그린다. 단, xz축 평면 위에 그리는 것이므로
		//y좌가 0인 것이다.
		for (int j = 0; j < 360; j += 360 / sides)
		{
			GLdouble heading = j * M_PI / 180;
			glVertex3f(cos(heading) * planets[i].distance, 0.0, sin(heading) * planets[i].distance);
		}
		glEnd();
	}
}

//전역변수 planets에 필요한 정보를 담는다.
void initializePlanets()
{
	char tempNames[PLANET_NUM][64] = {"SUN", "MERCURY", "VENUS", "EARTH", "MARS", "JUPITER", "SATURN", "URANUS", "NEPTUNE"};
	GLfloat distances[PLANET_NUM] = {0.0, 4.0, 6.0, 10.0, 14.0, 18.0, 26.0, 30.0, 32.0};
	GLfloat degrees[PLANET_NUM] = {0.0, };
	GLfloat rads[PLANET_NUM] = {1.0, 0.2, 0.4, 0.5, 0.7, 1.0, 0.92, 0.3, 0.3};
	GLfloat colors1[PLANET_NUM][3] = {{1.0, 0.0, 0.0}, {0.4, 0.4, 0.4}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 
									{1.0, 0.2, 0.2}, {0.8, 0.6, 0.4}, {0.85, 0.65, 0.4}, {0.0, 1.0, 1.0}, {0.2, 0.0, 1.0}};
	GLfloat colors2[PLANET_NUM][3] = {{1.0, 1.0, 0.0}, {0.8, 0.8, 0.8}, {1.0, 0.5, 0.5}, {0.3, 0.85, 0.3}, 
									{1.0, 0.6, 0.6}, {0.5, 0.4, 0.0}, {0.55, 0.45, 0.0}, {0.0, 0.4, 0.4}, {0.0, 0.8, 1.0}};

	for(int i = 0; i < PLANET_NUM; i++)
	{
		strcpy(planets[i].name, tempNames[i]);
		planets[i].distance = distances[i];
		planets[i].self_rot_deg = degrees[i];
		planets[i].direction = degrees[i];
		planets[i].rad = rads[i];
		
		//색을 할당한다.
		for(int j = 0; j < 3; j++)
		{
			planets[i].color1[j] = colors1[i][j];
			planets[i].color2[j] = colors2[i][j];
		}
	}

}


void main (int argc, char** argv)
{
    glutInit (&argc, argv);    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize (900, 900);   
    glutInitWindowPosition (0, 0);    
	glutCreateWindow ("20133265 CHA DONG MIN, Solar System");  
	glClearColor(0.0, 0.0, 0.0, 1.0);
	initializePlanets();	//행성 준비

    glutDisplayFunc (MyDisplay);   
	glutKeyboardFunc(MyKeyboard);
	//glutTimerFunc(40, MyTimer, 1);
	glutSpecialFunc(MyspecialKey);
	glutReshapeFunc(MyReshape);  
    glutIdleFunc(MyIdle);
    glutMainLoop();    
}
