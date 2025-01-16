#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

#include <cstdio> // Necessário para sprintf
#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>





//Controle da transla  o
GLfloat posicaoX=0.8, posicaoY=0.7;

GLfloat posicaoCactos = 1.0f; // Posição inicial dos cactos fora da tela (à direita)
GLfloat velocidadeCactos = 0.0001f; // Velocidade dos cactos (0,0001)
GLfloat posicaoPintinhoY = -0.19f;  // Posição inicial do pintinho no eixo Y
GLfloat velocidadePulo = 0.0002f;    // Velocidade do pulo (0.0005, qt menor o valor masi devagar ele pula)
GLboolean emPulo = GL_FALSE;       // Indica se o pintinho está no ar
GLfloat alturaMaxima = 0.7f;       // Altura máxima do pulo (0,8)

GLboolean gameOverFlag = GL_FALSE; // Indica o estado do jogo
GLboolean canScore = GL_TRUE;
GLboolean canChangeDay = GL_FALSE;

int contadorPulos = 0;
GLboolean dia = true;

bool gameIniciado = false;


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
void desenharOlhoPintinhoMortoANTIGO(){

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
                glColor3f(0.0f, 0.0f, 0.0f);
            // Segundo retângulo (diagonal inferior esquerda para superior direita)
                desenharRetangulo(-0.01f, 0.275f, -0.015f, 0.015f); // Note o ajuste em y para criar a diagonal
        glPopAttrib();
     glPopMatrix();

}

void desenharOlhoPintinhoMorto() {
    // Primeira diagonal do "X" (de cima à esquerda para baixo à direita)
    glPushMatrix();
        glPushAttrib(GL_CURRENT_BIT);
            glColor3f(0.0f, 0.0f, 0.0f); // Cor preta
            glTranslatef(0.009f, 0.26f, 0.0f); // Ajusta posição do olho para o pintinho
            glRotatef(45.0f, 0.0f, 0.0f, 1.0f); // Rotaciona para formar a diagonal
            desenharRetangulo(-0.012f, 0.012f, 0.004f, 0.025f); // Desenha a linha diagonal
        glPopAttrib();
    glPopMatrix();

    // Segunda diagonal do "X" (de cima à direita para baixo à esquerda)
    glPushMatrix();
        glPushAttrib(GL_CURRENT_BIT);
            glColor3f(0.0f, 0.0f, 0.0f); // Cor preta
            glTranslatef(-0.009f, 0.26f, 0.0f); // Ajusta posição do olho para o pintinho
            glRotatef(-45.0f, 0.0f, 0.0f, 1.0f); // Rotaciona para formar a outra diagonal
            desenharRetangulo(-0.012f, 0.012f, 0.004f, 0.025f); // Desenha outra linha diagonal
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

    // desenhar o olho (vivo ou morto)
    if (gameOverFlag) {
        // Se o jogo terminou, desenha o olho morto
        desenharOlhoPintinhoMorto();
    } else {
        // Caso contrário, desenha o olho vivo
        desenharOlhoPintinhoVivo();
    }
    /*--------------------
     //olho Vivo (if pintinho vivo (desenharOlhoPintinhoVivo)else{desenharOlhoPintinhoMorto})
     desenharOlhoPintinhoVivo();
    /* VOLTAR
     glPushMatrix();
        glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.02f, 0.1f, 0.0f);
        desenharOlhoPintinhoMorto();
     glPopMatrix();
---------------------------------*/
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
            glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
           desenharPintinho();
        glPopMatrix();


    desenhaTexto(-0.2f, -0.2f, "Instrucoes de jogo:");
    desenhaTexto(-0.57f, -0.4f, "Pressionar as teclas 's' ou 'S' para dar start no jogo");
    desenhaTexto(-0.57f, -0.5f, "Pressionar as teclas de 'r' ou 'R'  para resetar o jogo");
    desenhaTexto(-0.45f, -0.6f, "Pressionar a tecla 'esc' para sair do jogo");
    desenhaTexto(-0.55f, -0.7f, "Pressionar a tecla de 'w' ou 'W' para pular os cactos");
    desenhaTexto(-0.97f, -0.8f, "Caso queira mudar de dia para noite e vice e versa manualmente pressione a tecla de 'espaco'");

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
    GLfloat cactoMaxX = cactoMinX + 0.2f; // Largura do cacto       // MEXI AQUI
    GLfloat cactoMinY = -0.38f;
    GLfloat cactoMaxY = cactoMinY + 0.53f; // Altura do cacto       // MEXI AQUI

    // Se o cacto resetou, libera para pontuar
    if (posicaoCactos == 1.0f) {                   // MEXI AQUI
        canScore = GL_TRUE;
    }

    // Verifica sobreposição entre pintinho e cacto
    if (pintinhoMaxX > cactoMinX && pintinhoMinX < cactoMaxX &&
        pintinhoMaxY > cactoMinY && pintinhoMinY < cactoMaxY) {
        gameOverFlag = GL_TRUE; // Aciona o estado de "game over"
    }

    // Define uma "barreira" de checkpoint             // MEXI AQUI PRA BAIXO
    GLfloat checkpointX = cactoMaxX + 0.001f;

    // Verifica se o pintinho passou a barreira de checkpoint e atualiza se pode ou não contar ponto
    if (pintinhoMinX > checkpointX && canScore) {
        canScore = GL_FALSE;  // bloqueia para não contar mais que 1 ponto
        contadorPulos++;      // Aciona a pontuação
        velocidadeCactos = velocidadeCactos + 0.00001f;   // incrementa as velocidades
        if (velocidadePulo < 0.002f) {
            velocidadePulo = velocidadePulo + 0.00001;
        }
    }
}

//-----> tela de game over
void gameOver(){

 glClearColor(0.2627f, 0.4863f, 0.4941f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    desenhaTexto(-0.2f, 0.7f, "Game Over");

        glPushMatrix();
           glTranslatef(0.23f, 0.2f, 0.0f);
           glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
           desenharPintinho();
        glPopMatrix();


    std::string mensagemPontuacao = "Quantidade de cactos pulados: ";
    mensagemPontuacao += std::to_string(contadorPulos);

    desenhaTexto(-0.4f, -0.2f, mensagemPontuacao.c_str());

	glFlush();

}

#define NUM_ESTRELAS 100

static void desenharEstrelasAleatorias() {

    glColor3f(1.0f, 1.0f, 1.0f); //branca

    glBegin(GL_POINTS);

    for (int i = 0; i < NUM_ESTRELAS; i++) {
         GLfloat x = ((rand() % 2000) - 1000) / 1000.0f; // Faixa de -1.0 a 1.0
        GLfloat y = ((rand() % 1000)) / 1000.0f;
        glVertex2f(x, y);
    }
    glEnd();
}

//-----> tela de cenario
void desenhandoCenario() {
    if (contadorPulos%10 == 1) {
        canChangeDay = GL_TRUE;
    }

    if (contadorPulos%10 == 0 && canChangeDay) {
        canChangeDay = GL_FALSE;
        dia = !dia;     // inverte o boleano (se false vira true e vice versa)
    }

     if (gameOverFlag) {
        gameOver();
        return;
    }

    if(dia){
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
        //glPushMatrix();
        //    glTranslatef(posicaoCactos, -0.38, 0);
        //    desenharRetangulo(0.0f, 0.0f, 0.4f, 0.2f);  // REMOVER TUDO ISSO AQUI
       // glPopMatrix();

        // Cactos (posição dinâmica no eixo X)
        glPushMatrix();
            glTranslatef(posicaoCactos+0.45, -0.38, -0.5);    // MEXI AQUI
            desenharCactos();
        glPopMatrix();

        // Sol
        glPushMatrix();
            glTranslatef(posicaoX, posicaoY, 0);
            glScalef(0.1, 0.1 , 0.1);
            glColor3f(1.0f, 0.5686f, 0.3020f);
            desenharCirculo(20);
        glPopMatrix();
    }else{
       glPointSize(1.7f);
        desenharEstrelasAleatorias();

        // Gramado
        glPushMatrix();
            glColor3f(0.7451f, 0.5725f, 0.4627f);
            desenharRetangulo(-40.0f, -0.999f, 1.0f, 100.0f);
        glPopMatrix();

        // Pintinho (posição dinâmica no eixo Y)
        glPushMatrix();
            glTranslatef(-0.8, posicaoPintinhoY, 0);
            desenharPintinho();
        glPopMatrix();

        // Cactos (posição dinâmica no eixo X)
       // glPushMatrix();
        //    glTranslatef(posicaoCactos, -0.38, 0);      // REMOVER TUDO ISSO AQUI
          //----VOLTA  desenharCactos();
         //   desenharRetangulo(0.0f, 0.0f, 0.4f, 0.2f);
        //glPopMatrix();

        // Cactos (posição dinâmica no eixo X)
        glPushMatrix();
            glTranslatef(posicaoCactos+0.45, -0.38, -0.5);    // MEXI AQUI
            desenharCactos();
        glPopMatrix();
    }

     // Incrementa o contador de pulos ao iniciar um pulo
    //if (jumpedTheCactus) {
    //    contadorPulos++;
    //    jumpedTheCactus = GL_FALSE;
   // }

    // Mostra o número de cactos pulados
    char texto[50];
    sprintf(texto, "Cactos pulados: %d", contadorPulos);
    desenhaTexto(-0.9f, 0.8f, texto);

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

    if(dia){
          glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    }else{
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //preto

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

/*-------------------------------------  AQUI FICA
-------------------------------------    */
    //gameOver();

    /* glPushMatrix();
          telaInstrucoes();
    glPopMatrix();

    glPushMatrix();
          gameOver();
    glPopMatrix();

*/
glutSwapBuffers();
}

void resetaConfigs() {
    posicaoCactos = 1.0f;
    posicaoPintinhoY = -0.19f;
    gameOverFlag = GL_FALSE;
    gameIniciado = false;
    contadorPulos = 0;
    velocidadeCactos = 0.0001f;
    velocidadePulo = 0.0002f;
    GLboolean canChangeDay = GL_FALSE;
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
        resetaConfigs();  // MEXI AQUI
        //posicaoCactos = 1.0f;
        //posicaoPintinhoY = -0.19f;
        //gameOverFlag = GL_FALSE;
        // gameIniciado = false;
         //contadorPulos = 0;
    }
    else if (key == 's' || key == 'S'){
           gameIniciado = true;
    }
    else if (key == 32 ) { // Tecla espaço
        dia = !dia;
        glutPostRedisplay(); // Atualiza a tela
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


