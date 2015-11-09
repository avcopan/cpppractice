// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2014 Benoit Steiner <benoit.steiner.goog@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_CXX11_TENSOR_TENSOR_FUNCTORS_H
#define EIGEN_CXX11_TENSOR_TENSOR_FUNCTORS_H

namespace Eigen {
namespace internal {


/** \internal
 * \brief Template functor to compute the modulo between an array and a scalar.
 */
template <typename Scalar>
struct scalar_mod_op {
  scalar_mod_op(const Scalar& divisor) : m_divisor(divisor) {}
  inline Scalar operator() (const Scalar& a) const { return a % m_divisor; }
  const Scalar m_divisor;
};
template <typename Scalar>
struct functor_traits<scalar_mod_op<Scalar> >
{ enum { Cost = 2 * NumTraits<Scalar>::MulCost, PacketAccess = false }; };


/** \internal
  * \brief Template functor to compute the sigmoid of a scalar
  * \sa class CwiseUnaryOp, ArrayBase::sigmoid()
  */
template <typename T>
struct scalar_sigmoid_op {
  EIGEN_EMPTY_STRUCT_CTOR(scalar_sigmoid_op)
  inline T operator()(const T& x) const {
    const T one = T(1);
    return one / (one + std::exp(-x));
  }

  template <typename Packet>
  inline Packet packetOp(const Packet& x) const {
    const Packet one = pset1<Packet>(1);
    return pdiv(one, padd(one, pexp(pnegate(x))));
  }
};

template <typename T>
struct functor_traits<scalar_sigmoid_op<T> > {
  enum {
    Cost = NumTraits<T>::AddCost * 2 + NumTraits<T>::MulCost * 6,
    PacketAccess = packet_traits<T>::HasAdd && packet_traits<T>::HasDiv &&
                   packet_traits<T>::HasNegate && packet_traits<T>::HasExp
  };
};



// Random number generation
namespace {
int get_random_seed() {
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return static_cast<int>(ts.tv_nsec);
}
}

template <typename T> class UniformRandomGenerator {

 public:
  static const bool PacketAccess = true;

  UniformRandomGenerator(bool deterministic = true) : m_deterministic(deterministic) {
    if (!deterministic) {
      srand(get_random_seed());
    }
  }
  UniformRandomGenerator(const UniformRandomGenerator& other) {
    m_deterministic = other.m_deterministic;
  }

  template<typename Index>
  T operator()(Index, Index = 0) const {
    return random<T>();
  }
  template<typename Index>
  typename internal::packet_traits<T>::type packetOp(Index, Index = 0) const {
    const int packetSize = internal::packet_traits<T>::size;
    EIGEN_ALIGN_MAX T values[packetSize];
    for (int i = 0; i < packetSize; ++i) {
      values[i] = random<T>();
    }
    return internal::pload<typename internal::packet_traits<T>::type>(values);
  }

 private:
  bool m_deterministic;
};

template <> class UniformRandomGenerator<float> {
 public:
  static const bool PacketAccess = true;

  UniformRandomGenerator(bool deterministic = true) : m_deterministic(deterministic) {
    if (!deterministic) {
      m_generator.seed(get_random_seed());
    }
  }
  UniformRandomGenerator(const UniformRandomGenerator<float>& other) {
    m_generator.seed(other(0, 0) * UINT_MAX);
    m_deterministic = other.m_deterministic;
  }

  template<typename Index>
  float operator()(Index, Index = 0) const {
    return m_distribution(m_generator);
  }
  template<typename Index>
  typename internal::packet_traits<float>::type packetOp(Index i, Index j = 0) const {
    const int packetSize = internal::packet_traits<float>::size;
    EIGEN_ALIGN_MAX float values[packetSize];
    for (int k = 0; k < packetSize; ++k) {
      values[k] = this->operator()(i, j);
    }
    return internal::pload<typename internal::packet_traits<float>::type>(values);
  }

 private:
  UniformRandomGenerator& operator = (const UniformRandomGenerator&);
  // Make sure m_deterministic comes first to match the layout of the cpu
  // version of the code.
  bool m_deterministic;
  mutable std::mt19937 m_generator;
  mutable std::uniform_real_distribution<float> m_distribution;
};

template <> class UniformRandomGenerator<double> {
 public:
  static const bool PacketAccess = true;

  UniformRandomGenerator(bool deterministic = true) : m_deterministic(deterministic) {
    if (!deterministic) {
      m_generator.seed(get_random_seed());
    }
  }
  UniformRandomGenerator(const UniformRandomGenerator<double>& other) {
    m_generator.seed(other(0, 0) * UINT_MAX);
    m_deterministic = other.m_deterministic;
  }

  template<typename Index>
  double operator()(Index, Index = 0) const {
    return m_distribution(m_generator);
  }
  template<typename Index>
  typename internal::packet_traits<double>::type packetOp(Index i, Index j = 0) const {
    const int packetSize = internal::packet_traits<double>::size;
    EIGEN_ALIGN_MAX double values[packetSize];
    for (int k = 0; k < packetSize; ++k) {
      values[k] = this->operator()(i, j);
    }
    return internal::pload<typename internal::packet_traits<double>::type>(values);
  }

 private:
  UniformRandomGenerator& operator = (const UniformRandomGenerator&);
  // Make sure m_deterministic comes first to match the layout of the cpu
  // version of the code.
  bool m_deterministic;
  mutable std::mt19937 m_generator;
  mutable std::uniform_real_distribution<double> m_distribution;
};


template <typename T> class NormalRandomGenerator {
 public:
  static const bool PacketAccess = true;

  NormalRandomGenerator(bool deterministic = true) : m_deterministic(deterministic), m_distribution(0, 1) {
    if (!deterministic) {
      m_generator.seed(get_random_seed());
    }
  }
  NormalRandomGenerator(const NormalRandomGenerator& other)
      : m_deterministic(other.m_deterministic), m_distribution(other.m_distribution) {
    m_generator.seed(other(0, 0) * UINT_MAX);
  }

  template<typename Index>
  T operator()(Index, Index = 0) const {
    return m_distribution(m_generator);
  }
  template<typename Index>
  typename internal::packet_traits<T>::type packetOp(Index, Index = 0) const {
    const int packetSize = internal::packet_traits<T>::size;
    EIGEN_ALIGN_MAX T values[packetSize];
    for (int i = 0; i < packetSize; ++i) {
      values[i] = m_distribution(m_generator);
    }
    return internal::pload<typename internal::packet_traits<T>::type>(values);
  }

 private:
  bool m_deterministic;
  mutable std::normal_distribution<T> m_distribution;
  mutable std::mt19937 m_generator;
};


template <typename T, typename Index, size_t NumDims>
class GaussianGenerator {
 public:
  static const bool PacketAccess = false;

  GaussianGenerator(const array<T, NumDims>& means,
                                      const array<T, NumDims>& std_devs)
      : m_means(means)
  {
    for (size_t i = 0; i < NumDims; ++i) {
      m_two_sigmas[i] = std_devs[i] * std_devs[i] * 2;
    }
  }

  T operator()(const array<Index, NumDims>& coordinates) const {
    T tmp = T(0);
    for (size_t i = 0; i < NumDims; ++i) {
      T offset = coordinates[i] - m_means[i];
      tmp += offset * offset / m_two_sigmas[i];
    }
    return std::exp(-tmp);
  }

 private:
  array<T, NumDims> m_means;
  array<T, NumDims> m_two_sigmas;
};


} // end namespace internal
} // end namespace Eigen

#endif // EIGEN_CXX11_TENSOR_TENSOR_FUNCTORS_H
