//
//  main.cpp
//  Factoring
//
//  Created by Edvard Ahlsén on 18/11/16.
//  Copyright © 2016 Edvard Ahlsén. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <chrono>
#include <gmpxx.h>
#include <assert.h>

#include "constants.h"
#include "trialdivision.h"

int main(int argc, const char * argv[]) {
    
    //TODO tidy if working
    std::chrono::time_point<std::chrono::high_resolution_clock> deadline =
    std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(1900);
    
    //TODO tidy if working
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time =
    std::chrono::high_resolution_clock::now();
    
    //TODO make into macro definition
    const bool debug = false; // DEBUG FLAG
    const bool fileIn = false; // REDIRECT FILE TO STDIN
    
    std::ifstream in;
    if (fileIn) {
        in = std::ifstream("../../../../testfiles/factortest.in");
        std::cin.rdbuf(in.rdbuf());
    }
    
    mpz_class N;
    
    char s[100];
    while (std::cin.getline(s,100)) {
        try {
            N = mpz_class(s);
        } catch (std::invalid_argument) {
            
        }
        if (mpz_probab_prime_p (N.get_mpz_t(), 15)) {
            std::cout << N << std::endl;
        } else {
            try {
                std::vector<mpz_class> *factors = trialdivision(N);
                for (auto it = factors->begin(); it != factors->end(); ++it) {
                    std::cout << *it << std::endl;
                }
            } catch (const char* msg) {
                std::cout << msg << std::endl;
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
