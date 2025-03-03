// sherpa-onnx/csrc/transpose.cc
//
// Copyright (c)  2023  Xiaomi Corporation

#include "sherpa-onnx/csrc/transpose.h"

#include <assert.h>

#include <algorithm>
#include <vector>

namespace sherpa_onnx {

template <typename T /*=float*/>
Ort::Value Transpose01(OrtAllocator *allocator, const Ort::Value *v) {
  std::vector<int64_t> shape = v->GetTensorTypeAndShapeInfo().GetShape();
  assert(shape.size() == 3);

  std::array<int64_t, 3> ans_shape{shape[1], shape[0], shape[2]};
  Ort::Value ans = Ort::Value::CreateTensor<float>(allocator, ans_shape.data(),
                                                   ans_shape.size());

  T *dst = ans.GetTensorMutableData<T>();
  auto plane_offset = shape[1] * shape[2];

  for (int64_t i = 0; i != ans_shape[0]; ++i) {
    const T *src = v->GetTensorData<T>() + i * shape[2];
    for (int64_t k = 0; k != ans_shape[1]; ++k) {
      std::copy(src, src + shape[2], dst);
      src += plane_offset;
      dst += shape[2];
    }
  }

  return ans;
}

template Ort::Value Transpose01<float>(OrtAllocator *allocator,
                                       const Ort::Value *v);

}  // namespace sherpa_onnx
