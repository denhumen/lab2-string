// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <cstring>
#include "mystring.hpp"

// Author: Kostyantin Savorona
size_t my_str_t::increase_to_divided_by_16(size_t x) {
    return x +  (16 - (x % 16));
}

// Author: Kostyantin Savorona
my_str_t::my_str_t(size_t size, char initial) : size_m(size), capacity_m(increase_to_divided_by_16(size)) {
    data_m = new char[capacity_m];
    std::memset(data_m, initial, size);
    data_m[size_m] = '\0';
}

// Author: Kostyantin Savorona
my_str_t::my_str_t(const char* cstr) {
    size_m = strlen(cstr);
    capacity_m = increase_to_divided_by_16(size_m);
    data_m = new char[capacity_m];
    std::strcpy(data_m, cstr);
}

// Author: Kostyantin Savorona
my_str_t::my_str_t(const std::string &str) {
    size_m = str.size();
    capacity_m = increase_to_divided_by_16(size_m);
    data_m = new char[capacity_m];
    std::memmove(data_m, str.c_str(), size_m);
    data_m[size_m] = '\0';
}

// Author: Kostyantin Savorona
my_str_t::my_str_t(const my_str_t &my_str_t) : size_m(my_str_t.size_m), capacity_m(my_str_t.capacity_m) {
    data_m = new char[capacity_m];
    for (size_t i = 0; i < size_m; ++i) {
        data_m[i] = my_str_t.data_m[i];
    }
    data_m[size_m] = '\0';
}

// Author: Denis Humeniuk
my_str_t::my_str_t(my_str_t &&str) noexcept : size_m(str.size_m), capacity_m(str.capacity_m) {
    data_m = str.data_m;
    str.data_m = nullptr;
}

// Author: Kostyantin Savorona
char& my_str_t::operator[](size_t idx) {
    return this->data_m[idx];
}

// Author: Kostyantin Savorona
const char& my_str_t::operator[](size_t idx) const {
    return this->data_m[idx];
}

// Author: Kostyantin Savorona
my_str_t& my_str_t::operator=(const my_str_t &mystr) {
    my_str_t temp(mystr);
    std::swap(*this, temp);
    return *this;
}

// Author: Denis Humeniuk
my_str_t& my_str_t::operator=(my_str_t &&mstr) noexcept {
    if (this != &mstr) {
        delete[] data_m;
        size_m = mstr.size_m;
        capacity_m = mstr.capacity_m;
        data_m = mstr.data_m;
        mstr.size_m = 0;
        mstr.capacity_m = 0;
        mstr.data_m = nullptr;
    }
    return *this;
}

// Author: Kostyantin Savorona
void my_str_t::swap(my_str_t &other) {
    std::swap(*this, other);
}

// Author: Kostyantin Savorona
char& my_str_t::at(size_t idx) {
    if (idx >= size_m) {
        throw std::out_of_range("There is no such index");
    }
    return this->data_m[idx];
}

// Author: Kostyantin Savorona
[[nodiscard]] const char& my_str_t::at(size_t idx) const {
    if (idx >= size_m) {
        throw std::out_of_range("There is no such index");
    }
    return this->data_m[idx];
}

// Author: Kostyantin Savorona
void my_str_t::reserve(size_t new_capacity) {
    if (new_capacity > capacity_m) {
        capacity_m = new_capacity;
        char *new_data = new char[new_capacity];
        std::memcpy(new_data, data_m, size_m);
        delete[] data_m;
        data_m = new_data;
        data_m[size_m] = '\0';
    }
}

// Author: Kostyantin Savorona
void my_str_t::shrink_to_fit() {
    capacity_m = size_m + 1;
    char *new_data = new char[capacity_m];
    for (size_t i = 0; i < size_m; i++) {
        new_data[i] = data_m[i];
    }
    delete[] data_m;
    data_m = new_data;
    data_m[size_m] = '\0';
}

// Author: Kostyantin Savorona
void my_str_t::resize(size_t new_size, char new_char) {
    if (new_size <= size_m) size_m = new_size;
    if (new_size > size_m && new_size <= capacity_m) {
        for (size_t i = size_m; i < new_size; i++) {
            data_m[i] = new_char;
        }
        size_m = new_size;
        data_m[size_m] = '\0';
    }
    if (new_size > capacity_m) {
        reserve(new_size);
        size_m = new_size;
    }
}

// Author: Kostyantin Savorona
void my_str_t::clear() {
    *data_m = '\0';
    size_m = 0;
}

// Author: Kostyantin Savorona
void my_str_t::insert(size_t idx, const my_str_t &str) {
    if (idx > size_m) throw std::out_of_range("Index out of range!");

    if (str.size() + size_m > capacity_m) {
        capacity_m = increase_to_divided_by_16(size_m + str.size_m);
        char* new_data = new char[capacity_m];
        std::memcpy(new_data, data_m, idx);
        std::memcpy(new_data + idx, str.data_m, str.size_m);
        std::memcpy(new_data + idx + str.size_m, data_m + idx, size_m - idx);
        delete[] data_m;
        data_m = new_data;
    } else {
        std::memmove(data_m + idx + str.size_m, data_m + idx, size_m - idx);
        std::memcpy(data_m + idx, str.data_m, str.size_m);
    }

    size_m += str.size_m;
    data_m[size_m] = '\0';
}

// Author: Kostyantin Savorona
void my_str_t::insert(size_t idx, char c) {
    if (idx > size_m)
        throw std::out_of_range("Index out of range!");

    if (size_m + 1 > capacity_m){
        capacity_m = increase_to_divided_by_16(size_m + 1);
        char* new_data = new char[capacity_m];
        std::memcpy(new_data, data_m, size_m);
        delete[] data_m;
        data_m = new_data;
    }
    std::memmove(data_m + idx + 1, data_m + idx, size_m - idx);
    size_m++;
    data_m[idx] = c;
    data_m[size_m] = '\0';
}

// Author: Denis Humeniuk
void my_str_t::insert(size_t idx, const char* cstr) {
    if (idx > size_m)
        throw std::out_of_range("Index out of range!");

    size_t cstr_length = strlen(cstr);
    if (size_m + cstr_length > capacity_m) {
        reserve(size_m + cstr_length + 1);
    }

    std::memmove(data_m + idx + cstr_length, data_m + idx, size_m - idx);

    std::memcpy(data_m + idx, cstr, cstr_length);

    size_m += cstr_length;
    data_m[size_m] = '\0';
}

// Author: Kostyantin Savorona
void my_str_t::append(const my_str_t &str) {
    capacity_m = increase_to_divided_by_16(size_m + str.size_m);
    char *new_data = new char[capacity_m];
    for (size_t i = 0; i < size_m; i++) {
        new_data[i] = data_m[i];
    }

    for (size_t k = 0; k < str.size_m; k++) {
        new_data[size_m + k] = str[k];
    }
    delete[] data_m;
    data_m = new_data;
    size_m += str.size_m;
    data_m[size_m] = '\0';
}

// Author: Kostyantin Savorona
void my_str_t::append(char c) {
    if (size_m + 1 >= capacity_m) {
        capacity_m = increase_to_divided_by_16(size_m + 2);
        char* new_data = new char[capacity_m];
        for (size_t i = 0; i < size_m; i++) {
            new_data[i] = data_m[i];
        }
        delete[] data_m;
        data_m = new_data;
    }
    data_m[size_m] = c;
    size_m++;
    data_m[size_m] = '\0';
}

// Author: Kostyantin Savorona
void my_str_t::append(const char* cstr) {
    size_t size = 0;
    const char *copy_str = cstr;
    while (*cstr != '\0') {
        size++;
        cstr++;
    }

    size_t new_size = size_m + size;
    capacity_m = increase_to_divided_by_16(new_size);
    char *new_data = new char[capacity_m];
    for (size_t i = 0; i < size_m; i++)
        new_data[i] = data_m[i];

    for (size_t k = 0; k < size; k++) {
        new_data[k + size_m] = copy_str[k];
    }
    size_m = new_size;
    delete[] data_m;
    data_m = new_data;
    data_m[size_m] = '\0';
}

// Author: Denis Humeniuk
void my_str_t::erase(size_t begin, size_t size) {
    if (begin > size_m)
        throw std::out_of_range("Index out of range!");

    if (size == 0)
        return;

    if (begin + size > size_m)
        size = size_m - begin;

    size_t i;

    for (i = begin; i < begin + size; ++i){
        data_m[i] = '\0';
    }

    for (size_t j = i; j < size_m; ++j){
        data_m[j-size] = data_m[j];
        data_m[j] = '\0';
    }

    size_m -= size;
    data_m[size_m] = '\0';
}

// Author: Kostyantin Savorona
[[nodiscard]] size_t my_str_t::size() const noexcept { return size_m; }

// Author: Kostyantin Savorona
[[nodiscard]] size_t my_str_t::capacity() const noexcept { return capacity_m; }

// Author: Kostyantin Savorona
size_t my_str_t::find(char c, size_t idx) {
    if (idx > size_m ) { throw std::out_of_range("Index out of range!"); }
    for (size_t i = idx; i < size_m; i++) {
        if (data_m[i] == c) { return i; }
    }
    return my_str_t::not_found;
}

// Author: Kostyantin Savorona
size_t my_str_t::find(const std::string &str, size_t idx) {
    if (idx > size_m ) { throw std::out_of_range("Index out of range!"); }

    for (size_t i = idx; i < size_m; i++) {
        if (data_m[i] == str[0]) {
            bool flag = true;
            for (size_t j = 0; j < str.size(); j++) {
                if (data_m[i + j] != str[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) { return i; }
        }
    }
    return my_str_t::not_found;
}

// Author: Denis Humeniuk
size_t my_str_t::find(const char* cstr, size_t idx) {
    if (idx > size_m)
        throw std::out_of_range("Index out of range!");

    for (size_t i = idx; i < size_m; ++i){
        if (data_m[i] == cstr[0]){
            bool flag = true;
            size_t length = std::strlen(cstr);
            for (size_t j = 0; j < length; ++j){
                if (data_m[i+j] != cstr[j]){
                    flag = false;
                    break;
                }
            }
            if (flag) return i;
        }
    }

    return my_str_t::not_found;
}

// Author: Kostyantin Savorona
my_str_t my_str_t::substr(size_t begin, size_t size) {
    if (begin > size_m) { throw std::out_of_range("Index out of range!"); }
    size_t res_size = (size > size_m - begin)? size_m - begin : size;
    my_str_t result_string{res_size};
    for (size_t i = 0; i < res_size; i++) {
        result_string[i] = data_m[begin + i];
    }
    return result_string;
}

// Author: Kostyantin Savorona
my_str_t& my_str_t::operator+=(const my_str_t &str) {
    if (str.size_m < capacity_m - size_m) {
        for (size_t i = 0; i < str.size_m; i++) {
            data_m[size_m + i] = str[i];
        }
        size_m += str.size_m;
        data_m[size_m] = '\0';
        return *this;
    } else {
        size_t new_size = size_m + str.size_m;
        size_t new_capacity = increase_to_divided_by_16(new_size);
        char* new_data = new char[new_capacity];
        for (size_t i = 0; i < size_m; i++) {
            new_data[i] = data_m[i];
        }
        for (size_t j = 0; j < str.size_m; j++) {
            new_data[size_m + j] = str[j];
        }
        size_m = new_size;
        capacity_m = new_capacity;
        delete[] data_m;
        data_m = new_data;
        data_m[size_m] = '\0';
        return *this;
    }
}

// Author: Kostyantin Savorona
my_str_t& my_str_t::operator*=(int number) {
    if (number == -1) { throw std::invalid_argument("Invalid argument!"); }
    if (number == 0) {
        this->clear();
        return *this;
    }
    if (capacity_m > size_m * number) {
        size_t new_size = size_m * (number - 1);
        for (size_t i = 0; i < new_size; i++) {
            data_m[size_m + i] = data_m[i % size_m];
        }
        size_m += new_size;
        data_m[size_m] = '\0';
        return *this;
    } else {
        size_t new_size = size_m * number;
        size_t new_capacity = increase_to_divided_by_16(new_size);
        char* new_data = new char[new_capacity];
        for (size_t i = 0; i < new_size; i++) {
            new_data[i] = data_m[i % size_m];
        }
        size_m = new_size;
        capacity_m = new_capacity;
        delete[] data_m;
        data_m = new_data;
        data_m[size_m] = '\0';
        return *this;
    }
}

// Author: Kostyantin Savorona
[[nodiscard]] char *my_str_t::c_str() const { return data_m; }

// Author: Kostyantin Savorona
my_str_t::~my_str_t() {
    delete[] data_m;
}

// Author: Kostyantin Savorona
std::ostream &operator<<(std::ostream &stream,const my_str_t &str) {
    stream << str.c_str();
    return stream;
}

// Author: Kostyantin Savorona
std::istream &operator>>(std::istream &stream, my_str_t &str) {
    str.clear();
    int ch = stream.get();
    while (std::isspace(ch)) {
        ch = stream.get();
    }
    while (!std::isspace(ch) && ch != EOF) {
        str.append((char) ch);
        ch = stream.get();
    }
    return stream;
}

// Author: Kostyantin Savorona
bool operator==(const my_str_t &str1, const my_str_t &str2) {
    if (str1.size() != str2.size()) { return false; }
    for (size_t i = 0; i < str1.size(); i++) {
        if (str1[i] != str2[i]) { return false; }
    }
    return true;
}

// Author: Kostyantin Savorona
bool operator!=(const my_str_t &str1, const my_str_t &str2) {
    return !(str1 == str2);
}

// Author: Kostyantin Savorona
bool operator>(const my_str_t &str1, const my_str_t &str2) {
    size_t min_size = (str1.size() < str2.size())? str1.size() : str2.size();
    for (size_t i = 0; i < min_size; i++) {
        if (str2[i] < str1[i]) { return true; }
        else if (str2[i] > str1[i]) { return false; }
    }
    return str1.size() > str2.size();
}

// Author: Kostyantin Savorona
bool operator>=(const my_str_t &str1, const my_str_t &str2) {
    return (str1 > str2 || str1 == str2);
}

// Author: Kostyantin Savorona
bool operator<(const my_str_t &str1, const my_str_t &str2) {
    return !(str1 >= str2);
}

// Author: Kostyantin Savorona
bool operator<=(const my_str_t &str1, const my_str_t &str2) {
    size_t min_size = (str1.size() < str2.size())? str1.size() : str2.size();
    for (size_t i = 0; i < min_size; i++) {
        if (str1[i] < str2[i]) { return true; }
        else if (str1[i] > str2[i]) { return false; }
    }
    return str1.size() <= str2.size();
}

// Author: Denis Humeniuk
bool operator==(const my_str_t &str1, const char* cstr2){
    if (str1.size() != std::strlen(cstr2))
        return false;
    for (size_t i = 0; i < str1.size(); ++i){
        if (str1[i] != cstr2[i])
            return false;
    }
    return true;
}

// Author: Denis Humeniuk
bool operator!=( const my_str_t &str1, const char * cstr2){
    return !(str1 == cstr2);
}

// Author: Denis Humeniuk
bool operator>(const my_str_t &str1, const char * cstr2 ){
    size_t min_size = (str1.size() < std::strlen(cstr2))? str1.size() : std::strlen(cstr2);
    for (size_t i = 0; i < min_size; ++i){
        if (str1[i] > cstr2[i])
            return true;
        else if (str1[i] < cstr2[i])
            return false;
    }
    return str1.size() > strlen(cstr2);
}

// Author: Denis Humeniuk
bool operator>=(const my_str_t &str1, const char * cstr2){
    return (str1 > cstr2) || (str1 == cstr2);
}

// Author: Denis Humeniuk
bool operator<( const my_str_t &str1, const char * cstr2){
    return !(str1 >= cstr2);
}

// Author: Denis Humeniuk
bool operator<=(const my_str_t &str1, const char * cstr2){
    return !(str1 > cstr2);
}

// Author: Denis Humeniuk
bool operator==(const char * cstr1, const my_str_t &str2){
    if (std::strlen(cstr1) != str2.size())
        return false;
    size_t str2_size = str2.size();
    for (size_t i = 0; i < str2_size; ++i){
        if (cstr1[i] != str2[i])
            return false;
    }
    return true;
}

// Author: Denis Humeniuk
bool operator!=( const char * cstr1, const my_str_t &str2){
    return !(cstr1 == str2);
}

// Author: Denis Humeniuk
bool operator>(const char * cstr1, const my_str_t &str2){
    size_t min_size = (std::strlen(cstr1) > str2.size()) ? str2.size() : std::strlen(cstr1);
    for (size_t i = 0; i < min_size; ++i){
        if (cstr1[i] > str2[i])
            return true;
        else if (cstr1[i] < str2[i]) { return false; }
    }
    return strlen(cstr1) > str2.size();
}

// Author: Denis Humeniuk
bool operator>=( const char * cstr1, const my_str_t &str2){
    return (cstr1 > str2) || (cstr1 == str2);
}

// Author: Denis Humeniuk
bool operator<( const char * cstr1, const my_str_t &str2){
    return !(cstr1 >= str2);
}

// Author: Denis Humeniuk
bool operator<=( const char * cstr1, const my_str_t &str2){
    return !(cstr1 > str2);
}

// Author: Denis Humeniuk
my_str_t operator+(const my_str_t &str1, const my_str_t &str2) {
    size_t new_size = str1.size_m + str2.size_m;
    char *new_data = new char[new_size+1];

    size_t i;
    for (i = 0; i < str1.size_m; ++i) {
        new_data[i] = str1.data_m[i];
    }
    for (size_t j = 0; j < str2.size_m; ++j) {
        new_data[i + j] = str2.data_m[j];
    }

    new_data[new_size] = '\0';
    my_str_t result(new_data);
    delete[] new_data;
    return result;
}

// Author: Denis Humeniuk
my_str_t operator*(const my_str_t &str1, const int number) {
    size_t new_size = str1.size_m * number;
    my_str_t result(new_size);
    for (size_t i = 0; i < new_size; i++) {
        result.data_m[i] = str1.data_m[i % str1.size_m];
    }
    result.data_m[new_size] = '\0';
    return result;
}

// Author: Denis Humeniuk
std::istream &readline (std::istream &stream, my_str_t &str){
    str.clear();
    char ch;
    while (stream.get(ch) && ch != '\n') {
        str.append(ch);
    }
    return stream;
}
