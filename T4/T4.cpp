/*
Eduardo Santos Carlos de Souza
9293481

Leonardo Cesar Cerqueira
8937483
*/

#include <GL/glut.h>
#include <cmath>
#include <cstring>

#include <vector>

using namespace std;



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

class Ellipsoid
{
public:
	vector<vector<Point3D> > points;
	GLfloat expoent, color[4], sparkle[4], radiance[4];

	Ellipsoid() : Ellipsoid(1.0, 1.0, 1.0, (2.0*M_PI)/20.0, (M_PI)/20.0, NULL){}
	Ellipsoid(double a, double b, double c, double theta_step,  double phi_step, GLfloat ** parameters)
	{
		this->points = vector<vector<Point3D> >();

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
			while(jkeep){
				if (theta>=(2.0*M_PI)){
					jkeep = false;
					theta = (2.0*M_PI);
				}

				points[this->points.size()-1].push_back(Point3D(a*cos(theta)*cos(phi), b*sin(theta)*cos(phi), c*sin(phi)));
				theta+=theta_step;
			}

			phi+=phi_step;
		}

		if (parameters==NULL){
			this->expoent = 1.0;
			this->color[0] = this->color[1] = this->color[2] = this->color[3] = 1.0f;
			this->sparkle[0] = this->sparkle[1] = this->sparkle[2] = this->sparkle[3] = 1.0f;
			this->radiance[0] = this->radiance[1] = this->radiance[2] = 0.0f;
			this->radiance[3] = 1.0f;
		}
		else{
			memcpy((&this->expoent), parameters[0], sizeof(GLfloat));
			memcpy(this->color, parameters[1], 4*sizeof(GLfloat));
			memcpy(this->sparkle, parameters[2], 4*sizeof(GLfloat));
			memcpy(this->radiance, parameters[3], 4*sizeof(GLfloat));
		}
	}

	void draw()
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, this->color);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,this->expoent);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, this->sparkle);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, this->radiance);

		glBegin(GL_QUADS);
		for (int i=0; i<this->points.size()-1; i++){
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
	}

};



Ellipsoid e;
Point3D light_pos;



void DefineIluminacao ()
{
	GLfloat luzAmbiente[4]={0.0,0.0,0.0,0.0}; 
	GLfloat luzDifusa[4]={1.0,1.0,1.0,1.0};
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};
	GLfloat posicaoLuz[4]={1.0, 1.0, -1.0, 1.0};
	// Define a refletância do material 
	

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );   
}


/*
Desenha a cena completa
*/
void draw_all()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	DefineIluminacao();

	glPushMatrix();
	glScalef(0.5, 0.5f, 0.5f);
	glColor3f(0.0f, 0.0f, 1.0f);
	e.draw();
	glPopMatrix();
	

	glutSwapBuffers();
	glFlush();
}



/*
Funcao chamada quando uma tecla especial
do teclado e solta
*/
void special_up_call(int key, int x, int y)
{
	/*
	if (key == GLUT_KEY_LEFT) ship_dir++;
	else if (key == GLUT_KEY_RIGHT) ship_dir--;*/
}

/*
Funcao chamada quando uma tecla especial
do teclado e apertada
*/
void special_down_call(int key, int x, int y)
{
	/*
	if (key == GLUT_KEY_LEFT) ship_dir--;
	else if (key == GLUT_KEY_RIGHT) ship_dir++;*/
}

/*
Funcao chamada quando uma tecla
do teclado e solta
*/
void keyboard_up_call(unsigned char key, int x, int y)
{
	/*
	if (key == ' ') {
		if (!missile_firing) {
			missile_firing = true;
			missile_x = ship_x;
			missile_y = SHIP_Y_OFFSET + (SHIP_SCALE * 0.5f) + (MISSILE_SCALE * 0.3f);
		}
	}*/
}

/*
Funcao chamada quando uma tecla
do teclado e apertada
*/
void keyboard_down_call(unsigned char key, int x, int y)
{
	/*
	if (key == ' ') {
		if (!missile_firing) {
			missile_firing = true;
			missile_x = ship_x;
			missile_y = SHIP_Y_OFFSET + (SHIP_SCALE * 0.5f) + (MISSILE_SCALE * 0.3f);
		}
	}*/
}



int main(int argc, char * argv[])
{
	//Inicializacao do glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Ellipsoid");

	//Setar os parametros do OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);  
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	//glShadeModel(GL_SMOOTH);

	//Setar elipse
	GLfloat ** parameters = (GLfloat**) malloc(4 * sizeof(GLfloat*));
	for (int i=0; i<4; i++) parameters[i] = (GLfloat*) malloc(4 * sizeof(GLfloat));
	parameters[0][0] = 1.0f;
	parameters[1][1] = 0.0f;
	parameters[1][0] = parameters[1][2] = parameters[1][3] = 1.0f;
	parameters[2][0] = parameters[2][1] = parameters[2][2] = parameters[2][3] = 1.0f;
	parameters[3][0] = parameters[3][1] = parameters[3][2] = 0.0f;
	parameters[3][3] = 1.0f;
	e = Ellipsoid(2.0, 1.0, 1.0, (2.0*M_PI)/50.0, (M_PI)/50.0, parameters);
	for (int i=0; i<4; i++) free(parameters[i]);
	free(parameters);

	//Setar as funcoes de callback
	glutIgnoreKeyRepeat(1);
	glutSpecialFunc(&special_down_call);
	glutKeyboardFunc(&keyboard_down_call);
	glutSpecialUpFunc(&special_up_call);
	glutKeyboardUpFunc(&keyboard_down_call);
	glutDisplayFunc(&draw_all);
	//glutTimerFunc(0, &move_ship, 0);

	glutMainLoop();

	return 0;
}
