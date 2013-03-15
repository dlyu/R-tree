#ifndef RT_RTree
#define RT_RTree

#include "aabb.h"

class RTree
{
public:
	RTree();
	~RTree();

    void insertAABB(AABB aabb);
    void removeAABB(AABB aabb);
private:
};

#endif
