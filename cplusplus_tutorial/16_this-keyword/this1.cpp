#include <stdio.h>

class Dummy {
  public:
    bool isitme(Dummy& obj);
};

bool Dummy::isitme(Dummy& obj)
{
  if (&obj == this) return true ; // keyword 'this' represents a pointer to the object whose member function is being executed
  else              return false;
}

int main()
{
  Dummy  dummy, dumbo;
  Dummy* pdummy = &dummy;

  printf("%s\n", pdummy->isitme(dummy) ? "true" : "false");
  printf("%s\n", pdummy->isitme(dumbo) ? "true" : "false");
}
