#include <gtest/gtest.h>
#include "Particle.h"
#include "Vec3.h"
#include "Emitter.h"

TEST(Particle,ctor)
{
  Particle p;
  EXPECT_EQ(p.life,100);
  EXPECT_FLOAT_EQ(p.size,0.5f);
  EXPECT_FLOAT_EQ(p.pos.x,0.0f);
  EXPECT_FLOAT_EQ(p.pos.y,0.0f);
  EXPECT_FLOAT_EQ(p.pos.z,0.0f);
  EXPECT_FLOAT_EQ(p.dir.x,0.0f);
  EXPECT_FLOAT_EQ(p.dir.y,0.0f);
  EXPECT_FLOAT_EQ(p.dir.z,0.0f);

  EXPECT_FLOAT_EQ(p.colour.x,1.0f);
  EXPECT_FLOAT_EQ(p.colour.y,1.0f);
  EXPECT_FLOAT_EQ(p.colour.z,1.0f);

}

TEST(Vec3,ctor)
{
  Vec3 v;
  EXPECT_FLOAT_EQ(v.x,0.0f);
  EXPECT_FLOAT_EQ(v.y,0.0f);
  EXPECT_FLOAT_EQ(v.z,0.0f);
}

TEST(Vec3,userCtor)
{
  Vec3 v(1.0f,1.0f,1.0f);
}

TEST(Emitter,ctor)
{
  Emitter e(100);
  EXPECT_EQ(e.size(),100);
}