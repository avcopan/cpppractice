// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2014 Benoit Steiner <benoit.steiner.goog@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_CXX11_TENSOR_TENSOR_BASE_H
#define EIGEN_CXX11_TENSOR_TENSOR_BASE_H

// clang-format off

namespace Eigen {

/** \class TensorBase
  * \ingroup CXX11_Tensor_Module
  *
  * \brief The tensor base class.
  *
  * This class is the common parent of the Tensor and TensorMap class, thus
  * making it possible to use either class interchangably in expressions.
  */

template<typename Derived>
class TensorBase<Derived, ReadOnlyAccessors>
{
  public:
    typedef internal::traits<Derived> DerivedTraits;
    typedef typename DerivedTraits::Scalar Scalar;
    typedef typename DerivedTraits::Index Index;
    typedef typename internal::remove_const<Scalar>::type CoeffReturnType;
    typedef typename internal::packet_traits<CoeffReturnType>::type PacketReturnType;
    static const int NumDimensions = DerivedTraits::NumDimensions;

    // Generic nullary operation support.
    template <typename CustomNullaryOp> 
    inline const TensorCwiseNullaryOp<CustomNullaryOp, const Derived>
    nullaryExpr(const CustomNullaryOp& func) const {
      return TensorCwiseNullaryOp<CustomNullaryOp, const Derived>(derived(), func);
    }

    // Coefficient-wise nullary operators
    
    inline const TensorCwiseNullaryOp<internal::scalar_constant_op<Scalar>, const Derived>
    constant(const Scalar& value) const {
      return nullaryExpr(internal::scalar_constant_op<Scalar>(value));
    }

    
    inline const TensorCwiseNullaryOp<internal::UniformRandomGenerator<Scalar>, const Derived>
    random() const {
      return nullaryExpr(internal::UniformRandomGenerator<Scalar>());
    }
    template <typename RandomGenerator> 
    inline const TensorCwiseNullaryOp<RandomGenerator, const Derived>
    random(const RandomGenerator& gen = RandomGenerator()) const {
      return nullaryExpr(gen);
    }

    // Generic unary operation support.
    template <typename CustomUnaryOp> 
    inline const TensorCwiseUnaryOp<CustomUnaryOp, const Derived>
    unaryExpr(const CustomUnaryOp& func) const {
      return TensorCwiseUnaryOp<CustomUnaryOp, const Derived>(derived(), func);
    }

    // Coefficient-wise unary operators
    
    inline const TensorCwiseUnaryOp<internal::scalar_opposite_op<Scalar>, const Derived>
    operator-() const {
      return unaryExpr(internal::scalar_opposite_op<Scalar>());
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_sqrt_op<Scalar>, const Derived>
    sqrt() const {
      return unaryExpr(internal::scalar_sqrt_op<Scalar>());
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_rsqrt_op<Scalar>, const Derived>
    rsqrt() const {
      return unaryExpr(internal::scalar_rsqrt_op<Scalar>());
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_square_op<Scalar>, const Derived>
    square() const {
      return unaryExpr(internal::scalar_square_op<Scalar>());
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_cube_op<Scalar>, const Derived>
    cube() const {
      return unaryExpr(internal::scalar_cube_op<Scalar>());
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_inverse_op<Scalar>, const Derived>
    inverse() const {
      return unaryExpr(internal::scalar_inverse_op<Scalar>());
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_tanh_op<Scalar>, const Derived>
    tanh() const {
      return unaryExpr(internal::scalar_tanh_op<Scalar>());
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_sigmoid_op<Scalar>, const Derived>
    sigmoid() const {
      return unaryExpr(internal::scalar_sigmoid_op<Scalar>());
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_exp_op<Scalar>, const Derived>
    exp() const {
      return unaryExpr(internal::scalar_exp_op<Scalar>());
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_log_op<Scalar>, const Derived>
    log() const {
      return unaryExpr(internal::scalar_log_op<Scalar>());
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_abs_op<Scalar>, const Derived>
    abs() const {
      return unaryExpr(internal::scalar_abs_op<Scalar>());
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_pow_op<Scalar>, const Derived>
    pow(Scalar exponent) const {
      return unaryExpr(internal::scalar_pow_op<Scalar>(exponent));
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_add_op<Scalar>, const Derived>
    operator+ (Scalar rhs) const {
      return unaryExpr(internal::scalar_add_op<Scalar>(rhs));
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_sub_op<Scalar>, const Derived>
    operator- (Scalar rhs) const {
      static_assert((std::numeric_limits<Scalar>::is_signed || internal::is_same<Scalar, const std::complex<float> >::value), "you made a programming mistake");
      return unaryExpr(internal::scalar_sub_op<Scalar>(rhs));
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_multiple_op<Scalar>, const Derived>
    operator* (Scalar rhs) const {
      return unaryExpr(internal::scalar_multiple_op<Scalar>(rhs));
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_quotient1_op<Scalar>, const Derived>
    operator/ (Scalar rhs) const {
      // static_assert(!std::numeric_limits<Scalar>::is_integer, "you made a programming mistake");
      return unaryExpr(internal::scalar_quotient1_op<Scalar>(rhs));
    }

    
    inline const TensorCwiseUnaryOp<internal::scalar_mod_op<Scalar>, const Derived>
    operator% (Scalar rhs) const {
      static_assert(std::numeric_limits<Scalar>::is_integer, "you made a programming mistake");
      return unaryExpr(internal::scalar_mod_op<Scalar>(rhs));
    }

    
    inline const TensorCwiseBinaryOp<internal::scalar_max_op<Scalar>, const Derived, const TensorCwiseNullaryOp<internal::scalar_constant_op<Scalar>, const Derived> >
    cwiseMax(Scalar threshold) const {
      return cwiseMax(constant(threshold));
    }

    
    inline const TensorCwiseBinaryOp<internal::scalar_min_op<Scalar>, const Derived, const TensorCwiseNullaryOp<internal::scalar_constant_op<Scalar>, const Derived> >
    cwiseMin(Scalar threshold) const {
      return cwiseMin(constant(threshold));
    }

    // Generic binary operation support.
    template <typename CustomBinaryOp, typename OtherDerived> 
    inline const TensorCwiseBinaryOp<CustomBinaryOp, const Derived, const OtherDerived>
    binaryExpr(const OtherDerived& other, const CustomBinaryOp& func) const {
      return TensorCwiseBinaryOp<CustomBinaryOp, const Derived, const OtherDerived>(derived(), other, func);
    }

    // Coefficient-wise binary operators.
    template<typename OtherDerived> inline
    const TensorCwiseBinaryOp<internal::scalar_sum_op<Scalar>, const Derived, const OtherDerived>
    operator+(const OtherDerived& other) const {
      return binaryExpr(other.derived(), internal::scalar_sum_op<Scalar>());
    }

    template<typename OtherDerived> inline
    const TensorCwiseBinaryOp<internal::scalar_difference_op<Scalar>, const Derived, const OtherDerived>
    operator-(const OtherDerived& other) const {
      return binaryExpr(other.derived(), internal::scalar_difference_op<Scalar>());
    }

    template<typename OtherDerived> inline
    const TensorCwiseBinaryOp<internal::scalar_product_op<Scalar>, const Derived, const OtherDerived>
    operator*(const OtherDerived& other) const {
      return binaryExpr(other.derived(), internal::scalar_product_op<Scalar>());
    }

    template<typename OtherDerived> inline
    const TensorCwiseBinaryOp<internal::scalar_quotient_op<Scalar>, const Derived, const OtherDerived>
    operator/(const OtherDerived& other) const {
      return binaryExpr(other.derived(), internal::scalar_quotient_op<Scalar>());
    }

    template<typename OtherDerived> inline
    const TensorCwiseBinaryOp<internal::scalar_max_op<Scalar>, const Derived, const OtherDerived>
    cwiseMax(const OtherDerived& other) const {
      return binaryExpr(other.derived(), internal::scalar_max_op<Scalar>());
    }

    template<typename OtherDerived> inline
    const TensorCwiseBinaryOp<internal::scalar_min_op<Scalar>, const Derived, const OtherDerived>
    cwiseMin(const OtherDerived& other) const {
      return binaryExpr(other.derived(), internal::scalar_min_op<Scalar>());
    }

    template<typename OtherDerived> inline
    const TensorCwiseBinaryOp<internal::scalar_boolean_and_op, const Derived, const OtherDerived>
    operator&&(const OtherDerived& other) const {
      return binaryExpr(other.derived(), internal::scalar_boolean_and_op());
    }

    template<typename OtherDerived> inline
    const TensorCwiseBinaryOp<internal::scalar_boolean_or_op, const Derived, const OtherDerived>
    operator||(const OtherDerived& other) const {
      return binaryExpr(other.derived(), internal::scalar_boolean_or_op());
    }

    // Comparisons and tests.
    template<typename OtherDerived> inline
    const TensorCwiseBinaryOp<internal::scalar_cmp_op<Scalar, internal::cmp_LT>, const Derived, const OtherDerived>
    operator<(const OtherDerived& other) const {
      return binaryExpr(other.derived(), internal::scalar_cmp_op<Scalar, internal::cmp_LT>());
    }
    template<typename OtherDerived> inline
    const TensorCwiseBinaryOp<internal::scalar_cmp_op<Scalar, internal::cmp_LE>, const Derived, const OtherDerived>
    operator<=(const OtherDerived& other) const {
      return binaryExpr(other.derived(), internal::scalar_cmp_op<Scalar, internal::cmp_LE>());
    }
    template<typename OtherDerived> inline
    const TensorCwiseBinaryOp<internal::scalar_cmp_op<Scalar, internal::cmp_GT>, const Derived, const OtherDerived>
    operator>(const OtherDerived& other) const {
      return binaryExpr(other.derived(), internal::scalar_cmp_op<Scalar, internal::cmp_GT>());
    }
    template<typename OtherDerived> inline
    const TensorCwiseBinaryOp<internal::scalar_cmp_op<Scalar, internal::cmp_GE>, const Derived, const OtherDerived>
    operator>=(const OtherDerived& other) const {
      return binaryExpr(other.derived(), internal::scalar_cmp_op<Scalar, internal::cmp_GE>());
    }

    template<typename OtherDerived> inline
    const TensorCwiseBinaryOp<internal::scalar_cmp_op<Scalar, internal::cmp_EQ>, const Derived, const OtherDerived>
    operator==(const OtherDerived& other) const {
      return binaryExpr(other.derived(), internal::scalar_cmp_op<Scalar, internal::cmp_EQ>());
    }
    template<typename OtherDerived> inline
    const TensorCwiseBinaryOp<internal::scalar_cmp_op<Scalar, internal::cmp_NEQ>, const Derived, const OtherDerived>
    operator!=(const OtherDerived& other) const {
      return binaryExpr(other.derived(), internal::scalar_cmp_op<Scalar, internal::cmp_NEQ>());
    }

    // comparisons and tests for Scalars
    
    inline const TensorCwiseBinaryOp<internal::scalar_cmp_op<Scalar, internal::cmp_LT>, const Derived, const TensorCwiseNullaryOp<internal::scalar_constant_op<Scalar>, const Derived> >
    operator<(Scalar threshold) const {
      return operator<(constant(threshold));
    }
    
    inline const TensorCwiseBinaryOp<internal::scalar_cmp_op<Scalar, internal::cmp_LE>, const Derived, const TensorCwiseNullaryOp<internal::scalar_constant_op<Scalar>, const Derived> >
    operator<=(Scalar threshold) const {
      return operator<=(constant(threshold));
    }
    
    inline const TensorCwiseBinaryOp<internal::scalar_cmp_op<Scalar, internal::cmp_GT>, const Derived, const TensorCwiseNullaryOp<internal::scalar_constant_op<Scalar>, const Derived> >
    operator>(Scalar threshold) const {
      return operator>(constant(threshold));
    }
    
    inline const TensorCwiseBinaryOp<internal::scalar_cmp_op<Scalar, internal::cmp_GE>, const Derived, const TensorCwiseNullaryOp<internal::scalar_constant_op<Scalar>, const Derived> >
    operator>=(Scalar threshold) const {
      return operator>=(constant(threshold));
    }
    
    inline const TensorCwiseBinaryOp<internal::scalar_cmp_op<Scalar, internal::cmp_EQ>, const Derived, const TensorCwiseNullaryOp<internal::scalar_constant_op<Scalar>, const Derived> >
    operator==(Scalar threshold) const {
      return operator==(constant(threshold));
    }
    
    inline const TensorCwiseBinaryOp<internal::scalar_cmp_op<Scalar, internal::cmp_NEQ>, const Derived, const TensorCwiseNullaryOp<internal::scalar_constant_op<Scalar>, const Derived> >
    operator!=(Scalar threshold) const {
      return operator!=(constant(threshold));
    }

    // Coefficient-wise ternary operators.
    template<typename ThenDerived, typename ElseDerived> inline
    const TensorSelectOp<const Derived, const ThenDerived, const ElseDerived>
    select(const ThenDerived& thenTensor, const ElseDerived& elseTensor) const {
      return TensorSelectOp<const Derived, const ThenDerived, const ElseDerived>(derived(), thenTensor.derived(), elseTensor.derived());
    }

    // Contractions.
    typedef Eigen::IndexPair<Index> DimensionPair;

    template<typename OtherDerived, typename Dimensions> inline
    const TensorContractionOp<const Dimensions, const Derived, const OtherDerived>
    contract(const OtherDerived& other, const Dimensions& dims) const {
      return TensorContractionOp<const Dimensions, const Derived, const OtherDerived>(derived(), other.derived(), dims);
    }

    template <typename Broadcast> inline
    const TensorBroadcastingOp<const Broadcast, const Derived>
    broadcast(const Broadcast& broadcast) const {
      return TensorBroadcastingOp<const Broadcast, const Derived>(derived(), broadcast);
    }


    // Morphing operators.
    template <typename NewDimensions> inline
    const TensorReshapingOp<const NewDimensions, const Derived>
    reshape(const NewDimensions& newDimensions) const {
      return TensorReshapingOp<const NewDimensions, const Derived>(derived(), newDimensions);
    }
    template <typename StartIndices, typename Sizes> inline
    const TensorSlicingOp<const StartIndices, const Sizes, const Derived>
    slice(const StartIndices& startIndices, const Sizes& sizes) const {
      return TensorSlicingOp<const StartIndices, const Sizes, const Derived>(derived(), startIndices, sizes);
    }
    template <typename Shuffle> inline
    const TensorShufflingOp<const Shuffle, const Derived>
    shuffle(const Shuffle& shuffle) const {
      return TensorShufflingOp<const Shuffle, const Derived>(derived(), shuffle);
    }
    // Returns a tensor containing index/value tuples
    inline
    const TensorIndexTupleOp<const Derived>
    index_tuples() const {
      return TensorIndexTupleOp<const Derived>(derived());
    }

    // Force the evaluation of the expression.
    inline
    const TensorForcedEvalOp<const Derived> eval() const {
      return TensorForcedEvalOp<const Derived>(derived());
    }

  protected:
    template <typename Scalar, std::size_t NumIndices, int Options, typename IndexType> friend class Tensor;
   template <typename Scalar, typename Dimensions, int Option, typename IndexTypes> friend class TensorFixedSize;
    template <typename OtherDerived, int AccessLevel> friend class TensorBase;
    
    inline const Derived& derived() const { return *static_cast<const Derived*>(this); }
};

template<typename Derived>
class TensorBase<Derived, WriteAccessors> : public TensorBase<Derived, ReadOnlyAccessors> {
 public:
    typedef internal::traits<Derived> DerivedTraits;
    typedef typename DerivedTraits::Scalar Scalar;
    typedef typename DerivedTraits::Index Index;
    typedef Scalar CoeffReturnType;
    typedef typename internal::packet_traits<Scalar>::type PacketReturnType;
    static const int NumDimensions = DerivedTraits::NumDimensions;

    template <typename Scalar, std::size_t NumIndices, int Options, typename IndexType> friend class Tensor;
    template <typename Scalar, typename Dimensions, int Option, typename IndexTypes> friend class TensorFixedSize;
    template <typename OtherDerived, int AccessLevel> friend class TensorBase;

    
    inline Derived& setZero() {
      return setConstant(Scalar(0));
    }
    
    inline Derived& setConstant(const Scalar& val) {
      return derived() = this->constant(val);
    }
    
    inline Derived& setRandom() {
      return derived() = this->random();
    }
    template <typename RandomGenerator> 
    inline Derived& setRandom() {
      return derived() = this->template random<RandomGenerator>();
    }

    
    inline Derived& setValues(
        const typename internal::Initializer<Derived, NumDimensions>::InitList& vals) {
      TensorEvaluator<Derived, DefaultDevice> eval(derived(), DefaultDevice());
      internal::initialize_tensor<Derived, NumDimensions>(eval, vals);
      return derived();
    }

    template<typename OtherDerived> inline
    Derived& operator+=(const OtherDerived& other) {
      return derived() = derived() + other.derived();
    }
    template<typename OtherDerived> inline
    Derived& operator-=(const OtherDerived& other) {
      return derived() = derived() - other.derived();
    }
    template<typename OtherDerived> inline
    Derived& operator*=(const OtherDerived& other) {
      return derived() = derived() * other.derived();
    }
    template<typename OtherDerived> inline
    Derived& operator/=(const OtherDerived& other) {
      return derived() = derived() / other.derived();
    }

    template <typename NewDimensions> inline
    const TensorReshapingOp<const NewDimensions, const Derived>
    reshape(const NewDimensions& newDimensions) const {
      return TensorReshapingOp<const NewDimensions, const Derived>(derived(), newDimensions);
    }
    template <typename NewDimensions> inline
    TensorReshapingOp<const NewDimensions, Derived>
    reshape(const NewDimensions& newDimensions) {
      return TensorReshapingOp<const NewDimensions, Derived>(derived(), newDimensions);
    }

    template <typename StartIndices, typename Sizes> inline
    const TensorSlicingOp<const StartIndices, const Sizes, const Derived>
    slice(const StartIndices& startIndices, const Sizes& sizes) const {
      return TensorSlicingOp<const StartIndices, const Sizes, const Derived>(derived(), startIndices, sizes);
    }
    template <typename StartIndices, typename Sizes> inline
    TensorSlicingOp<const StartIndices, const Sizes, Derived>
    slice(const StartIndices& startIndices, const Sizes& sizes) {
      return TensorSlicingOp<const StartIndices, const Sizes, Derived>(derived(), startIndices, sizes);
    }

    template <typename Shuffle> inline
    const TensorShufflingOp<const Shuffle, const Derived>
    shuffle(const Shuffle& shuffle) const {
      return TensorShufflingOp<const Shuffle, const Derived>(derived(), shuffle);
    }
    template <typename Shuffle> inline
    TensorShufflingOp<const Shuffle, Derived>
    shuffle(const Shuffle& shuffle) {
      return TensorShufflingOp<const Shuffle, Derived>(derived(), shuffle);
    }

    // Select the device on which to evaluate the expression.
    template <typename DeviceType>
    TensorDevice<Derived, DeviceType> device(const DeviceType& device) {
      return TensorDevice<Derived, DeviceType>(device, derived());
    }

 protected:
    
    inline Derived& derived() { return *static_cast<Derived*>(this); }
    
    inline const Derived& derived() const { return *static_cast<const Derived*>(this); }
};

} // end namespace Eigen

#endif // EIGEN_CXX11_TENSOR_TENSOR_BASE_H
