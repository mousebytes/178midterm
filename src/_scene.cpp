#include "_scene.h"

#include<_common.h>

#include<_player.h>
#include<_parallax.h>
#include<_inputs.h>
#include<_enms.h>

_player *player = new _player();
_parallax *parallax = new _parallax();
_inputs *inputs = new _inputs();
_enms enemies[10];

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



}


int _scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_KEYDOWN:
        inputs->wParam = wParam;
        inputs->keyPressedPRLX(parallax);
        break;

    case WM_KEYUP: break;

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
