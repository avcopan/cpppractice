#include <iostream>
#include <vector>


// a semi-dumb pointer class -- simply acts as a wrapper
// to the pointer and calls *delete* when the object goes
// out of scope
template<class T>
class SmartPointer {
  private:
    T* _pt;
  public:
    // constructor
    SmartPointer(T* pt) : _pt(pt) {}
    // destructor
    ~SmartPointer() {delete  _pt;}
    // access operations
    T& operator* () {return *_pt;}
    T* operator->() {return  _pt;}
};

char space_or_newline(int i, int max) {return i+1 == max ? '\n' : ' ';}

int main() {
  SmartPointer<int> pint(new int(5));
  std::cout << *pint << std::endl;

//{SmartPointer<int> pint2 = pint;} // run-time error -- pint2 goes out of scope and calls delete
                                    // so that once pint goes out of scope its destructor calls
                                    // delete on a non-existent resource

  SmartPointer<std::vector<int> > pvec(new std::vector<int>);
  pvec->push_back(0);
  pvec->push_back(1);
  pvec->push_back(2);
  pvec->push_back(3);
  pvec->push_back(4);
  pvec->push_back(5);
  pvec->push_back(6);

  std::cout << "std::vector size:     " <<  pvec->size()                      << std::endl;
  std::cout << "std::vector max_size: " <<  pvec->max_size()                  << std::endl;
  std::cout << "std::vector empty:    " << (pvec->empty() ? "true" : "false") << std::endl;
  for(int i=0; i<7; ++i)
    std::cout << (*pvec)[i] << space_or_newline(i, 7);
}
