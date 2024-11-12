#include "Image.h"
#include <random>
#include <iostream>
#include "Walker.h"
#include <fmt/format.h>

int main()
{
  std::cout<<"DLA\n";
  Walker w(400,400);
  w.seed_image(5);
  // loop sim
  int frameNumber =0;
  for(size_t i=0; i<10000; ++i)
  {
    if(w.walk())
    {

      std::cout<<"found seed\n";
      if((i % 100) == 0)
        w.save_image(fmt::format("/transfer/DLA/DLA.{:04d}.jpg",frameNumber++));
    }
    w.resetStart();
  }
  w.save_image("test.png");
}