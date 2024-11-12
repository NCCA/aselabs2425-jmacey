#include "Walker.h"
#include <iostream>
std::random_device g_rd;
std::seed_seq g_seed{g_rd(),g_rd(),g_rd(),g_rd(),g_rd(),g_rd(),g_rd(),g_rd()};
std::mt19937 g_rng(g_seed);
std::uniform_int_distribution<int>g_walkDir(-1,1);
Walker::Walker(int _w, int _h) : m_width{_w},m_height{_h}
{
  m_map = std::make_unique<Image>(_w,_h,255,255,255,255);
  initRNG();
}

void Walker::initRNG()
{
  m_xRand = std::uniform_int_distribution<int>(1,m_width-1);
  m_yRand = std::uniform_int_distribution<int>(1,m_height-1);
  resetStart();

}

bool Walker::walk()
{
  // while not walking
  // have I hit the edge if so return false
  // get current pixel, is it near a seed
  // if so plant new seed return true
  // else walk (goto top)
  bool walking = true;
  bool found=false;
  while(walking)
  {
    // move to a new position
    m_xpos += g_walkDir(g_rng);
    m_ypos += g_walkDir(g_rng);
    if(m_xpos == 0 || m_xpos>=m_width ||
       m_ypos == 0 || m_ypos>=m_height)
    {
      walking = false;
      found = false;
      std::cout<<"Hit edge\n";
      break;
    }
    // sample our pixels
    RGBA p;
    for(int y=-1; y<=1; ++y)
    {
      for(int x=-1; x<=1; ++x)
      {
        p=m_map->getPixel(m_xpos+x,m_ypos+y);
        if(p.a == 0)
        {
          std::cout<<"Found Seed\n";
          m_map->setPixel(m_xpos,m_ypos,255,0,0,0);
          return true;
        }
      }
    }
  }

  return true;
}

void Walker::resetStart()
{
  m_xpos = m_xRand(g_rng);
  m_ypos = m_yRand(g_rng);
  std::cout<<"Reset Start "<<m_xpos<<' '<<m_ypos<<'\n';

}


void Walker::seed_image(int _num)
{
  for(int i=0; i<_num; ++i)
  {
    m_map->setPixel(m_xRand(g_rng),m_yRand(g_rng),255,0,0,0);
  }
}
void Walker::save_image(std::string_view _fname)
{
  m_map->save(_fname);
}