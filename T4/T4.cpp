/*
Eduardo Santos Carlos de Souza
9293481

Leonardo Cesar Cerqueira
8937483
*/

#include <GL/glut.h>
#include <cmath>

#include <vector>

using namespace std;



class Point3D
{
public:
	GLfloat x, y, z;

	Point3D(){ this->x = this->y = this->z = 0.0; }

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

	Ellipsoid() : Ellipsoid(1.0, 1.0, 1.0, (2.0*M_PI)/10.0, (M_PI)/10.0){}
	Ellipsoid(double a, double b, double c, double theta_step,  double phi_step)
	{
		this->points = vector<vector<Point3D> >(((int)(M_PI/phi_step))+1);
		for (int i=0; i<this->points.size(); i++) this->points[i] = vector<Point3D>(((int)((2.0*M_PI)/theta_step))+1);

		int i = 0;
		bool ikeep = true;
		double phi = -(M_PI/2.0);
		while(ikeep){
			if (phi>=(M_PI/2.0)){
				ikeep = false;
				phi = (M_PI/2.0);
			}

			int j = 0;
			bool jkeep = true;
			double theta = 0.0;
			while(jkeep){
				if (theta>=(2.0*M_PI)){
					jkeep = false;
					theta = (2.0*M_PI);
				}

				points[i][j++] = Point3D(a*cos(theta)*cos(phi), b*sin(theta)*cos(phi), c*sin(phi));
				theta+=theta_step;
			}

			i++;
			phi+=phi_step;
		}
	}

	void draw()
	{
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



// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (void)
{
	GLfloat luzAmbiente[4]={1.0,1.0,1.0,1.0}; 
	GLfloat luzDifusa[4]={1.0,1.0,1.0,1.0};	   // "cor" da fonte de luz 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={1.0, 1.0, -1.0, 1.0};
	GLfloat semCorEmissao[4]={0.0,0.0,0.0,1.0};

	GLfloat diffuse[] = {0.5f, 0.5f, 0.8f, 1.0f};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 

	// Define a refletância do material 
	glMaterialfv(GL_FRONT,GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,100);

	glMaterialfv(GL_FRONT,GL_EMISSION,semCorEmissao);

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
	glScalef(0.1, 0.1f, 0.1f);
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

	//Setar as variabeis globais e parametros do OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);  
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	//glShadeModel(GL_SMOOTH);
	e = Ellipsoid(1.0, 2.0, 4.0, (M_PI*10.0)/180.0, (M_PI*10.0)/180.0);

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
