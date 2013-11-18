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
/*! \file coldet.h
    3D Collision Detection

    Interface for the library.
    Isolated from any implementation details.
*/
#ifndef H_COLDET
#define H_COLDET

#include "global.h"
#include <cstddef>

class ModelCollisionTest;
class RayCollisionTest;
class SphereCollisionTest;

/*! Collision Model.  Will represent the mesh to be tested for
    collisions.  It has to be notified of all triangles, via
    addTriangle()
    After all triangles are added, a call to finalize() will
    process the information and prepare for collision tests.
    Call modelCollision(), rayCollision(), sphereCollision() to check for a collision

    Note: Transformations must not contain scaling.
*/
class CollisionModel3D
{
public:
  /*! Various model types */
  enum ModelType
  {
    /*! The model is dynamic ie. can move */
    DynamicModel,
    /*! The model is static ie. does not move and certain calculations can be done every time its
     *  transform changes instead of every collision test
     */
    StaticModel
  };

  virtual ~CollisionModel3D() {}

  /*! Optional: Optimization for construction speed. If you know the number of triangles. */
  virtual void setTriangleNumber(int num) = 0;

  /*! Use any of the forms of this functions to enter the coordinates of the model's triangles. */
  virtual void addTriangle(float x1, float y1, float z1,
                           float x2, float y2, float z2,
                           float x3, float y3, float z3) = 0;
  virtual void addTriangle(const float v1[3], const float v2[3], const float v3[3]) = 0;

  /*! All triangles have been added, process model. */
  virtual void finalize() = 0;

  /*! The current affine matrix for the model.
   *  See transform.txt for format information */
  virtual void setTransform(const float m[16]) = 0;

  /*! Check for collision with another model (do not mix model types)
   *
   *  \param maxProcessingTime determines the maximum time in milliseconds
   *         to check for collision.  If a rejection is not found by that
   *         time, the function will return true.
   *
   *  \warning ModelCollisionTest::accuracyDepth() is not yet supported
   */
  virtual bool modelCollision(ModelCollisionTest* test, int maxProcessingTime = 0) const = 0;

  /*! Returns true if the ray given in world space coordinates intersects with the object */
  virtual bool rayCollision(RayCollisionTest* test) const = 0;

  /*! Returns true if the given sphere collides with the model */
  virtual bool sphereCollision(SphereCollisionTest* test) const = 0;

  /*! Create a new collision model object.
   *  Use delete when finished with it
   */
  FOUGCOLDET_LIB_EXPORT static CollisionModel3D* create(ModelType type = DynamicModel);
};

/*! Timeout exception class.  Exception will be thrown if
    the detection algorithm could not complete within
    the given time limit. */
class TimeoutExpired {};

/*! Inconsistency exception. Exception will be thrown if
    the model is inconsistent.
    Examples:
      Checking for collisions before calling finalize()
      Trying to add triangles after calling finalize()  */
class Inconsistency {};



//////////////////////////////////////////////
// Utility Functions
//////////////////////////////////////////////

/*! Checks for intersection between a ray and a sphere.
    center, radius define the sphere
    origin, direction define the ray
    point will contain point of intersection, if one is found.
*/
FOUGCOLDET_LIB_EXPORT bool SphereRayCollision(const float sphereCenter[3],
                                              float sphereRadius,
                                              const float rayOrigin[3],
                                              const float rayDirection[3],
                                              float point[3]);

/*! Checks for intersection between 2 spheres. */
FOUGCOLDET_LIB_EXPORT bool SphereSphereCollision(const float c1[3], float r1,
                                                 const float c2[3], float r2,
                                                 float point[3]);

#endif // H_COLDET
