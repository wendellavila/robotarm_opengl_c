#include <GL/glut.h>
#include <stdlib.h>

/***********************************************************************************************
*  
*     Autor: Wendell João Castro de Ávila
*     RA: 2017.1.08.013
*     Disciplina: Computação Gráfica
*     Data: 30/10/12
*
************************************************************************************************/

/***********************************************************************************************
*     Comandos:
*     
*     BRAÇO: 
*
*		W / S : Subir/descer cotovelo
*     A / D : Girar antebraço para esquerda/direita
*     Q / E : Subir/descer braço
*     MOUSE PRIMARIO/SECUNDARIO : Abrir/Fechar dedos
*
*     OBSERVADOR:
*
*     RODA MOUSE FRENTE/TRAS : Zoom In/Out
*     SETA ESQ / SETA DIR :	 Girar observador ao redor
*     SETA CIMA / SETA BAIXO : Subir / descer observador
*     
************************************************************************************************/

static int shoulderY = 45, shoulderZ = 0, elbow = 90, hand = 90, finger = 0, angleRot = 0;

GLfloat angle, fAspect;
GLfloat obs[3]={0.0,0.0,6.0};//posicao do observador

// Inicializa parâmetros de rendering
void init(void){
   glClearColor (0.85, 0.85, 0.85, 0.0);
   glShadeModel (GL_FLAT);
   angle = 100.0;
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void){
   //projeção
   glMatrixMode(GL_PROJECTION); //especifica sistema de coordenadas
   glLoadIdentity(); //inicializa sistema de coordenadas
   gluPerspective(angle,fAspect,1.0,20); //especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)

   //modelo
   glMatrixMode(GL_MODELVIEW); //especifica sistema de coordenadas
   glLoadIdentity(); //inicializ sistema de coordenadas

   //Especifica posição do observador e do alvo
   gluLookAt(obs[0],obs[1],obs[2], 0,0,0, 0,1,0);
}

// Desenhar objetos
void display(void){
   GLUquadricObj *quadric;
   glClear (GL_COLOR_BUFFER_BIT);
   
   //chao
   glRotatef((GLfloat) angleRot, 0.0, 1.0, 0.0); //rotaçao observador em torno de y
   glPushMatrix();
   glColor3f(0.1f, 0.1f, 0.1f);
   glScalef (10.0, 0.1, 10.0);
   glTranslatef (0.0, -25.0, 0.0);
   glutSolidCube (1.0);
   glPopMatrix();

   //base
   glColor3f(0.9f, 0.9f, 0.3f);
   glPushMatrix();
   glTranslatef (0.0, -4.0, 0.0);
   glRotatef (90, 0.0, 0.0, 1.0);
   glTranslatef (1.5, 0.0, 0.0);
   glPushMatrix();
   glScalef (0.5, 2.0, 2.0);
   glutSolidCube (1.0);
   glPopMatrix();

   //antebraço
   glColor3f(0.2f, 0.2f, 0.7f);
   glRotatef ((GLfloat) shoulderY, 1.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulderZ, 0.0, 0.0, 1.0);
   glPushMatrix();
   glTranslatef (0.2, 0.0, 0.0);
   glScalef (2.5, 0.4, 0.35);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //colocar cilidro no eixo y
   quadric=gluNewQuadric(); 
   gluCylinder(quadric, 0.5, 0.5, 1.2, 12, 3);
   glPopMatrix();

   //braço
   glColor3f(0.7f, 0.7f, 0.7f);
   glTranslatef (3.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   //glTranslatef (1.5, -1.5, 0.0);
   glPushMatrix();
   glScalef (2.5, 0.4, 0.35);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //colocar cilidro no eixo y
   quadric=gluNewQuadric(); 
   gluCylinder(quadric, 0.5, 0.5, 1.2, 12, 3);
   glPopMatrix();

   //mao
   glColor3f(0.9f, 0.2f, 0.2f);
   glTranslatef (3.0, 0.0, 0.0);
   glRotatef ((GLfloat) hand, 0.0, 0.0, 1.0);
   glPushMatrix();
   glScalef (0.4, 0.8, 0.8);
   glutSolidCube (1.0);
   glPopMatrix();

   //dedos
   glColor3f(0.2f, 0.2f, 0.2f);
   //1
   glPushMatrix();
   glRotatef ((GLfloat) finger, 0.0, 0.0, 1.0);
   glTranslatef (0.0, -0.3, 0.0);
   glScalef (0.6, 0.1, 0.1);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //colocar cilidro no eixo y
   quadric=gluNewQuadric(); 
   gluCylinder(quadric, 0.5, 0.5, 1.0, 12, 3);
   glPopMatrix();
   //2
   glPushMatrix();
   glRotatef ((GLfloat) finger, 0.0, -1.0, -1.0);
   glTranslatef (0.0, 0.2, -0.3);
   glScalef (0.6, 0.1, 0.1);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //colocar cilidro no eixo y
   quadric=gluNewQuadric(); 
   gluCylinder(quadric, 0.5, 0.5, 1.0, 12, 3);
   glPopMatrix();
   //3
   glPushMatrix();
   glRotatef ((GLfloat) finger, 0.0, 1.0, -1.0);
   glTranslatef (0.0, 0.2, 0.3);
   glScalef (0.6, 0.1, 0.1);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //colocar cilidro no eixo y
   quadric=gluNewQuadric(); 
   gluCylinder(quadric, 0.5, 0.5, 1.0, 12, 3);
   glPopMatrix();


   glPopMatrix();
   glutSwapBuffers();
}

// Função callback chamada quando o tamanho da janela é alterado 
void reshape (int w, int h){
   glViewport (0, 0, (GLfloat) w, (GLfloat) h);

   // Para previnir uma divisão por zero
   if (h == 0)
      h = 1;
   // Calcula a correção de aspecto
   fAspect = (GLfloat)w/(GLfloat)h;
   EspecificaParametrosVisualizacao();
}

// Gerenciar eventos do teclado
void keyboard (unsigned char key, int x, int y){
   switch (key){
   //movimentação braço em torno de Y
   case 'D':
   case 'd':
      shoulderY = (shoulderY + 5) % 360;
      break;
   case 'A':
   case 'a':
      shoulderY = (shoulderY - 5) % 360;
      break;
   //movimentação cotovelo
   case 'W':
   case 'w':
      if(shoulderZ < 90){
         shoulderZ = (shoulderZ + 5) % 360;
         elbow = (elbow - 5) % 360;
      }
      break;
   case 'S':
   case 's':
      if(shoulderZ > -45){
         shoulderZ = (shoulderZ - 5) % 360;
         elbow = (elbow + 5) % 360;
      }
      break;
   //movimentação antebraço
   case 'Q':
   case 'q':
      if(elbow < 135){
         elbow = (elbow + 5) % 360;
         hand = (hand - 5) % 360; //manter mao sempre para baixo
      }
      break;
   case 'E':
   case 'e':
      if(elbow > 0){
         elbow = (elbow - 5) % 360;
         hand = (hand + 5) % 360; //manter mao sempre para baixo
      }
      break;
   //movimentação dedos
   case 'Z':
   case 'z':
      if(finger < 30){
         finger = (finger + 5) % 360;
      }
      break;
   case 'X':
   case 'x':
      if(finger > 0){
         finger = (finger - 5) % 360;
      }
      break;
   //sair
   case 27:
      exit(0);
      break;
   }
   EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void special(int key, int x, int y){
	switch (key) {
	//movimentação observador cima/baixo
	case GLUT_KEY_UP:
		obs[1]=obs[1]+1;
		break;
	case GLUT_KEY_DOWN:
		obs[1] =obs[1]-1;
		break;
	//movimentação observador girar
	case GLUT_KEY_LEFT:
		angleRot = (angleRot - 5) % 360;
		break;
	case GLUT_KEY_RIGHT:
		angleRot = (angleRot + 5) % 360;
		break;
	}
	EspecificaParametrosVisualizacao();
   glutPostRedisplay();
}

// Gerenciar eventos do mouse
void mouse(int button, int state, int x, int y){
   //movimentação observador zoom in/zoom out
   if(button == 3)
      if(angle >= 30){
         angle -= 5;
      }
   if(button == 4)
      if(angle <= 130){
         angle += 5;
      }

	if(button == GLUT_LEFT_BUTTON)
      while(finger < 25){
         finger = (finger + 5) % 360;
      }
   if(button == GLUT_RIGHT_BUTTON)
      while(finger > 0){
         finger = (finger - 5) % 360;
      }
   EspecificaParametrosVisualizacao();
   glutPostRedisplay();
}

int main(int argc, char** argv){
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (800, 600); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Braco Robotico");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
   glutMouseFunc(mouse);
   glutMainLoop();
   return 0;
}
