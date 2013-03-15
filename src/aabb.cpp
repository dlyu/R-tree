#include <cstring>
#include "aabb.h"

using namespace std;

AABB::AABB(int x1, int x2, int y1, int y2)
{
    this.m_bounds[0][0] = x1;
    this.m_bounds[0][1] = x2;
    this.m_bounds[1][0] = y1;
    this.m_bounds[1][1] = y2;
}

AABB::~AABB()
{

}
