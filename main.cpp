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

#include "pollard.h"


//Compile options g++ *.cpp -o prg -std=gnu++11 -lgmpxx -lgmp
int main(int argc, const char * argv[]) {
    
    //TODO tidy if working
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time =
    std::chrono::high_resolution_clock::now();
    
    //TODO make into macro definition
    const bool debug = false; // DEBUG FLAG
    //const bool fileIn = true; // REDIRECT FILE TO STDIN
    
    gmp_randclass randoCalrissian(gmp_randinit_default);
    randoCalrissian.seed(mpz_class(time(NULL)));
    
    std::ifstream in;
    if (debug) {
        in = std::ifstream("../../../../testfiles/factortest.in");
        std::cin.rdbuf(in.rdbuf());
    }
    
    mpz_class N;
    
    // Set threshold to be the largest integer repsesented by BIT_CUTOFF bits.
    mpz_class threshold;
    mpz_ui_pow_ui(threshold.get_mpz_t(), 2, BIT_CUTOFF);
    
    char s[100];
    while (std::cin.getline(s,100)) {
        try {
            N = mpz_class(s);
        } catch (std::invalid_argument) {
            
        }
        
        if (mpz_probab_prime_p (N.get_mpz_t(), 15)) { // N is already prime //TODO unneccessary
            std::cout << N << std::endl;
        } else if (N > threshold) { // N is larger than BIT_CUTOFF
            std::cout << "fail" << std::endl;
        } else  {
            //TODO tidy if working
            std::chrono::time_point<std::chrono::high_resolution_clock> deadline =
            std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(TIME_CUTOFF);
            
            std::vector<mpz_class> *factors = new std::vector<mpz_class>();
            
            while (true) {
                try {
                    factors = pollardsrho(N, factors, randoCalrissian);
                    for (auto it = factors->begin(); it != factors->end(); ++it) {
                        std::cout << *it << std::endl;
                    }
                    break; // Break for success
                } catch (const char* msg) {
                    if (std::chrono::high_resolution_clock::now() > deadline) {
                        std::cout << msg << std::endl;
                        break; // Break for fail
                    } else {
                        // Try again
                    }
                }
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
