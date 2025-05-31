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
  Middle_Out_Iterator begin_mid_out() const {
    Middle_Out_Iterator it(container);
    size_t n = container.size();
    if (n == 0) {
        return it;
    }

    size_t middle = n / 2;
    it.set_index(middle);

 
    if (middle == 0) {
        it.set_left((size_t)-1);
    } else {
        it.set_left(middle - 1);
    }

    
    it.set_right(middle + 1);

    
    it.set_went_left(false);

    return it;
}

Middle_Out_Iterator end_mid_out() const {
    Middle_Out_Iterator it(container);
    it.set_index(container.size());
    return it;
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
    

Side_Cross_Order begin_side_cross() {
    Side_Cross_Order it(container);
    return it;
}

    Side_Cross_Order end_side_cross(){
       Side_Cross_Order iterator(container);
       iterator.set_index(container.size() / 2);
       return iterator;
    }


class Middle_Out_Iterator {
private:
    vector<T> arrange;
    size_t index;
    size_t left;
    size_t right;
    bool went_left;    
    size_t sz;  
    bool start;       

public:
    
    Middle_Out_Iterator(const vector<T>& data)
        : arrange(data),
          index(data.size()),    
          left((size_t)-1),
          right(data.size()),
          went_left(false),
          sz(data.size()),
          start(true)
    {}

    Middle_Out_Iterator(const Middle_Out_Iterator& other) = default;
    ~Middle_Out_Iterator() = default;
    Middle_Out_Iterator& operator=(const Middle_Out_Iterator& other) = default;

    T operator*() const {
        return arrange.at(index);
    }


    Middle_Out_Iterator& operator++() {
        if (index == sz) {
            return *this;
        }
        if(start){
            start = false;
            went_left = true;
            index = left;
            left--;
            return *this;
        }

        if (went_left) {
            if (right < sz) {
                index = right;
                ++right;
            } else {
                index = sz;
            }
        } else {
            if (left != (size_t)-1) {
                index = left;
                if (left > 0) {
                    --left;
                } else {
                    left = (size_t)-1;
                }
            } else {
                index = sz;  
            }
        }


        went_left = !went_left;
        return *this;
    }


    bool operator!=(const Middle_Out_Iterator& other) const {
        return this->index != other.index;
    }

    void set_index(size_t chagne){
        index = chagne;
    }

    void set_went_left(bool value){
        went_left = value;
    }
    void set_right(size_t change){
        if(change >= sz){
            return;
        }
        right = change;
    }

    void set_left(size_t change){
        if(change >= sz){
            return;
        }
        left = change;
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

    bool operator==(const Ascending_Iterator& other){
        return this->index == other.index;
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
    bool operator==(const Descending_Iterator& other){
        return this->index == other.index;
    }



};

class Side_Cross_Order{

    private:
    size_t index;
    vector<T> sorted;
    size_t right;
    size_t left;
    bool from_left;
    bool at_end;

    public:

    Side_Cross_Order(const vector<T>& data)
        :sorted(data), right(sorted.size() - 1), left(0), from_left(true),at_end(false) {
            std::sort(sorted.begin(),sorted.end());
            index = left;
        }

    ~Side_Cross_Order() = default;
    Side_Cross_Order(const Side_Cross_Order& other) = default;
    Side_Cross_Order& operator=(const Side_Cross_Order& other) = default;

    bool get_end()const {
        return at_end;
    }
    bool get_from_left()const {
        return from_left;
    }
    size_t get_left()const{
        return left;
    }

    size_t get_right()const{
        return right;
    }

    void set_left(size_t change){
        if(change >= sorted.size()){
            return;
        }
        left = change;
    }

    void set_right(size_t change){
        if(change >= sorted.size()){
            return;
        }
        right = change;
    } 

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
        if ( left > right ) {
            at_end = true;
            return *this;
        }
        if( left == 0 ){
            left++;
        }
        if(from_left){
            index = right--;
        } else{
            index = left++;
        }
        from_left = !from_left;


        return *this;
    }



    bool operator!=(const Side_Cross_Order& other) const {
        return !at_end || this->index != other.index ;
    }

      bool operator==(const Side_Cross_Order& other){
        return this->index == other.index;
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

    bool operator==(const Reverse_Iterator other){
        return this->index == other.index;
    }

    };
};




};







#endif