#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

//-----> desenhando texto na janela
void desenhaTexto(float x, float y, const char* texto)
{
  	glPushMatrix();
        // Posi��o do texto
        glRasterPos2f(x,y);

        while(*texto)
             glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*texto++);
	glPopMatrix();
}


//-----> desenhando quadrado
void desenharQuadrado(float a, float b, float tam) {
    glBegin(GL_QUADS);
       glVertex2f(a, b);
       glVertex2f(a, b+tam);
       glVertex2f(a+tam, b+tam);
       glVertex2f(a+tam, b);
    glEnd();
}

//-----> desenhando retangulo
void desenharRetangulo(float a, float b, float altura, float largura) {
     glBegin(GL_QUADS);
        glVertex2f(a, b);                        // Canto inferior esquerdo
        glVertex2f(a, b + altura);               // Canto superior esquerdo
        glVertex2f(a + largura, b + altura);     // Canto superior direito
        glVertex2f(a + largura, b);             // Canto inferior direito
    glEnd();
}

//-----> desenhando o pintinho
void desenharPintinho(){

    //corpinho
    glPushAttrib(GL_CURRENT_BIT); // Salva o estado atual da cor
        glColor3f(1.0f, 1.0f, 0.0f); // Define a cor para amarelo
        desenharQuadrado(-0.05f, 0.2f, 0.091f);
    glPopAttrib(); // Restaura o estado anterior da cor

     //olho
     glPushMatrix();
         glPushAttrib(GL_CURRENT_BIT);
            glColor3f(0.0f, 0.0f, 0.0f);
            desenharQuadrado(-0.01f, 0.26f, 0.015f);
        glPopAttrib();
     glPopMatrix();

    //bico
    glPushMatrix();
        glPushAttrib(GL_CURRENT_BIT);
            glColor3f(1.0f, 0.647f, 0.0f);
            desenharRetangulo(0.02f, 0.24f, 0.023f, 0.03f);
        glPopAttrib();
     glPopMatrix();

    //patinha esquerda
    glPushMatrix();
         glPushAttrib(GL_CURRENT_BIT);
            glColor3f(1.0f, 0.647f, 0.0f);
            glTranslatef(0.21f, 0.135f, 0.0f);
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            desenharRetangulo(0.02f, 0.24f, 0.02f, 0.045f);
        glPopAttrib();
    glPopMatrix();

    //patinha direita
     glPushMatrix();
         glPushAttrib(GL_CURRENT_BIT);
            glColor3f(1.0f, 0.647f, 0.0f);
            glTranslatef(0.28f, 0.135f, 0.0f);
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            desenharRetangulo(0.02f, 0.24f, 0.02f, 0.045f);
        glPopAttrib();
     glPopMatrix();
}

//-----> janela de visualizacao
void display(){

    glClearColor(0.2627f, 0.4863f, 0.4941f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    desenhaTexto(-0.1f, 0.7f, "Chick Run");

        glPushMatrix();
           desenharPintinho();
        glPopMatrix();


    desenhaTexto(-0.2f, -0.2f, "Instrucoes de jogo:");
    desenhaTexto(-0.65f, -0.4f, "Pressionar a tecla de 'espaco' para pular os cactos");
    desenhaTexto(-0.65f, -0.5f, "Pressionar a tecla 'esc' para sair do jogo");
    desenhaTexto(-0.65f, -0.6f, "Pressionar as teclas de 'r' ou 'R'  para resetar o jogo");
    desenhaTexto(-0.65f, -0.7f, "Pressionar as teclas 's' ou 'S' para dar start no jogo");

	glFlush();
}


//-----> eventos do teclado
static void key(unsigned char key, int x, int y){
	if (key == 27)
		exit(0);
}


// Programa Principal
int main(int argc, char *argv[]){
    // utilizada para inicializar a biblioteca GLUT
    glutInit(&argc, argv);

	// define do modo de opera  o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);


    glutInitWindowSize(800, 600);
    glutInitWindowPosition(350, 100);



	// cria a janela passando como t tulo como argumento
	glutCreateWindow("Chick Run");

	// registra a fun  o callback de redesenho da janela de visualiza  o
	glutDisplayFunc(display);

	// registra a fun  o callback para tratar os eventos do teclado
	glutKeyboardFunc(key);

	// Registra a fun  o callback para tratamento das teclas Especiais
	//glutSpecialFunc(specialkey);

	// registra a fun  o callback de redimensionamento da janela de visualiza  o
	//glutReshapeFunc(resize);

	// chama a fun  o respons vel por fazer as inicializa  es
	//setup();

	// inicia o processamento e aguarda intera  es do usu rio
	glutMainLoop();

    return 0;
}
