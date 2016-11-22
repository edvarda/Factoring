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
    
    // Declare, init and see a random generator. (Default is based on mersenne twister engine)
    gmp_randclass randoCalrissian(gmp_randinit_default);
    randoCalrissian.seed(mpz_class(time(NULL)));
    
    // This block makes it easier to run tests in Xcode
    std::ifstream in;
    if (debug) {
        in = std::ifstream("../../../../testfiles/factortest.in");
        std::cin.rdbuf(in.rdbuf());
    }
    
    mpz_class N; // Holds the number to be factored
    
    // Set threshold to be the largest integer repsesented by BIT_CUTOFF bits.
    mpz_class threshold;
    mpz_class preprocessing_limit = mpz_class(1000);
    mpz_ui_pow_ui(threshold.get_mpz_t(), 2, BIT_CUTOFF);
    
    char s[100]; // Input numbers are guaranteed to be at most 100 bits.
    while (std::cin.getline(s,100)) { // Read a number from input
        try {
            N = mpz_class(s); // Try to store it
        } catch (std::invalid_argument) {
            // This happens if number is too large or formatted incorrectly
        }
        
        if (mpz_probab_prime_p (N.get_mpz_t(), 15)) { // N is already prime
            std::cout << N << std::endl;
        } else if (N > threshold) { // We don't even try for numbers larger than this threshold
            std::cout << "fail" << std::endl;
        } else  {
            std::chrono::time_point<std::chrono::high_resolution_clock> deadline =
            std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(TIME_CUTOFF);
            std::vector<mpz_class> *factors = new std::vector<mpz_class>();
            
            while (true) {
                try {
                    factors = pollardsrho(N, factors, randoCalrissian);
                    for (auto it = factors->begin(); it != factors->end(); ++it) {
                        std::cout << *it << std::endl; // Print factors
                    }
                    break; // Break for success
                } catch (const char* msg) { // Catch fail messages
                    if (std::chrono::high_resolution_clock::now() > deadline) { // If passed deadline
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
