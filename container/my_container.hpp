#ifndef  MY_CONTAINER_HPP
#define MY_CONTAINER_HPP
#include <iostream>
#include <algorithm>
#include <vector>
#include <typeinfo>
using std::vector;
using std::cout;


namespace amit_container{
    template <typename T>
    class My_Container{

        private:
        vector<T> container;

        public:
        class Ascending_Iterator;
        class Descending_Iterator;
        class Side_Cross_Order;
        class Reverse_Iterator;
        class Order_Iterator;
        class Middle_Out_Iterator;


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

        size_t size() const{
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
     
    Middle_Out_Iterator begin_mid_out(){
        int middle = (this->size() / 2);
        Middle_Out_Iterator iter(container);
        iter.set_index(middle);
        return iter;
    }    

    Middle_Out_Iterator end_mid_out(){
      int end = (this->size() % 2 != 0) ? this->size() : 0;
      Middle_Out_Iterator iter(container);
      iter.set_index(end);
      return iter; 
    }


    Order_Iterator begin_order(){
        return Order_Iterator(container);
    }
    
    Order_Iterator end_order(){
        Order_Iterator iter(container);
        iter.set_index(container.size());
        return iter;
    }

    Reverse_Iterator begin_reverse(){
       return  Reverse_Iterator(container);
    }
    Reverse_Iterator end_reverse(){
        Reverse_Iterator iter(container);
        iter.set_index(container.size());
        return iter;
    }

    Ascending_Iterator begin_ascending(){
     return Ascending_Iterator(container);
    }

    Ascending_Iterator end_ascending(){
       Ascending_Iterator asc_it(container);
       asc_it.set_index(container.size());
       return asc_it;
    }        

    Descending_Iterator begin_descending(){
        return Descending_Iterator(container); 
    }
    
    Descending_Iterator end_descending(){
        Descending_Iterator it(container);
        it.set_index(container.size());
        return it;
    }
    

    Side_Cross_Order begin_side_cross(){
        return Side_Cross_Order(container);
    }

    Side_Cross_Order end_side_cross(){
       Side_Cross_Order iterator(container);
       iterator.set_index(container.size());
       return iterator;
    }


class Middle_Out_Iterator{
    
    private:
    vector<T> arrange;
    size_t index;
    size_t left;
    size_t right;
    size_t middle;
    bool went_left;

    public:

    Middle_Out_Iterator(const vector<T> data): arrange(data),index(0),went_left(false){
        middle = arrange.size() / 2;
        right = middle + 1;
        left = middle - 1;
    };
    Middle_Out_Iterator(const Middle_Out_Iterator& other) = default;
    ~Middle_Out_Iterator() = default;
    Middle_Out_Iterator& operator=(const Middle_Out_Iterator& other) = default;


    T operator*(){
        return arrange[index];
    }

 Middle_Out_Iterator& operator++() {
    if (went_left && right < arrange.size()) {
        index = right++;
    } else if (!went_left && left < arrange.size()) {
        index = left--;
    } else {
        index = arrange.size();  // terminate
    }
    went_left = !went_left;
    return *this;
}



    bool operator!=(const Middle_Out_Iterator& other){
        return this->index != other.index;
    }

    void set_index(size_t changed){
        if(changed > arrange.size()){
            throw std::runtime_error("Index Out Of Bounce");
        }
        index = changed;
    }


};    


class Order_Iterator{


    private:
    vector<T> arrange;
    size_t index;

    public:
    Order_Iterator(const vector<T> data):arrange(data),index(0){};
    Order_Iterator(const Order_Iterator& other) = default;
    ~Order_Iterator() = default;
    Order_Iterator& operator=(const Order_Iterator& other) = default;

    void set_index(size_t changed){
        if(changed > arrange.size()){
            throw std::runtime_error("Index Out Of Bounce");
        }
        index = changed;
    }


    T operator*(){
        return arrange.at(index);
    }

    bool operator!=(const Order_Iterator& other){
        return this->index != other.index;
    }

    Order_Iterator& operator++(){
        ++index;
        return *this;
    }

};    
    

    

    

class Ascending_Iterator{
    private:
    vector<T> sorted;
    size_t index;

    public:
    Ascending_Iterator(const vector<T>& data): sorted(data),index(0){
        std::sort(sorted.begin(),sorted.end());
    }

     ~Ascending_Iterator() = default;
    Ascending_Iterator& operator=(const Ascending_Iterator& other) = default;

    void set_index(size_t changed){
        if(changed > sorted.size()){
            throw std::runtime_error("Index Out Of Bounce");
        }
        index = changed;
    }

    T operator*() const{
        return sorted.at(index);
    }

    Ascending_Iterator& operator++(){
        ++index;
        return *this;
    }

    bool operator!=(const Ascending_Iterator& other){
       return this->index != other.index;
    }




};



class Descending_Iterator{
    private:
    vector<T> sorted;
    size_t index;

    public:

    Descending_Iterator(const vector<T>& data):sorted(data){
        std::sort(sorted.begin(), sorted.end(), std::greater<T>());
        index = 0;
    }
    ~Descending_Iterator() = default;
    Descending_Iterator& operator=(const Descending_Iterator& other) = default;

    T operator*() const{
        return sorted.at(index);
    }

    void set_index(size_t changed){
        if( changed > sorted.size()){
            throw std::runtime_error("Index Out Of Bounce");
        }
        index = changed;
    }

    Descending_Iterator& operator++(){
        ++index;
        return *this;
    }

    bool operator!=(const Descending_Iterator& other){
        return this->index != other.index;
    }




};

class Side_Cross_Order{

    private:
    size_t index;
    vector<T> sorted;
    size_t right;
    size_t left;
    bool from_left;

    public:

    Side_Cross_Order(const vector<T>& data)
        :sorted(data), right(sorted.size() - 1), left(0), from_left(true) {
            std::sort(sorted.begin(),sorted.end());
            index = data.size;
        }

    ~Side_Cross_Order() = default;
    Side_Cross_Order(const Side_Cross_Order& other) = default;
    Side_Cross_Order& operator=(const Side_Cross_Order& other) = default;

    T operator*()const{
        return sorted.at(index);
    }

    void set_index(size_t changed){
        if(changed > sorted.size()){
            throw std::runtime_error("Index Out Of Bounce");
        }
        index = changed;
    }

    Side_Cross_Order& operator++() {
        if (left > right) {
            index = sorted.size();  // Mark as end
            return *this;
        }

        if (from_left) {
            index = left++;
        } else {
            index = right--;
        }

        from_left = !from_left;
        return *this;
    }



    bool operator!=(const Side_Cross_Order& other) const {
        return this->index != other.index;
    }



};



class Reverse_Iterator {
    private:
        vector<T> reversed;
        size_t index;

    public:
        Reverse_Iterator(const vector<T>& data) : reversed(data), index(0) {
            std::reverse(reversed.begin(), reversed.end());
        }

        T operator*() const {
            return reversed.at(index);
        }

        Reverse_Iterator& operator++() {
            ++index;
            return *this;
        }

        bool operator!=(const Reverse_Iterator& other) const {
            return index != other.index;
        }

    void set_index(size_t changed){
        if(changed > reversed.size()){
            throw std::runtime_error("Index Out Of Bounce");
        }
        index = changed;
    }
    };
};




};







#endif