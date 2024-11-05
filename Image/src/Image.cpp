#include "Image.h"
#include <OpenImageIO/imageio.h>


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

void Image::setPixel(int _x, int _y,unsigned char _r, unsigned char _g,
        unsigned char _b, unsigned char _a)
{
    int index=_x*m_width+_y;
    m_pixels[index].r=_r;
    m_pixels[index].g=_g;
    m_pixels[index].b=_b;
    m_pixels[index].a=_a;
    
}

RGBA Image::getPixel(int _x , int _y) const
{
    int index=_x*m_width+_y;
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

