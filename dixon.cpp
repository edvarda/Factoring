//
//  dixon.cpp
//  Factoring
//
//  Created by Edvard Ahlsén on 20/11/16.
//  Copyright © 2016 Edvard Ahlsén. All rights reserved.
//

#include "dixon.h"

std::vector<mpz_class>* dixonFactorer(mpz_class &N, std::vector<mpz_class> *factors,
                                    gmp_randclass &randoCalrissian) {

	//Choose a bound B.
	//Identify the factor base and call it P.
	//Search for positive integers z such that z^2 mod N is B-smooth.

    gmp_printf("in dixon.\n");
    gmp_printf("N: %Zd \n", N);

	mpz_class a,b,k;

	k = 20; //TODO: determinte what k should be.


	//1. Randomly select a in Zn.
	a = randoCalrissian.get_z_range(N); //TODO:Make it possibly negative as well
	gmp_printf("a: %Zd \n", a);




	//2. Let b = a^2 mod N.
	mpz_powm (b.get_mpz_t(), a.get_mpz_t(), mpz_class(2).get_mpz_t(), N.get_mpz_t());
	gmp_printf("b: %Zd \n", b);


	//3. Check if b is k-smooth.
	//A positive integer is called k-smooth if none of its prime factors is greater than k.
	



    return 0;
}















/*
// Lotsa crap just to get some random numbers ---
	mpz_t rand_Num;
    unsigned long int i, seed;
    gmp_randstate_t r_state;
    seed = time(NULL);
    gmp_randinit_default (r_state);
    gmp_randseed_ui(r_state, seed);
    mpz_init(rand_Num);
	mpz_urandomb(rand_Num,r_state, 14); //TODO: The number 14 should be N and the number rand_Num shuld also be negative sometimes.
	a = 12312312;
    gmp_printf("%Zd\n", rand_Num);*/