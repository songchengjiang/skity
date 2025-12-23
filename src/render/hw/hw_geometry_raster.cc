// Copyright 2021 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#include "src/render/hw/hw_geometry_raster.hpp"

namespace skity {

HWGeometryRaster::HWGeometryRaster(Paint const& paint, const Matrix& matrix,
                                   VectorCache<float>* vertex_vector_cache,
                                   VectorCache<uint32_t>* index_vector_cache)
    : paint_(paint),
      vertex_vector_cache_(vertex_vector_cache),
      index_vector_cache_(index_vector_cache),
      vertex_buffer_(vertex_vector_cache->ObtainVector()),
      index_buffer_(index_vector_cache->ObtainVector()),
      matrix_(matrix) {}

HWGeometryRaster::~HWGeometryRaster() {
  vertex_vector_cache_->StoreVector(vertex_buffer_);
  index_vector_cache_->StoreVector(index_buffer_);
}

uint32_t HWGeometryRaster::AppendLineVertex(Vec2 const& p) {
  return AppendVertex(p.x, p.y, 1.0f);
}

uint32_t HWGeometryRaster::AppendLineVertex(Vec2 const& p, float alpha) {
  return AppendVertex(p.x, p.y, alpha);
}

uint32_t HWGeometryRaster::AppendVertex(float x, float y, float alpha) {
  auto index = static_cast<uint32_t>(vertex_buffer_.size() / 3);

  vertex_buffer_.emplace_back(x);
  vertex_buffer_.emplace_back(y);
  vertex_buffer_.emplace_back(alpha);

  return index;
}

uint32_t HWGeometryRaster::AppendVertex(float x, float y, float u, float v) {
  auto index = static_cast<uint32_t>(vertex_buffer_.size() / 4);

  vertex_buffer_.emplace_back(x);
  vertex_buffer_.emplace_back(y);
  vertex_buffer_.emplace_back(u);
  vertex_buffer_.emplace_back(v);

  return index;
}

void HWGeometryRaster::AppendRect(uint32_t a, uint32_t b, uint32_t c,
                                  uint32_t d) {
  /**
   *   a --------- c
   *   |           |
   *   |           |
   *   b-----------d
   */

  index_buffer_.emplace_back(a);
  index_buffer_.emplace_back(b);
  index_buffer_.emplace_back(c);

  index_buffer_.emplace_back(b);
  index_buffer_.emplace_back(d);
  index_buffer_.emplace_back(c);

  front_count_ += 6;
}

void HWGeometryRaster::AppendFrontTriangle(uint32_t a, uint32_t b, uint32_t c) {
  index_buffer_.emplace_back(a);
  index_buffer_.emplace_back(b);
  index_buffer_.emplace_back(c);

  front_count_ += 3;
}

void HWGeometryRaster::AppendBackTriangle(uint32_t a, uint32_t b, uint32_t c) {
  index_buffer_.emplace_back(a);
  index_buffer_.emplace_back(b);
  index_buffer_.emplace_back(c);

  back_count_ += 3;
}

}  // namespace skity
