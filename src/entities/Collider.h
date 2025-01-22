#ifndef COLLIDER_H
#define COLLIDER_H

#include <tuple>

/*

void SetCollider(float width, float height, tuple<float, float> origin) {
    this->a = origin; 
    this->b = origin - height; 
    this->c = origin - height + width; 
    this->d = origin + width; 
}

bool IsColliding()

class Collider {
public: 


private: 
tuple<float, float> a; 
tuple<float, float> b; 
tuple<float, float> c; 
tuple<float, float> d; 
};

*/

struct Collider {
    tuple<float, float> a; 
    tuple<float, float> b; 
    tuple<float, float> c; 
    tuple<float, float> d; 

    Collider(tuple<float, float> a, tuple<float, float> b, tuple<float, float> c, tuple<float, float> d); 
};


#endif 