/*
Eduardo Santos Carlos de Souza
9293481
*/

#include <GL/glut.h>
#include <stdlib.h>

#define SHIP_SCALE 0.20f
#define SHIP_Y_OFFSET -0.9f
#define SHIP_STEP 0.03f

#define MISSILE_SCALE 0.07f
#define MISSILE_STEP 0.05f
#define MISSILE_DELAY 30

#define ALIEN_FLEET_ROWS 12
#define ALIEN_FLEET_COLUMNS 8
#define ALIEN_BOX_X 0.15f
#define ALIEN_BOX_Y 0.07875f
#define ALIEN_SPACING 0.05f
#define ALIEN_FLEET_START_POS_X -0.9
#define ALIEN_FLEET_START_POS_Y 1.0f
#define POS(i,j) (a * ALIEN_FLEET_COLUMNS + j)

typedef struct
{
    GLfloat x_pos;
    GLfloat y_pos;
    bool alive;
}AlienShip;

GLfloat ship_x;
AlienShip *fleet;
GLfloat missile_x, missile_y;
char missile_firing;

void draw_ship();
void draw_alien(GLfloat, GLfloat);
void draw_fleet();
void draw_missile();
void draw_all();

void detect_colision();
void build_alien_fleet();

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
void draw_alien(GLfloat x_coord, GLfloat y_coord)
{
    glBegin(GL_LINE_STRIP);

    glColor3f(1.0f, 0.4f, 0.0f);
    glVertex2f(x_coord + 0.1, y_coord);
    glVertex2f(x_coord + 0.3, y_coord);
    glVertex2f(x_coord + 0.3, y_coord - 0.07);
    glVertex2f(x_coord + 0.4, y_coord - 0.21);
    glVertex2f(x_coord, y_coord - 0.21);
    glVertex2f(x_coord + 0.1, y_coord - 0.07);
    glVertex2f(x_coord + 0.1, y_coord);

    glEnd();

    glBegin(GL_LINES);

    glVertex2f(x_coord + 0.05, y_coord - 0.14);
    glVertex2f(x_coord + 0.35, y_coord - 0.14);

    glEnd();
}

/*
*/
void draw_fleet()
{
  int i;

  for (i = 0; i < ALIEN_FLEET_ROWS * ALIEN_FLEET_COLUMNS; i++)
  {
      glPushMatrix();

      glTranslatef(fleet[i].x_pos + 0.2, fleet[i].y_pos - 0.105, 0.0f);
      glScalef(ALIEN_BOX_X/0.4, ALIEN_BOX_Y/0.21, 1.0f);
      glTranslatef(-(fleet[i].x_pos + 0.2), -(fleet[i].y_pos - 0.105), 0.0f);

      draw_alien(fleet[i].x_pos, fleet[i].y_pos);

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

	if (missile_firing){
		glPushMatrix();
		glTranslatef(missile_x, missile_y, 0.0f);
		glScalef(MISSILE_SCALE, MISSILE_SCALE, 1.0f);
		draw_missile();
		glPopMatrix();
	}

	draw_fleet();

	glFlush();
}

/*
*/
void build_alien_fleet()
{
    int i;
    fleet = (AlienShip*) malloc(sizeof(AlienShip) * ALIEN_FLEET_ROWS * ALIEN_FLEET_COLUMNS);

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

	build_alien_fleet();
	glutMainLoop();
	free(fleet);
	return 0;
}
