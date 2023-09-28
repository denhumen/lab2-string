// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "mystring.hpp"


int main() {

    my_str_t init_string(10); // constructor, that takes size and optional char(default='a')
    for (size_t i = 0; i < init_string.size(); i++) {
        std::cout << init_string[i] << std::endl;
    }

    my_str_t string_from_c{"Hello everyone! I'm string!"}; // c-string constructor
    std::cout << string_from_c << std::endl;
    std::cout << string_from_c.size() << std::endl; // actual string size
    std::cout << string_from_c.capacity() << std::endl; // the smallest greater than size number, that divides 16 + 1

    std::string cpp_string = "Another test of this string!";
    my_str_t str_from_cpp{cpp_string}; // c++ string constructor

    std::cout << str_from_cpp << std::endl;

    my_str_t copy_of_string(str_from_cpp); // copying constructor

    std::cout << copy_of_string << std::endl;
    str_from_cpp[1] = 'q'; // changed the string, which we copied

    std::cout << str_from_cpp << std::endl; // changed
    std::cout << copy_of_string << std::endl; // not changed

    my_str_t original_string("Let's check if we can assign it to smth");

    my_str_t test_assign = original_string;

    original_string[1] = 'q';

    std::cout << test_assign << std::endl; // didn't change

    my_str_t str_to_move("Hello there");
    my_str_t str_to_get_info(std::move(str_to_move)); //move constructor
    std::cout << str_to_get_info << std::endl;

    my_str_t str_to_move2("Hello");
    my_str_t str_to_get_info2 = std::move(str_to_move2); // another way to move
    std::cout << str_to_get_info2 << std::endl;

    const my_str_t String("This is a story about Harry Potter");

    std::cout << String[16] << std::endl;

    //checking swap
    my_str_t str1("String1");
    my_str_t str2("String2");
    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;

    str1.swap(str2);

    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;

    std::cout << str1.at(2) << std::endl;
//    std::cout << str1.at(7) << std::endl; // exception raised

    const my_str_t constant_string("Hi! I'm constant string!");
//    constant_string.at(10); // have warning, because our method is [[nodiscard]]
    std::cout << constant_string.at(2) << std::endl;

    my_str_t small_string("I'm small!");
    std::cout << small_string.capacity() << std::endl;
    small_string.reserve(12);
    std::cout << small_string.capacity() << std::endl; //nothing changed
    small_string.reserve(124); // increasing capacity
    std::cout << small_string.capacity() << std::endl;

    small_string.shrink_to_fit(); //decreasing capacity to the smallest possible
    std::cout << small_string.capacity() << std::endl;

    my_str_t string_that_will_be_increased("small one");
    string_that_will_be_increased.resize(17, 'a'); // resizing for size that is <= capcaity
    std::cout << string_that_will_be_increased << std::endl;
    std::cout << string_that_will_be_increased.capacity() << std::endl;

    string_that_will_be_increased.resize(100); // resizing to the size bigger that capacity, reserve() worked
    std::cout << string_that_will_be_increased << std::endl;
    std::cout << string_that_will_be_increased.size() << std::endl;
    std::cout << string_that_will_be_increased.capacity() << std::endl;

    string_that_will_be_increased.clear(); // clearing fully the string
    std::cout << string_that_will_be_increased << std::endl;
    std::cout << string_that_will_be_increased.size() << std::endl;
    std::cout << string_that_will_be_increased.capacity() << std::endl;

    my_str_t piece_of_string("aaabbb");
    my_str_t good_string("Hello Everyone");

//    piece_of_string.insert(50, good_string); // exception here

    piece_of_string.insert(2, good_string);
    std::cout << piece_of_string << std::endl;
    std::cout << piece_of_string.size() << std::endl;
    std::cout << piece_of_string.capacity() << std::endl;

    piece_of_string.insert(0, 'q');
    std::cout << piece_of_string << std::endl;

    piece_of_string.insert(0, "ppp");
    std::cout << piece_of_string << std::endl;
    my_str_t string_will_append_to("UCU");
    my_str_t appended_string(" is the best university");
    string_will_append_to.append(appended_string);
    std::cout << string_will_append_to << std::endl;
    std::cout << string_will_append_to.size() << std::endl;
    std::cout << string_will_append_to.capacity() << std::endl;

    string_will_append_to.append('q');
    std::cout << string_will_append_to << std::endl;
    std::cout << string_will_append_to.size() << std::endl;
    std::cout << string_will_append_to.capacity() << std::endl;

    string_will_append_to.append(" Exactly");
    std::cout << string_will_append_to << std::endl;
    std::cout << string_will_append_to.size() << std::endl;
    std::cout << string_will_append_to.capacity() << std::endl;

    my_str_t will_be_erased("Let's see what we have here.");
    std::cout << will_be_erased << std::endl;
    std::cout << will_be_erased.size() << std::endl;
    std::cout << will_be_erased.capacity() << std::endl;
    will_be_erased.erase(3, 4);
    std::cout << will_be_erased << std::endl;
    std::cout << will_be_erased.size() << std::endl;
    std::cout << will_be_erased.capacity() << std::endl;

    will_be_erased.erase(1, 100);
    std::cout << will_be_erased << std::endl;
    std::cout << will_be_erased.size() << std::endl;
    std::cout << will_be_erased.capacity() << std::endl;

//    will_be_erased.size(); // can't do this because of [[nodiscard]]
//    will_be_erased.capacity(); // same situation

    my_str_t string_will_search_in("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    std::cout << string_will_search_in.find('X', 0) << std::endl;
    std::cout << string_will_search_in.find('A', 2) << std::endl;
//    std::cout << string_will_search_in.find('A', 53) << std::endl; // won't work because of big index

    std::string substr{"BCD"};
    std::cout << string_will_search_in.find(substr, 0) << std::endl;

    std::cout << string_will_search_in.find("XYZ", 0) << std::endl;

//    std::cout << string_will_search_in.substr(27, 29); //exception beacuse of index
    my_str_t new_str =  string_will_search_in.substr(1, 5);
    std::cout << new_str << std::endl;
    std::cout << new_str.size() << std::endl;
    std::cout << new_str.capacity() << std::endl;

    my_str_t added_str("GHIJKL");

    new_str += added_str;

    std::cout << new_str << std::endl;
    std::cout << new_str.size() << std::endl;
    std::cout << new_str.capacity() << std::endl;

    my_str_t add1("Hello");
    my_str_t add2(" How are you?");
    my_str_t result = add1 + add2;
    std::cout << result << std::endl;
    std::cout << result.size() << std::endl;
    std::cout << result.capacity() << std::endl;

    new_str *= 2;

    std::cout << new_str << std::endl;
    std::cout << new_str.size() << std::endl;
    std::cout << new_str.capacity() << std::endl;

    my_str_t result2 = new_str * 3;
    std::cout << result2 << std::endl;
    std::cout << result2.size() << std::endl;
    std::cout << result2.capacity() << std::endl;

//    new_str.c_str(); // can't do this because of [[nodiscard]]

    std::cout << new_str.c_str() << std::endl;
    std::cout << strlen(new_str.c_str()) << std::endl;

    my_str_t checked1("Hello");
    my_str_t checked2("HelloHello");
    std::cout << ((checked1 * 2) == checked2) << std::endl;
    std::cout << ((checked1 * 3) != checked2) << std::endl;

    my_str_t to_compare1("AB");
    my_str_t to_compare2("ABC");
    std::cout << (to_compare1 < to_compare2) << std::endl;
    std::cout << (to_compare1 > to_compare2) << std::endl;

    my_str_t to_compare3("XYXYXY");
    my_str_t to_compare4("XYXYXY");
    std::cout << (to_compare3 <= to_compare4) << std::endl;
    std::cout << (to_compare3 >= to_compare4) << std::endl;
    std::cout << (to_compare3 <= to_compare2) << std::endl;
    std::cout << (to_compare4 >= to_compare1) << std::endl;
}