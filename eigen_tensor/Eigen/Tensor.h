#ifndef EIGEN_CXX11_TENSOR_MODULE
#define EIGEN_CXX11_TENSOR_MODULE


#include "src/Core/util/DisableStupidWarnings.h"

// BEGIN STUFF FROM CORE

#define EIGEN_DEVICE_FUNC

#define EIGEN_USING_STD_MATH(FUNC) using std::FUNC;

#include "src/Core/util/Macros.h"

#include <complex>

#include "src/Core/util/MKL_support.h"

#include <cerrno>
#include <cstddef>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <functional>
#include <iosfwd>
#include <cstring>
#include <string>
#include <limits>
#include <climits> // for CHAR_BIT
#include <algorithm>

using std::size_t;
using std::ptrdiff_t;

#include "src/Core/util/Constants.h"
#include "src/Core/util/Meta.h"
#include "src/Core/util/ForwardDeclarations.h"
#include "src/Core/util/StaticAssert.h"
#include "src/Core/util/XprHelper.h"
#include "src/Core/util/Memory.h"

#include "src/Core/NumTraits.h"
#include "src/Core/MathFunctions.h"
#include "src/Core/GenericPacketMath.h"

#include "src/Core/arch/Default/Settings.h"

#include "src/Core/functors/BinaryFunctors.h"
#include "src/Core/functors/UnaryFunctors.h"
#include "src/Core/functors/NullaryFunctors.h"
#include "src/Core/functors/AssignmentFunctors.h"

#include "src/Core/DenseCoeffsBase.h"
#include "src/Core/DenseBase.h"
#include "src/Core/MatrixBase.h"
#include "src/Core/EigenBase.h"

#include "src/Core/CoreEvaluators.h"
#include "src/Core/AssignEvaluator.h"

#include "src/Core/ArrayBase.h"
#include "src/Core/util/BlasUtil.h"
#include "src/Core/DenseStorage.h"

#include "src/Core/PlainObjectBase.h"
#include "src/Core/Matrix.h"
#include "src/Core/Array.h"
#include "src/Core/Stride.h"
#include "src/Core/MapBase.h"
#include "src/Core/Map.h"
#include "src/Core/Transpose.h"
#include "src/Core/IO.h"
#include "src/Core/GeneralProduct.h"
#include "src/Core/products/GeneralBlockPanelKernel.h"
#include "src/Core/products/Parallelizer.h"
#include "src/Core/ProductEvaluators.h"
#include "src/Core/products/GeneralMatrixVector.h"
#include "src/Core/products/GeneralMatrixMatrix.h"

// END   STUFF FROM CORE


#include <vector>
#include <array>
#include "src/Core/util/CXX11Workarounds.h"
#include "src/Core/util/CXX11Meta.h"

#include <cstddef>
#include <cstring>
#include <stdint.h>

#include <time.h>

#include "src/Tensor/TensorForwardDeclarations.h"
#include "src/Tensor/TensorMeta.h"
#include "src/Tensor/TensorDeviceType.h"
#include "src/Tensor/TensorIndexList.h"
#include "src/Tensor/TensorDimensionList.h"
#include "src/Tensor/TensorDimensions.h"
#include "src/Tensor/TensorInitializer.h"
#include "src/Tensor/TensorTraits.h"
#include "src/Tensor/TensorFunctors.h"
#include "src/Tensor/TensorIntDiv.h"

#include "src/Tensor/TensorBase.h"

#include "src/Tensor/TensorEvaluator.h"
#include "src/Tensor/TensorExpr.h"
#include "src/Tensor/TensorContraction.h"
#include "src/Tensor/TensorBroadcasting.h"
#include "src/Tensor/TensorMorphing.h"
#include "src/Tensor/TensorShuffling.h"
#include "src/Tensor/TensorEvalTo.h"
#include "src/Tensor/TensorForcedEval.h"
#include "src/Tensor/TensorAssign.h"

#include "src/Tensor/TensorExecutor.h"

#include "src/Tensor/TensorStorage.h"
#include "src/Tensor/Tensor.h"

#include "src/Tensor/TensorIO.h"

#include "src/Core/util/ReenableStupidWarnings.h"

#endif // EIGEN_CXX11_TENSOR_MODULE
