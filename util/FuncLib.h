/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncLib.h
 *
 * Created on June 29, 2021, 9:27 AM
 */

#ifndef UTIL_FUNCLIB_H_
#define UTIL_FUNCLIB_H_

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "util/MurmurHash2.h"
#include "util/MurmurHash2_64.h"

/*
 References:
 [1] https://cp-algorithms.com/std::string/std::string-hashing.html
 [2] http://www.cse.yorku.ca/~oz/hash.html
 [3] https://sites.google.com/site/murmurhash/
 */

int hash_simple(std::string& key, int size){
    int sum =0;
    for(int idx=0; idx < key.length(); idx++)
        sum += key[idx];
    return sum%size;
}

int hash_polynomial_rolling(std::string& key, int size){
    unsigned long long m = 1e9 + 9;
    const int p = 31;
    unsigned long long code = 0;
    unsigned long long base = 1;
    for (char c : key) {
        code = (code + (c - 'a' + 1) * base) % m;
        base = (base * p) % m;
    }
    return code % size;
}


int hash_djb2(std::string& key, int size){
    unsigned long code = 5381;
    for (char c : key) {
        code = ((code << 5) + code) + c; /* hash * 33 + c */
    }
    return code % size;
}
    
int hash_sdbm(std::string& key, int size){
    unsigned long code = 0;
    for (char c : key) {
        code = c + (code << 6) + (code << 16) - code;
    }
    return code % size;
}

int hash_murmur(std::string& key, int size){
    unsigned int code = MurmurHash2(key.c_str(), key.length(), 100);
    return code % size;
}
int hash_murmur64(std::string& key, int size){
    unsigned int code = MurmurHash64A(key.c_str(), key.length(), 100);
    return code % size;
}




#endif /* FUNCLIB_H */

