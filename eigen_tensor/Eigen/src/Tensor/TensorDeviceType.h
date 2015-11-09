// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2014 Benoit Steiner <benoit.steiner.goog@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_CXX11_TENSOR_TENSOR_DEVICE_TYPE_H
#define EIGEN_CXX11_TENSOR_TENSOR_DEVICE_TYPE_H


namespace Eigen {

// Default device for the machine (typically a single cpu core)
struct DefaultDevice {
  inline void* allocate(size_t num_bytes) const {
    return internal::aligned_malloc(num_bytes);
  }
  inline void deallocate(void* buffer) const {
    internal::aligned_free(buffer);
  }
  inline void memcpy(void* dst, const void* src, size_t n) const {
    ::memcpy(dst, src, n);
  }
  inline void memcpyHostToDevice(void* dst, const void* src, size_t n) const {
    memcpy(dst, src, n);
  }
  inline void memcpyDeviceToHost(void* dst, const void* src, size_t n) const {
    memcpy(dst, src, n);
  }
  inline void memset(void* buffer, int c, size_t n) const {
    ::memset(buffer, c, n);
  }

  inline size_t numThreads() const {
    return 1;
  }

  inline int majorDeviceVersion() const {
    return 1;
  }
};




}  // end namespace Eigen

#endif // EIGEN_CXX11_TENSOR_TENSOR_DEVICE_TYPE_H
