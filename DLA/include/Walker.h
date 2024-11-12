#ifndef WALKER_H_
#define WALKER_H_

#include "Image.h"
#include <memory>
#include <string_view>
#include <random>

class Walker
{
public :
    Walker(int _w, int _h);
    // add _num random seeds to the image
    // this will set the alpha to 0 and rgb to black
    void seed_image(int _num);
    void save_image(std::string_view _fname);
    [[nodiscard]] bool walk();
    void resetStart();
private :
    int m_width;
    int m_height;
    std::unique_ptr<Image> m_map;
    std::uniform_int_distribution<int> m_xRand;
    std::uniform_int_distribution<int> m_yRand;
    void initRNG();
    int m_xpos;
    int m_ypos;

};

#endif