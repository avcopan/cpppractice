#include <boost/shared_ptr.hpp>
#include <cstdio>

int main()
{
  printf("\n");
  boost::shared_ptr<int> pint1{new int{1}}; // initialize pointer, and store the number 1 at its address
  printf("%p\n", pint1.get());              // print pointer address
  printf("%d\n", *pint1);                   // print stored value

  printf("\n");
  boost::shared_ptr<int> pint2{pint1};      // initialize another variable sharing the pointer pint1 -- i.e. having the same address
  printf("%p\n", pint2.get());              //  - now both pint1 and pint2 share ownership of the same int object, which has value 1
  printf("%d\n", *pint2);                   //  - note that this isn't possible for ordinary scoped_ptrs, for which only one pointer can
                                            //    own a given address
                                            //  - the shared_ptr class automatically calls *delete* when the number of pointers holding
                                            //    a given address goes to 0
  printf("\n");
  pint1.reset(new int{7});
  printf("%p\n", pint1.get());
  printf("%d\n", *pint1);
  printf("%p\n", pint2.get());
  printf("%d\n", *pint2);

  printf("\n");
  pint2 = pint1;
  printf("%p\n", pint1.get());
  printf("%d\n", *pint1);
  printf("%p\n", pint2.get());
  printf("%d\n", *pint2);

  printf("\n");
  pint2.reset();
  printf("%p\n", pint1.get());
  printf("%s\n", bool(pint1) ? "true" : "false");
  printf("%p\n", pint2.get());
  printf("%s\n", bool(pint2) ? "true" : "false");
}
