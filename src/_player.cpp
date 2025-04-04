#include "_player.h"

_player::_player()
{
    //ctor
}

_player::~_player()
{
    //dtor
}
void _player::initPlayer(int xfrm, int yfrm, char* fileName)
{
    //init Quad
    vert[0].x = -1.0; vert[0].y = -1.0; vert[0].z = 0.0;
    vert[1].x =  1.0; vert[1].y = -1.0; vert[1].z = 0.0;
    vert[2].x =  1.0; vert[2].y =  1.0; vert[2].z = 0.0;
    vert[3].x = -1.0; vert[3].y =  1.0; vert[3].z = 0.0;

    //init player position

    plPos.x =0;
    plPos.y =-0.65;
    plPos.z =-2;

    // init player size
    plScl.x = plScl.y=plScl.z = 0.5;

    // get frame count
    framesX = xfrm;
    framesY = yfrm;

    actionTrigger =1;  // set action to STAND

    //setup Texture
    xMin=0;
    xMax= 1.0/(float)framesX;
    yMax= 1.0/(float)framesY;
    yMin = yMax-(1/(float)framesY);

    pTex->loadTexture(fileName);
}

void _player::drawPlayer()
{
    glPushMatrix();
      glTranslatef(plPos.x,plPos.y,plPos.z);
      if(player_facing_right)
        glScalef(plScl.x, plScl.y,plScl.z);
      else
        glScalef(-plScl.x,plScl.y,plScl.z);

      glColor3f(1.0,1.0,1.0);

      pTex->textureBinder();

      glBegin(GL_QUADS);
      glTexCoord2f(xMin,yMax);
      glVertex3f(vert[0].x,vert[0].y,vert[0].z);

      glTexCoord2f(xMax,yMax);
      glVertex3f(vert[1].x,vert[1].y,vert[1].z);

      glTexCoord2f(xMax,yMin);
      glVertex3f(vert[2].x,vert[2].y,vert[2].z);

      glTexCoord2f(xMin,yMin);
      glVertex3f(vert[3].x,vert[3].y,vert[3].z);
      glEnd();

    glPopMatrix();
}

void _player::playerActions()
{
    switch(actionTrigger)
    {
    case STAND:
        //xMin =0;
        //xMax = 1.0/(float)framesX;
        //yMax = 1.0/(float)framesY;
        //yMin = yMax- (1.0/(float)framesY);
        if(pTmer->getTicks()>70)
        {
            yMax = 1.0/(3.0);
            yMin = 0.0;
            xMax += 1.0/(float)framesX;
            xMin+= 1.0/(float)framesX;
        }

        break;

    case LEFTWALK:

        if(pTmer->getTicks() >70)
        {
        //yMax +=1.0/(float)framesY;
        //yMin +=1.0/(float)framesY;

        yMax=1.0;
        yMin=2.0/(float)framesY;

        xMax += 1.0/(float)framesX;
        xMin += 1.0/(float)framesX;



        if(plPos.x > -1.75)
        {
            plPos.x -=0.05;
        }
        //player_facing_right = false;
        pTmer->reset();
        }
        break;
    case RIGHTWALK:
        if(pTmer->getTicks()>70)
        {
            yMax=2.0/(float)framesY;
            yMin=1.0/(float)framesY;

            xMax += 1.0/(float)framesX;
            xMin += 1.0/(float)framesX;

            if(plPos.x < 1.75)
            {
                plPos.x += 0.05;
            }
            pTmer->reset();
        }
        //player_facing_right = true;
        break;
    case UP:
        if(pTmer->getTicks()>70)
        {
            yMax = 1.0/(3.0);
            yMin = 0.0;
            xMax += 1.0/(float)framesX;
            xMin+= 1.0/(float)framesX;

            if(plPos.y < 1.75)
            {
                plPos.y +=0.05;
            }

            pTmer->reset();
        }



        break;
    case DOWN:
        if(pTmer->getTicks()>70)
        {
            yMax = 1.0/(3.0);
            yMin = 0.0;
            xMax += 1.0/(float)framesX;
            xMin+= 1.0/(float)framesX;

            if(plPos.y > -1.75)
            {
                plPos.y -=0.05;
            }

            pTmer->reset();
        }



        break;

    }
}

