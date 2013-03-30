#ifndef RT_AABB
#define RT_AABB

#define RT_AABB_TYPE_INTEGER 0x01
#define RT_AABB_TYPE_DOUBLE 0x02
#define RT_AABB_TYPE_STRING 0x04

struct attribute_data {
    /*
        Type can be any of the following:
        0x1: integer
        0x2: double
        0x4: string/char array
    */
    int type;
    union {
        int integer;
        double decimal;
        char* string;
    } data;
};

/*
    Define the class for axis-aligned bounding box, or AABB for short.
    Supports any number of dimensions.
*/
class AABB
{
public:
	AABB(attribute_data** bounds);
	~AABB();

    bool intersects(AABB* other);
    bool contains(AABB* other);
    void combine(AABB* other);
    attribute_data** getBounds();

    static attribute_data*  getAttributeInt(int data);
    static attribute_data*  getAttributeDouble(double data);
    static attribute_data*  getAttributeString(char* data);
    
private:
    attribute_data** m_bounds;
    
    static int              compare(attribute_data* A, attribute_data* B);
    static attribute_data*  min(attribute_data* A, attribute_data* B);
    static attribute_data*  max(attribute_data* A, attribute_data* B);
};

#endif
