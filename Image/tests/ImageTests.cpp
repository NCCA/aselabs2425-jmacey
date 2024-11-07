#include <gtest/gtest.h>
#include "Image.h"

TEST(Image,ctor)
{
    Image img(100,100);
    EXPECT_EQ(img.width(),100);
    EXPECT_EQ(img.height(),100);
}

TEST(Image,ctorColour)
{
    Image img(100,100,255,0,0);
    EXPECT_TRUE(img.save("red.png"));
}


TEST(Image,setPixel)
{
    Image img(3,1);
    EXPECT_EQ(img.width(),3);
    EXPECT_EQ(img.height(),1);
    img.setPixel(0,0,255,0,0); // red
    img.setPixel(1,0,0,255,0); // red
    img.setPixel(2,0,0,0,255); // red


    RGBA pixel;
   pixel=img.getPixel(0,0);
    EXPECT_EQ(pixel.r,255);
    EXPECT_EQ(pixel.g,0);
    EXPECT_EQ(pixel.b,0);
    EXPECT_EQ(pixel.a,255);

   pixel=img.getPixel(1,0);
    EXPECT_EQ(pixel.r,0);
    EXPECT_EQ(pixel.g,255);
    EXPECT_EQ(pixel.b,0);
    EXPECT_EQ(pixel.a,255);

   pixel=img.getPixel(2,0);
    EXPECT_EQ(pixel.r,0);
    EXPECT_EQ(pixel.g,0);
    EXPECT_EQ(pixel.b,255);
    EXPECT_EQ(pixel.a,255);
    EXPECT_TRUE(img.save("rgb.png"));

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