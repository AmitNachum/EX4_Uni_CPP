#include <iostream>
#include "my_container.hpp"

using namespace std;
using namespace amit_container;
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"
#define BRIGHT_BLACK   "\033[1;30m"
#define BRIGHT_RED     "\033[1;31m"
#define BRIGHT_GREEN   "\033[1;32m"
#define BRIGHT_YELLOW  "\033[1;33m"
#define BRIGHT_BLUE    "\033[1;34m"
#define BRIGHT_MAGENTA "\033[1;35m"
#define BRIGHT_CYAN    "\033[1;36m"
#define BRIGHT_WHITE   "\033[1;37m"
#define DARK_BROWN "\033[38;5;94m"
#define DARK_RED "\033[38;2;139;0;0m"



void print_title(const std::string& title, const std::string& color) {
    std::cout << color << "=== " << title << " ===" << RESET << '\n';
}

template <typename Iterator>
void print_iterator(Iterator begin, Iterator end,size_t cont_size) {
    std::cout << "\n   {";
    size_t index_comma = 0;
    for (auto it = begin; it != end; ++it) {
        std::cout << *it;
        if(index_comma < cont_size - 1){
            index_comma++;
            cout<< ", ";
        }

    }
    std::cout << "}\n\n";
}



using namespace amit_container;
using namespace std;

int main() {
    My_Container<int> container;
    container.add_element(7);
    container.add_element(15);
    container.add_element(6);
    //container.add_element(1);
    container.add_element(2);

    cout << "=== Original Container ===\n";
    cout << "   Size of container: " << container.size() << "\n" << endl;
    cout << "    " << container <<"\n\n";

    print_title("Ascending Iterator",BLUE);
    print_iterator(container.begin_ascending(), container.end_ascending(),container.size());
    print_title("End Ascending",BLUE);
    cout <<"\n\n";

    print_title("Descending Iterator",GREEN);
    print_iterator(container.begin_descending(),container.end_descending(),container.size());
    print_title("End Descending",GREEN);
    cout << "\n\n";

    print_title("Side Cross Iterator",MAGENTA);
    print_iterator(container.begin_side_cross(),container.end_side_cross(),container.size());
    print_title("Side Cross End",MAGENTA);
    cout << "\n\n";

    print_title("Reverse Iterator",RED);
    print_iterator(container.begin_reverse(),container.end_reverse(),container.size());
    print_title("Reverse End",RED);
    cout <<"\n\n";


    print_title("Order Iterator",DARK_BROWN);
    print_iterator(container.begin_order(),container.end_order(),container.size());
    print_title("End Order",DARK_BROWN);
    cout <<"\n\n";

    try{
    print_title("Middle Out Iterator",DARK_RED);
    print_iterator(container.begin_mid_out(),container.end_mid_out(),container.size());
    print_title("Middle Out end",DARK_RED);
    } catch(std::exception& ex){
        std::cout << (ex.what());
    }
    

    return 0;
}
