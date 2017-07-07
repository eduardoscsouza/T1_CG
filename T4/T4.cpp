/*
Eduardo Santos Carlos de Souza
9293481
*/

#include <GL/glut.h>
#include <cmath>
#include <cstring>

#include <vector>

//Macros para auxiliar no codigo
#define LIGHT_STEP 0.05f
#define LIGHT_DELAY 40

#define ROTATION_STEP 5.0f
#define ROTATION_DELAY 40

#define ZOOM_STEP 0.05f
#define ZOOM_DELAY 40

#define FPS 60

#define AMBIENT_COLOR {0.2f, 0.2f, 0.2f}

//Vetores de cor para auxiliar no codigo
GLfloat white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat black[4] = {0.0f, 0.0f, 0.0f, 1.0f};

using namespace std;



/*
Classe para um ponto em 3 dimensoes
*/
class Point3D
{
public:
	GLfloat x, y, z;

	Point3D() : Point3D(0.0, 0.0, 0.0){}

	Point3D(GLfloat x, GLfloat y, GLfloat z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

/*
Classe que gera a malha poligonal da elipse,
e a desenha com a cor e as normais
*/
class Ellipsoid
{
public:
	vector<vector<Point3D> > points;
	GLfloat sparkle[4], color[4], radiance[4];

	Ellipsoid() : Ellipsoid(1.0, 1.0, 1.0, 0.25, 0.25, NULL){}
	Ellipsoid(double a, double b, double c, double theta_step,  double phi_step, GLfloat ** parameters)
	{
		this->points = vector<vector<Point3D> >();

		/*
		Loop que define os pontos da elipsoide
		Ele utiliza a definicao da elipsoide em coordenadas polares,
		e varia o Theta e o Phi de forma que variando o Phi gere-se
		"fatias" da elipsoide, e dentro dessas fatias varia-se o theta para
		completar o circulo.
		Foi necessario um pouco de manipulação para garantir que sempre o ultimo
		ponto do loop seja igual ao primeiro
		*/
		bool ikeep = true;
		double phi = -(M_PI/2.0);
		while(ikeep){
			this->points.push_back(vector<Point3D>());
			if (phi>=(M_PI/2.0)){
				ikeep = false;
				phi = (M_PI/2.0);
			}

			bool jkeep = true;
			double theta = 0.0;
			int cur_line = this->points.size()-1;
			while(jkeep){
				if (theta>=(2.0*M_PI)){
					jkeep = false;
					theta = (2.0*M_PI);
				}

				points[cur_line].push_back(Point3D(a*cos(theta)*cos(phi), b*sin(theta)*cos(phi), c*sin(phi)));
				theta+=theta_step;
			}

			phi+=phi_step;
		}

		if (parameters==NULL){
			memcpy(this->color, white, 4*sizeof(GLfloat));
			memcpy(this->sparkle, white, 4*sizeof(GLfloat));
			memcpy(this->radiance, black, 4*sizeof(GLfloat));
		}
		else{
			memcpy(this->color, parameters[0], 4*sizeof(GLfloat));
			memcpy(this->sparkle, parameters[1], 4*sizeof(GLfloat));
			memcpy(this->radiance, parameters[2], 4*sizeof(GLfloat));
		}
	}

	void draw()
	{
		//Definicao das propriedade de cor do material
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->color);
		glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);
		glMaterialfv(GL_FRONT, GL_SPECULAR, this->sparkle);
		glMaterialfv(GL_FRONT, GL_EMISSION, this->radiance);

		/*
		Desenho da Elipsoide
		As "fatias" intermediarias sao feitas com quadrados, de forma
		que cada quadrado aproxime a região da superficie da elipse
		de um intervalo de Phi e Theta. O topo e o fundo foram feitos com triangulos,
		com as fatias adjacentes, ja que efetivamente so a um ponto nas fatias superiores
		e inferiores.
		Como é uma elipsoide centrada em (0,0) o vetor normal em cada ponto é paralelo ao vetor
		da posição do ponto. Também, não foi necessário normalizar por haver habilitado o GL_NORMALIZE
		*/
		glBegin(GL_QUADS);
		for (int i=1; i<this->points.size()-2; i++){
			for (int j=0; j<this->points[i].size()-1; j++){
				glNormal3f(this->points[i][j].x, this->points[i][j].y, this->points[i][j].z);
				glVertex3f(this->points[i][j].x, this->points[i][j].y, this->points[i][j].z);
				glNormal3f(this->points[i][j+1].x, this->points[i][j+1].y, this->points[i][j+1].z);
				glVertex3f(this->points[i][j+1].x, this->points[i][j+1].y, this->points[i][j+1].z);
				glNormal3f(this->points[i+1][j+1].x, this->points[i+1][j+1].y, this->points[i+1][j+1].z);
				glVertex3f(this->points[i+1][j+1].x, this->points[i+1][j+1].y, this->points[i+1][j+1].z);
				glNormal3f(this->points[i+1][j].x, this->points[i+1][j].y, this->points[i+1][j].z);
				glVertex3f(this->points[i+1][j].x, this->points[i+1][j].y, this->points[i+1][j].z);
			}
		}
		glEnd();

		glBegin(GL_TRIANGLES);
		for (int i=0; i<this->points[1].size()-1; i++){
			glNormal3f(this->points[0][0].x, this->points[0][0].y, this->points[0][0].z);
			glVertex3f(this->points[0][0].x, this->points[0][0].y, this->points[0][0].z);
			glNormal3f(this->points[1][i].x, this->points[1][i].y, this->points[1][i].z);
			glVertex3f(this->points[1][i].x, this->points[1][i].y, this->points[1][i].z);
			glNormal3f(this->points[1][i+1].x, this->points[1][i+1].y, this->points[1][i+1].z);
			glVertex3f(this->points[1][i+1].x, this->points[1][i+1].y, this->points[1][i+1].z);

			int lin = this->points.size()-1;
			glNormal3f(this->points[lin][0].x, this->points[lin][0].y, this->points[lin][0].z);
			glVertex3f(this->points[lin][0].x, this->points[lin][0].y, this->points[lin][0].z);
			glNormal3f(this->points[lin-1][i].x, this->points[lin-1][i].y, this->points[lin-1][i].z);
			glVertex3f(this->points[lin-1][i].x, this->points[lin-1][i].y, this->points[lin-1][i].z);
			glNormal3f(this->points[lin-1][i+1].x, this->points[lin-1][i+1].y, this->points[lin-1][i+1].z);
			glVertex3f(this->points[lin-1][i+1].x, this->points[lin-1][i+1].y, this->points[lin-1][i+1].z);
		}
		glEnd();
	}

};

class Light
{
public:
	int idx;
	Point3D pos;
	GLfloat color[4];

	Light() : Light(0, Point3D(0.0, 0.0, 0.0), NULL){}
	Light(int idx, Point3D pos, GLfloat * color)
	{
		this->idx = idx;
		this->pos = pos;
		if (color==NULL) memcpy(this->color, white, 4*sizeof(GLfloat));
		else memcpy(this->color, color, 4*sizeof(GLfloat));
	}

	void shine()
	{
		glLightfv(GL_LIGHT0 + idx, GL_AMBIENT, black);
		glLightfv(GL_LIGHT0 + idx, GL_DIFFUSE, this->color);
		glLightfv(GL_LIGHT0 + idx, GL_SPECULAR, white);
		GLfloat aux_pos[4] = {this->pos.x, this->pos.y, this->pos.z, 1.0f};
		glLightfv(GL_LIGHT0 + idx, GL_POSITION, aux_pos);   
	}
};



Ellipsoid e;
bool el_rotating;
GLfloat el_x_angle, el_y_angle, el_z_angle;
char el_x_dir, el_y_dir, el_z_dir;
Light l;
bool light_moving;
char light_x_dir, light_y_dir, light_z_dir;
GLfloat camera_lin_pos;
bool camera_moving;
char camera_dir;



/*
Desenha a cena completa
*/
void draw_all()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	l.shine();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
	glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);
	glMaterialfv(GL_FRONT, GL_EMISSION, white);
	glTranslatef(l.pos.x, l.pos.y, l.pos.z);
	glutSolidSphere(0.04, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(el_z_angle, 0.0f, 0.0f, 1.0f);
	glRotatef(el_y_angle, 0.0f, 1.0f, 0.0f);
	glRotatef(el_x_angle, 1.0f, 0.0f, 0.0f);
	e.draw();
	glPopMatrix();
	
	glutSwapBuffers();
	glFlush();
}



void move_light(int value)
{
	bool again = false;
	if (light_x_dir || light_y_dir || light_z_dir) again=true;

	l.pos.x += light_x_dir * LIGHT_STEP;
	l.pos.y += light_y_dir * LIGHT_STEP;
	l.pos.z += light_z_dir * LIGHT_STEP;

	if (again) glutTimerFunc(LIGHT_DELAY, &move_light, 0);
	else light_moving = false;
}

void change_angle(int value)
{
	bool again = false;
	if (el_x_dir || el_y_dir || el_z_dir) again=true;

	el_x_angle += el_x_dir * ROTATION_STEP;
	el_y_angle += el_y_dir * ROTATION_STEP;
	el_z_angle += el_z_dir * ROTATION_STEP;

	if (again) glutTimerFunc(ROTATION_DELAY, &change_angle, 0);
	else el_rotating = false;
}

void set_camera(int value)
{
	camera_lin_pos += camera_dir * ZOOM_STEP;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.1f, 100.0f); 
	gluLookAt(-2.0f + camera_lin_pos, 2.0f - camera_lin_pos, -2.0f + camera_lin_pos, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	if (camera_dir) glutTimerFunc(ZOOM_DELAY, &set_camera, 0);
	else camera_moving = false;
}



/*
Funcao chamada quando uma tecla especial
do teclado e solta
*/
void special_up_call(int key, int x, int y)
{
	
	if (key == GLUT_KEY_LEFT) light_x_dir++;
	else if (key == GLUT_KEY_RIGHT) light_x_dir--;
	else if (key == GLUT_KEY_UP) light_y_dir--;
	else if (key == GLUT_KEY_DOWN) light_y_dir++;
}

/*
Funcao chamada quando uma tecla especial
do teclado e apertada
*/
void special_down_call(int key, int x, int y)
{
	
	if (key == GLUT_KEY_LEFT) light_x_dir--;
	else if (key == GLUT_KEY_RIGHT) light_x_dir++;
	else if (key == GLUT_KEY_UP) light_y_dir++;
	else if (key == GLUT_KEY_DOWN) light_y_dir--;
	
	if (!light_moving){
		glutTimerFunc(0, &move_light, 0);
		light_moving = true;
	}
}

/*
Funcao chamada quando uma tecla
do teclado e solta
*/
void keyboard_up_call(unsigned char key, int x, int y)
{
	if (key=='p') light_z_dir--;
	else if (key=='o') light_z_dir++;
	else if (key=='q') el_x_dir++;
	else if (key=='a') el_x_dir--;
	else if (key=='w') el_y_dir--;
	else if (key=='s') el_y_dir++;
	else if (key=='e') el_z_dir++;
	else if (key=='d') el_z_dir--;
	else if (key=='m') camera_dir--;
	else if (key=='n') camera_dir++;
}

/*
Funcao chamada quando uma tecla
do teclado e apertada
*/
void keyboard_down_call(unsigned char key, int x, int y)
{
	if (key=='p') light_z_dir++;
	else if (key=='o') light_z_dir--;
	else if (key=='q') el_x_dir--;
	else if (key=='a') el_x_dir++;
	else if (key=='w') el_y_dir++;
	else if (key=='s') el_y_dir--;
	else if (key=='e') el_z_dir--;
	else if (key=='d') el_z_dir++;
	else if (key=='m') camera_dir++;
	else if (key=='n') camera_dir--;

	if ((key=='p' || key=='o') && !light_moving){
		glutTimerFunc(0, &move_light, 0);
		light_moving = true;
	}
	else if ((key=='m' || key=='n') && !camera_moving){
		glutTimerFunc(0, &set_camera, 0);
		camera_moving = true;
	}
	else if (!el_rotating){
		glutTimerFunc(0, &change_angle, 0);
		el_rotating = true;
	}
}



void redraw(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, &redraw, 0);
}



int main(int argc, char * argv[])
{
	//Inicializacao do glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Ellipsoid");

	//Setar os parametros do OpenGL
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_LIGHTING);  
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	GLfloat ambient[4] = AMBIENT_COLOR;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glShadeModel(GL_SMOOTH);

	//Setar elipse
	el_x_angle = el_y_angle = el_z_angle = 0.0f;
	GLfloat ** parameters = (GLfloat**) malloc(3 * sizeof(GLfloat*));
	for (int i=0; i<3; i++) parameters[i] = (GLfloat*) malloc(4 * sizeof(GLfloat));
	parameters[0][0] = parameters[0][2] = parameters[0][3] = 1.0f;
	parameters[0][1] = 0.0f;
	memcpy(parameters[1], white, 4*sizeof(GLfloat));
	memcpy(parameters[2], black, 4*sizeof(GLfloat));
	e = Ellipsoid(0.5, 0.25, 0.25, (2.0*M_PI)/60.0, (M_PI)/60.0, parameters);
	for (int i=0; i<3; i++) free(parameters[i]);
	free(parameters);

	//Setar luz
	light_moving = false;
	light_x_dir = light_y_dir = light_z_dir = 0;
	l = Light(0, Point3D(0.0f, 0.5f, 0.0f), white);

	//Setar camera
	camera_lin_pos = 0.0f;
	camera_moving = false;
	camera_dir = 0;	
	set_camera(0);

	//Setar as funcoes de callback
	glutIgnoreKeyRepeat(1);
	glutSpecialFunc(&special_down_call);
	glutKeyboardFunc(&keyboard_down_call);
	glutSpecialUpFunc(&special_up_call);
	glutKeyboardUpFunc(&keyboard_up_call);
	glutDisplayFunc(&draw_all);
	
	glutTimerFunc(0, &redraw, 0);

	glutMainLoop();

	return 0;
}
