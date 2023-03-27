// sherpa-onnx/csrc/online-transducer-decoder.cc
//
// Copyright (c)  2023  Xiaomi Corporation

#include "sherpa-onnx/csrc/online-transducer-decoder.h"

#include <utility>
#include <vector>

#include "onnxruntime_cxx_api.h"  // NOLINT
#include "sherpa-onnx/csrc/onnx-utils.h"

namespace sherpa_onnx {

OnlineTransducerDecoderResult::OnlineTransducerDecoderResult(
    const OnlineTransducerDecoderResult &other)
    : OnlineTransducerDecoderResult() {
  *this = other;
}

OnlineTransducerDecoderResult &OnlineTransducerDecoderResult::operator=(
    const OnlineTransducerDecoderResult &other) {
  if (this == &other) {
    return *this;
  }

  tokens = other.tokens;
  timestamps = other.timestamps;
  silences = other.silences;

  num_processed_frames = other.num_processed_frames;
  num_blank_frames = other.num_blank_frames;
  
  num_trailing_blanks = other.num_trailing_blanks;
  
  Ort::AllocatorWithDefaultOptions allocator;
  if (other.decoder_out) {
    decoder_out = Clone(allocator, &other.decoder_out);
  }

  hyps = other.hyps;

  return *this;
}

OnlineTransducerDecoderResult::OnlineTransducerDecoderResult(
    OnlineTransducerDecoderResult &&other)
    : OnlineTransducerDecoderResult() {
  *this = std::move(other);
}

OnlineTransducerDecoderResult &OnlineTransducerDecoderResult::operator=(
    OnlineTransducerDecoderResult &&other) {
  if (this == &other) {
    return *this;
  }

  tokens = std::move(other.tokens);
  timestamps = std::move(other.timestamps);
  silences = std::move(other.silences);
  
  num_processed_frames = other.num_processed_frames;
  num_blank_frames = other.num_blank_frames;
  num_trailing_blanks = other.num_trailing_blanks;
  
  decoder_out = std::move(other.decoder_out);
  hyps = std::move(other.hyps);

  return *this;
}

}  // namespace sherpa_onnx
