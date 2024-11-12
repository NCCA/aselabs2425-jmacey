#ifndef IMAGE_H_
#define IMAGE_H_
#include "RGBA.h"
#include <memory>
#include <string_view>

class Image
{
    public :
        Image(int _w , int _h);
        Image(int _w, int _h,unsigned char _r, unsigned char _g,unsigned char _b, unsigned char _a=255 );
        void clear(unsigned char _r, unsigned char _g,unsigned char _b, unsigned char _a=255);
        int width() const ;
        int height() const;
        RGBA getPixel(int _x, int _y)const;
        void setPixel(int _x, int y,unsigned char _r, unsigned char _g,
        unsigned char _b, unsigned char _a=255);
        bool save(std::string_view fname) const;
    private :
        int m_width;
        int m_height;
        std::unique_ptr<RGBA []> m_pixels;
};

#endif