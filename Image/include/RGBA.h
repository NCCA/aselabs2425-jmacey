#ifndef RGBA_H_
#define RGBA_H_

#include <cstdint>
struct RGBA
{
    union
    {
        uint32_t rgba=0;
        struct
        {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        };
    };
    RGBA()=default;
    RGBA(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a=255) :
    r{_r},g{_g},b{_b},a{_a}
    {
    }
    void set(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a=255)
    {
        r=_r;
        g=_g;
        b=_b;
        a=_a; 
    }

};


#endif




