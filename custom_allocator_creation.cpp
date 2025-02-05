// What do we need for custom allocators
// well we need to know class strcuture
// class name has: constructor and destructor with same name by convention and also methods
// they can be static or dynamic, the methods
// static belong to class itself can be called without object creation
// the other belongs to the object created as a representation of that class

// purpose of custom allocators:
//    - faster then classic new and delete
//    - class based
//    - using ref and pointers
//    - faster in terms of accessing the memory
//    - better memory locality. Avoids possible fragmentation
//    - optimizable for specific objects like pools, collections, or fixed objects
//    - there s no allocation overhead

#include <iostream>
#include <fstream>
#include <mutex>
#include <memory>
#include <cstdlib>
using namespace std;

class CustomAlloc{
  public:
    static void* operator new( std::size_t iGiveTheSize ){
        // pointer to a fucntion accessible outside the class without object creation that allocates memory
        // with the dimension that i specify and its a fucntion that overloads the operator new
        std::cout << "Custom `new` allocator of size: " << iGiveTheSize << "bytes \n";
        return std::malloc( iGiveTheSize );
    }
    static void operator delete( void* ptr ){
        // we send a void pointer because it is overwriteable by any data type
        std::cout << "custom `delete` operator overloading\n";
        std::free(ptr);
    }
};

int main(){
    CustomAlloc* obj = new CustomAlloc(); // here we use the overloaded operator new
    delete obj;  // it will call the overloaded fuction to free up the resources existing in heap memory
    return 0;
}
// at execution we see that the current method allocates 1 byte because
// that s cause new size_t executes before constructor runs
// thus class creates room enough for 1 object that is 1 byte
// If we wanna create custom allocators then we have to make pools

// custom allocator makes use of static functions withut returning type to overload the new and delete operators to make them faster and the associated memory less volatile
