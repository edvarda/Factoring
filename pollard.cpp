//
//  pollard.cpp
//  Factoring
//
//  Created by Edvard Ahlsén on 20/11/16.
//  Copyright © 2016 Edvard Ahlsén. All rights reserved.
//

#include "pollard.h"

// TODO låt pollard returnera så fort en faktor hittats. pss försvinner den tokiga rekursionen. Låt en yttre funktion kolla när N är primt.

//TODO gör mer semantiskt korrekt
mpz_class f(const mpz_class x_prev,const mpz_class &c, const mpz_class &N) {
    mpz_class x;
    mpz_powm (x.get_mpz_t(), x_prev.get_mpz_t(), mpz_class(2).get_mpz_t(), N.get_mpz_t());
    x = (x+1)%N;
    return x;
}

std::vector<mpz_class>* pollardsrho(mpz_class &N, std::vector<mpz_class> *factors,
                                    gmp_randclass &randoCalrissian) {
    
    if (mpz_probab_prime_p (N.get_mpz_t(), 15)) { // If N is prime
        factors->push_back(N);
        return factors;
    } else if (N < TRIAL_CUTOFF) { // If N is "small"
        return trialdivision(N, factors); // TODO Change return type to void
    }
    
    mpz_class x,y,c,p;
    
    x = randoCalrissian.get_z_range(N-1)+1; // Get random from [0,N)
    c = randoCalrissian.get_z_range(N-1)+1; // Get random from [1,N)
    y = x;
    while (true) {
        x = f(x,c,N);
        y = f(f(y,c,N),c,N);
        
        if (x == y) {
            break;
        }
        
        p = gcd(abs(x-y),N);
        if (p > 1) { // Found a factor p, so that p|N

            // Is factor p prime or not?
            if (mpz_probab_prime_p (p.get_mpz_t(), 15)) {
                factors->push_back(p);
            } else { //TODO Will this throwing a "fail" result in an error?
                     //Possible mismatch between N and factors
                mpz_class pnp(p); // Use pnp = p, so we still have a copy of p
                while (true) { // TODO subject this subroutine to a deadline?
                               // Feels unneccessary since p <= sqrt(N)
                    try {
                        factors = pollardsrho(pnp, factors, randoCalrissian);
                        break;
                    } catch (const char* msg) {
                        // Try again
                    }
                }
            }

            N /= p; // Divide N by p, since we made sure factors contain all prime factors of p
            break;
        }
        
    };

    //return pollardsrho(N,factors, randoCalrissian);
    throw "fail";
}

