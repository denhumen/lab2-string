//
// Created by mail0 on 19.09.2023.
//

#ifndef STR_PROJECT_MYSTRING_HPP
#define STR_PROJECT_MYSTRING_HPP

/**
 * @file my_str_t.h
 * @author Denis Humeniuk
 * @author Kostya Savorona
 * @date 2023-09-21
 * @brief This file contains the custom string class defenition.
 */

#pragma once

#include <iostream>
#include <cstring>

/**
 * @class my_str_t
 * @brief A custom string class implementation.
 *
 * This class provides a set of functions to manage, modify, and query strings.
 */
class my_str_t {

private:
    char *data_m; ///< String data.
    size_t capacity_m; ///< Capacity allocated for the string. It is always bigger than current size.
    size_t size_m; ///< Current size of the string.

public:
    /**
     * @brief Calculates the next devided by 16 value according to input size argument.
     * @param x The input size.
     * @return The next devided by 16 value.
     */
    static size_t increase_to_divided_by_16(size_t x);

    /**
     * @brief Constructs string with given size and initial char.
     * @param size_t The input size.
     * @param char Initial char to construct string with.
     */
    explicit my_str_t(size_t size, char initial='a');

    /**
     * @brief Constructs string with given C-string.
     * @param cstr Pointer to C-string.
     */
    explicit my_str_t(const char* cstr);

    /**
     * @brief Constructs string with given std:string.
     * @param std::string std::string.
     */
    explicit my_str_t(const std::string &str);

    /**
     * @brief Constructs string with given my_str_t object.
     * @param my_str_t my_str_t object.
     */
    my_str_t(const my_str_t &my_str_t);

    /**
     * @brief Constructs string with given my_str_t object by moving all data from there.
     * @param my_str_t my_str_t object.
     */
    my_str_t(my_str_t &&str) noexcept;

    /**
     * @brief Assignment operator that moves all data from given my_str_t object.
     * @param my_str_t my_str_t object.
     */
    my_str_t &operator=(my_str_t &&str) noexcept;

    /**
     * @brief Operator for getting the char by given index.
     * @param size_t Input index.
     */
    char& operator[](size_t idx);

    /**
     * @brief Operator for getting the char by given index.
     * @param size_t Input index.
     */
    const char& operator[](size_t idx) const;

    /**
     * @brief Assignment operator that gets all data from given my_str_t object.
     * @param my_str_t my_str_t object.
     */
    my_str_t& operator=(const my_str_t &mystr);

    /**
     * @brief Swaps data between two my_str_t objects.
     * @param my_str_t my_str_t object.
     */
    void swap(my_str_t &other);

    /**
     * @brief Gives ability to get the char on the specific position.
     * @param size_t Input index.
     * @throws std::out_of_range In the case when input index is not in the range of string length.
     */
    char &at(size_t idx);

    /**
     * @brief Gives read-only ability to get the char on the specific position.
     * @param size_t Input index.
     * @throws std::out_of_range In the case when input index is not in the range of string length.
     */
    [[nodiscard]] const char &at(size_t idx) const;

    /**
     * @brief Changes capacity of the string according to input new capacity.
     * @param size_t New capacity.
     */
    void reserve(size_t new_capacity);

    /**
     * @brief Changes capacity of the string by one.
     */
    void shrink_to_fit();

    /**
     * @brief Resizes string object to input size using input character.
     * @param size_t New capacity.
     * @param char New char to fill string with.
     */
    void resize(size_t new_size, char new_char = ' ');

    /**
     * @brief Clears string object.
     */
    void clear();

    /**
     * @brief Inserts my_str_t object according to input index and input my_str_t object.
     * @param size_t Input index.
     * @param my_str_t Input my_str_t object.
     */
    void insert(size_t idx, const my_str_t &str);

    /**
     * @brief Inserts character according to input index.
     * @param size_t Input index.
     * @param char Input character.
     */
    void insert(size_t idx, char c);

    /**
     * @brief Inserts C-string according to input index.
     * @param size_t Input index.
     * @param cstr Input C-string.
     */
    void insert(size_t idx, const char* cstr);

    /**
     * @brief Appends my_str_t object in the end of the current according to input my_str_t object.
     * @param my_str_t Input my_str_t object.
     */
    void append(const my_str_t &str);

    /**
     * @brief Appends character to the end of the string.
     * @param char Input character.
     */
    void append(char c);

    /**
     * @brief Inserts C-string to the end of the string.
     * @param cstr Input C-string.
     */
    void append(const char* cstr);

    /**
     * @brief Deletes characters by input size to delete and index to start from.
     * @param size_t Start index.
     * @param size_t Size to delete from the string.
     */
    void erase(size_t begin, size_t size);

    /**
     * @brief Returns size of the string.
     * @return Size.
     */
    [[nodiscard]] size_t size() const noexcept;

    /**
     * @brief Returns capacity of the string.
     * @return Capacity.
     */
    [[nodiscard]] size_t capacity() const noexcept;

    static constexpr size_t not_found = -1;

    /**
     * @brief Finds character in the string.
     * @param char Character to find.
     * @param size_t Start index.
     * @return Index of found element. If element was not found - returns -1.
     */
    size_t find(char c, size_t idx = 0);

    /**
     * @brief Finds input std::string in the string.
     * @param std::string String to found to find.
     * @param size_t Start index.
     * @return Start index of found string. If string was not found returns -1.
     */
    size_t find(const std::string &str, size_t idx = 0);

    /**
     * @brief Finds input C-string  in the string.
     * @param cstr C-string to found to find.
     * @param size_t Start index.
     * @return Start index of found C-string . If C-string  was not found returns -1.
     */
    size_t find(const char* cstr, size_t idx = 0);

    /**
     * @brief Returns substring of string starting from certain index.
     * @param size_t Start index.
     * @param size_t Size of substring to return.
     * @return Substring as my_str_t object
     */
    my_str_t substr(size_t begin, size_t size);


    my_str_t& operator+=(const my_str_t &str);


    my_str_t& operator*=(int number);

    /**
     * @brief Returns C-string that represents current string.
     * @return C-string that represents string
     */
    [[nodiscard]] char *c_str() const;

    /**
     * @brief Destructor for the my_str_t class. Frees allocated memory.
     */
    ~my_str_t();


    friend std::ostream& operator<<(std::ostream &stream,const my_str_t &str);


    friend std::istream& operator>>(std::istream &stream, my_str_t &str);


    friend bool operator==(const my_str_t &str1, const my_str_t &str2);


    friend bool operator!=(const my_str_t &str1, const my_str_t &str2);


    friend bool operator>(const my_str_t &str1, const my_str_t &str2);


    friend bool operator>=(const my_str_t &str1, const my_str_t &str2);


    friend bool operator<(const my_str_t &str1, const my_str_t &str2);


    friend bool operator<=(const my_str_t &str1, const my_str_t &str2);


    friend my_str_t operator+(const my_str_t &str1, const my_str_t &str2);


    friend my_str_t operator*(const my_str_t &str1, int number);
};


bool operator==(const my_str_t &str1, const char* cstr2);


bool operator!=(const my_str_t &str1, const char* cstr2);


bool operator>(const my_str_t &str1, const char* cstr2);


bool operator>=(const my_str_t &str1, const char* cstr2);


bool operator<(const my_str_t &str1, const char* cstr2);


bool operator<=(const my_str_t &str1, const char* cstr2);


bool operator==(const char* cstr1, const my_str_t &str2);


bool operator!=(const char* cstr1, const my_str_t &str2);


bool operator>(const char* cstr1, const my_str_t &str2);


bool operator>=(const char* cstr1, const my_str_t &str2);


bool operator<(const char* cstr1, const my_str_t &str2);


bool operator<=(const char* cstr1, const my_str_t &str2);

/**
 * @brief Reads stream and writes all data to input my_str_t object.
 * @param std::istream Stream to read from.
 * @param my_str_t Object to write to.
 * @return Stream
 */
std::istream &readline (std::istream &stream, my_str_t &str);


my_str_t operator+(const my_str_t &str1, const my_str_t &str2);

#endif //STR_PROJECT_MYSTRING_HPP
