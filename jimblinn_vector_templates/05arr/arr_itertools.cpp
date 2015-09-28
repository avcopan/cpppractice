#include <boost/shared_ptr.hpp>
#include <vector>
#include <cppitertools/zip.hpp>
#include <tuple> // provides std::get<i>(tuple) on the return value of iter::zip()

#include <iostream>
#include <iomanip>


template<class T>
void print(const T& v)
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

    dtype  operator()(const std::initializer_list<int>& tensor_index) const
    {
      int global_index = 0;
      for(auto pair : iter::zip(tensor_index, _stride))
        global_index += std::get<0>(pair) * std::get<1>(pair);
      return _array[global_index];
    }

    dtype& operator()(const std::initializer_list<int>& tensor_index)
    {
      int global_index = 0;
      for(auto pair : iter::zip(tensor_index, _stride))
        global_index += std::get<0>(pair) * std::get<1>(pair);
      return _array[global_index];
    }

    dtype  operator[](int global_index) const
    {
      return _array[global_index];
    }

    dtype& operator[](int global_index)
    {
      return _array[global_index];
    }
};



int main()
{
  Tensor<double> T({5,5,5});
  Tensor<double> A({10,6,8,11});

  int i=1, j=2, k=3;

  T({i,j,k}) = 5.0;
  std::cout << T[i*25+j*5+k] << std::endl;
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
