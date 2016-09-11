#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
int dx=0,dy=0,d0=0,sx=1,sy=1;
int S_width=640,S_height=480;
static void resize1(int width, int height)
{
    S_width=width;
    S_height=height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width/2,width/2,-height/2,height/2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT );//| GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(dx,dy,0);
    glScalef(sx,sy,0);
    glRotatef(d0*10,0,0,1);
    glBegin(GL_POLYGON);
        glColor3d(.5,0,.2);
        glVertex3f(-15,15,0);
        glVertex3f(-15,-15,0);
        glVertex3f(15,-15,0);
        glVertex3f(15,15,0);
    glEnd();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void splkey(int key, int x, int y)
{
    switch (key){
        case GLUT_KEY_RIGHT:
            dx+=5;
            break;

        case GLUT_KEY_LEFT:
            dx-=5;
            break;

        case GLUT_KEY_UP:
            dy+=5;
            break;

        case GLUT_KEY_DOWN:
            dy-=5;
            break;

        default:
         break;
    }
    glutPostRedisplay();
}
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'd':
            dx+=5;
            break;
        case 'a':
            dx-=5;
            break;
        case 'w':
            dy+=5;
            break;
        case 's':
            dy-=5;
            break;
        case '+':
            d0++;
            break;
        case '-':
            d0--;
            break;
        case '*':
            sx++;
            sy++;
            break;
        case '/':
            sx--;
            sy--;
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */

void myinit()
{
	glClearColor(0.8,0.8,0.8,1.0);
	glMatrixMode(GL_PROJECTION);
	glColor3f(1.0,0.0,0.0);
	glPointSize(7.0);
	gluOrtho2D(-100,100,-100,100);
	glMatrixMode(GL_MODELVIEW);

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(S_width,S_height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );//| GLUT_DEPTH);

    glutCreateWindow("Game");

    glutReshapeFunc(resize1);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(splkey);
    glutIdleFunc(idle);
    myinit();
//    generateLine();
    glutMainLoop();

    return EXIT_SUCCESS;
}
