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

#define X_SIZE 5.0f
#define Y_SIZE 5.0f
#define GRASS_FRAC 0.4f

#define SCALE 0.15f

unsigned int seed;
GLfloat angle;



/*
Funcao para desenhar as pas do cata-vento.
x_ori, y_ori, wingspan sao respectivamente 
as coordenadas do centro e o tamanho das pas
*/
void draw_wings(GLfloat x_ori, GLfloat y_ori, GLfloat wingspan)
{
	//Definicao de variaveis que facilitam e organizam o codigo
	GLfloat wing_half = wingspan / 2.0f, wing_oneandhalf = (wingspan+wing_half);

	glBegin(GL_QUADS);

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
void draw_post(GLfloat x_ori, GLfloat y_ori, GLfloat post_height, GLfloat post_width, GLfloat base_width)
{
	//Definicao de variaveis que facilitam e organizam o codigo
	GLfloat post_half = post_width / 2.0f, base_half = base_width / 2.0f;

	glBegin(GL_QUADS);

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

/*
Funcao para desenhar o plano de fundo
x_size, y_size, grass_frac sao respectivamente as dimensoes do plano
de fundo e a fracao que deve ser grama(e por conseuqncia o resto sera o ceu)
*/
void draw_background(GLfloat x_size, GLfloat y_size, GLfloat grass_frac)
{
	//Definicao de variaveis que facilitam e organizam o codigo
	GLfloat xsize_half = x_size / 2.0f, ysize_half = y_size / 2.0f;
	GLfloat grassfrac_centered = (y_size*grass_frac) - ysize_half;

	glBegin(GL_QUADS);

	//Grama na parte inferior do plano de fundo
	glColor3f(0.5020f, 0.9647f, 0.4784f);
	glVertex2f(-xsize_half, -ysize_half);
	glVertex2f(-xsize_half, grassfrac_centered);
	glVertex2f(+xsize_half, grassfrac_centered);
	glVertex2f(+xsize_half, -ysize_half);
	
	//Ceu na parte superior do plano de fundo
	glColor3f(0.0000f, 0.0000f, 0.0000f);
	glVertex2f(+xsize_half, +ysize_half);
	glVertex2f(-xsize_half, +ysize_half);
	glColor3f(1.0000f, 0.2471f, 0.0039f);
	glVertex2f(-xsize_half, grassfrac_centered);
	glVertex2f(+xsize_half, grassfrac_centered);

	//Desenho das estrelas
	/*
	Elas sao geradas com uma sequencia aleatoria de numeros,
	entao para manter constante a sequencia toda vez que a cena
	for desenhada, reseta-se a seed.
	*/
	srand(seed);
	//Loop que gera 20 estrelas
	for (int i=0; i<20; i++){
		//Geracao das coordenadas x e y da estrela
		GLfloat cur_x = ((rand() % (int)((1.8f*xsize_half)*1000.f))/1000.f) - (xsize_half*0.90f);
		GLfloat cur_y = ((rand() % (int)((0.3f*ysize_half)*1000.f))/1000.f) + (ysize_half*0.55f);
		
		//Switch para definir a cor da estrela(tambem aleatoria)
		GLfloat r, g, b;
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

		//Desenhar a estrela
		glColor3f(r, g, b);
		glVertex2f(cur_x, cur_y);
		glVertex2f(cur_x-0.075f, cur_y-0.075f);
		glVertex2f(cur_x, cur_y-0.15f);
		glVertex2f(cur_x+0.075f, cur_y-0.075f);
	}

	//Desenho do arco iris

	GLfloat rain_x = -(xsize_half*0.1),rain_y = (y_size*(grass_frac+0.1f)) - ysize_half;
	//Vetores com as cores das faixas do arco-iris
	GLfloat vr[5] = {0.6157f, 0.9412f, 0.3764f, 0.6157f, 0.9333f};
	GLfloat vg[5] = {0.4627f, 0.5176f, 1.0000f, 1.0000f, 0.9765f};
	GLfloat vb[5] = {0.6431f, 0.8353f, 1.0000f, 0.7333f, 0.7255f};
	//Loop que gera as 5 faixas
	for (int i=0; i<5; i++){
		glColor3f(vr[i], vg[i], vb[i]);
		glVertex2f(-xsize_half, rain_y + i*0.15f);
		glVertex2f(-xsize_half, rain_y + (i+1)*0.15f);
		glVertex2f(rain_x -(i+1)*0.15f, ysize_half);
		glVertex2f(rain_x -i*0.15f, ysize_half);
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
	draw_background(X_SIZE, Y_SIZE, GRASS_FRAC);
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
do cata-vento quando o mouse e clicado, e faz com
que a tela seja atualizada
*/
void mouse_call(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN){
		//Incrementar ou decrementar o angulo em 5 graus
		angle += ((button==GLUT_LEFT_BUTTON) ? ANGLE_STEP : ((button==GLUT_RIGHT_BUTTON) ? -ANGLE_STEP : 0.0f));

		//Fazer com que a cena seja atualizada
		glutPostRedisplay();
	}
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
	glutDisplayFunc(&draw_all);

	glutMainLoop();
	return 0;
}