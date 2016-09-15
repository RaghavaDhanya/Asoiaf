#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
//int
float ss=1,dx=0,dy=0,d0=0;
/* keys[]={up,down,left,right,+,-,*,/} */
bool keys[]={false,false,false,false,false,false,false,false};
int S_width=640,S_height=480;
int LastUpdateTime=0;
void update()
{
    dy=(dy+=5*int(keys[0]))>(S_height/2-15*ss)?(S_height/2-15*ss):dy;
    dy=(dy-=5*int(keys[1]))<(-S_height/2+15*ss)?(-S_height/2+15*ss):dy;
    dx=(dx-=5*int(keys[2]))<(-S_width/2+15*ss)?(-S_width/2+15*ss):dx;
    dx=(dx+=5*int(keys[3]))>(S_width/2-15*ss)?(S_width/2-15*ss):dx;
    d0+=int(keys[4]);
    d0-=int(keys[5]);
    ss+=.2*int(keys[6]);
    ss-=.2*int(keys[7]);
}
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
void timer(int value)
{
    int CurrentTime=glutGet(GLUT_ELAPSED_TIME);
    if((CurrentTime-LastUpdateTime)<20)
        glutTimerFunc(5, timer, 0);
    else
    {
        LastUpdateTime=CurrentTime;
        update();
        glutPostRedisplay();
    }
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
   // update();
    drawSmBox();
    glFlush();
    glutSwapBuffers();
}

static void splkey(int key, int x, int y)
{
    switch (key){
        case GLUT_KEY_RIGHT:
            keys[3]=true;
            break;

        case GLUT_KEY_LEFT:
            keys[2]=true;
            break;

        case GLUT_KEY_UP:
            keys[0]=true;
            break;

        case GLUT_KEY_DOWN:
            keys[1]=true;
            break;
    }
    glutTimerFunc(0,timer,0);
    //glutPostRedisplay();
}
static void splkeyup(int key, int x, int y)
{
    switch (key){
        case GLUT_KEY_RIGHT:
            keys[3]=false;
            break;

        case GLUT_KEY_LEFT:
            keys[2]=false;
            break;

        case GLUT_KEY_UP:
            keys[0]=false;
            break;

        case GLUT_KEY_DOWN:
            keys[1]=false;
            break;
    }
    glutTimerFunc(0,timer,0);
   // glutPostRedisplay();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
        case 'q':
            exit(0);
            break;
        case 'd':
            keys[3]=true;
            break;
        case 'a':
            keys[2]=true;
            break;
        case 'w':
            keys[0]=true;
            break;
        case 's':
            keys[1]=true;
            break;
        case '+':
            keys[4]=true;
            break;
        case '-':
            keys[5]=true;
            break;
        case '*':
            keys[6]=true;
            break;
        case '/':
            keys[7]=true;
            break;
    }

    glutTimerFunc(0,timer,0);
    //glutPostRedisplay();
}
static void keyup(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
        case 'q':
            exit(0);
            break;
        case 'd':
            keys[3]=false;
            break;
        case 'a':
            keys[2]=false;
            break;
        case 'w':
            keys[0]=false;
            break;
        case 's':
            keys[1]=false;
            break;
        case '+':
            keys[4]=false;
            break;
        case '-':
            keys[5]=false;
            break;
        case '*':
            keys[6]=false;
            break;
        case '/':
            keys[7]=false;
            break;
    }
    glutTimerFunc(0,timer,0);
    //glutPostRedisplay();
}

static void idle(void)
{
    glutTimerFunc(0,timer,0);
   // glutPostRedisplay();
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
    glutKeyboardUpFunc(keyup);
    glutSpecialFunc(splkey);
    glutSpecialUpFunc(splkeyup);
    glutIdleFunc(idle);
    glutSetKeyRepeat(0);
    glutTimerFunc(0,timer,0);
    glutMainLoop();

    return EXIT_SUCCESS;
}
