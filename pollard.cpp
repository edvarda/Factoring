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
    
//    while (N % 2 != 1 && !mpz_probab_prime_p (N.get_mpz_t(), 15) ) {
//        N = N/2;
//        factors->push_back(mpz_class(2));
//    }

    mpz_class x,y,c,p;
    
    x = randoCalrissian.get_z_range(N-1)+1; // Get random from [0,N)
    c = randoCalrissian.get_z_range(N-1)+1; // Get random from [1,N)
    y = x;
//    std::cerr << "Top level N: " << N.get_mpz_t() << std::endl;
//    std::cerr << "c: " << c.get_mpz_t() << std::endl;
    while (true) {
        x = f(x,c,N);
        y = f(f(y,c,N),c,N);
        
//        std::cerr << "x: " << x.get_mpz_t() << std::endl;
//        std::cerr << "y: " << y.get_mpz_t() << std::endl;
        
        if (x == y) {
            break;
        }
        
        p = gcd(abs(x-y),N);
        //std::cerr << "P: " << p.get_mpz_t() << std::endl;
        if (p > 1) { // Found a factor p, so that p|N

            if (mpz_probab_prime_p (p.get_mpz_t(), 15)) {
                factors->push_back(p);
                //std::cerr << "Found prime factor: " << p.get_mpz_t() << std::endl;
            } else { //TODO Will this throwing a "fail" result in an error?
                     //Possible mismatch between N and factors
                
                //std::cerr << "Found non-prime factor: " << p.get_mpz_t() << std::endl;
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
            // Divide N by p, since we made sure factors contain all prime factors of p
            N = N/p;
            
            //std::cerr << "New N: " << N.get_mpz_t() << std::endl;
            
            //TODO kolla om p delar N mer än en gång
            //return pollardsrho(N,factors,randoCalrissian); // Found a factor, make recursive call
//            if (mpz_probab_prime_p (N.get_mpz_t(), 15)) {
//                factors->push_back(N);
////                std::cerr << "Final factor: " << N.get_mpz_t() << std::endl;
////                std::cerr << "---------------------------" << std::endl;
//                return factors;
//            }
//            
//            x = randoCalrissian.get_z_range(N-1)+1; // Get random from [2,N)
//            c = randoCalrissian.get_z_range(N-1)+1; // Get random from [1,N)
//            y = f(x,c,N);
            break;
        }
        
    };

    return pollardsrho(N,factors, randoCalrissian);
    //throw "fail";
}

