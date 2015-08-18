#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <thread>
#include <functional>
#include <cstdio>

void reset(boost::shared_ptr<int>& sh) { sh.reset(); }

void print(boost::weak_ptr<int>&   wk)
{
  boost::shared_ptr<int> sh = wk.lock();
  if(sh) printf("%d\n", *sh);
}


int main()
{
  boost::shared_ptr<int> sh{new int{99}};
  boost::weak_pter<int>  wk{sh};

  
}
