#include <cstdlib>  // std::malloc

// creation policy-classes
template<class T>
struct CreationPolicyNew {
  static T* create() {return new T;}
};
template<class T>
struct CreationPolicyMalloc {
  static T* create() {
    void* buf = std::malloc(sizeof(T));
    if (!buf) return 0;
    return new(buf) T;
  }
};
template<class T>
struct CreationPolicyProto {
  private:
    T* _pt;
  public:
    CreationPolicyProto(T* pt = 0) _pt(pt) {;}
    T*   get_prototype()      {return _pt;}
    void set_prototype(T* pt) {_pt = pt;}
    T* create() {return _pt ? _pt->clone() : 0;}
};

// host class for the creation policies
template<class CreationPolicy>
class WidgetManager : public CreationPolicy { // this is the CRTP
};
