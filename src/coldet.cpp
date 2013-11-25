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
#include "sysdep.h"
#include "coldetimpl.h"
#include "mytritri.h"
#include <cassert>

#include "model_collision_test.h"
#include "ray_collision_test.h"
#include "sphere_collision_test.h"

#include <algorithm>

class Check
{
public:
  Check() {}
  Check(const BoxTreeNode* f, const BoxTreeNode* s, int d)
    : m_first(f), m_second(s), depth(d) {}
  const BoxTreeNode* m_first;
  const BoxTreeNode* m_second;
  int depth;
};

bool CollisionModel3DImpl::modelCollision(ModelCollisionTest* test, int maxProcessingTime) const
{
  const CollisionModel3DImpl* o = static_cast<const CollisionModel3DImpl*>(test->otherModel());
  test->m_iColTri = -1;
  test->m_iOtherColTri = -1;
  test->m_colPointIsDirty = true;

  if (!m_Final)
    throw Inconsistency();
  if (!o->m_Final)
    throw Inconsistency();
  Matrix3D t = (test->otherModelTransform() == NULL ? o->m_Transform :
                                                      *((const Matrix3D*)test->otherModelTransform()));
  if (m_Static)
    t *= m_InvTransform;
  else
    t *= m_Transform.Inverse();
  RotationState rs(t);

  int accuracyDepth = test->accuracyDepth();
  if (accuracyDepth < 0)
    accuracyDepth = 0xFFFFFF;
  if (maxProcessingTime == 0)
    maxProcessingTime = 0xFFFFFF;
  
  DWORD EndTime, BeginTime = GetTickCount();
  int num = std::max(m_Triangles.size(), o->m_Triangles.size());
  int Allocated = std::max(64, (num>>4));
  std::vector<Check> checks(Allocated);
  
  int queue_idx = 1;
  Check& c=checks[0];
  c.m_first = &m_Root;
  c.depth = 0;
  c.m_second = &o->m_Root;
  while (queue_idx > 0) {
    if (queue_idx > (Allocated / 2)) { // Enlarge the queue
      Check c;
      checks.insert(checks.end(), Allocated, c);
      Allocated *= 2;
    }
    EndTime=GetTickCount();
    if (EndTime >= (BeginTime + maxProcessingTime))
      throw TimeoutExpired();

    // @@@ add depth check
    //Check c=checks.back();
    Check& c = checks[--queue_idx];
    const BoxTreeNode* first = c.m_first;
    const BoxTreeNode* second = c.m_second;
    assert(first != NULL);
    assert(second != NULL);
    if (first->intersect(*second, rs)) {
      int tnum1 = first->getTrianglesNumber();
      int tnum2 = second->getTrianglesNumber();
      if (tnum1 > 0 && tnum2 > 0) {
        {
          for (int i = 0; i < tnum2; i++) {
            const BoxedTriangle* bt2 = second->getTriangle(i);
            Triangle tt(Transform(bt2->v1, rs.t),
                        Transform(bt2->v2, rs.t),
                        Transform(bt2->v3, rs.t));
            for (int j = 0; j < tnum1; j++) {
              const BoxedTriangle* bt1 = first->getTriangle(j);
              if (tt.intersect(*bt1)) {
                bt1->copyCoords(test->m_colTri);
                test->m_iColTri = this->getTriangleIndex(bt1);
                tt.copyCoords(test->m_otherColTri);
                test->m_iOtherColTri = o->getTriangleIndex(bt2);
                return true;
              }
            }
          }
        }
      }
      else if (first->getSonsNumber() == 0) {
        const BoxTreeNode* s1 = second->getSon(0);
        const BoxTreeNode* s2 = second->getSon(1);
        assert(s1 != NULL);
        assert(s2 != NULL);
        
        Check& c1 = checks[queue_idx++];
        c1.m_first = first;
        c1.m_second = s1;

        Check& c2 = checks[queue_idx++];
        c2.m_first = first;
        c2.m_second = s2;
      }
      else if (second->getSonsNumber() == 0) {
        const BoxTreeNode* f1 = first->getSon(0);
        const BoxTreeNode* f2 = first->getSon(1);
        assert(f1 != NULL);
        assert(f2 != NULL);
        
        Check& c1 = checks[queue_idx++];
        c1.m_first = f1;
        c1.m_second = second;

        Check& c2 = checks[queue_idx++];
        c2.m_first = f2;
        c2.m_second = second;
      }
      else {
        float v1 = first->getVolume();
        float v2=second->getVolume();
        if (v1 > v2) {
          const BoxTreeNode* f1=first->getSon(0);
          const BoxTreeNode* f2=first->getSon(1);
          assert(f1 != NULL);
          assert(f2 != NULL);

          Check& c1 = checks[queue_idx++];
          c1.m_first = f1;
          c1.m_second = second;

          Check& c2 = checks[queue_idx++];
          c2.m_first = f2;
          c2.m_second = second;
        }
        else {
          const BoxTreeNode* s1 = second->getSon(0);
          const BoxTreeNode* s2 = second->getSon(1);
          assert(s1 != NULL);
          assert(s2 != NULL);

          Check& c1 = checks[queue_idx++];
          c1.m_first = first;
          c1.m_second = s1;

          Check& c2 = checks[queue_idx++];
          c2.m_first = first;
          c2.m_second = s2;
        }
      }
    }
  }
  return false;
}

bool CollisionModel3DImpl::rayCollision(RayCollisionTest *test) const
{
  if (test == NULL)
    return false;

  float mintparm = 9e9f,tparm;
  Vector3D col_point;
  Vector3D O;
  Vector3D D;
  float segmin = test->raySegmentMin();
  float segmax = test->raySegmentMax();

  test->m_iColTri = -1;

  if (m_Static) {
    O = Transform(Vector3D::asConstRef(test->rayOrigin()), m_InvTransform);
    D = rotateVector(Vector3D::asConstRef(test->rayDirection()), m_InvTransform);
  }
  else {
    const Matrix3D inv = m_Transform.Inverse();
    O = Transform(Vector3D::asConstRef(test->rayOrigin()), inv);
    D = rotateVector(Vector3D::asConstRef(test->rayDirection()), inv);
  }
  // TODO: use better comparison
  if (segmin != 0.0f) { // Normalize ray
    O += segmin * D;
    segmax -= segmin;
    segmin = 0.0f;
  }
  if (segmax < segmin)
  {
    D = -D;
    segmax = -segmax;
  }
  std::vector<const BoxTreeNode*> checks;
  checks.push_back(&m_Root);
  while (!checks.empty()) {
    const BoxTreeNode* b = checks.back();
    checks.pop_back();
    if (b->intersect(O, D, segmax)) {
      int sons = b->getSonsNumber();
      if (sons) {
        while (sons--)
          checks.push_back(b->getSon(sons));
      }
      else {
        int tri=b->getTrianglesNumber();
        while (tri--) {
          const BoxedTriangle* bt = b->getTriangle(tri);
          const Triangle* t = static_cast<const Triangle*>(bt);
          if (t->intersect(O, D, col_point, tparm, segmax))  {
            if (test->raySearch() == RayCollisionTest::SearchClosestTriangle) {
              if (tparm < mintparm) {
                mintparm = tparm;
                bt->copyCoords(test->m_colTri);
                test->m_iColTri = this->getTriangleIndex(bt);
                Vector3D::asRef(test->m_colPnt) = col_point;
              }
            }
            else {
              bt->copyCoords(test->m_colTri);
              test->m_iColTri = this->getTriangleIndex(bt);
              Vector3D::asRef(test->m_colPnt) = col_point;
              return true;
            }
          }
        }
      }
    }
  }
  if (test->raySearch() == RayCollisionTest::SearchClosestTriangle && mintparm < 9e9f)
    return true;
  return false;
}

bool CollisionModel3DImpl::sphereCollision(SphereCollisionTest *test) const
{
  if (test == NULL)
    return false;

  test->m_iColTri = -1;

  Vector3D O;
  if (m_Static) {
    O = Transform(Vector3D::asConstRef(test->sphereCenter()), m_InvTransform);
  }
  else {
    const Matrix3D inv = m_Transform.Inverse();
    O = Transform(Vector3D::asConstRef(test->sphereCenter()), inv);
  }
  std::vector<const BoxTreeNode*> checks;
  checks.push_back(&m_Root);
  while (!checks.empty()) {
    const BoxTreeNode* b = checks.back();
    checks.pop_back();
    if (b->intersect(O, test->sphereRadius())) {
      int sons = b->getSonsNumber();
      if (sons) {
        while (sons--)
          checks.push_back(b->getSon(sons));
      }
      else {
        int tri = b->getTrianglesNumber();
        while (tri--) {
          const BoxedTriangle* bt = b->getTriangle(tri);
          const Triangle* t = static_cast<const Triangle*>(bt);
          if (t->intersect(O, test->sphereRadius(), Vector3D::asPointer(test->m_colPnt))) {
            bt->copyCoords(test->m_colTri);
            test->m_iColTri = this->getTriangleIndex(bt);
            return true;
          }
        }
      }
    }
  }
  return false;
}


bool SphereRayCollision(const float sphereCenter[3],
                        float sphereRadius,
                        const float rayOrigin[3],
                        const float rayDirection[3],
                        float point[3])
{
  const Vector3D& C=  *((const Vector3D*)sphereCenter);
  const Vector3D& O = *((const Vector3D*)rayOrigin);
  const Vector3D  D = ((const Vector3D*)rayDirection)->Normalized();
  Vector3D& P = *((Vector3D*)point);
  const Vector3D EO = C - O;
  const float v = EO*D;
  const float disc = sphereRadius*sphereRadius - (EO*EO - v*v);
  if (disc<0.0f) return false;
  const float d = sqrt(disc);
  P = O + (v - d) * D;
  return true;
}

bool SphereSphereCollision(const float c1[], float r1,
                           const float c2[], float r2,
                           float point[3])
{
  const Vector3D& C1=*((const Vector3D*)c1);
  const Vector3D& C2=*((const Vector3D*)c2);
  float dist=(C2-C1).SquareMagnitude();
  float sum=r1+r2;
  if (dist < sum*sum)
  {
      Vector3D& P =*((Vector3D*)point);

      P = C1 - C2;
      P.Normalized();
      P*=r1;
      P += C1;
      return true;
  }
  return false;
}

