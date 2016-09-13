#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
int dx=0,dy=0,d0=0;
float ss=1;
int S_width=640,S_height=480;
void drawSmBox()
{
     glPushMatrix();
    glTranslatef(dx,dy,0);
    glScalef(ss,ss,0);
    glRotatef(d0*10,0,0,1);
    glBegin(GL_POLYGON);
        glColor3d(.5,0,.2);
        glVertex3f(-15,15,0);
        glVertex3f(-15,-15,0);
        glVertex3f(15,-15,0);
        glVertex3f(15,15,0);
    glEnd();
    glPopMatrix();
}
static void resize1(int width, int height)
{
    glClearColor(0.8,0.8,0.8,1.0);
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
    drawSmBox();
    glFlush();
    glutSwapBuffers();
}

static void splkey(int key, int x, int y)
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
            ss+=.2;
            break;
        case '/':
            ss-=.2;
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
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
    glutMainLoop();

    return EXIT_SUCCESS;
}
