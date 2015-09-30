#include <boost/shared_ptr.hpp>
#include <vector>

#include <iostream>
#include <iomanip>

int get_global_index(const std::vector<int>& stride, int axis)
{
  return 0;
}

template<typename ... Types>
inline const
int get_global_index(const std::vector<int>& stride, int axis, int axis_index, Types ... other_indices)
{
  return axis_index * (stride[axis]) + get_global_index(stride, ++axis, other_indices...);
}

template<class dtype>
class Tensor {
  private:
    int                        _rank , _size = 1;
    boost::shared_ptr<dtype[]> _array;
    std::vector<int>           _shape, _stride;
  public:
    // constructor 
    Tensor(const std::vector<int>& shape) : _shape(shape), _stride(shape.size()), _rank(shape.size())
    {
      for(int ax = _rank - 1; ax >= 0; --ax) {
        _stride[ax] = _size;  _size *= _shape[ax];
      }
      _array = boost::shared_ptr<dtype[]>(new dtype[_size]);
    }

    // element access
    dtype  operator[](int global_index) const {return _array[global_index];}
    dtype& operator[](int global_index)       {return _array[global_index];}
    template<typename... Index>
    dtype  operator()(Index... tensor_index) const {return _array[get_global_index(_stride, 0, tensor_index...)];}
    template<typename... Index>
    dtype& operator()(Index... tensor_index)       {return _array[get_global_index(_stride, 0, tensor_index...)];}
};



int main()
{
  Tensor<double> T({5,5,5});
  Tensor<double> A({10,6,8,11});

  int i=3, j=4, k=1;
  T(i,j,k) = 11.0;
  std::cout << T[5*5*i + 5*j + k] << std::endl;
}
