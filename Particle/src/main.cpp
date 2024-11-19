#include <iostream>
#include <chrono>
#include "Emitter.h"
#include <fmt/format.h>
int main()
{
  std::cout<<"Particle System\n";
  Emitter m(10);
  m.debug();

  for(int i=0; i<10; ++i)
  {
    m.update();

    m.writeGeo(fmt::format("test{:04d}.geo",i));
  }
  return EXIT_SUCCESS;
}