#include "_scene.h"

#include<_common.h>

#include<_player.h>
#include<_parallax.h>
#include<_inputs.h>
#include<_enms.h>
#include<_collisionckeck.h>

#define MAX_ENEMY_COUNT 10

_player *player = new _player();
_parallax *parallax = new _parallax();
_inputs *inputs = new _inputs();
_enms enemies[10];
_collisionCkeck *collide = new _collisionCkeck();

_scene::_scene()
{
    //ctor
}

_scene::~_scene()
{
    //dtor
}
GLint _scene::initGL()
{
    srand(time(NULL));

   glClearColor(1.0,1.0,1.0,1.0);
   glClearDepth(1.0);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);

   glEnable(GL_BLEND); // take off the transparent background
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

  // glEnable(GL_COLOR_MATERIAL);
  // myLight->setLight(GL_LIGHT0);

   dim.x = GetSystemMetrics(SM_CXSCREEN);
   dim.y = GetSystemMetrics(SM_CYSCREEN);

    //player->initPlayer(1,1,"rocket.png");



    parallax->initPrlx("images/space_bg.png");

    enemies[0].initEnms("images/asteroid.png");
    enemies[0].speed = (float)((rand()%3)+1.0)/100.0;
    enemies[0].actionTrigger = enemies[0].FALLING;

    player->initPlayer(2,3,"images/rocket2.png");
    player->actionTrigger = player->STAND;

    for(int i = 0; i < MAX_ENEMY_COUNT; i++)
    {
        //enemies[i].pos.x = (float)rand()/(float)(RAND_MAX)*5-2.5;

        // only want the x pos randomized the rest of the vector could be set by constructor
        enemies[i].placeEnms({(float)rand()/(float)(RAND_MAX)*5-2.5, enemies[i].pos.y, enemies[i].pos.z});
        enemies[i].scale.x = enemies[i].scale.y = (float)(rand()%12)/50.0;

        // random speed
        enemies[i].fall_speed = (float)((rand()%3)+1.0)/100.0;

    }


   return true;
}

void _scene::reSize(GLint width, GLint height)
{
    GLfloat aspectRatio = (GLfloat)width/(GLfloat)height;
    // keep track of the resize window
    glViewport(0,0,width,height); // adjusting the viewport
    glMatrixMode(GL_PROJECTION);  // perspective projection settings
    glLoadIdentity();             // identity matrix
    gluPerspective(45,aspectRatio,0.1,100.0); // projection settings
    glMatrixMode(GL_MODELVIEW);   // camera and model settings
    glLoadIdentity();             // identity matrix

    dim.x = GetSystemMetrics(SM_CXSCREEN);
    dim.y = GetSystemMetrics(SM_CYSCREEN);
}

void _scene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0,0,1,0,0,0,0,1,0); // look at this place in 3d view

    glPushMatrix(); // push matrix for scale
    glScalef(13.3,13.3,1); // change size bg
    parallax->drawBackground(dim.x,dim.y); // draw using prlx function
    glPopMatrix(); // [pop for every push
    parallax->scrollDown();



    //enemies[0].actions();
    enemies[0].drawEnms(enemies[0].myTex->tex);

    for(int i = 0; i < MAX_ENEMY_COUNT;i++)
    {
        if(!enemies[i].is_collided)
        {
            enemies[i].drawEnms(enemies[0].myTex->tex);
            enemies[i].actionTrigger = enemies[i].FALLING;

            enemies[i].actions();
        }
        else
        {
            enemies[i].drawEnms(enemies[0].myTex->tex);
            enemies[i].actions();
        }
        enemies[i].move_enemy_towards_player(player);



        if(collide->isRadialCol(enemies[i].pos, player->plPos, 0.2,0.3,0.0002))
    {
        if(enemies[i].pos.x > player->plPos.x)
        {
            enemies[i].actionTrigger = enemies[i].MOVERIGHT;
            enemies[i].is_collided = true;
        }
        else
        {
            enemies[i].actionTrigger = enemies[i].MOVELEFT;
            enemies[i].is_collided = true;
        }
    }
    }

    //enemies[0].actionTrigger = 1;

    player->drawPlayer();
    //player->actionTrigger = player->LEFTWALK;
    player->playerActions();





}


int _scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_KEYDOWN:
        inputs->wParam = wParam;
        //inputs->keyPressedPRLX(parallax);
        inputs->keyPressed(player);

        break;

    case WM_KEYUP:
        inputs->wParam = wParam;
        inputs->keyUP(player);
        break;

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:

        break;
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:

        break;
    case WM_MOUSEMOVE:

        break;
    case WM_MOUSEWHEEL:

        break;
    }
}
