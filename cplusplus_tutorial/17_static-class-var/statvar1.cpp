#include <stdio.h>

class Dummy {
  public:
    static int n;     // static variables are fixed for *all* objects of the class Dummy
    Dummy () { n++; };// in this case, n (if initialized to 0 and not directly altered)
};                    // will count the number of objects of class dummy

int Dummy::n = 0;

int main()
{
  printf("Dummy::n is %d\n", Dummy::n);
  Dummy dummy;
  printf("Dummy::n is %d\n", Dummy::n);
  Dummy dumbo = dummy;
  printf("Dummy::n is %d\n", Dummy::n); // in this case, Dummy::n keeps its value because dumbo
                                        // was set equal to dummy without calling the constructor
  Dummy dumby;
  printf("Dummy::n is %d\n", Dummy::n); // now, Dummy::n will have been incremented by 1
  Dummy dumpy[5]; // initializes an array of 5 Dummy objects, each of which calls the constructor, so Dummy::n will be incremented by 5
  printf("Dummy::n is %d\n", Dummy::n);
  Dummy* pdumpo = new Dummy; // declaring new memory block to store Dummy object pointer also calls the constructor,
                             // so Dummy::n will be incremented
  printf("Dummy::n is %d\n", Dummy::n);

  // Dummy::n can also be accessed as an attribute of any specific object -- it has the same value for each at any given instant of run-time
  printf("Dummy::n is %d\n", dummy.n);
  printf("Dummy::n is %d\n", dumbo.n);
  printf("Dummy::n is %d\n", dumby.n);
  printf("Dummy::n is %d\n", dumpy[0].n);
  printf("Dummy::n is %d\n", dumpy[1].n);
  printf("Dummy::n is %d\n", dumpy[2].n);
  printf("Dummy::n is %d\n", dumpy[3].n);
  printf("Dummy::n is %d\n", dumpy[4].n);
  printf("Dummy::n is %d\n", pdumpo->n);

  delete pdumpo;
}
