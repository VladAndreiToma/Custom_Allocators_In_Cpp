//stl compatible allocator is as follows
// must work with stl libraries std::vector std::map and so on
// must allocate n elements and memory correspondent to it so allocate size_t n instances
// deallocate memory and quantity so a pointer to the head of the memory chunck and the quantity
// define what data type it allocates
// rebinding to diff types
// to be generic we will use template and rebind to another template

// class is private and encapsulates code by default
// struct is not private and does not encapsulate code by default

#include <iostream>
#include <memory>
#include <vector>

template<typename T>  // accepts whatever vector map anything

struct CustomAlloc{
    using value_type = T;
    // allocator fucntion
    T* allocate( std::size_t n ){
        std::cout << "Allocating: " << n << " elements\n";
        return static_cast<T*>(std::malloc(n*sizeof(T)));
    } 
    //deallocator function
    void deallocate(T* p , std::size_t n){
        std::cout<<"Deallocating: " << n << " elements\n";
        std::free(p);
    } 
    // rebinding for stl compatibility
    template<typename U>
    struct rebind{
        using other = CustomAlloc<U>;
    };
};

int main(){
    std::vector<int, CustomAlloc<int>> vec;
     vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    for (int val : vec) {
        std::cout << val << " ";
    }

    return 0;
}