#include <iostream>
#include <chrono>
#include "Emitter.h"
#include <fmt/format.h>
#include <filesystem>
int main()
{
  namespace fs=std::filesystem;
  std::cout<<"Particle System\n";
  // we will dump particles to the /transfer/Particles directory
  auto folder=fs::path("/transfer/Particles/");
  if(! fs::exists(folder))
  {
    fs::create_directory(folder);
  }
  Emitter m(2000);
  m.debug();

  for(int i=0; i<240; ++i)
  {
    m.update();

    m.writeGeo(fmt::format("{}test{:04d}.geo",folder.c_str(),i));
  }
  return EXIT_SUCCESS;
}