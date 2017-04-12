/*
Eduardo Santos Carlos de Souza
9293481
*/

#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

#define X_ORI 0.0f
#define Y_ORI 1.5f
#define WINGSPAN 1.0f
#define ANGLE_STEP 5.0f

#define POST_HEIGHT 5.0f
#define POST_WIDTH 0.1f
#define BASE_WIDTH 4.0f

#define X_SIZE 14.0f
#define Y_SIZE 14.0f

#define SCALE 0.15f

unsigned int seed;
float angle;



/*
Funcao para desenhar as pas do cata-vento.
x_ori, y_ori, wingspan sao respectivamente 
as coordenadas do centro e o tamanho das pas
*/
void draw_wings(float x_ori, float y_ori, float wingspan)
{
	glBegin(GL_QUADS);

	//Definicao de variaveis que facilitam e organizam o codigo
	float wing_half = wingspan / 2.0f;
	float wing_oneandhalf = (wingspan+wing_half);

	//Quadrado central
	glColor3f(1.0000f, 0.6352f, 0.9019f);
	glVertex2f(x_ori+wing_half, y_ori+wing_half);
	glVertex2f(x_ori+wing_half, y_ori-wing_half);
	glVertex2f(x_ori-wing_half, y_ori-wing_half);
	glVertex2f(x_ori-wing_half, y_ori+wing_half);

	//Pa de cima
	glColor3f(1.0000f, 0.6352f, 0.9019f);
	glVertex2f(x_ori-wing_half, y_ori+wing_half);
	glVertex2f(x_ori+wing_half, y_ori+wing_half);
	glColor3f(0.9333f, 0.1372f, 0.1921f);
	glVertex2f(x_ori+wing_oneandhalf, y_ori+wing_oneandhalf);
	glVertex2f(x_ori+wing_half, y_ori+wing_oneandhalf);
	
	//Pa da direita
	glColor3f(1.0000f, 0.6352f, 0.9019f);
	glVertex2f(x_ori+wing_half, y_ori+wing_half);
	glVertex2f(x_ori+wing_half, y_ori-wing_half);
	glColor3f(0.1450f, 0.4470f, 0.9960f);
	glVertex2f(x_ori+wing_oneandhalf, y_ori-wing_oneandhalf);
	glVertex2f(x_ori+wing_oneandhalf, y_ori-wing_half);

	//Pa de baixo
	glColor3f(1.0000f, 0.6352f, 0.9019f);
	glVertex2f(x_ori+wing_half, y_ori-wing_half);
	glVertex2f(x_ori-wing_half, y_ori-wing_half);
	glColor3f(0.8470f, 0.9176f, 0.9059f);
	glVertex2f(x_ori-wing_oneandhalf, y_ori-wing_oneandhalf);
	glVertex2f(x_ori-wing_half, y_ori-wing_oneandhalf);

	//Pa da esquerda
	glColor3f(1.0000f, 0.6352f, 0.9019f);
	glVertex2f(x_ori-wing_half, y_ori-wing_half);
	glVertex2f(x_ori-wing_half, y_ori+wing_half);
	glColor3f(0.5450f, 0.1529f, 0.8980f);
	glVertex2f(x_ori-wing_oneandhalf, y_ori+wing_oneandhalf);
	glVertex2f(x_ori-wing_oneandhalf, y_ori+wing_half);

	glEnd();
}

/*
Funcao para desenhar o suporte do cata-vento.
x_ori, y_ori, post_height, post_width, base_width
sao respectivamente as coordenadas do centro, altura e largura dos
postes, e largura da base toda do suporte
*/
void draw_post(float x_ori, float y_ori, float post_height, float post_width, float base_width)
{
	glBegin(GL_QUADS);

	//Definicao de variaveis que facilitam e organizam o codigo
	float post_half = post_width / 2.0f;
	float base_half = base_width / 2.0f;

	//Poste da direita
	glColor3f(1.0000f, 0.6352f, 0.9019f);
	glVertex2f(x_ori-post_half, y_ori);
	glVertex2f(x_ori+post_half, y_ori);
	glColor3f(0.1372f, 0.4196f, 0.9059f);
	glVertex2f(x_ori+(base_half+post_half), y_ori-post_height);
	glVertex2f(x_ori+(base_half-post_half), y_ori-post_height);

	//Poste da esquera
	glColor3f(1.0000f, 0.6352f, 0.9019f);
	glVertex2f(x_ori-post_half, y_ori);
	glVertex2f(x_ori+post_half, y_ori);
	glColor3f(0.1372f, 0.4196f, 0.9059f);
	glVertex2f(x_ori-(base_half-post_half), y_ori-post_height);
	glVertex2f(x_ori-(base_half+post_half), y_ori-post_height);

	//Poste central
	glColor3f(1.0000f, 0.6352f, 0.9019f);
	glVertex2f(x_ori-post_half, y_ori);
	glVertex2f(x_ori+post_half, y_ori);
	glColor3f(0.1843f, 0.9725f, 0.1647f);
	glVertex2f(x_ori+post_half, y_ori-post_height);
	glVertex2f(x_ori-post_half, y_ori-post_height);

	glEnd();
}

void draw_background(float x_size, float y_size)
{
	float half = x_size / 2.0f;

	glBegin(GL_QUADS);

	glColor3f(0.4016f, 0.7718f, 0.3827f);
	glVertex2f(-half, -half);
	glVertex2f(-half, -(half*0.2f));
	glVertex2f(+half, -(half*0.2f));
	glVertex2f(+half, -half);

	glColor3f(0.0000f, 0.0000f, 0.0000f);
	glVertex2f(+half, +half);
	glVertex2f(-half, +half);
	glColor3f(1.0000f, 0.2471f, 0.0039f);
	glVertex2f(-half, -(half*0.2f));
	glVertex2f(+half, -(half*0.2f));

	float vr[5] = {0.6157f, 0.9412f, 0.3764f, 0.6157f, 0.9333f};
	float vg[5] = {0.4627f, 0.5176f, 1.0000f, 1.0000f, 0.9765f};
	float vb[5] = {0.6431f, 0.8353f, 1.0000f, 0.7333f, 0.7255f};
	for (int i=0; i<5; i++){
		glColor3f(vr[i], vg[i], vb[i]);
		glVertex2f(-half-1.00f + i*0.15f, +(half*0.2f));
		glVertex2f(-half-0.85f + i*0.15f, +(half*0.2f));
		glVertex2f(-half+5.15f + i*0.15f, +half);
		glVertex2f(-half+5.00f + i*0.15f, +half);
	}

	srand(seed);
	for (int i=0; i<20; i++){
		float cur_x = ((rand() % (int)((1.8f*half)*1000.f))/1000.f) - (half*0.90f);
		float cur_y = ((rand() % (int)((0.3f*half)*1000.f))/1000.f) + (half*0.55f);
		
		float r, g, b;
		switch (rand() % 4){
			case 0:
				r=0.9215f;g=0.9876f;b=1.0000f;
				break;

			case 1:
				r=0.9216f;g=0.9216f;b=0.1922f;
				break;

			case 2:
				r=0.0039f;g=0.5490f;b=0.7490f;
				break;

			case 3:
				r=0.9882f;g=0.7098f;b=0.8471f;
				break;
		}

		glColor3f(r, g, b);
		glVertex2f(cur_x, cur_y);
		glVertex2f(cur_x-0.075f, cur_y-0.075f);
		glVertex2f(cur_x, cur_y-0.15f);
		glVertex2f(cur_x+0.075f, cur_y-0.075f);
	}
	
	glEnd();
}



/*
Funcao que desenha a cena toda com as variaveis
definidase com as transformacoes necessarias.
Essa funcao é utilizada como funcao de display do glut.
*/
void draw_all()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//Transformacao de escala para a cena toda
	glLoadIdentity();
	glScalef(SCALE, SCALE, SCALE);

	//Desenhar as partes estaticas da cena
	draw_background(X_SIZE, Y_SIZE);
	draw_post(X_ORI, Y_ORI, POST_HEIGHT, POST_WIDTH, BASE_WIDTH);

	//Aplicar a rotacao em relacao ao eixo central do cata-vento
	glTranslatef(X_ORI, Y_ORI, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-X_ORI, -Y_ORI, 0.0f);
	
	//Desenhar o cata-vento rotacionado
	draw_wings(X_ORI, Y_ORI, WINGSPAN);
	
	//Remocao da matriz gerada da pilha de matrizes
	glPopMatrix();

	glFlush();
}

/*
Funcao que incrementa ou decrementa o angulo
do cata-vento quando o mouse e clicado
*/
void mouse_call(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
		angle += ((button==GLUT_LEFT_BUTTON) ? ANGLE_STEP : ((button==GLUT_RIGHT_BUTTON) ? -ANGLE_STEP : 0.0f));
}



int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Cata-Vento");

	seed = time(NULL);
	angle = 0.0f;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	glutMouseFunc(&mouse_call);
	glutIdleFunc(&glutPostRedisplay);
	glutDisplayFunc(&draw_all);

	glutMainLoop();
	return 0;
}