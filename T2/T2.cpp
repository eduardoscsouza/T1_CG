/*
Eduardo Santos Carlos de Souza
9293481
*/

#include <GL/glut.h>
#include <stdlib.h>

#define SHIP_SCALE 0.20f
#define SHIP_Y_OFFSET -0.9f
#define SHIP_STEP 0.02f
#define SHIP_DELAY 30

#define MISSILE_SCALE 0.07f
#define MISSILE_STEP 0.05f
#define MISSILE_DELAY 30

#define ALIEN_FLEET_ROWS 6
#define ALIEN_FLEET_COLUMNS 8
#define ALIEN_BOX_X 0.15f
#define ALIEN_BOX_Y 0.07875f
#define ALIEN_SPACING 0.05f
#define ALIEN_FLEET_START_POS_X (ALIEN_BOX_X - 1)
#define ALIEN_FLEET_START_POS_Y 1.0f
#define ALIEN_FLEET_RIGHT_MOV 1
#define ALIEN_FLEET_LEFT_MOV -1
#define POS(i,j) (a * ALIEN_FLEET_COLUMNS + j)

typedef struct
{
	GLfloat x_pos;
	GLfloat y_pos;
	bool alive;
}AlienShip;

GLfloat ship_x;
char ship_dir;
AlienShip *fleet;
int fleet_direction = ALIEN_FLEET_RIGHT_MOV;
GLfloat missile_x, missile_y;
bool missile_firing;

void draw_ship();
void draw_alien(GLfloat, GLfloat);
void draw_fleet();
void draw_missile();
void draw_all();

void detect_colision();
void build_alien_fleet();

void special_up_call(int, int, int);
void special_down_call(int, int, int);
void keyboard_down_call(unsigned char, int, int);

void move_missile(int);
void move_ship(int);



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
void draw_alien(GLfloat x_coord, GLfloat y_coord, int type)
{
	if (type == 0)
	{
		glBegin(GL_LINE_STRIP);

		glColor3f(1.0f, 0.4f, 0.0f);
		glVertex2f(x_coord + 0.1, y_coord);
		glVertex2f(x_coord + 0.3, y_coord);
		glVertex2f(x_coord + 0.3, y_coord - 0.07);
		glVertex2f(x_coord + 0.4, y_coord - 0.2);
		glVertex2f(x_coord, y_coord - 0.2);
		glVertex2f(x_coord + 0.1, y_coord - 0.07);
		glVertex2f(x_coord + 0.1, y_coord);

		glEnd();

		glBegin(GL_LINES);

		glVertex2f(x_coord + 0.05, y_coord - 0.14);
		glVertex2f(x_coord + 0.35, y_coord - 0.14);

		glEnd();
	}
	else if (type == 1)
	{
		glBegin(GL_LINE_STRIP);
		
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(x_coord + 0.05, y_coord);
		glVertex2f(x_coord + 0.35, y_coord);
		glVertex2f(x_coord + 0.4, y_coord - 0.08);
		glVertex2f(x_coord + 0.35, y_coord - 0.2);
		glVertex2f(x_coord + 0.275, y_coord - 0.1);
		glVertex2f(x_coord + 0.215, y_coord - 0.1);
		glVertex2f(x_coord + 0.2, y_coord - 0.2);
		glVertex2f(x_coord + 0.185, y_coord - 0.1);
		glVertex2f(x_coord + 0.125, y_coord - 0.1);
		glVertex2f(x_coord + 0.05, y_coord - 0.2);
		glVertex2f(x_coord, y_coord - 0.08);
		glVertex2f(x_coord + 0.05, y_coord);
		
		glEnd();
	}
	else if (type == 2)
	{
		glBegin(GL_LINE_STRIP);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex2f(x_coord, y_coord);
		glVertex2f(x_coord + 0.4, y_coord);
		glVertex2f(x_coord + 0.3, y_coord - 0.05);
		glVertex2f(x_coord + 0.25, y_coord - 0.2);
		glVertex2f(x_coord + 0.15, y_coord - 0.2);
		glVertex2f(x_coord + 0.1, y_coord - 0.05);
		glVertex2f(x_coord, y_coord);
		

		glEnd();

		glBegin(GL_LINE_STRIP);

		glVertex2f(x_coord + 0.06, y_coord - 0.03);
		glVertex2f(x_coord + 0.06, y_coord - 0.14);
		glVertex2f(x_coord + 0.13, y_coord - 0.14);
		
		glEnd();

		glBegin(GL_LINE_STRIP);

		glVertex2f(x_coord + 0.34, y_coord - 0.03);
		glVertex2f(x_coord + 0.34, y_coord - 0.14);
		glVertex2f(x_coord + 0.27, y_coord - 0.14);

		glEnd();
	}
}

/*
*/
void draw_fleet()
{
	int i;

	for (i = 0; i < ALIEN_FLEET_ROWS * ALIEN_FLEET_COLUMNS; i++)
	{
		glPushMatrix();

		glTranslatef(fleet[i].x_pos + 0.2, fleet[i].y_pos - 0.1, 0.0f);
		glScalef(ALIEN_BOX_X / 0.4, ALIEN_BOX_Y / 0.2, 1.0f);
		glTranslatef(-(fleet[i].x_pos + 0.2), -(fleet[i].y_pos - 0.1), 0.0f);

		draw_alien(fleet[i].x_pos, fleet[i].y_pos, (i/ALIEN_FLEET_COLUMNS)/2);

		glPopMatrix();
	}
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

	if (missile_firing) {
		glPushMatrix();
		glTranslatef(missile_x, missile_y, 0.0f);
		glScalef(MISSILE_SCALE, MISSILE_SCALE, 1.0f);
		draw_missile();
		glPopMatrix();
	}

	draw_fleet();

	glutSwapBuffers();
	glFlush();
}

/*
*/
void build_alien_fleet()
{
	int i;
	fleet = (AlienShip*)malloc(sizeof(AlienShip) * ALIEN_FLEET_ROWS * ALIEN_FLEET_COLUMNS);

	for (i = 0; i < ALIEN_FLEET_ROWS * ALIEN_FLEET_COLUMNS; i++)
	{
		fleet[i].alive = true;
		fleet[i].x_pos = ALIEN_FLEET_START_POS_X + ((i % ALIEN_FLEET_COLUMNS) * (ALIEN_BOX_X + ALIEN_SPACING));
		fleet[i].y_pos = ALIEN_FLEET_START_POS_Y - ((i / ALIEN_FLEET_COLUMNS) * (ALIEN_BOX_Y + ALIEN_SPACING));
	}
}

/*
*/
void detect_colision()
{
	if (missile_y > 1.0f) {
		missile_firing = 0;
		missile_x = missile_y = -1.0f;
	}
}



/*
*/
void special_up_call(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) ship_dir++;
	else if (key == GLUT_KEY_RIGHT) ship_dir--;
}

/*
*/
void special_down_call(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) ship_dir--;
	else if (key == GLUT_KEY_RIGHT) ship_dir++;
}

/*
*/
void keyboard_down_call(unsigned char key, int x, int y)
{
	if (key == ' ') {
		if (!missile_firing) {
			missile_firing = 1;
			missile_x = ship_x;
			missile_y = SHIP_Y_OFFSET + (SHIP_SCALE * 0.5f) + (MISSILE_SCALE * 0.3f);

			glutTimerFunc(MISSILE_DELAY, &move_missile, 0);
		}
	}
}



void move_missile(int value)
{
	if (missile_firing) missile_y += MISSILE_STEP;
	detect_colision();

	glutPostRedisplay();
	if (missile_firing) glutTimerFunc(MISSILE_DELAY, &move_missile, 0);
}

void move_ship(int value)
{
	if (ship_dir) {
		ship_x += ship_dir * SHIP_STEP;
		ship_x = (ship_x>1.0f) ? 1.0f : ((ship_x<-1.0f) ? -1.0f : ship_x);

		glutPostRedisplay();
	}

	glutTimerFunc(SHIP_DELAY, &move_ship, 0);
}

void move_alien_fleet(int value)
{
	int i;
	bool move_down = false;
	
	if ((fleet[ALIEN_FLEET_COLUMNS - 1].x_pos + 2 * ALIEN_BOX_X >= 1.0f
		|| fleet[0].x_pos <= -1.08f) && !value)
		move_down = true;

	if (move_down)
	{
		for (i = 0; i < ALIEN_FLEET_ROWS * ALIEN_FLEET_COLUMNS; i++)
				fleet[i].y_pos -= ALIEN_BOX_Y;
		fleet_direction *= -1;
		glutPostRedisplay();
		glutTimerFunc(1000, move_alien_fleet, 1);
	}
	else
	{
		for (i = 0; i < ALIEN_FLEET_ROWS * ALIEN_FLEET_COLUMNS; i++)
			fleet[i].x_pos += 0.25 * ALIEN_BOX_X * fleet_direction;
		glutPostRedisplay();
		glutTimerFunc(750, move_alien_fleet, 0);
	}
}



int main(int argc, char * argv[])
{
	//Inicializacao do glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Space Invaders");

	//Setar as variabeis globais e parametros do OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	ship_x = 0.0f;
	ship_dir = 0;
	missile_firing = 0;
	missile_x = missile_y = -1.0f;

	//Setar as funcoes de callback
	glutIgnoreKeyRepeat(1);
	glutSpecialFunc(&special_down_call);
	glutKeyboardFunc(&keyboard_down_call);
	glutSpecialUpFunc(&special_up_call);
	glutDisplayFunc(&draw_all);
	glutTimerFunc(0, &move_ship, 0);
	glutTimerFunc(750, move_alien_fleet, 0);

	build_alien_fleet();
	glutMainLoop();
	free(fleet);
	return 0;
}
