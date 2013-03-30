#include <cstring>
#include "aabb.h"
#include "stdlib.h"

using namespace std;

AABB::AABB(attribute_data** bounds)
{
    if (sizeof(bounds)/sizeof(attribute_data*) % 2 == 0) {
        this->m_bounds = bounds;
    }
    else {
        // ERROR
    }
}

AABB::~AABB() {
    // Free up all attribute data in the bounds array
}

/*
    Returns the following values depending on the outcome of the comparison:
    1: Attribute A is greater than attribute B
    0: Attribute A is equal to attribute B
    -1: Attribute A is lower than attribute B
    -9999: An error has occurred; attribute A is not the same type as attribute B
*/
static int compare(attribute_data* A, attribute_data* B) {
    int ret = -9999;

    // If true, then they are both equal and a logical AND of these two values (of base 2) do not give a zero.
    if (A->type && B->type) {
        int type = A->type;

        if (type == RT_AABB_TYPE_INTEGER) {
            if (A->data.integer == B->data.integer) { ret = 0; }
            else if (A->data.integer > B->data.integer) { ret = 1; }
            else { ret = -1; }
        }
        else if (type == RT_AABB_TYPE_DOUBLE) {
            if (A->data.decimal == B->data.decimal) { ret = 0; }
            else if (A->data.decimal > B->data.decimal) { ret = 1; }
            else { ret = -1; }
        }
        else if (type == RT_AABB_TYPE_STRING) {
            // Do a lexicographical comparison. Assume that both strings have a length of at least 1.
            char charA;
            char charB;
            int idx = 0;
            bool done = false;
            ret = 0;

            for (idx = 0; ; idx++) {
                charA = *(A->data.string + idx);
                charB = *(B->data.string + idx);
            
                // If true, then sets the current ret from 0 to -1 (string A is smaller than string B).
                if (charA == NULL) {
                    ret--;
                    done = true;
                }
                // If true, then sets the current ret from 0 to 1 (string A is bigger than string B), or -1 to 0 (string A is equal to string B, this should happen if the current index at string A is also null).
                if (charB == NULL) {
                    ret++;
                    done = false;
                }
                
                if (done) { break; }

                // At this point we have established that the current index points to a non-null character in both strings.

                if (charA == charB) {
                    ret = 0;
                }
                // If one character is bigger than the other, then we are done here.
                else if (charA > charB) {
                    ret = 1;
                    break;
                }
                else {
                    ret = -1;
                    break;
                }
            }
        }
        else {
            // ERROR
            // Invalid attribute type
        }
    }
    else {
        // ERROR; cannot compare two data types
    }
}

static attribute_data* min(attribute_data* A, attribute_data* B) {
    int result = compare(A, B);
    if (result == -1) { return A; }
    else if (result == 1 | result == 0) { return B; }
    else { return NULL; } // ERROR
}

static attribute_data* max(attribute_data* A, attribute_data* B) {
    int result = compare(A, B);
    if (result == -1) { return B; }
    else if (result == 1 | result == 0) { return A; }
    else { return NULL; } // ERROR
}

bool AABB::intersects(AABB* other) {
    // TODO
    // Might want to check this: http://en.wikipedia.org/wiki/Hyperplane_separation_theorem
    return true;
}

bool AABB::contains(AABB* other) {
    // TODO
    return true;
}

attribute_data** AABB::getBounds() {
    return this->m_bounds;
}

void AABB::combine(AABB* other) {
    // Assume that both AABB's have the same number of bounds

    attribute_data** otherBounds = other->getBounds();
    int idx = 0;
    int boundsCount = sizeof(otherBounds);
    
    for (idx = 0; idx < boundsCount; idx+=2) {        
        // TODO
        // Consider discarding the argument AABB since we don't really need it anymore (I think).
        // Also, consider copying bound data to the newly combined AABB.
        // If we keep assigning pointers everywhere, I might end up with a very tangled pointer shenanigans and it might be hard to do proper cleanup.
        *(this->m_bounds + idx) = min(*(this->m_bounds + idx), *(otherBounds + idx));
        *(this->m_bounds + idx + 1) = max(*(this->m_bounds + idx + 1), *(otherBounds + idx + 1));
    }
}

static attribute_data* getAttributeInt(int data) {
    attribute_data* integerData = (attribute_data*)malloc(sizeof(attribute_data));
    integerData->type = RT_AABB_TYPE_INTEGER;
    integerData->data.integer = data;
    return integerData;
}

static attribute_data* getAttributeDouble(double data) {
    attribute_data* doubleData = (attribute_data*)malloc(sizeof(attribute_data));
    doubleData->type = RT_AABB_TYPE_DOUBLE;
    doubleData->data.decimal = data;
    return doubleData;
}

static attribute_data* getAttributeString(char* data) {
    // Invalid data
    if (sizeof(data) == 0) { return NULL; }
    
    attribute_data* stringData = (attribute_data*)malloc(sizeof(attribute_data));
    stringData->type = RT_AABB_TYPE_STRING;
    stringData->data.string = data;
    return stringData;
}
