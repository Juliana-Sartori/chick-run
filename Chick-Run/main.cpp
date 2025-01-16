#ifdef __APPLE__
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

GLfloat posicaoX=0.8, posicaoY=0.7;
GLfloat posicaoCactos = 1.0f;
GLfloat velocidadeCactos = 0.0001f;
GLfloat posicaoPintinhoY = -0.19f;
GLfloat velocidadePulo = 0.0002f;
GLboolean emPulo = GL_FALSE;
GLfloat alturaMaxima = 0.7f;
GLboolean gameOver = GL_FALSE;
GLboolean marcador = GL_TRUE;
GLboolean mudarDia = GL_FALSE;
GLboolean dia = true;
int contadorPulos = 0;
bool gameIniciado = false;


void desenhaTexto(float x, float y, const char* texto){
    glPushMatrix();
        glRasterPos2f(x,y);
        while(*texto)
             glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*texto++);
	glPopMatrix();
}

void desenharQuadrado(float a, float b, float tam) {
    glBegin(GL_QUADS);
       glVertex2f(a, b);
       glVertex2f(a, b+tam);
       glVertex2f(a+tam, b+tam);
       glVertex2f(a+tam, b);
    glEnd();
}

void desenharRetangulo(float a, float b, float altura, float largura) {
     glBegin(GL_QUADS);
        glVertex2f(a, b);
        glVertex2f(a, b + altura);
        glVertex2f(a + largura, b + altura);
        glVertex2f(a + largura, b);
    glEnd();
}

void desenharCirculo(GLsizei numeroVertice){
     float angulo, incremento;
     incremento = (2 * M_PI) / numeroVertice;
     glBegin(GL_POLYGON);
         for(angulo=0; angulo<2*M_PI; angulo+=incremento){
            glVertex2f(cos(angulo), sin(angulo));
         }
     glEnd();
}

void desenharOlhoPintinhoVivo(){
    glPushMatrix();
         glPushAttrib(GL_CURRENT_BIT);
            glColor3f(0.0f, 0.0f, 0.0f);
            desenharQuadrado(-0.01f, 0.26f, 0.015f);
        glPopAttrib();
     glPopMatrix();
}

void desenharOlhoPintinhoMorto() {
    // perna do X : \.
    glPushMatrix();
        glPushAttrib(GL_CURRENT_BIT);
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslatef(0.009f, 0.26f, 0.0f);
            glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
            desenharRetangulo(-0.012f, 0.012f, 0.004f, 0.025f);
        glPopAttrib();
    glPopMatrix();

    // perna do X : /.
    glPushMatrix();
        glPushAttrib(GL_CURRENT_BIT);
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslatef(-0.009f, 0.26f, 0.0f);
            glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
            desenharRetangulo(-0.012f, 0.012f, 0.004f, 0.025f);
        glPopAttrib();
    glPopMatrix();
}

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

void desenharPintinho(){
    //corpinho
    glPushAttrib(GL_CURRENT_BIT);
        glColor3f(1.0f, 0.8706f, 0.3490f);
        desenharQuadrado(-0.05f, 0.2f, 0.091f);
    glPopAttrib();

    // desenhar o olho (vivo ou morto)
    if (gameOver) {
        desenharOlhoPintinhoMorto();
    } else {
        desenharOlhoPintinhoVivo();
    }

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

        if (posicaoPintinhoY >= alturaMaxima) {
            emPulo = GL_FALSE;
        }
    } else if (posicaoPintinhoY > -0.19f) {
        posicaoPintinhoY -= velocidadePulo;

        if (posicaoPintinhoY <= -0.19f) {
            posicaoPintinhoY = -0.19f;
        }
    }

    glutPostRedisplay();
}

void telaInstrucoes(){
    glClearColor(0.2627f, 0.4863f, 0.4941f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    desenhaTexto(-0.1f, 0.7f, "Chick Run");

        glPushMatrix();
            glTranslatef(0.0f, 0.05f, 0.0f);
            glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
            desenharPintinho();
        glPopMatrix();

    desenhaTexto(-0.2f, -0.2f, "Instrucoes de jogo:");
    desenhaTexto(-0.57f, -0.4f, "Pressionar a tecla 's' ou 'S' para dar start no jogo");
    desenhaTexto(-0.56f, -0.5f, "Pressionar a tecla 'r' ou 'R'  para resetar o jogo");
    desenhaTexto(-0.45f, -0.6f, "Pressionar a tecla 'esc' para sair do jogo");
    desenhaTexto(-0.55f, -0.7f, "Pressionar a tecla 'w' ou 'W' para pular os cactos");
    desenhaTexto(-0.97f, -0.8f, "Caso queira mudar de dia para noite e vice e versa manualmente pressione a tecla de 'espaco'");

	glFlush();
}

void verificarColisao() {
    // Limite do pintinho
    GLfloat pintinhoMinX = -0.8f;
    GLfloat pintinhoMaxX = pintinhoMinX + 0.1f;
    GLfloat pintinhoMinY = posicaoPintinhoY;
    GLfloat pintinhoMaxY = pintinhoMinY + 0.09f;

    // Limite do cacto
    GLfloat cactoMinX = posicaoCactos;
    GLfloat cactoMaxX = cactoMinX + 0.2f;
    GLfloat cactoMinY = -0.38f;
    GLfloat cactoMaxY = cactoMinY + 0.53f;

    if (posicaoCactos == 1.0f) {
        marcador = GL_TRUE;
    }

    if (pintinhoMaxX > cactoMinX && pintinhoMinX < cactoMaxX &&
        pintinhoMaxY > cactoMinY && pintinhoMinY < cactoMaxY) {
        gameOver = GL_TRUE;
    }

    GLfloat checkpointX = cactoMaxX + 0.001f;

    if (pintinhoMinX > checkpointX && marcador) {
        marcador = GL_FALSE;
        contadorPulos++;
        velocidadeCactos = velocidadeCactos + 0.00001f;

        if (velocidadePulo < 0.002f) {
            velocidadePulo = velocidadePulo + 0.00001;
        }
    }
}

void telaGameOver(){
    glClearColor(0.2627f, 0.4863f, 0.4941f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    desenhaTexto(-0.13f, 0.7f, "Game Over");

        glPushMatrix();
           glTranslatef(0.19f, 0.2f, 0.0f);
           glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
           desenharPintinho();
        glPopMatrix();

    std::string mensagemPontuacao = "Quantidade de cactos pulados: ";
    mensagemPontuacao += std::to_string(contadorPulos);

    desenhaTexto(-0.35f, -0.2f, mensagemPontuacao.c_str());

    desenhaTexto(-0.60f, -0.5f, "Pressione a tecla de 'r' ou 'R'  para resetar o jogo");
    desenhaTexto(-0.48f, -0.6f, "Pressione a tecla 'esc' para sair do jogo");

	glFlush();
}

#define NUM_ESTRELAS 100
static void desenharEstrelasAleatorias() {
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);

    for (int i = 0; i < NUM_ESTRELAS; i++) {
        GLfloat x = ((rand() % 2000) - 1000) / 1000.0f;
        GLfloat y = ((rand() % 1000)) / 1000.0f;
        glVertex2f(x, y);
    }
    glEnd();
}

void desenhandoCenario() {
    if (contadorPulos%10 == 1) {
        mudarDia = GL_TRUE;
    }

    if (contadorPulos%10 == 0 && mudarDia) {
        mudarDia = GL_FALSE;
        dia = !dia;
    }

     if (gameOver) {
        telaGameOver();
        return;
    }

    if(dia){
        // Gramado
        glPushMatrix();
            glColor3f(0.4353f, 0.7804f, 0.4392f);
            desenharRetangulo(-40.0f, -0.999f, 1.0f, 100.0f);
        glPopMatrix();

        // Pintinho
        glPushMatrix();
            glTranslatef(-0.8, posicaoPintinhoY, 0);
            desenharPintinho();
        glPopMatrix();

        // Cactos
        glPushMatrix();
            glTranslatef(posicaoCactos+0.45, -0.38, -0.5);
            desenharCactos();
        glPopMatrix();

        // Sol
        glPushMatrix();
            glTranslatef(posicaoX, posicaoY, 0);
            glScalef(0.1, 0.1 , 0.1);
            glColor3f(1.0f, 0.5686f, 0.3020f);
            desenharCirculo(20);
        glPopMatrix();
    }
    else{
        glPointSize(1.7f);
        desenharEstrelasAleatorias();

        // Gramado
        glPushMatrix();
            glColor3f(0.7451f, 0.5725f, 0.4627f);
            desenharRetangulo(-40.0f, -0.999f, 1.0f, 100.0f);
        glPopMatrix();

        // Pintinho
        glPushMatrix();
            glTranslatef(-0.8, posicaoPintinhoY, 0);
            desenharPintinho();
        glPopMatrix();

        // Cactos
        glPushMatrix();
            glTranslatef(posicaoCactos+0.45, -0.38, -0.5);
            desenharCactos();
        glPopMatrix();
    }

    std::string mensagemPontuacao = "Cactos pulados: ";
    mensagemPontuacao += std::to_string(contadorPulos);

    desenhaTexto(-0.9f, 0.8f, mensagemPontuacao.c_str());

    glFlush();
}

void display(){
    if(dia){
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }else{
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    if(gameIniciado){
        glPushMatrix();
            desenhandoCenario();
        glPopMatrix();
    }else{
        glPushMatrix();
          telaInstrucoes();
        glPopMatrix();
    }

    glutSwapBuffers();
}

void resetaConfigs() {
    posicaoCactos = 1.0f;
    posicaoPintinhoY = -0.19f;
    gameOver = GL_FALSE;
    gameIniciado = false;
    contadorPulos = 0;
    velocidadeCactos = 0.0001f;
    velocidadePulo = 0.0002f;
    GLboolean mudarDia = GL_FALSE;
}

static void key(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
    else if (key == 'w' || key == 'W') {
        if (posicaoPintinhoY == -0.19f && !gameOver) {
            emPulo = GL_TRUE;
        }
    }else if (key == 'r' || key == 'R') {
        resetaConfigs();
    }
    else if (key == 's' || key == 'S'){
        gameIniciado = true;
    }
    else if (key == 32 ) {
        dia = !dia;
        glutPostRedisplay();
    }
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(850, 600);
    glutInitWindowPosition(350, 100);

    glutCreateWindow("Chick Run");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);

    glutIdleFunc([]() {
         if (!gameOver) {
            posicaoCactos -= velocidadeCactos;
            if (posicaoCactos < -1.2f) posicaoCactos = 1.0f;
            atualizarPulo();
            verificarColisao();
        }
    });

    glutMainLoop();
    return 0;
}


