#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

//Controle da transla  o
GLfloat posicaoX=0.8, posicaoY=0.7;

GLfloat posicaoCactos = 1.0f; // Posição inicial dos cactos fora da tela (à direita)
GLfloat velocidadeCactos = 0.0001f; // Velocidade dos cactos (0,0001)
GLfloat posicaoPintinhoY = -0.19f;  // Posição inicial do pintinho no eixo Y
GLfloat velocidadePulo = 0.0002f;    // Velocidade do pulo (0.0005, qt menor o valor masi devagar ele pula)
GLboolean emPulo = GL_FALSE;       // Indica se o pintinho está no ar
GLfloat alturaMaxima = 0.7f;       // Altura máxima do pulo (0,8)

GLboolean gameOverFlag = GL_FALSE; // Indica o estado do jogo

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
     glPopMatrix();


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

     glPopMatrix();
}

void atualizarCactosCALMA() {
    posicaoCactos -= velocidadeCactos; // Movimenta os cactos para a esquerda

    // Reinicia a posição dos cactos quando saem da tela
    if (posicaoCactos < -1.2f) {
        posicaoCactos = 1.0f; // Volta para o lado direito
    }

    glutPostRedisplay(); // Solicita a atualização da tela
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

void atualizarPulo() {
    if (emPulo) {
        posicaoPintinhoY += velocidadePulo;

        // Verifica se atingiu a altura máxima
        if (posicaoPintinhoY >= alturaMaxima) {
            emPulo = GL_FALSE; // Inicia descida
        }
    } else if (posicaoPintinhoY > -0.19f) {
        // Descendo
        posicaoPintinhoY -= velocidadePulo;

        // Verifica se voltou ao chão
        if (posicaoPintinhoY <= -0.19f) {
            posicaoPintinhoY = -0.19f; // Corrige posição
        }
    }

    glutPostRedisplay(); // Atualiza a tela
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

// -----> verificando colisão
void verificarColisao() {
    // Define os limites do pintinho
    GLfloat pintinhoMinX = -0.8f; // Posição fixa no eixo X
    GLfloat pintinhoMaxX = pintinhoMinX + 0.1f; // Tamanho do pintinho no eixo X
    GLfloat pintinhoMinY = posicaoPintinhoY;
    GLfloat pintinhoMaxY = pintinhoMinY + 0.09f;

    // Define os limites do cacto
    GLfloat cactoMinX = posicaoCactos;
    GLfloat cactoMaxX = cactoMinX + 0.2f; // Largura do cacto
    GLfloat cactoMinY = -0.38f;
    GLfloat cactoMaxY = cactoMinY + 0.4f; // Altura do cacto

    // Verifica sobreposição entre pintinho e cacto
    if (pintinhoMaxX > cactoMinX && pintinhoMinX < cactoMaxX &&
        pintinhoMaxY > cactoMinY && pintinhoMinY < cactoMaxY) {
        gameOverFlag = GL_TRUE; // Aciona o estado de "game over"
    }
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

//-----> tela de cenario
void desenhandoCenario() {

     if (gameOverFlag) {
        gameOver();
        return;
    }

    // Gramado
    glPushMatrix();
        glColor3f(0.4353f, 0.7804f, 0.4392f);
        desenharRetangulo(-40.0f, -0.999f, 1.0f, 100.0f);
    glPopMatrix();

    // Pintinho (posição dinâmica no eixo Y)
    glPushMatrix();
        glTranslatef(-0.8, posicaoPintinhoY, 0);
        desenharPintinho();
    glPopMatrix();

    // Cactos (posição dinâmica no eixo X)
    glPushMatrix();
        glTranslatef(posicaoCactos, -0.38, 0);
      //----VOLTA  desenharCactos();
        desenharRetangulo(0.0f, 0.0f, 0.4f, 0.2f);
    glPopMatrix();

    // Sol
    glPushMatrix();
        glTranslatef(posicaoX, posicaoY, 0);
        glScalef(0.1, 0.1 , 0.1);
        glColor3f(1.0f, 0.5686f, 0.3020f);
        desenharCirculo(20);
    glPopMatrix();

    glFlush();
}

void verificarColisaoNAO() {
    // Dimensões do pintinho (aproximadas)
    GLfloat alturaPintinho = 0.05f;
    GLfloat larguraPintinho = 0.02;
    GLfloat pintinhoX = -0.9f; // Posição fixa no eixo X
    GLfloat pintinhoY = posicaoPintinhoY;

    // Dimensões dos cactos (aproximadas como um retângulo)
    GLfloat larguraCacto = 0.4f; // Largura total dos cactos
    GLfloat alturaCacto = 0.6f;  // Altura total dos cactos
    GLfloat cactoX = posicaoCactos;
    GLfloat cactoY = -0.8f; // Posição fixa no eixo Y

    // Imprimir limites para depuração
    GLfloat pintinhoDireita = pintinhoX + larguraPintinho;
    GLfloat pintinhoEsquerda = pintinhoX;
    GLfloat pintinhoCima = pintinhoY + alturaPintinho;
    GLfloat pintinhoBaixo = pintinhoY;

    GLfloat cactoDireita = cactoX + larguraCacto;
    GLfloat cactoEsquerda = cactoX;
    GLfloat cactoCima = cactoY + alturaCacto;
    GLfloat cactoBaixo = cactoY;

  //  printf("Pintinho: direita=%f, esquerda=%f, cima=%f, baixo=%f\n", pintinhoDireita, pintinhoEsquerda, pintinhoCima, pintinhoBaixo);
  //  printf("Cacto: direita=%f, esquerda=%f, cima=%f, baixo=%f\n", cactoDireita, cactoEsquerda, cactoCima, cactoBaixo);

    // Verifica colisão entre os limites do pintinho e do cacto
    GLboolean colidiu =
        pintinhoX < cactoX + larguraCacto &&  // Lado direito do pintinho toca o cacto
        pintinhoX + larguraPintinho > cactoX && // Lado esquerdo do pintinho toca o cacto
        pintinhoY < cactoY + alturaCacto &&  // Parte superior do pintinho toca o cacto
        pintinhoY + alturaPintinho > cactoY; // Parte inferior do pintinho toca o cacto

    if (colidiu) {
     //   printf("Colisão detectada!\n");
        gameOver(); // Chama a tela de Game Over
        // exit(0); // Encerra o jogo (removido para depuração)
    } else {
   //     printf("Sem colisão.\n");

    }
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
 //   glPushMatrix();
         desenhandoCenario();
  //  glPopMatrix();

}


//-----> eventos do teclado
static void key(unsigned char key, int x, int y) {
    if (key == 27) // Tecla 'ESC'
        exit(0);
    else if (key == 'w' || key == 'W') {
        if (posicaoPintinhoY == -0.19f && !gameOverFlag) {
            emPulo = GL_TRUE; // Inicia o pulo
        }
    }else if (key == 'r' || key == 'R') {
        // Reinicia o jogo
        posicaoCactos = 1.0f;
        posicaoPintinhoY = -0.19f;
        gameOverFlag = GL_FALSE;
    }
}


int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(350, 100);

    glutCreateWindow("Chick Run");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);

    // Registra funções de animação contínua
    glutIdleFunc([]() {
         if (!gameOverFlag) {
            posicaoCactos -= velocidadeCactos;
            if (posicaoCactos < -1.2f) posicaoCactos = 1.0f; // Reseta cacto
            atualizarPulo();
            verificarColisao(); // Verifica colisão continuamente
        }
    });

    glutMainLoop();
    return 0;
}



// Programa Principal

