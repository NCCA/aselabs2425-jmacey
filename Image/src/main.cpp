#include "Image.h"
#include <random>


int main()
{

    std::random_device rd;
    std::mt19937 gen(rd());
    gen.seed(2343);
    constexpr int imageWidth=720;
    constexpr int imageHeight=420;

    std::uniform_int_distribution<> width_distrib(0,imageWidth);
    std::uniform_int_distribution<> height_distrib(0,imageHeight);
    std::uniform_int_distribution<unsigned char> colour(0,255);
    Image img(imageWidth,imageHeight,255,255,255);

    for(size_t i=0; i<imageHeight*imageWidth*5; ++i)
    {
        img.setPixel(width_distrib(gen),height_distrib(gen),colour(gen),colour(gen),colour(gen));
    }

    img.save("random.png");

}