// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2014 Benoit Steiner <benoit.steiner.goog@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_CXX11_TENSOR_TENSOR_INTDIV_H
#define EIGEN_CXX11_TENSOR_TENSOR_INTDIV_H


namespace Eigen {

/** \internal
  *
  * \class TensorIntDiv
  * \ingroup CXX11_Tensor_Module
  *
  * \brief Fast integer division by a constant.
  *
  * See the paper from Granlund and Montgomery for explanation.
  *   (at http://dx.doi.org/10.1145/773473.178249)
  *
  * \sa Tensor
  */

namespace internal {

namespace {
  // Note: result is undefined if val == 0
  template <typename T>
  inline int count_leading_zeros(const T val)
  {
    if (sizeof(T) == 8) {
      return __builtin_clzl(static_cast<uint64_t>(val));
    }
    return __builtin_clz(static_cast<uint32_t>(val));
  }

  template <typename T>
  struct UnsignedTraits {
    typedef typename conditional<sizeof(T) == 8, uint64_t, uint32_t>::type type;
  };

  template <typename T>
  struct DividerTraits {
    typedef typename UnsignedTraits<T>::type type;
    static const int N = sizeof(T) * 8;
  };

  template <typename T>
  inline uint32_t muluh(const uint32_t a, const T b) {
    return (static_cast<uint64_t>(a) * b) >> 32;
  }

  template <typename T>
  inline uint64_t muluh(const uint64_t a, const T b) {
    __uint128_t v = static_cast<__uint128_t>(a) * static_cast<__uint128_t>(b);
    return static_cast<uint64_t>(v >> 64);
  }

  template <int N, typename T>
  struct DividerHelper {
    static inline uint32_t computeMultiplier (const int log_div, const T divider) {
      static_assert(N == 32, "you made a programming mistake");
      return static_cast<uint32_t>((static_cast<uint64_t>(1) << (N+log_div)) / divider - (static_cast<uint64_t>(1) << N) + 1);
    }
  };

  template <typename T>
  struct DividerHelper<64, T> {
    static inline uint64_t computeMultiplier(const int log_div, const T divider) {
      return static_cast<uint64_t>((static_cast<__uint128_t>(1) << (64+log_div)) / static_cast<__uint128_t>(divider) - (static_cast<__uint128_t>(1) << 64) + 1);
    }
  };
}


template <typename T>
struct TensorIntDivisor {
 public:
  inline TensorIntDivisor() {
    multiplier = 0;
    shift1 = 0;
    shift2 = 0;
  }

  // Must have 0 < divider < 2^31. This is relaxed to
  // 0 < divider < 2^63 when using 64-bit indices on platforms that support
  // the __uint128_t type.
  inline TensorIntDivisor(const T divider) {
    const int N = DividerTraits<T>::N;
    eigen_assert(static_cast<typename UnsignedTraits<T>::type>(divider) < NumTraits<UnsignedType>::highest()/2);
    eigen_assert(divider > 0);

    // fast ln2
    const int leading_zeros = count_leading_zeros(static_cast<UnsignedType>(divider));
    int log_div = N - leading_zeros;
    // if divider is a power of two then log_div is 1 more than it should be.
    if ((static_cast<typename UnsignedTraits<T>::type>(1) << (log_div-1)) == static_cast<typename UnsignedTraits<T>::type>(divider))
      log_div--;

    multiplier = DividerHelper<N, T>::computeMultiplier(log_div, divider);
    shift1 = log_div > 1 ? 1 : log_div;
    shift2 = log_div > 1 ? log_div-1 : 0;
  }

  // Must have 0 <= numerator. On platforms that dont support the __uint128_t
  // type numerator should also be less than 2^32-1.
  inline T divide(const T numerator) const {
    eigen_assert(static_cast<typename UnsignedTraits<T>::type>(numerator) < NumTraits<UnsignedType>::highest()/2);
    //eigen_assert(numerator >= 0); // this is implicitly asserted by the line above

    UnsignedType t1 = muluh(multiplier, numerator);
    UnsignedType t = (static_cast<UnsignedType>(numerator) - t1) >> shift1;
    return (t1 + t) >> shift2;
  }

 private:
  typedef typename DividerTraits<T>::type UnsignedType;
  UnsignedType multiplier;
  int32_t shift1;
  int32_t shift2;
};


// Optimized version for signed 32 bit integers.
// Derived from Hacker's Delight.
template <>
class TensorIntDivisor<int32_t> {
 public:
  inline TensorIntDivisor() {
    magic = 0;
    shift = 0;
  }
  // Must have 2 <= divider
  TensorIntDivisor(int32_t divider)  {
    eigen_assert(divider >= 2);
    calcMagic(divider);
  }

  inline int divide(const int32_t n) const {
    uint64_t v = static_cast<uint64_t>(magic) * static_cast<uint64_t>(n);
    return (static_cast<uint32_t>(v >> 32) >> shift);
  }

private:
  // Compute the magic numbers. See Hacker's Delight section 10 for an in
  // depth explanation.
  void calcMagic(int32_t d) {
   const unsigned two31 = 0x80000000;     // 2**31.
   unsigned ad = d;
   unsigned t = two31 + (ad >> 31);
   unsigned anc = t - 1 - t%ad;     // Absolute value of nc.
   int p = 31;                      // Init. p.
   unsigned q1 = two31/anc;         // Init. q1 = 2**p/|nc|.
   unsigned r1 = two31 - q1*anc;    // Init. r1 = rem(2**p, |nc|).
   unsigned q2 = two31/ad;          // Init. q2 = 2**p/|d|.
   unsigned r2 = two31 - q2*ad;     // Init. r2 = rem(2**p, |d|).
   unsigned delta = 0;
   do {
      p = p + 1;
      q1 = 2*q1;           // Update q1 = 2**p/|nc|.
      r1 = 2*r1;           // Update r1 = rem(2**p, |nc|).
      if (r1 >= anc) {     // (Must be an unsigned
         q1 = q1 + 1;      // comparison here).
         r1 = r1 - anc;}
      q2 = 2*q2;           // Update q2 = 2**p/|d|.
      r2 = 2*r2;           // Update r2 = rem(2**p, |d|).
      if (r2 >= ad) {      // (Must be an unsigned
         q2 = q2 + 1;      // comparison here).
         r2 = r2 - ad;}
      delta = ad - r2;
   } while (q1 < delta || (q1 == delta && r1 == 0));

   magic = (unsigned)(q2 + 1);
   shift = p - 32;
  }

  uint32_t magic;
  int32_t shift;
};


template <typename T>
static inline T operator / (const T& numerator, const TensorIntDivisor<T>& divisor) {
  return divisor.divide(numerator);
}


} // end namespace internal
} // end namespace Eigen

#endif // EIGEN_CXX11_TENSOR_TENSOR_INTDIV_H
