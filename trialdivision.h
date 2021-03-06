//
//  trialdivision.h
//  Factoring
//
//  Created by Edvard Ahlsén on 18/11/16.
//  Copyright © 2016 Edvard Ahlsén. All rights reserved.
//

#ifndef trialdivision_h
#define trialdivision_h

#include <vector>
#include <stdio.h>
#include <gmpxx.h>
#include <time.h>
#include <chrono>


#include "constants.h"

std::vector<mpz_class>* trialdivision(mpz_class &N, std::vector<mpz_class> *factors);
std::vector<mpz_class>* trialdivisionShanks(mpz_class &N, std::vector<mpz_class> *factors, std::chrono::time_point<std::chrono::high_resolution_clock> started);
std::vector<mpz_class>* trialdivision(mpz_class &N, mpz_class &limit, std::vector<mpz_class> *factors);

#endif /* trialdivision_h */

