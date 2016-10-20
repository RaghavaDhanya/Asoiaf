#ifndef ASOIAF_H_
#define ASOIAF_H_
#include <cstdlib>
int S_width=640,S_height=480;
/* keys[]={up,down,left,right,+,-,*,/} */
bool keys[]={false,false,false,false,false,false,false,false};
class Box
{
protected:
    float scale,x,y,rot;
public:
    Box()
    {scale=1;x=y=rot=0;}
    Box(float scale,float x,float y,float rot)
    {
        this->scale=scale;this->x=x;this->y=y;this->rot=rot;
    }
    virtual void update()=0;
    void drawBox()
            {
                glPushMatrix();
                glTranslatef(this->x,this->y,0);
                glScalef(this->scale,this->scale,0);
                glRotatef(this->rot*5,0,0,1);
                glBegin(GL_POLYGON);
                    glColor3d(.5,0,.2);
                    glVertex3f(-15,15,0);
                    glVertex3f(-15,-15,0);
                    glVertex3f(15,-15,0);
                    glVertex3f(15,15,0);
                glEnd();
                glPopMatrix();
            }
    friend bool collideBox(Box &,Box &);
};
class userBox:public Box
{
public:
        void update()
        {
            y=(y+=5*int(keys[0]))>(S_height/2-15*scale)?(S_height/2-15*scale):y;
            y=(y-=5*int(keys[1]))<(-S_height/2+15*scale)?(-S_height/2+15*scale):y;
            x=(x-=5*int(keys[2]))<(-S_width/2+15*scale)?(-S_width/2+15*scale):x;
            x=(x+=5*int(keys[3]))>(S_width/2-15*scale)?(S_width/2-15*scale):x;
            rot+=1;//int(keys[4]);
            //d0-=int(keys[5]);
            //scale+=.2*int(keys[6]);
            //scale-=.2*int(keys[7]);
        }
};
class randomBox:public Box
{
    //0 left , 1 right, 3 up, 2 down
    int direction;
public:
    randomBox(int d)
    {
        this->direction=d;
        this->scale=1;
        this->rot=0;
        switch(d)
        {
        case 0: this->x=S_width/2;
                this->y=rand()%(S_height)-(S_height/2);
                break;
        case 1: this->x=-S_width/2;
                this->y=rand()%(S_height)-(S_height/2);
                break;
        case 2: this->x=rand()%(S_width)-(S_width/2);
                this->y=S_height/2;
                break;
        case 3: this->x=rand()%(S_width)-(S_width/2);
                this->y=-S_height/2;
                break;

        }

    }
    void update()
    {
        switch(this->direction)
        {
        case 0:
            x=(x-=1)<(-S_width/2+15*scale)?(-S_width/2+15*scale):x;
            break;
        case 1:
            x=(x+=1)>(S_width/2-15*scale)?(S_width/2-15*scale):x;
            break;
        case 2:
            y=(y-=1)<(-S_height/2+15*scale)?(-S_height/2+15*scale):y;
            break;
        case 3:
            y=(y+=1)>(S_height/2-15*scale)?(S_height/2-15*scale):y;
            break;
        }
    }
};
bool collideBox(Box &a,Box &b)
{
    return false;
}
#endif
