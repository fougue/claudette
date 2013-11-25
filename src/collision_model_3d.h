/*   ColDet - C++ 3D Collision Detection Library
 *   Copyright (C) 2000   Amir Geva
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA  02111-1307, USA.
 *
 * Any comments, questions and bug reports send to:
 *   photon@photoneffect.com
 *
 * Or visit the home page: http://photoneffect.com/coldet/
 */

/*! \file collision_model_3d.h
 *  3D Collision Detection
 *
 *  Interface for the library.
 *  Isolated from any implementation details.
 */
#ifndef FOUGCOLDET_COLLISION_MODEL_3D_H
#define FOUGCOLDET_COLLISION_MODEL_3D_H

#include "global.h"
#include <cstddef>

class ModelCollisionTest;
class RayCollisionTest;
class SphereCollisionTest;

/*! \brief Collision Model, will represent the mesh to be tested for collisions
 *
 *  It has to be notified of all triangles, via addTriangle(). \n
 *  After all triangles are added, a call to finalize() will process the information and prepare
 *  for collision tests. \n
 *  Call modelCollision(), rayCollision(), sphereCollision() to check for a collision
 *
 */
class FOUGCOLDET_LIB_EXPORT CollisionModel3D
{
public:
  //! Various model types
  enum ModelType
  {
    //! The model is dynamic ie. can move
    DynamicModel,
    //! The model is static ie. does not move and certain calculations can be done every time its
    //! transform changes instead of every collision test
    StaticModel
  };

  virtual ~CollisionModel3D() {}

  //! Optional: Optimization for construction speed. If you know the number of triangles
  virtual void setTriangleNumber(int num) = 0;

  //! Add a triangle to the mesh
  virtual void addTriangle(float x1, float y1, float z1,
                           float x2, float y2, float z2,
                           float x3, float y3, float z3) = 0;
  //! \overload
  virtual void addTriangle(const float v1[3], const float v2[3], const float v3[3]) = 0;

  //! All triangles have been added, process model
  virtual void finalize() = 0;

  /*! \brief The current affine matrix for the model.
   *
   *  \note Transformations must not contain scaling.
   *
   *  See transform.txt for format information
   */
  virtual void setTransform(const float m[16]) = 0;

  /*! \brief Check for collision with another model (do not mix model types)
   *
   *  \param maxProcessingTime determines the maximum time in milliseconds
   *         to check for collision.  If a rejection is not found by that
   *         time, the function will return true.
   *
   *  \warning ModelCollisionTest::accuracyDepth() is not yet supported
   */
  virtual bool modelCollision(ModelCollisionTest* test, int maxProcessingTime = 0) const = 0;

  //! Returns true if the ray given in world space coordinates intersects with the object
  virtual bool rayCollision(RayCollisionTest* test) const = 0;

  //! Returns true if the given sphere collides with the model
  virtual bool sphereCollision(SphereCollisionTest* test) const = 0;

  /*! \brief Create a new collision model object
   *
   *  Use delete when finished with it
   */
  static CollisionModel3D* create(ModelType type = DynamicModel);
};

/*! \brief Inconsistency exception.
 *
 *  Exception will be thrown if the model is inconsistent.
 *   Examples:
 *     \li Checking for collisions before calling finalize()
 *     \li Trying to add triangles after calling finalize()
 */
class Inconsistency {};



//////////////////////////////////////////////
// Utility Functions
//////////////////////////////////////////////

/*! \brief Checks for intersection between a ray and a sphere.
 *  \param point will contain point of intersection, if one is found.
 */
FOUGCOLDET_LIB_EXPORT bool SphereRayCollision(const float sphereCenter[3],
                                              float sphereRadius,
                                              const float rayOrigin[3],
                                              const float rayDirection[3],
                                              float point[3]);

/*! \brief Checks for intersection between 2 spheres.
 */
FOUGCOLDET_LIB_EXPORT bool SphereSphereCollision(const float c1[3], float r1,
                                                 const float c2[3], float r2,
                                                 float point[3]);

#endif // FOUGCOLDET_COLLISION_MODEL_3D_H
