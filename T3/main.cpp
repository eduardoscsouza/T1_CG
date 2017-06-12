/*
Eduardo Santos Carlos de Souza
9293481

Leonardo Cesar Cerqueira
8937483
*/

#include <cstdlib>
#include <cmath>
#include <ctime>

#include"helper.h"

//angle of rotation
float xpos = -50.0f, ypos = 10.0f, zpos = -40.0f, xrot = 0, yrot = 0, angle = 0.0;

float lastx, lasty;

//positions of the cubes
float positionz[10];
float positiony[10];
float positionx[10];
float colors[10][3];
float cRadius = 20.0f;
float cRotation = 180.0f;

//set the positions of the cubes
void objectPositions(void) 
{ 
	for (int i = 0; i<10; i++)
	{
		positionz[i] = float(rand() % 8 + 5);
		positiony[i] = float(rand() % 8 + 5);
		positionx[i] = float(rand() % 8 + 5);
		colors[i][0] = float(rand() % 255) / 255;
		colors[i][1] = float(rand() % 255) / 255;
		colors[i][2] = float(rand() % 255) / 255;
	}
}

//draw the donuts
void object(void) 
{
	for (int i = 0; i<10; i++)
	{
		glPushMatrix();
		glTranslated(-positionx[i + 1] * 10, -positiony[i + 1] * 10, -positionz[i + 1] * 10); //translate the cube
		glColor3f(colors[i][0], colors[i][1], colors[i][2]);
		glutSolidTorus(2.5, 8.5, 50, 50);
		glPopMatrix();
	}

	glColor3f(1.0, 0.0, 1.0);
	for (int i=0; i<8; i++){
		glPushMatrix();
		glTranslatef((i&1) ? 10.0 : -10.0, (i&2) ? 10.0 : -10.0, (i&4) ? 10.0 : -10.0);
		glutSolidCube(3.0);
		glPopMatrix();
	}
}

void model(void) 
{
	glPushMatrix();
	glRotatef(cRotation, 0.0, 1.0, 0.0);
	glScaled(10, 10, 10);
	DrawFrame();
	glPopMatrix();
}

void init(void) 
{
	objectPositions();
}

void enable(void) 
{
	glEnable(GL_DEPTH_TEST); //enable the depth testing
	glShadeModel(GL_SMOOTH); //set the shader to smooth shader
}

void display(void) 
{
	glClearColor(1.0, 1.0, 1.0, 1.0); //clear the screen to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	glLoadIdentity();
	enable();
	glTranslatef(0.0f, 0.0f, -cRadius);
	glRotatef(xrot, 1.0, 0.0, 0.0);
	model(); //Our character to follow

	glRotatef(yrot, 0.0, 1.0, 0.0);  //rotate our camera on the y - axis(up and down)
	glTranslated(-xpos, -ypos, -zpos); //translate the screen to the position of our camera
	glColor3f(1.0f, 1.0f, 1.0f);
	object(); //call the cube drawing function
	glutSwapBuffers(); //swap the buffers
	//angle++; //increase the angle
}

void reshape(int w, int h) 
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	glMatrixMode(GL_PROJECTION); //set the matrix to projection

	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, depth)
	
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

void keyboard(unsigned char key, int x, int y) 
{
	if (key == 'q')
	{
		cRotation += 45;
		if (cRotation > 360) xrot -= 360;
	}

	if (key == 'z')
	{
		cRotation -= 45;
		if (cRotation < -360) xrot += 360;
	}

	if (key == 'w')
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos += float(sin(yrotrad));
		zpos -= float(cos(yrotrad));
		ypos -= float(sin(xrotrad));
	}

	if (key == 's')
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos -= float(sin(yrotrad));
		zpos += float(cos(yrotrad));
		ypos += float(sin(xrotrad));
	}

	if (key == 'd')
	{
		float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos += float(cos(yrotrad) * 0.2);
		zpos += float(sin(yrotrad) * 0.2);
	}

	if (key == 'a')
	{
		float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos -= float(cos(yrotrad) * 0.2);
		zpos -= float(sin(yrotrad) * 0.2);
	}

	if (key == 27)
	{
		UnloadModel();
		exit(0);
	}
}

void mouseMovement(int x, int y) 
{
	float diffx = x - lastx; //check the difference between the current x and the last x position
	float diffy = y - lasty; //check the difference between the current y and the last y position
	lastx = x; //set lastx to the current x position
	lasty = y; //set lasty to the current y position
	xrot += diffy; //set the xrot to xrot with the addition of the difference in the y position
	if (xrot > 90)
		xrot = 90;
	else if (xrot < -90)
		xrot = -90;

	yrot += diffx; //set the xrot to yrot with the addition of the difference in the x position
}

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Pokedonuts");
	srand((unsigned)time(0));
	init();
	InitApp("pikachu/P2_Pikachu.obj");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutPassiveMotionFunc(mouseMovement); //check for mouse	movement

	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}