/*
 * Copyright (c) 2018-2021, NVIDIA CORPORATION.  All rights reserved.
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
 * SPDX-FileCopyrightText: Copyright (c) 2018-2021 NVIDIA CORPORATION
 * SPDX-License-Identifier: Apache-2.0
 */
//--------------------------------------------------------------------

#include "cameramanipulator.hpp"
#include <chrono>
#include <iostream>
#include <nvp/nvpwindow.hpp>
#include <Engine/Math/Vector2.h>

namespace nvh {

inline float sign(float s)
{
  return (s < 0.f) ? -1.f : 1.f;
}

//--------------------------------------------------------------------------------------------------
//
//
CameraManipulator::CameraManipulator()
{
  update();
}

//--------------------------------------------------------------------------------------------------
// Set the new camera as a goal
//
void CameraManipulator::setCamera(Camera camera, bool instantSet /*=true*/)
{
  m_anim_done = true;

  if(instantSet)
  {
    m_current = camera;
    update();
  }
  else if(camera != m_current)
  {
    m_goal       = camera;
    m_snapshot   = m_current;
    m_anim_done  = false;
    m_start_time = getSystemTime();
    findBezierPoints();
  }
}

//--------------------------------------------------------------------------------------------------
// Creates a viewing matrix derived from an eye point, a reference point indicating the center of
// the scene, and an up vector
//
void CameraManipulator::setLookat(const vec3& eye, const vec3& center, const vec3& up, bool instantSet)
{
  Camera camera{eye, center, up, m_current.fov};
  setCamera(camera, instantSet);
}

//--------------------------------------------------------------------------------------------------
// Modify the position of the camera over time
// - The camera can be updated through keys. A key set a direction which is added to both
//   eye and center, until the key is released
// - A new position of the camera is defined and the camera will reach that position
//   over time.
void CameraManipulator::updateAnim()
{
  auto elapse = static_cast<float>(getSystemTime() - m_start_time) / 1000.f;

  // Key animation
  if(m_key_vec != vec3(0, 0, 0))
  {
    m_current.eye += m_key_vec * 0.01f;//elapse;
    m_current.ctr += m_key_vec * 0.01f;//elapse;
    update();
    m_start_time = getSystemTime();
    return;
  }

  // Camera moving to new position
  if(m_anim_done)
    return;

  float t = std::min(elapse / float(m_duration), 1.0f);
  // Evaluate polynomial (smoother step from Perlin)
  t = t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
  if(t >= 1.0f)
  {
    m_current   = m_goal;
    m_anim_done = true;
    return;
  }

  // Interpolate camera position and interest
  // The distance of the camera between the interest is preserved to
  // create a nicer interpolation
  vec3 vpos, vint, vup;
  m_current.ctr =m_snapshot.ctr.Lerp(m_goal.ctr, t);
  m_current.up  =m_snapshot.up.Lerp(m_goal.up, t);
  m_current.eye = computeBezier(t, m_bezier[0], m_bezier[1], m_bezier[2]);
  m_current.fov = (1 - t) * m_snapshot.fov + t * m_goal.fov;


  update();
}


//-----------------------------------------------------------------------------
// Get the current camera information
//   position  camera position
//   interest  camera interesting point (look at position)
//   up        camera up vector
//
void CameraManipulator::getLookat(vec3& eye, vec3& center, vec3& up) const
{
  eye    = m_current.eye;
  center = m_current.ctr;
  up     = m_current.up;
}

//--------------------------------------------------------------------------------------------------
//
void CameraManipulator::setMatrix(const mat4& matrix, bool instantSet, float centerDistance)
{
  Camera camera;
  camera.eye = matrix.Translation();
  auto rotMat = (mat3)matrix;
  camera.ctr  = {0, 0, -centerDistance};
  camera.ctr  = camera.eye + (rotMat * camera.ctr);
  camera.up   = {0, 1, 0};
  camera.fov  = m_current.fov;

  m_anim_done = instantSet;

  if(instantSet)
  {
    m_current = camera;
  }
  else
  {
    m_goal       = camera;
    m_snapshot   = m_current;
    m_start_time = getSystemTime();
    findBezierPoints();
  }
  update();
}

//--------------------------------------------------------------------------------------------------
//
//
void CameraManipulator::setMousePosition(int x, int y)
{
  m_mouse = {static_cast<float>(x), static_cast<float>(y)};
}

//--------------------------------------------------------------------------------------------------
//
//
void CameraManipulator::getMousePosition(int& x, int& y)
{
  x = static_cast<int>(m_mouse[0]);
  y = static_cast<int>(m_mouse[1]);
}

//--------------------------------------------------------------------------------------------------
//
//
void CameraManipulator::setWindowSize(int w, int h)
{
  m_width  = w;
  m_height = h;
}

//--------------------------------------------------------------------------------------------------
//
// Low level function for when the camera move.
//
void CameraManipulator::motion(int x, int y, int action)
{
  float dx = -float(x - m_mouse[0]) / float(m_width);
  float dy = -float(y - m_mouse[1]) / float(m_height);

  dx *= m_current.fov / 60;
  dy *= m_current.fov / 60;

  switch(action)
  {
    case Orbit:
      orbit(dx, dy, false);
      break;
    case CameraManipulator::Dolly:
      dolly(dx, dy);
      break;
    case CameraManipulator::Pan:
      pan(dx, dy);
      break;
    case CameraManipulator::LookAround:
      orbit(dx, -dy, true);
      break;
  }

  // Resetting animation
  m_anim_done = true;

  update();

  m_mouse[0] = static_cast<float>(x);
  m_mouse[1] = static_cast<float>(y);
}


//
// Function for when the camera move with keys.
//
void CameraManipulator::keyMotion(float dx, float dy, float dz, int action)
{
  if(action == NoAction)
  {
    m_key_vec = {0, 0, 0};
    return;
  }

  auto d = (m_current.ctr - m_current.eye).Unit();
  dx *= m_speed * 2.f;
  dy *= m_speed * 2.f;
  dz *= m_speed * 2.f;

  vec3 key_vec;
  if(action == Dolly)
  {
    key_vec = d * dx;
    if(m_mode == Walk)
    {
      if(m_current.up.Y > m_current.up.Z)
        key_vec.Y = 0;
      else
        key_vec.Z = 0;
    }
  }
  else if(action == Pan || action == Pan2)
  {
    vec3 r = d.Cross(m_current.up).Unit();
    vec3 currentUp = action == Pan2 ? m_current.up : r.Cross(d).Unit();
    vec3 l = currentUp.Cross(r).Unit();
    key_vec = r * dx + currentUp * dy + l * dz;

  }

  m_key_vec += key_vec;

  // Resetting animation
  m_start_time = getSystemTime();
}


//--------------------------------------------------------------------------------------------------
// To call when the mouse is moving
// It find the appropriate camera operator, based on the mouse button pressed and the
// keyboard modifiers (shift, ctrl, alt)
//
// Returns the action that was activated
//
CameraManipulator::Actions CameraManipulator::mouseMove(int x, int y, const Inputs& inputs)
{
  if(!inputs.lmb && !inputs.rmb && !inputs.mmb)
  {
    setMousePosition(x, y);
    return NoAction;  // no mouse button pressed
  }

  Actions curAction = NoAction;
  if(inputs.lmb)
  {
    if(((inputs.ctrl) && (inputs.shift)) || inputs.alt)
      curAction = m_mode == Examine ? LookAround : Orbit;
    else if(inputs.shift)
      curAction = Dolly;
    else if(inputs.ctrl)
      curAction = Pan;
    else
      curAction = m_mode == Examine ? Orbit : LookAround;
  }
  else if(inputs.mmb)
    curAction = Pan;
  else if(inputs.rmb)
    curAction = Dolly;

  if(curAction != NoAction)
    motion(x, y, LookAround);

  return curAction;
}

//--------------------------------------------------------------------------------------------------
// Trigger a dolly when the wheel change
//
void CameraManipulator::wheel(int value, const Inputs& inputs)
{
  float fval(static_cast<float>(value));
  float dx = (fval * fabsf(fval)) / static_cast<float>(m_width);

  if (m_current.fov < 30)
    fval *= 0.5f;

  if (m_current.fov < 15)
    fval *= 0.5f;

  if (m_current.fov < 8)
    fval *= 0.5f;

  if (m_current.fov < 4)
    fval *= 0.5f;

  if (m_current.fov < 2)
    fval *= 0.5f;

  //if(inputs.shift)
  {
    setFov(m_current.fov - fval);
  }
  //else
  //{
  //  dolly(dx * m_speed, dx * m_speed);
  //  update();
  //}
}

// Set and clamp FOV between 0.01 and 179 degrees
void CameraManipulator::setFov(float _fov)
{
  m_current.fov = std::min(std::max(_fov, 0.01f), 179.0f);
}

vec3 CameraManipulator::computeBezier(float t, vec3& p0, vec3& p1, vec3& p2)
{
  float u  = 1.f - t;
  float tt = t * t;
  float uu = u * u;

  vec3 p = uu * p0;  // first term
  p += 2 * u * t * p1;        // second term
  p += tt * p2;               // third term

  return p;
}

void CameraManipulator::findBezierPoints()
{
  vec3 p0 = m_current.eye;
  vec3 p2 = m_goal.eye;
  vec3 p1, pc;

  // point of interest
  vec3 pi = (m_goal.ctr + m_current.ctr) * 0.5f;

  vec3 p02    = (p0 + p2) * 0.5f;                            // mid p0-p2
  float         radius = ((p0 - pi).Length() + (p2 - pi).Length()) * 0.5f;  // Radius for p1
  vec3 p02pi(p02 - pi);                                      // Vector from interest to mid point
  p02pi.Normalize();
  p02pi *= radius;
  pc   = pi + p02pi;                        // Calculated point to go through
  p1   = 2.f * pc - p0 * 0.5f - p2 * 0.5f;  // Computing p1 for t=0.5
  p1.Y = p02.Y;                             // Clamping the P1 to be in the same height as p0-p2

  m_bezier[0] = p0;
  m_bezier[1] = p1;
  m_bezier[2] = p2;
}

//--------------------------------------------------------------------------------------------------
// Pan the camera perpendicularly to the light of sight.
//
void CameraManipulator::pan(float dx, float dy)
{
  if(m_mode == Fly)
  {
    dx *= -1;
    dy *= -1;
  }

  vec3 z(m_current.eye - m_current.ctr);
  float         length = static_cast<float>(z.Length()) / 0.785f;  // 45 degrees
  z.Normalize();
  vec3 x      = m_current.up.Cross(z);
  x.Normalize();
  vec3 y      = z.Cross(x);
  y.Normalize();
  x *= -dx * length;
  y *= dy * length;

  m_current.eye += x + y;
  m_current.ctr += x + y;
}

//--------------------------------------------------------------------------------------------------
// Orbit the camera around the center of interest. If 'invert' is true,
// then the camera stays in place and the interest orbit around the camera.
//
void CameraManipulator::orbit(float dx, float dy, bool invert)
{
  if(dx == 0 && dy == 0)
    return;

  // Full width will do a full turn
  dx *= nv_two_pi;
  dy *= nv_two_pi;

  // Get the camera
  vec3 origin(invert ? m_current.eye : m_current.ctr);
  vec3 position(invert ? m_current.ctr : m_current.eye);

  // Get the length of sight
  vec3 centerToEye(position - origin);
  float         radius = centerToEye.Length();
  centerToEye.Normalize();

  mat4 rot_x, rot_y;

  // Find the rotation around the UP axis (Y)
  vec3 axe_z(centerToEye);
  rot_y = mat4::AxisRotation(m_current.up, -dx);

  // Apply the (Y) rotation to the eye-center vector
  vec4 vect_tmp = rot_y * vec4(centerToEye.X, centerToEye.Y, centerToEye.Z, 0);
  centerToEye            = vec3(vect_tmp.X, vect_tmp.Y, vect_tmp.Z);

  // Find the rotation around the X vector: cross between eye-center and up (X)
  vec3 axe_x = m_current.up.Cross(axe_z);
  axe_x.Normalize();
  rot_x               = mat4::AxisRotation(axe_x, -dy);

  // Apply the (X) rotation to the eye-center vector
  vect_tmp = rot_x * vec4(centerToEye.X, centerToEye.Y, centerToEye.Z, 0);
  vec3 vect_rot(vect_tmp.X, vect_tmp.Y, vect_tmp.Z);
  if(sign(vect_rot.X) == sign(centerToEye.X))
    centerToEye = vect_rot;

  // Make the vector as long as it was originally
  centerToEye *= radius;

  // Finding the new position
  vec3 newPosition = centerToEye + origin;

  if(!invert)
  {
    m_current.eye = newPosition;  // Normal: change the position of the camera
  }
  else
  {
    m_current.ctr = newPosition;  // Inverted: change the interest point
  }
}

//--------------------------------------------------------------------------------------------------
// Move the camera toward the interest point, but don't cross it
//
void CameraManipulator::dolly(float dx, float dy)
{
  vec3 z      = m_current.ctr - m_current.eye;
  float         length = static_cast<float>(z.Length());

  // We are at the point of interest, and don't know any direction, so do nothing!
  if(length < 0.000001f)
    return;

  // Use the larger movement.
  float dd;
  if(m_mode != Examine)
    dd = -dy;
  else
    dd = fabs(dx) > fabs(dy) ? dx : -dy;
  float factor = m_speed * dd;

  // Adjust speed based on distance.
  if(m_mode == Examine)
  {
    // Don't move over the point of interest.
    if(factor >= 1.0f)
      return;

    z *= factor;
  }
  else
  {
    // Normalize the Z vector and make it faster
    z *= factor / length * 10.0f;
  }

  // Not going up
  if(m_mode == Walk)
  {
    if(m_current.up.Y > m_current.up.Z)
      z.Y = 0;
    else
      z.Z = 0;
  }

  m_current.eye += z;

  // In fly mode, the interest moves with us.
  if(m_mode != Examine)
    m_current.ctr += z;
}

//--------------------------------------------------------------------------------------------------
// Return the time in fraction of milliseconds
//
double CameraManipulator::getSystemTime()
{
  auto now(std::chrono::system_clock::now());
  auto duration = now.time_since_epoch();
  return std::chrono::duration_cast<std::chrono::microseconds>(duration).count() / 1000.0;
}

//--------------------------------------------------------------------------------------------------
// Return a string which can be included in help dialogs
//
const std::string& CameraManipulator::getHelp()
{
  static std::string helpText =
      "LMB: rotate around the target\n"
      "RMB: Dolly in/out\n"
      "MMB: Pan along view plane\n"
      "LMB + Shift: Dolly in/out\n"
      "LMB + Ctrl: Pan\n"
      "LMB + Alt: Look aroundPan\n"
      "Mouse wheel: Dolly in/out\n"
      "Mouse wheel + Shift: Zoom in/out\n";
  return helpText;
}

//--------------------------------------------------------------------------------------------------
// Move the camera closer or further from the center of the the bounding box, to see it completely
//
// boxMin - lower corner of the bounding box
// boxMax - upper corner of the bounding box
// instantFit - true: set the new position, false: will animate to new position.
// tight - true: fit exactly the corner, false: fit to radius (larger view, will not get closer or further away)
// aspect - aspect ratio of the window.
//
void CameraManipulator::fit(const vec3& boxMin, const vec3& boxMax, bool instantFit /*= true*/, bool tight /*=false*/, float aspect /*=1.0f*/)
{
  const vec3 boxHalfSize = (boxMax - boxMin) * .5f;
  const vec3 boxCenter   = boxMin + boxHalfSize;

  float offset = 0;
  float yfov   = m_current.fov;
  float xfov   = m_current.fov * aspect;

  if(!tight)
  {
    // Using the bounding sphere
    float radius = boxHalfSize.Length();
    if(aspect > 1.f)
      offset = radius / sin(nv_to_rad * yfov * 0.5f);
    else
      offset = radius / sin(nv_to_rad * xfov * 0.5f);
  }
  else
  {
    mat4 mView = mat4(m_current.eye, boxCenter - m_current.eye, m_current.up);
    mView.SetTranslation({0, 0, 0});  // Keep only rotation

    for(int i = 0; i < 8; i++)
    {
      vec3 vct(i & 1 ? boxHalfSize.X : -boxHalfSize.X, i & 2 ? boxHalfSize.Y : -boxHalfSize.Y,
                        i & 4 ? boxHalfSize.Z : -boxHalfSize.Z);
      vct = vec3(mView * vct);

      if(vct.Z < 0)  // Take only points in front of the center
      {
        // Keep the largest offset to see that vertex
        offset = std::max(fabs(vct.Y) / tan(nv_to_rad * yfov * 0.5f) + fabs(vct.Z), offset);
        offset = std::max(fabs(vct.X) / tan(nv_to_rad * xfov * 0.5f) + fabs(vct.Z), offset);
      }
    }
  }

  // Re-position the camera
  auto viewDir = (m_current.eye - m_current.ctr).Unit();
  auto veye    = boxCenter + viewDir * offset;
  setLookat(veye, boxCenter, m_current.up, instantFit);
}

}  // namespace nvh
