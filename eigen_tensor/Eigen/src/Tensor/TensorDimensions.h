// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2014 Benoit Steiner <benoit.steiner.goog@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_CXX11_TENSOR_TENSOR_DIMENSIONS_H
#define EIGEN_CXX11_TENSOR_TENSOR_DIMENSIONS_H


namespace Eigen {

/** \internal
  *
  * \class TensorDimensions
  * \ingroup CXX11_Tensor_Module
  *
  * \brief Set of classes used to encode and store the dimensions of a Tensor.
  *
  * The Sizes class encodes as part of the type the number of dimensions and the
  * sizes corresponding to each dimension. It uses no storage space since it is
  * entirely known at compile time.
  * The DSizes class is its dynamic sibling: the number of dimensions is known
  * at compile time but the sizes are set during execution.
  *
  * \sa Tensor
  */

// Can't use std::pair on cuda devices
template <typename Index> struct IndexPair {
  inline IndexPair() : first(0), second(0) { }
  inline IndexPair(Index f, Index s) : first(f), second(s) { }
  Index first;
  Index second;
};

// Boilerplate code
namespace internal {

template<std::size_t n, typename Dimension> struct dget {
  static const std::size_t value = get<n, Dimension>::value;
};


template<typename Index, std::size_t NumIndices, std::size_t n, bool RowMajor>
struct fixed_size_tensor_index_linearization_helper
{
  template <typename Dimensions> 
  static inline Index run(array<Index, NumIndices> const& indices,
                          const Dimensions& dimensions)
  {
    return array_get<RowMajor ? n - 1 : (NumIndices - n)>(indices) +
        dget<RowMajor ? n - 1 : (NumIndices - n), Dimensions>::value *
        fixed_size_tensor_index_linearization_helper<Index, NumIndices, n - 1, RowMajor>::run(indices, dimensions);
  }
};

template<typename Index, std::size_t NumIndices, bool RowMajor>
struct fixed_size_tensor_index_linearization_helper<Index, NumIndices, 0, RowMajor>
{
  template <typename Dimensions> 
  static inline Index run(array<Index, NumIndices> const&, const Dimensions&)
  {
    return 0;
  }
};

template<typename Index, std::size_t n>
struct fixed_size_tensor_index_extraction_helper
{
  template <typename Dimensions> 
  static inline Index run(const Index index,
                          const Dimensions& dimensions)
  {
    const Index mult = (index == n-1) ? 1 : 0;
    return array_get<n-1>(dimensions) * mult +
        fixed_size_tensor_index_extraction_helper<Index, n - 1>::run(index, dimensions);
  }
};

template<typename Index>
struct fixed_size_tensor_index_extraction_helper<Index, 0>
{
  template <typename Dimensions> 
  static inline Index run(const Index,
                          const Dimensions&)
  {
    return 0;
  }
  };

}  // end namespace internal


// Fixed size
template <typename std::ptrdiff_t... Indices>
struct Sizes : internal::numeric_list<std::ptrdiff_t, Indices...> {
  typedef internal::numeric_list<std::ptrdiff_t, Indices...> Base;
  static const std::ptrdiff_t total_size = internal::arg_prod(Indices...);

  inline std::ptrdiff_t rank() const {
    return Base::count;
  }

  static inline std::ptrdiff_t TotalSize() {
    return internal::arg_prod(Indices...);
  }

  Sizes() { }
  template <typename DenseIndex>
  explicit Sizes(const array<DenseIndex, Base::count>& /*indices*/) {
    // todo: add assertion
  }
  template <typename... DenseIndex> Sizes(DenseIndex...) { }
  explicit Sizes(std::initializer_list<std::ptrdiff_t> /*l*/) {
    // todo: add assertion
  }

  template <typename T> Sizes& operator = (const T& /*other*/) {
    // add assertion failure if the size of other is different
    return *this;
  }

  inline std::ptrdiff_t operator[] (const std::size_t index) const {
    return internal::fixed_size_tensor_index_extraction_helper<std::ptrdiff_t, Base::count>::run(index, *this);
  }

  template <typename DenseIndex> inline
  size_t IndexOfColMajor(const array<DenseIndex, Base::count>& indices) const {
    return internal::fixed_size_tensor_index_linearization_helper<DenseIndex, Base::count, Base::count, false>::run(indices, *static_cast<const Base*>(this));
  }
  template <typename DenseIndex> inline
  size_t IndexOfRowMajor(const array<DenseIndex, Base::count>& indices) const {
    return internal::fixed_size_tensor_index_linearization_helper<DenseIndex, Base::count, Base::count, true>::run(indices, *static_cast<const Base*>(this));
  }
};

namespace internal {
template <typename std::ptrdiff_t... Indices>
inline std::ptrdiff_t array_prod(const Sizes<Indices...>&) {
  return Sizes<Indices...>::total_size;
}
}


// Boilerplate
namespace internal {
template<typename Index, std::size_t NumIndices, std::size_t n, bool RowMajor>
struct tensor_index_linearization_helper
{
  static inline
  Index run(array<Index, NumIndices> const& indices, array<Index, NumIndices> const& dimensions)
  {
    return array_get<RowMajor ? n : (NumIndices - n - 1)>(indices) +
      array_get<RowMajor ? n : (NumIndices - n - 1)>(dimensions) *
        tensor_index_linearization_helper<Index, NumIndices, n - 1, RowMajor>::run(indices, dimensions);
  }
};

template<typename Index, std::size_t NumIndices, bool RowMajor>
struct tensor_index_linearization_helper<Index, NumIndices, 0, RowMajor>
{
  static inline
  Index run(array<Index, NumIndices> const& indices, array<Index, NumIndices> const&)
  {
    return array_get<RowMajor ? 0 : NumIndices - 1>(indices);
  }
};
}  // end namespace internal



// Dynamic size
template <typename DenseIndex, std::size_t NumDims>
struct DSizes : array<DenseIndex, NumDims> {
  typedef array<DenseIndex, NumDims> Base;
  static const std::size_t count = NumDims;

  inline size_t rank() const {
    return NumDims;
  }

  inline DenseIndex TotalSize() const {
    return internal::array_prod(*static_cast<const Base*>(this));
  }

  DSizes() {
    for (std::size_t i = 0 ; i < NumDims; ++i) {
      (*this)[i] = 0;
    }
  }
  explicit DSizes(const array<DenseIndex, NumDims>& a) : Base(a) { }

  template<typename... IndexTypes> 
  inline explicit DSizes(DenseIndex firstDimension, IndexTypes... otherDimensions) {
    static_assert(sizeof...(otherDimensions) + 1 == NumDims, "you made a programming mistake");
    (*this) = array<DenseIndex, NumDims>{{firstDimension, otherDimensions...}};
  }

  DSizes& operator = (const array<DenseIndex, NumDims>& other) {
    *static_cast<Base*>(this) = other;
    return *this;
  }

  // A constexpr would be so much better here
  inline DenseIndex IndexOfColMajor(const array<DenseIndex, NumDims>& indices) const {
    return internal::tensor_index_linearization_helper<DenseIndex, NumDims, NumDims - 1, false>::run(indices, *static_cast<const Base*>(this));
  }
  inline DenseIndex IndexOfRowMajor(const array<DenseIndex, NumDims>& indices) const {
    return internal::tensor_index_linearization_helper<DenseIndex, NumDims, NumDims - 1, true>::run(indices, *static_cast<const Base*>(this));
  }
};




// Boilerplate
namespace internal {
template<typename Index, std::size_t NumIndices, std::size_t n, bool RowMajor>
struct tensor_vsize_index_linearization_helper
{
  static inline
  Index run(array<Index, NumIndices> const& indices, std::vector<DenseIndex> const& dimensions)
  {
    return array_get<RowMajor ? n : (NumIndices - n - 1)>(indices) +
      array_get<RowMajor ? n : (NumIndices - n - 1)>(dimensions) *
        tensor_vsize_index_linearization_helper<Index, NumIndices, n - 1, RowMajor>::run(indices, dimensions);
  }
};

template<typename Index, std::size_t NumIndices, bool RowMajor>
struct tensor_vsize_index_linearization_helper<Index, NumIndices, 0, RowMajor>
{
  static inline
  Index run(array<Index, NumIndices> const& indices, std::vector<DenseIndex> const&)
  {
    return array_get<RowMajor ? 0 : NumIndices - 1>(indices);
  }
};
}  // end namespace internal


namespace internal {

template <typename DenseIndex, std::size_t NumDims> struct array_size<const DSizes<DenseIndex, NumDims> > {
  static const size_t value = NumDims;
};
template <typename DenseIndex, std::size_t NumDims> struct array_size<DSizes<DenseIndex, NumDims> > {
  static const size_t value = NumDims;
};
template <typename std::ptrdiff_t... Indices> struct array_size<const Sizes<Indices...> > {
static const std::ptrdiff_t value = Sizes<Indices...>::count;
};
template <typename std::ptrdiff_t... Indices> struct array_size<Sizes<Indices...> > {
static const std::ptrdiff_t value = Sizes<Indices...>::count;
};
template <std::ptrdiff_t n, typename std::ptrdiff_t... Indices> inline std::ptrdiff_t array_get(const Sizes<Indices...>&) {
  return get<n, internal::numeric_list<std::size_t, Indices...> >::value;
}

template <typename Dims1, typename Dims2, size_t n, size_t m>
struct sizes_match_below_dim {
  static inline bool run(Dims1&, Dims2&) {
    return false;
  }
};
template <typename Dims1, typename Dims2, size_t n>
struct sizes_match_below_dim<Dims1, Dims2, n, n> {
  static inline bool run(Dims1& dims1, Dims2& dims2) {
    return (array_get<n-1>(dims1) == array_get<n-1>(dims2)) &
        sizes_match_below_dim<Dims1, Dims2, n-1, n-1>::run(dims1, dims2);
  }
};
template <typename Dims1, typename Dims2>
struct sizes_match_below_dim<Dims1, Dims2, 0, 0> {
  static inline bool run(Dims1&, Dims2&) {
    return true;
  }
};

} // end namespace internal


template <typename Dims1, typename Dims2>
bool dimensions_match(Dims1& dims1, Dims2& dims2) {
  return internal::sizes_match_below_dim<Dims1, Dims2, internal::array_size<Dims1>::value, internal::array_size<Dims2>::value>::run(dims1, dims2);
}

} // end namespace Eigen

#endif // EIGEN_CXX11_TENSOR_TENSOR_DIMENSIONS_H
