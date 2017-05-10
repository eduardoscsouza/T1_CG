/*
Eduardo Santos Carlos de Souza
9293481
*/

#include <GL/glut.h>

#define SHIP_SCALE 0.20f
#define SHIP_Y_OFFSET -0.9f
#define SHIP_STEP 0.03f

#define MISSILE_SCALE 0.07f
#define MISSILE_STEP 0.05f
#define MISSILE_DELAY 30

GLfloat ship_x;

GLfloat missile_x, missile_y;
char missile_firing;

void draw_ship();
void draw_missile();
void draw_all();

void detect_colision();

void special_call(int, int, int);
void keyboard_call(unsigned char, int, int);
void move_missile(int);



/*
*/
void draw_ship()
{
	glBegin(GL_LINE_STRIP);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.2f, -0.2f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(-0.2f, -0.2f);
	glVertex2f(0.0f, 0.5f);

	glEnd();
}

/*
*/
void draw_missile()
{
	glBegin(GL_LINE_STRIP);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.1f, 0.4f);
	glVertex2f(0.1f, -0.2f);
	glVertex2f(0.2f, -0.3f);
	glVertex2f(-0.2f, -0.3f);
	glVertex2f(-0.2f, -0.3f);
	glVertex2f(-0.1f, -0.2f);
	glVertex2f(-0.1f, 0.4f);
	glVertex2f(0.0f, 0.5f);

	glEnd();
}

/*
*/
void draw_all()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glPushMatrix();
	glTranslatef(ship_x, SHIP_Y_OFFSET, 0.0f);
	glScalef(SHIP_SCALE, SHIP_SCALE, 1.0f);
	draw_ship();
	glPopMatrix();

	if (missile_firing){
		glPushMatrix();
		glTranslatef(missile_x, missile_y, 0.0f);
		glScalef(MISSILE_SCALE, MISSILE_SCALE, 1.0f);
		draw_missile();
		glPopMatrix();
	}

	glFlush();
}



/*
*/
void detect_colision()
{
	if (missile_y > 1.0f){
		missile_firing = 0;
		missile_x = missile_y = -1.0f;
	}
}



/*
*/
void special_call(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) ship_x -= SHIP_STEP;
	else if (key == GLUT_KEY_RIGHT) ship_x += SHIP_STEP;

	ship_x = (ship_x>1.0f) ? 1.0f : ((ship_x<-1.0f) ? -1.0f : ship_x);

	glutPostRedisplay();
}

/*
*/
void keyboard_call(unsigned char key, int x, int y)
{
	if (key == ' '){
		if (!missile_firing){
			missile_firing = 1;
			missile_x = ship_x;
			missile_y = SHIP_Y_OFFSET + (SHIP_SCALE * 0.5f) + (MISSILE_SCALE * 0.3f);

			glutTimerFunc(MISSILE_DELAY, &move_missile, 0);
		}
	}

	glutPostRedisplay();
}

void move_missile(int value)
{
	if (missile_firing) missile_y += MISSILE_STEP;
	detect_colision();

	glutPostRedisplay();
	if (missile_firing) glutTimerFunc(MISSILE_DELAY, &move_missile, 1);
}



int main(int argc, char * argv[])
{
	//Inicializacao do glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Space Invaders");

	//Setar as variabeis globais e parametros do OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	ship_x = 0.0f;
	missile_firing = 0;
	missile_x = missile_y = -1.0f;

	//Setar as funcoes de callback
	glutSpecialFunc(&special_call);
	glutKeyboardFunc(&keyboard_call);
	glutDisplayFunc(&draw_all);

	glutMainLoop();
	return 0;
}