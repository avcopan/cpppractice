// ordinary pointers do not have *value semantics* -- they cannot
// be *copied* or *assigned to* arbitrarily; for example
//   Thing* pthing = new Thing;
//   pthing = 0;
// is a guaranteed memory leak -- pthing owns the newly allocated
// memory, so setting it to a new value is effectively throwing
// away the keys; the memory address is now lost and cannot be freed

template<class T>
class SmartPointer {
  private:
    T* _pt;
  public:
    // all smart ptrs must have the following operators defined:
    T& operator* () const {return *_pt;}
    T* operator->() const {return  _pt;}
};
