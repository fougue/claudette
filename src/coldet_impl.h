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
#ifndef H_COLDET_IMPL
#define H_COLDET_IMPL

#include "collision_model_3d.h"
#include "box.h"
#include "math3d.h"
#include <vector>

class CollisionModel3DImpl : public CollisionModel3D
{
public:
  CollisionModel3DImpl(bool Static);
  void setTriangleNumber(int num) { if (!m_Final) m_Triangles.reserve(num); }

  void addTriangle(float x1, float y1, float z1,
                   float x2, float y2, float z2,
                   float x3, float y3, float z3)
  {
    addTriangle(Vector3D(x1,y1,z1),
                Vector3D(x2,y2,z2),
                Vector3D(x3,y3,z3));
  }
  void addTriangle(const float v1[3], const float v2[3], const float v3[3])
  {
    addTriangle(Vector3D(v1[0],v1[1],v1[2]),
                Vector3D(v2[0],v2[1],v2[2]),
                Vector3D(v3[0],v3[1],v3[2]));
  }
  void addTriangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);
  void finalize();

  void setTransform(const float m[16]) { setTransform(*(const Matrix3D*)m); }
  void setTransform(const Matrix3D& m);

  bool modelCollision(ModelCollisionTest* test, int maxProcessingTime = 0) const;

  bool rayCollision(RayCollisionTest* test) const;
  bool sphereCollision(SphereCollisionTest* test) const;


  int getTriangleIndex(const BoxedTriangle* bt) const
  {
    return int(bt-&(*m_Triangles.begin()));
  }

  /** Stores all the actual triangles.  Other objects will use pointers into this array.
   */
  std::vector<BoxedTriangle> m_Triangles;
  /** Root of the hierarchy tree */
  BoxTreeInnerNode           m_Root;
  /** The current transform and its inverse */
  Matrix3D                   m_Transform, m_InvTransform;

  /** Flag for indicating the model is finalized. */
  bool                       m_Final;
  /** Static models will maintain the same transform for a while
      so the inverse transform is calculated each set instead
      of in the collision test. */
  bool                       m_Static;
};


#endif // H_COLDET_IMPL
