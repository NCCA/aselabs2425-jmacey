#ifndef IMAGE_H_
#define IMAGE_H_
#include "RGBA.h"


class Image
{
    public :
        Image(int _w , int _h);
        int width() const ;
        int height() const;
        RGBA getPixel(int _x, int _y)const;
    private :
        int m_width;
        int m_height;

};

#endif