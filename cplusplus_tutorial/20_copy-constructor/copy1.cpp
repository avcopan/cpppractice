#include <cstdio>

/* a class with no copy constructor -- results in shallow copies: upon copying, pstr points to the same
   memory address for both the original object and the new copy */
class Dumbo {
    int* pint;

  public:
    Dumbo(int i) : pint(new int(i)) {} // constructor
    ~Dumbo() { delete pint; }          // destructor
    int get() { return *pint; }
    void set(int i) { *pint = i; }
};

/* a class with copy constructor -- results in deep copies: upon copying, pstr points to a new memory address
   and so the values pointed to by pstr can be changed independently for the original object and its copy */
class Dummy {
    int* pint;

  public:
    Dummy(int i) : pint(new int(i)) {} // constructor
    ~Dummy() { delete pint; }          // destructor
    int get() { return *pint; }
    void set(int i) { *pint = i; }

    // copy constructor:
    Dummy(Dummy& dummy) : pint(new int(dummy.get())) {}
};

int main()
{
  Dumbo dumbo(0);
  Dumbo dumby = dumbo; // this produces a segfault at the end of main, because delete gets called twice on the same address
  dumby.set(100);
  printf("dumbo.get() returns %d\n", dumbo.get());
  printf("dumby.get() returns %d\n", dumby.get());

  Dummy dummy(0);
  Dummy dumpy = dummy; // this produces a segfault at the end of main, because delete gets called twice on the same address
  dumpy.set(100);
  printf("dummy.get() returns %d\n", dummy.get());
  printf("dumpy.get() returns %d\n", dumpy.get());
}
