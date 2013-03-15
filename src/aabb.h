#ifndef RT_AABB
#define RT_AABB

#define DIMENSIONS 2

/*
    Define the class for axis-aligned bounding box, or AABB for short.
*/
class AABB
{
public:
	AABB(int x1, int x2, int y1, int y2);
	~AABB();
private:
    int m_bounds[DIMENSIONS][2];
};

#endif
