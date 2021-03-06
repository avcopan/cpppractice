// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2014 Benoit Steiner <benoit.steiner.goog@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_CXX11_TENSOR_TENSOR_TRAITS_H
#define EIGEN_CXX11_TENSOR_TENSOR_TRAITS_H

namespace Eigen {
namespace internal {


template<typename Scalar, int Options>
class compute_tensor_flags
{
  enum {
    is_dynamic_size_storage = 1,

    aligned_bit =
    (
        ((Options&DontAlign)==0) && (
#if EIGEN_MAX_STATIC_ALIGN_BYTES>0
            (!is_dynamic_size_storage)
#else
            0
#endif
            ||
#if EIGEN_MAX_ALIGN_BYTES>0
            is_dynamic_size_storage
#else
            0
#endif
      )
    ) ? AlignedBit : 0,
    packet_access_bit = packet_traits<Scalar>::Vectorizable && aligned_bit ? PacketAccessBit : 0
  };

  public:
    enum { ret = packet_access_bit | aligned_bit};
};


template<typename Scalar_, std::size_t NumIndices_, int Options_, typename IndexType_>
struct traits<Tensor<Scalar_, NumIndices_, Options_, IndexType_> >
{
  typedef Scalar_ Scalar;
  typedef Dense StorageKind;
  typedef IndexType_ Index;
  static const int NumDimensions = NumIndices_;
  static const int Layout = Options_ & RowMajor ? RowMajor : ColMajor;
  enum {
    Options = Options_,
    Flags = compute_tensor_flags<Scalar_, Options_>::ret | (is_const<Scalar_>::value ? 0 : LvalueBit),
  };
};

template<typename _Scalar, std::size_t NumIndices_, int Options, typename IndexType_>
struct eval<Tensor<_Scalar, NumIndices_, Options, IndexType_>, Eigen::Dense>
{
  typedef const Tensor<_Scalar, NumIndices_, Options, IndexType_>& type;
};

template<typename _Scalar, std::size_t NumIndices_, int Options, typename IndexType_>
struct eval<const Tensor<_Scalar, NumIndices_, Options, IndexType_>, Eigen::Dense>
{
  typedef const Tensor<_Scalar, NumIndices_, Options, IndexType_>& type;
};

// TODO nested<> does not exist anymore in Eigen/Core, and it thus has to be removed in favor of ref_selector.
template<typename T, int n=1, typename PlainObject = void> struct nested
{
  typedef typename ref_selector<T>::type type;
};

template <typename Scalar_, std::size_t NumIndices_, int Options_, typename IndexType_>
struct nested<Tensor<Scalar_, NumIndices_, Options_, IndexType_> >
{
  typedef const Tensor<Scalar_, NumIndices_, Options_, IndexType_>& type;
};

template <typename Scalar_, std::size_t NumIndices_, int Options_, typename IndexType_>
struct nested<const Tensor<Scalar_, NumIndices_, Options_, IndexType_> >
{
  typedef const Tensor<Scalar_, NumIndices_, Options_, IndexType_>& type;
};


}  // end namespace internal


}  // end namespace Eigen

#endif // EIGEN_CXX11_TENSOR_TENSOR_TRAITS_H
