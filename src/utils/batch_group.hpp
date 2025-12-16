// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef SRC_UTILS_BATCH_GROUP_HPP
#define SRC_UTILS_BATCH_GROUP_HPP

#include "skity/geometry/matrix.hpp"
#include "skity/graphic/paint.hpp"

namespace skity {

template <typename T>
struct BatchGroup {
  T item;
  Paint paint;
  Matrix transform;
};

}  // namespace skity

#endif
