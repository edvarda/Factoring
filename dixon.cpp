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
	//Choosing a bound B
	mpz_class B;
	B = 7;
	//Get the factorbase P which is all primes smaller than B
	std::vector<mpz_class> P = {2, 3, 5, 7};

	int numberOFRelations = P.size()+1;
	std::vector<mpz_class> *allZ = new std::vector<mpz_class>(numberOFRelations); //Vector to gather all the z's
	std::vector<mpz_class> *allPZ = new std::vector<mpz_class>(numberOFRelations); //Vector to gather all the p(z)'s
	std::vector<std::vector<mpz_class> > vMatrix(P.size(), std::vector<mpz_class>(numberOFRelations)); //Matrix for gauss elemination

	//Next, we search for positive integers z such that z^2 mod N is B-smooth.
	for(int pairs = 0 ; pairs < numberOFRelations ;){
		gmp_printf("---------------------------------- \n");
		mpz_class z, pz, pzTemp;
		z = randoCalrissian.get_z_range(N); //Random a number z
		mpz_powm (pz.get_mpz_t(), z.get_mpz_t(), mpz_class(2).get_mpz_t(), N.get_mpz_t());


		std::vector<mpz_class> *factorsOfPZ = new std::vector<mpz_class>();
		pzTemp = pz;
		factorsOfPZ = trialdivision(pzTemp, factorsOfPZ); //There is faster way to check it is B-smooth than to factorize the entire number.
		mpz_class biggestFactorInPZ = 1;

		//Next we check how big the biggest factor in pz is.
		for (auto it = factorsOfPZ->begin(); it != factorsOfPZ->end(); ++it) {
			if (*it > biggestFactorInPZ){
				biggestFactorInPZ = *it;
			}
	        std::cout <<"pz factor: " << *it << std::endl; // Print factors
	    }
	    gmp_printf("biggest factor in PZ: %Zd \n", biggestFactorInPZ);

	    //We add exponents of all the factors in the factorbase to the matrix.
	    if(biggestFactorInPZ <= B && biggestFactorInPZ != 1){
	    	gmp_printf("pz is B-smooth!!! \n");
	    	allZ->push_back(z);
	    	allPZ->push_back(pz);
	    	
	    	biggestFactorInPZ = 0;

	    	gmp_printf("incrementing the matrix \n");

	    	//Cases which whould have been expanded to a dynamic form if it would have worked.
	    	for (auto it = factorsOfPZ->begin(); it != factorsOfPZ->end(); ++it) {
				if (*it == 2){
	    			vMatrix[0][pairs]++;
				}
				else if (*it == 3){
	    			vMatrix[1][pairs]++;
				}
				else if (*it == 5){
	    			vMatrix[2][pairs]++;
				}
				else if (*it == 7){
	    			vMatrix[3][pairs]++;
				}
		    }

			for(int i = 0 ; i < P.size() ; i++){
				for(int j = 0 ; j < numberOFRelations ; j++){
					gmp_printf("%Zd; " , vMatrix[i][j]);
				}
				gmp_printf("\n");
			}
		    pairs++;
	    }







	}

		gmp_printf("The exponent Matrix \n");
		for(int i = 0 ; i < vMatrix.size() ; i++){
			for(int j = 0 ; j < vMatrix[0].size() ; j++){
				gmp_printf("%Zd; " , vMatrix[i][j]);
			}
			gmp_printf("\n");
		}
		gmp_printf("Now in mod 2 \n");
		for(int i = 0 ; i < vMatrix.size() ; i++){
			for(int j = 0 ; j < vMatrix[0].size() ; j++){
				vMatrix[i][j] = vMatrix[i][j] %2;
				gmp_printf("%Zd; " , vMatrix[i][j]);
			}
			gmp_printf("\n");
		}


		
		int rowGaussIndex = -1;
		std::vector<int> usedRow (vMatrix.size());





		//In this messy section we choose a row which has a 1 in the first column. Thereafter we gauss away all other rows which has a 1 in that column.
		//We repeat this process for each columns.



	    for(int i = 0 ; i < vMatrix.size() ; i++){
	    	for(int j = 0 ; j < vMatrix.size() ; j++){
		    	if(vMatrix[j][i] == 1 && usedRow[j] == 0){
		    		rowGaussIndex = j;
		    		usedRow[rowGaussIndex] = 1;
		    		break;
		    	}
		    }

		    if(rowGaussIndex != -1){
		    	//We now have a row with a 1 in the position we currently want to gauss away.
		    	for(int j = 0 ; j < vMatrix.size() ; j++){
		    		if(vMatrix[j][i] == 1){ // If it is a 1 in a column we want to gauus away.
		    			if(j != rowGaussIndex){ // We do not gauss a row from itself
		    				for(int k = 0 ; k < vMatrix[0].size() ; k++ ){ 
		    					if(vMatrix[rowGaussIndex][k] == 1){ //We check if the row we are using as gausser has a 1 in the right place.
			    						if(vMatrix[j][k] == 0) { 
				    					vMatrix[j][k] = 1;
				    				} else {
				    					vMatrix[j][k] = 0;
				    				}
		    					}
			    			}
		    			}
		    			
		    		}
		    	}
		    }

		    gmp_printf("round: %d \n", i);
			for(int i2 = 0 ; i2 < vMatrix.size() ; i2++){
				for(int j2 = 0 ; j2 < vMatrix[0].size() ; j2++){
					vMatrix[i2][j2] = vMatrix[i2][j2] %2;
					gmp_printf("%Zd; " , vMatrix[i2][j2]);
				}
				gmp_printf("\n");
			}
		    rowGaussIndex = -1;
	    }


	    gmp_printf("Now hopefully Gaussed \n");
		for(int i = 0 ; i < vMatrix.size() ; i++){
			for(int j = 0 ; j < vMatrix[0].size() ; j++){
				vMatrix[i][j] = vMatrix[i][j] %2;
				gmp_printf("%Zd; " , vMatrix[i][j]);
			}
			gmp_printf("\n");
		}

	    gmp_printf("All z's \n");
	 	for (auto it = allZ->begin(); it != allZ->end(); ++it) {
	        std::cout << *it << std::endl; // Print factors
	    }
	 	gmp_printf("All pz's \n");
	    for (auto it = allPZ->begin(); it != allPZ->end(); ++it) {
	        std::cout << *it << std::endl; // Print factors
	    }


	    //Now we have a gaussed matrix..

	    //Discontinued algorith.

	   

    return 0;
}



/*
//Choose a bound B.
	//Identify the factor base and call it P.
	//Search for positive integers z such that z^2 mod N is B-smooth.

    gmp_printf("in dixon.\n");
    gmp_printf("N: %Zd \n", N);

	mpz_class a,b,bTemp,bBiggestFact,k;

	k = 20; //TODO: determinte what k should be.
	bBiggestFact = 1; //Scrap value;
	int t = 20; //The number of (a,b) pairs we want to collect
	std::vector<mpz_class> *allA = new std::vector<mpz_class>(t+1);
	std::vector<mpz_class> *allB = new std::vector<mpz_class>(t+1);


	for(int i = 0 ; i < t ;){
		gmp_printf("Trying again to find a pair!----------------------- \n", a);
		//1. Randomly select a in Zn.
		a = randoCalrissian.get_z_range(N); //TODO:Make it possibly negative as well
		gmp_printf("a: %Zd \n", a);




		//2. Let b = a^2 mod N.
		mpz_powm (b.get_mpz_t(), a.get_mpz_t(), mpz_class(2).get_mpz_t(), N.get_mpz_t());
		gmp_printf("b: %Zd \n", b);
		bTemp = b;

		//3. Check if b is k-smooth.
		//A positive integer is called k-smooth if none of its prime factors is greater than k.
		std::vector<mpz_class> *factorsOfB = new std::vector<mpz_class>();
		factorsOfB = trialdivision(bTemp, factorsOfB); //Make sure this results in the desired result when b is a prime.
		for (auto it = factorsOfB->begin(); it != factorsOfB->end(); ++it) {
			if (*it > bBiggestFact){
				bBiggestFact = *it;
			}
	        std::cout << *it << std::endl; // Print factors
	    }
	    gmp_printf("biggest factor in b: %Zd \n", bBiggestFact);

	    if(bBiggestFact < k){
	    	gmp_printf("b is k-smooth!!! \n");
	    	gmp_printf("saving the pair (a,b) which is (%Zd,%Zd) \n", a, b);
	    	allA->push_back(a);
	    	allB->push_back(b);
	    	i++;
	    }
	    bBiggestFact = 0;
	    //4. If YES, let b = the product of all p^alpha^i  where{p1, ..., pt} is the set of primes ≤ k.
 	}






 	gmp_printf("All a's \n");
 	for (auto it = allA->begin(); it != allA->end(); ++it) {
        std::cout << *it << std::endl; // Print factors
    }
 	gmp_printf("All b's \n");
    for (auto it = allB->begin(); it != allB->end(); ++it) {
        std::cout << *it << std::endl; // Print factors
    }
    */




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