#include <Collider.h>
#include <tuple>

using namespace std; 

Collider::Collider(tuple<float, float> a, tuple<float, float> b, tuple<float, float> c, tuple<float, float> d) {
    this->a = a; 
    this->b = b; 
    this->c = c; 
    this->d = d; 
}