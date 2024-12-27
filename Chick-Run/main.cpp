#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

//Controle da transla  o
GLfloat posicaoX=0.8, posicaoY=0.7;

//-----> desenhando texto na janela
void desenhaTexto(float x, float y, const char* texto)
{
  	glPushMatrix();
        // Posição do texto
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
//-----> desenhando circulo
void desenharCirculo(GLsizei numeroVertice){
     float angulo, incremento;
     incremento = (2 * M_PI) / numeroVertice;
     glBegin(GL_POLYGON);
         for(angulo=0; angulo<2*M_PI; angulo+=incremento){
            glVertex2f(cos(angulo), sin(angulo));
         }
     glEnd();
}

//-----> desenhando o olho do pintinho VIVO
void desenharOlhoPintinhoVivo(){

    glPushMatrix();
         glPushAttrib(GL_CURRENT_BIT);
            glColor3f(0.0f, 0.0f, 0.0f);
            desenharQuadrado(-0.01f, 0.26f, 0.015f);
        glPopAttrib();
     glPopMatrix();
}

//-----> desenhando o olho do pintinho MORTO
void desenharOlhoPintinhoMorto(){
/*
    glPushMatrix();
         glPushAttrib(GL_CURRENT_BIT);
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslatef(0.25f, 0.25f, 0.0f);
            glRotatef(90.0f, -0.01f, 0.26f, 1.0f);
            desenharRetangulo(-0.01f, 0.26f, 0.005f, 0.026f);
        glPopAttrib();
     glPopMatrix();

     glPushMatrix();
         glPushAttrib(GL_CURRENT_BIT);
            glColor3f(1.0f, 0.0f, 1.0f);
            glTranslatef(0.0015f, 0.5f, 0.0f);
            glRotatef(180.0f, -0.01f, 0.26f, 1.0f);
            desenharRetangulo(-0.01f, 0.26f, 0.005f, 0.026f);
        glPopAttrib();
     glPopMatrix();*/

     /*
      glPushMatrix();
         glPushAttrib(GL_CURRENT_BIT);
            glColor3f(0.0f, 0.0f, 0.0f);

            // Primeiro retângulo (diagonal superior esquerda para inferior direita)
            desenharRetangulo(-0.01f, 0.26f, 0.015f, 0.015f);

            glPopAttrib();
     glPopMatrix();

           glPushMatrix();
                glPushAttrib(GL_CURRENT_BIT);
                glColor3f(1.0f, 0.0f, 1.0f);
            // Segundo retângulo (diagonal inferior esquerda para superior direita)
                desenharRetangulo(-0.01f, 0.275f, -0.015f, 0.015f); // Note o ajuste em y para criar a diagonal
        glPopAttrib();
     glPopMatrix();
     */
}
//-----> desenhando os cactos
void desenharCactos(){

    //parte do meio
    glPushMatrix();
         glPushAttrib(GL_CURRENT_BIT);
            glColor3f(0.3529f, 0.5490f, 0.4549f);
            glTranslatef(0.21f, 0.135f, 0.0f);
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            desenharRetangulo(0.2f, 0.6f, 0.03f, 0.4f);
        glPopAttrib();
    glPopMatrix();

    //vertical direita
    glPushMatrix();
         glPushAttrib(GL_CURRENT_BIT);
            glColor3f(0.3529f, 0.5490f, 0.4549f);
            glTranslatef(0.27f, 0.25f, 0.0f);
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            desenharRetangulo(0.2f, 0.6f, 0.03f, 0.2f);
        glPopAttrib();
    glPopMatrix();

    //horizontal direita
    glPushMatrix();
         glPushAttrib(GL_CURRENT_BIT);
            glColor3f(0.3529f, 0.5490f, 0.4549f);
            glTranslatef(-0.13f, 1.09f, 0.0f);
            glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
            desenharRetangulo(0.2f, 0.6f, 0.04f, 0.15f);
        glPopAttrib();
    glPopMatrix();

    //vertical esquerda
    glPushMatrix();
         glPushAttrib(GL_CURRENT_BIT);
            glColor3f(0.3529f, 0.5490f, 0.4549f);
            glTranslatef(0.15f, 0.25f, 0.0f);
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            desenharRetangulo(0.2f, 0.6f, 0.03f, 0.16f);
        glPopAttrib();
    glPopMatrix();

}
//-----> desenhando o pintinho
void desenharPintinho(){

    //corpinho
    glPushAttrib(GL_CURRENT_BIT);
        glColor3f(1.0f, 0.8706f, 0.3490f);
        desenharQuadrado(-0.05f, 0.2f, 0.091f);
    glPopAttrib();

     //olho Vivo (if pintinho vivo (desenharOlhoPintinhoVivo)else{desenharOlhoPintinhoMorto})
     desenharOlhoPintinhoVivo();
    /* VOLTAR
     glPushMatrix();
        glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.02f, 0.1f, 0.0f);
        desenharOlhoPintinhoMorto();
     glPopMatrix();
*/
    //bico
    glPushMatrix();
        glPushAttrib(GL_CURRENT_BIT);
            glColor3f(1.0f, 0.5686f, 0.3020f);
            desenharRetangulo(0.02f, 0.24f, 0.023f, 0.03f);
        glPopAttrib();
     glPopMatrix();

    //patinha esquerda
    glPushMatrix();
         glPushAttrib(GL_CURRENT_BIT);
            glColor3f(1.0f, 0.5686f, 0.3020f);
            glTranslatef(0.21f, 0.135f, 0.0f);
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            desenharRetangulo(0.02f, 0.24f, 0.02f, 0.045f);
        glPopAttrib();
    glPopMatrix();

    //patinha direita
     glPushMatrix();
         glPushAttrib(GL_CURRENT_BIT);
            glColor3f(1.0f, 0.5686f, 0.3020f);
            glTranslatef(0.28f, 0.135f, 0.0f);
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            desenharRetangulo(0.02f, 0.24f, 0.02f, 0.045f);
        glPopAttrib();
     glPopMatrix();
}


//-----> tela de instruçoes
void telaInstrucoes(){

 glClearColor(0.2627f, 0.4863f, 0.4941f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    desenhaTexto(-0.1f, 0.7f, "Chick Run");

        glPushMatrix();
          glTranslatef(-0.05f, 0.2f, 0.0f);
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
           desenharPintinho();
        glPopMatrix();


    desenhaTexto(-0.2f, -0.2f, "Instrucoes de jogo:");
    desenhaTexto(-0.65f, -0.4f, "Pressionar a tecla de 'espaco' para pular os cactos");
    desenhaTexto(-0.65f, -0.5f, "Pressionar a tecla 'esc' para sair do jogo");
    desenhaTexto(-0.65f, -0.6f, "Pressionar as teclas de 'r' ou 'R'  para resetar o jogo");
    desenhaTexto(-0.65f, -0.7f, "Pressionar as teclas 's' ou 'S' para dar start no jogo");

	glFlush();

}

//-----> tela de cenario
void desenhandoCenario(){

    //gramado
    glPushMatrix();
        glColor3f(0.4353f, 0.7804f, 0.4392f);
        desenharRetangulo(-40.0f, -0.999f, 1.0f, 100.0f);
    glPopMatrix();


    //pintinho
    glPushMatrix();
        glTranslatef(-0.8, -0.19, 0);
        desenharPintinho();
    glPopMatrix();

    //cactos
    glPushMatrix();
        glTranslatef(0.1, -0.38, 0);
        desenharCactos();
    glPopMatrix();

    //sol
    glPushMatrix();
        glTranslatef(posicaoX, posicaoY, 0);
        glScalef(0.1, 0.1 , 0.1);
        glColor3f(1.0f, 0.8706f, 0.3490f);
        desenharCirculo(20);
    glPopMatrix();

    /*
    //linha
    glPushMatrix();
        glLineWidth(1.5f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
           glVertex2i(40, 0);
           glVertex2i(-40, 0);
        glEnd();
    glPopMatrix();
*/
  glFlush();
}

//-----> tela de game over
void gameOver(){

 glClearColor(0.2627f, 0.4863f, 0.4941f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    desenhaTexto(-0.1f, 0.7f, "Game Over");

        glPushMatrix();
           glTranslatef(0.23f, 0.2f, 0.0f);
           glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
           desenharPintinho();
        glPopMatrix();


    desenhaTexto(-0.2f, -0.2f, "Score:");

	glFlush();

}

//-----> janela de visualizacao
void display(){

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

/*
     glPushMatrix();
          telaInstrucoes();
    glPopMatrix();

    glPushMatrix();
          gameOver();
    glPopMatrix();
*/
    glPushMatrix();
         desenhandoCenario();
    glPopMatrix();

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
