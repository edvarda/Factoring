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


#include "constants.h"

std::vector<mpz_class>* trialdivision(mpz_class &N, std::vector<mpz_class> *factors);

#endif /* trialdivision_h */

