//
//  dixon.h
//  Factoring
//
//  Created by Edvard Ahlsén on 20/11/16.
//  Copyright © 2016 Edvard Ahlsén. All rights reserved.
//

#ifndef shanks_h
#define shanks_h

#include <iostream>
#include <vector>
#include <gmpxx.h>
#include <time.h>
#include "constants.h"
#include "trialdivision.h"

std::vector<mpz_class>* shanksFactorer(mpz_class &N, std::vector<mpz_class> *factors,
                                    gmp_randclass &randoCalrissian);

#endif /* shanks_h */