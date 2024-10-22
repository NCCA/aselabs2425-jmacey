#include <gtest/gtest.h>
#include <iostream>
#include "RGBA.h"

TEST(RGBA,construct)
{
    RGBA pixel;
    ASSERT_EQ(pixel.r,0);
    ASSERT_TRUE(pixel.g == 0);
    ASSERT_TRUE(pixel.b == 0);
    ASSERT_TRUE(pixel.a == 0);
    ASSERT_TRUE(pixel.rgba == 0);
    
}

TEST(RGBA,ctor_user)
{
    RGBA pixel(255,128,64);
    ASSERT_TRUE(pixel.r == 255);
    ASSERT_TRUE(pixel.g == 128);
    ASSERT_TRUE(pixel.b == 64);
    ASSERT_TRUE(pixel.a == 255);

    auto p2=RGBA{0,0,100,128};
    ASSERT_TRUE(p2.r == 0);
    ASSERT_TRUE(p2.g == 0);
    ASSERT_TRUE(p2.b == 100);
    ASSERT_TRUE(p2.a == 128);

//    // RGBA p3={-100,1000,2000,256};
//     RGBA p3(-100,1000,2000,256);
//     EXPECT_EQ(p3.r,0);
//     EXPECT_EQ(p3.g,255);
//     EXPECT_EQ(p3.b,255);
//     EXPECT_EQ(p3.a,255);
}

TEST(RGBA,setPixel)
{
    RGBA pixel;
    pixel.set(255,128,64,0);
    EXPECT_EQ(pixel.r,255);
    EXPECT_EQ(pixel.g,128);
    EXPECT_EQ(pixel.b,64);
    EXPECT_EQ(pixel.a,0);
    std::cout<<pixel.rgba<<'\n';

}








