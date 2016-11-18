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

int main(int argc, const char * argv[]) {
    
    //TODO tidy if working
    std::chrono::time_point<std::chrono::high_resolution_clock> deadline =
    std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(1900);
    
    //TODO tidy if working
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time =
    std::chrono::high_resolution_clock::now();
    
    //TODO make into macro definition
    const bool debug = false; // DEBUG FLAG
    const bool fileIn = true; // REDIRECT FILE TO STDIN
    
    std::ifstream in;
    if (fileIn) {
        in = std::ifstream("../../../../testfiles/factortest.in");
        std::cin.rdbuf(in.rdbuf());
    }
    
    mpz_t N;
    int flag;
    mpz_init(N);
    mpz_set_ui(N,0);
    
    char s[100];
    while (std::cin.getline(s,100)) {
        flag = mpz_set_str(N,s, 10);
        assert (flag == 0); /* If flag is not 0 then the operation failed */
        std::cout << N << std::endl;
    }
    
    std::cout << "Hello, Worldz! " << PI[2] << "\n";
    
    
    
    return 0;
}
