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
        if (p > sqrt(N)) { break; }
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
