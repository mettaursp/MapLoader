/*
 * Copyright (c) 2022, NVIDIA CORPORATION.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-FileCopyrightText: Copyright (c) 2022 NVIDIA CORPORATION
 * SPDX-License-Identifier: Apache-2.0
 */

namespace nvh {

struct Bbox
{
  Bbox() = default;
  Bbox(vec3 _min, vec3 _max)
      : m_min(_min)
      , m_max(_max)
  {
  }
  Bbox(const std::vector<vec3>& corners)
  {
    for(auto& c : corners)
    {
      insert(c);
    }
  }

  void insert(const vec3& v)
  {
    m_min = {std::min(m_min.X, v.X), std::min(m_min.Y, v.Y), std::min(m_min.Z, v.Z)};
    m_max = {std::max(m_max.X, v.X), std::max(m_max.Y, v.Y), std::max(m_max.Z, v.Z)};
  }

  void insert(const Bbox& b)
  {
    insert(b.m_min);
    insert(b.m_max);
  }

  inline Bbox& operator+=(float v)
  {
    m_min -= v;
    m_max += v;
    return *this;
  }

  inline bool isEmpty() const
  {
    return m_min == vec3{std::numeric_limits<float>::max()}
           || m_max == vec3{std::numeric_limits<float>::lowest()};
  }

  inline uint32_t rank() const
  {
    uint32_t result{0};
    result += m_min.X < m_max.X;
    result += m_min.Y < m_max.Y;
    result += m_min.Z < m_max.Z;
    return result;
  }
  inline bool          isPoint() const { return m_min == m_max; }
  inline bool          isLine() const { return rank() == 1u; }
  inline bool          isPlane() const { return rank() == 2u; }
  inline bool          isVolume() const { return rank() == 3u; }
  inline vec3 min() { return m_min; }
  inline vec3 max() { return m_max; }
  inline vec3 extents() { return m_max - m_min; }
  inline vec3 center() { return (m_min + m_max) * 0.5f; }
  inline float         radius() { return (m_max - m_min).Length() * 0.5f; }

  Bbox transform(mat4 mat)
  {
    // Make sure this is a 3D transformation + translation:
    auto r = mat.Row(3);
    const float epsilon = 1e-6f;
    assert(fabs(r.X) <  epsilon && fabs(r.Y) <  epsilon && fabs(r.Z) <  epsilon && fabs(r.W - 1.0f) <  epsilon);

    std::vector<vec3> corners(8);
    corners[0] = vec3(mat * vec3(m_min.X, m_min.Y, m_min.Z));
    corners[1] = vec3(mat * vec3(m_min.X, m_min.Y, m_max.Z));
    corners[2] = vec3(mat * vec3(m_min.X, m_max.Y, m_min.Z));
    corners[3] = vec3(mat * vec3(m_min.X, m_max.Y, m_max.Z));
    corners[4] = vec3(mat * vec3(m_max.X, m_min.Y, m_min.Z));
    corners[5] = vec3(mat * vec3(m_max.X, m_min.Y, m_max.Z));
    corners[6] = vec3(mat * vec3(m_max.X, m_max.Y, m_min.Z));
    corners[7] = vec3(mat * vec3(m_max.X, m_max.Y, m_max.Z));

    Bbox result(corners);
    return result;
  }

private:
  vec3 m_min{std::numeric_limits<float>::max()};
  vec3 m_max{-std::numeric_limits<float>::max()};
};

template <typename T, typename TFlag>
inline bool hasFlag(T a, TFlag flag)
{
  return (a & flag) == flag;
}

}  // namespace nvh
