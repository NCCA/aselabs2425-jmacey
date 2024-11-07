#include "Image.h"
#include <OpenImageIO/imageio.h>
#include <algorithm>


bool Image::save(std::string_view _fname) const
{
    using namespace OIIO;
    auto out= ImageOutput::create(_fname.data());
    ImageSpec spec(m_width,m_height,4, TypeDesc::UINT8);
    bool success=out->open(_fname.data(),spec);
    success = out->write_image(TypeDesc::UINT8,m_pixels.get());
    success = out->close();
    return success;
}


Image::Image(int _w, int _h) : m_width{_w},
m_height{_h}
{
    m_pixels = std::make_unique<RGBA []>(m_width*m_height);
}

Image::Image(int _w, int _h,unsigned char _r, unsigned char _g,unsigned char _b, unsigned char _a ) :
Image(_w,_h)
{
    clear(_r,_g,_b,_a);
}

void Image::clear(unsigned char _r, unsigned char _g,unsigned char _b, unsigned char _a)
{
    for(size_t i=0; i<m_height*m_width; ++i)
    {
        m_pixels[i]=RGBA(_r,_g,_b,_a);
    }
}




void Image::setPixel(int _x, int _y,unsigned char _r, unsigned char _g,
        unsigned char _b, unsigned char _a)
{
    size_t index = (m_width*_y) + _x;
    m_pixels[index].r=_r;
    m_pixels[index].g=_g;
    m_pixels[index].b=_b;
    m_pixels[index].a=_a;
    
}

RGBA Image::getPixel(int _x , int _y) const
{
    size_t index = (m_width*_y) + _x;
    return m_pixels[index];
}

int Image::width() const
{
    return m_width;
}

int Image::height() const
{
    return m_height;
}

