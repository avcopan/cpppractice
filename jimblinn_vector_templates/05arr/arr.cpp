#include <boost/shared_ptr.hpp>
#include <vector>

#include <iostream>
#include <iomanip>


template<class T>
void print(const std::vector<T>& v)
{
  for(auto it = v.begin(); it != v.end(); ++it)
    std::cout << std::setw(4) << *it;
  std::cout << std::endl;
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
    template<typename... Args>
    dtype operator()(int i, Args... other)
    {
      return *this(other...);
    }
};



int main()
{
  Tensor<double> T({5,5,5});
  Tensor<double> A({10,6,8,11});

  print( T.get_tensor_index(73) );
  std::cout << T.get_global_index(T.get_tensor_index(73)) << std::endl;
}



// trash bin:
/*
    // convert between global and tensor index
    std::vector<int> get_tensor_index(int global_index)
    {
      std::vector<int> tensor_index;
      for(int ax = 0; ax < _rank; ++ax)
        tensor_index.push_back( ( global_index % (_shape[ax]*_stride[ax]) ) / _stride[ax] );
      return tensor_index;
    }
    int get_global_index(const std::vector<int>& tensor_index)
    {
      int global_index = 0;
      for(int ax = 0; ax < _rank; ++ax)
        global_index += tensor_index[ax] * _stride[ax];
      return global_index;
    }
*/
