#include "my_container.hpp"

using namespace amit_container;


int main(){

    My_Container<int> cont;
    
    for(size_t i = 0 ; i < 3 ; i++){
        
        cont.add_element(1);
    }



    std::cout << cont<<std::endl;


    cont.remove(1);

    std::cout <<cont << std::endl;
    return 0;
}