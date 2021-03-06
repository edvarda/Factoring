//
//  trialdivision.cpp
//  Factoring
//
//  Created by Edvard Ahlsén on 18/11/16.
//  Copyright © 2016 Edvard Ahlsén. All rights reserved.
//


#include "trialdivision.h"

std::vector<mpz_class>* trialdivision(mpz_class &N, std::vector<mpz_class> *factors) {
    // TODO use: void mpz_nextprime (mpz_t rop, const mpz_t op)

    for (auto p : PI) {
        if (mpz_probab_prime_p (N.get_mpz_t(), 15) || p > sqrt(N)) { break; }
        while(N % p == 0) {
            factors->push_back(mpz_class(p));
            N /= p;
        }
    }
    if (N > 1) {
        if (mpz_probab_prime_p (N.get_mpz_t(), 15)) {
            factors->push_back(N);
        } else {
            throw "fail";
        }
    }
    return factors;
}

std::vector<mpz_class>* trialdivisionShanks(mpz_class &N, std::vector<mpz_class> *factors, std::chrono::time_point<std::chrono::high_resolution_clock> started) {
    // TODO use: void mpz_nextprime (mpz_t rop, const mpz_t op)

    std::chrono::time_point<std::chrono::high_resolution_clock> deadline =
            started + std::chrono::milliseconds(10000);

    if(std::chrono::high_resolution_clock::now() > deadline){
            throw "fail";
        }
    for (auto p : PI) {
        if (mpz_probab_prime_p (N.get_mpz_t(), 15) || p > sqrt(N)) { break; }
        while(N % p == 0) {
            factors->push_back(mpz_class(p));
            N /= p;
        }
    }
    if (N > 1) {
        if (mpz_probab_prime_p (N.get_mpz_t(), 15)) {
            factors->push_back(N);
        } else {
            throw "fail";
        }
    }
    return factors;
}

std::vector<mpz_class>* trialdivision(mpz_class &N, mpz_class &limit, std::vector<mpz_class> *factors) {
    // TODO use: void mpz_nextprime (mpz_t rop, const mpz_t op)
    for (auto p : PI) {
        if (p > limit || mpz_probab_prime_p (N.get_mpz_t(), 15)) { break; }
        while(N % p == 0) {
            factors->push_back(mpz_class(p));
            N /= p;
        }
    }
    if (N > 1) {
        if (mpz_probab_prime_p (N.get_mpz_t(), 15)) {
            factors->push_back(N);
        } else {
            throw "fail";
        }
    }
    
    return factors;
}
