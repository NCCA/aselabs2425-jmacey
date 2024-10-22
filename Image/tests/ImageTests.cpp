#include <gtest/gtest.h>
#include "Image.h"

TEST(Image,ctor)
{
    Image img(100,100);
    EXPECT_EQ(img.width(),100);
    EXPECT_EQ(img.height(),100);
}

TEST(Image,getPixel)
{
    Image img(1,1);
    EXPECT_EQ(img.width(),1);
    EXPECT_EQ(img.height(),1);
    RGBA pixel=img.getPixel(0,0);
    EXPECT_EQ(pixel.r,0);
    EXPECT_EQ(pixel.g,0);
    EXPECT_EQ(pixel.b,0);
    EXPECT_EQ(pixel.a,0);
    
    
}