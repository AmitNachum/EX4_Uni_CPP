#ifndef  MY_CONTAINER_HPP
#define MY_CONTAINER_HPP
#include <iostream>
#include <algorithm>
#include <vector>
using std::vector,std::cout;


namespace amit_container{
    template <typename T>
    class My_Container{

        private:
        vector<T> container;

        public:
        My_Container() = default;
        My_Container(My_Container& other):container(other.container){};
        ~My_Container() = default;
        My_Container& operator=(My_Container & other){
            if(this == &other) return *this;

            this->container = other.container;

            return *this;
        }


        void add_element(T element){
            container.push_back(element);
        }
        void remove(T element){
            container.erase(std::remove(container.begin(),container.end(),element),container.end());
        }

        size_t size(){
            return container.size();
        }

    friend std::ostream& operator<<(std::ostream &os, My_Container& other) {
        os << "{";

        for (auto it = other.container.begin(); it != other.container.end(); ++it) {
                    os << *it;
            if (std::next(it) != other.container.end()) {
                os << ", ";
            }
            
            }

            os << "}";

        return os;
        }




    };





};


#endif