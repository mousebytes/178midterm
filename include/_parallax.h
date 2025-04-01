#ifndef _PARALLAX_H
#define _PARALLAX_H

#include<_common.h>
#include<_textureloader.h>
#include<_timer.h>

class _parallax
{
    public:
        _parallax();
        virtual ~_parallax();

        _textureLoader *background = new _textureLoader();
        _timer *tmr = new _timer();

        void drawBackground(float, float); // pass width and Height
        void initPrlx(char *);             // File Name
        void scroll(bool,string,float);    // Auto move, direction, speed
        void scrollDown();

        float xMax,xMin,yMax,yMin;         // Texture coordinates
        float speed;


    protected:

    private:
};

#endif // _PARALLAX_H
