//
//  shanks.cpp
//  Factoring
//
//  Created by Edvard Ahlsén on 20/11/16.
//  Copyright © 2016 Edvard Ahlsén. All rights reserved.
//

#include "shanks.h"
#include "pollard.h"



// This function factors a number "N" into factors "factors".
//The functions requires a starting time for the entire process and a gmp random generator class so that it can pass it through to other functions if need be. 
std::vector<mpz_class>* shanksFactorer(mpz_class &N, std::vector<mpz_class> *factors,
                                       std::chrono::time_point<std::chrono::high_resolution_clock> started,
                                       gmp_randclass &randoCalrissian) {
    

    //We try all parameters k from 1 to the number specified in the loop.
	for(int param = 1 ; param < 5 ; param++){

	    std::chrono::time_point<std::chrono::high_resolution_clock> deadline =
        started + std::chrono::milliseconds(10000);

	    if(std::chrono::high_resolution_clock::now() > deadline){
            throw "fail";
            break;
        }

		mpz_class k = param; //We choose a k.
		mpz_class perfectSquareCriterion = 0; //Just a criterion checking if we are done with the first loop.
		//int numberOfDigits = 7; //For debug print purposes.


		//Initialize p0, q0, q1 to the things they should be.
		mpz_class candidate, p0, q0, q1, b0, pCurr, pPrev, qNext, qCurr, qPrev, bCurr, bPrev, tmp, iCounter;

		tmp = k * N;
		mpz_sqrt(p0.get_mpz_t(), tmp.get_mpz_t());
		
		q0 = 1;
		mpz_pow_ui(tmp.get_mpz_t(), p0.get_mpz_t(), 2);
		q1 = k * N - tmp;



		//Init of first repeat step.
		pPrev = p0;
		qCurr = q1;
		qPrev = q0;
		bCurr = p0 + pPrev;
		if(qCurr == 0){ //There are sitation when q1 turn out to be 0 and we must then stop the algorithm and try another multiplier k.
			break;
		}
		bCurr = bCurr / qCurr;
		pCurr = bCurr * qCurr - pPrev;
		qNext = qPrev + bCurr * (pPrev-pCurr);
		perfectSquareCriterion =  mpz_perfect_square_p(qCurr.get_mpz_t());
		while(true){
			perfectSquareCriterion = 0; //Reset perfectSquareCriterion;
			//Set forward indexs.
			pPrev = pCurr;
			qPrev = qCurr;
			qCurr = qNext;
			
			//Do calculations
			bCurr = p0 + pPrev;		
			bCurr = bCurr / qCurr;
			pCurr = bCurr * qCurr;
			pCurr = pCurr - pPrev;
			qNext = qPrev + bCurr * (pPrev-pCurr);

			
			perfectSquareCriterion =  mpz_perfect_square_p(qCurr.get_mpz_t());
			if(perfectSquareCriterion != 0 && (iCounter%2) == 0){ //We break if qCurr is a perfect square and we are on an even i.
				break;
			}
			iCounter++;
		}


		//Yaaaaaaaaaaay we found a perfect square on an even iteration! Now initiate phace two!
		mpf_class p0f(p0), q0f(q0), q1f(q1), b0f(b0), pCurrf(pCurr), pPrevf(pPrev), 
		qNextf(qNext), qCurrf(qCurr), qPrevf(qPrev), bCurrf(bCurr), bPrevf(bPrev), 
		qCurrSqrtf, tmpf; //Since we have now have to deal with floats, we switch from mpz to mpf to be able to handle floats.



		//Initializing variables for second loop.
		b0f = p0f - pPrevf;
		mpf_sqrt(qCurrSqrtf.get_mpf_t(), qCurrf.get_mpf_t());
		b0f /= qCurrSqrtf;
		b0f = floor(b0f);

		p0f = b0f * qCurrSqrtf + pPrevf;

		q0f = qCurrSqrtf;

		mpf_pow_ui (tmpf.get_mpf_t(), p0f.get_mpf_t(), 2);
		q1f = (k * N - tmpf) / q0f;


		pPrevf = p0f;
		qPrevf = q0f;
		qCurrf = q1f;

		//Second loop.
		while(true){
			bCurrf = (p0f + pPrevf) / qCurrf;
			bCurrf = floor(bCurrf);

			pCurrf = bCurrf * qCurrf - pPrevf;

			qNextf = qPrevf + bCurrf * (pPrevf - pCurrf);

			if(pCurrf == pPrevf){
				break;
			}

			pPrevf = pCurrf;
			qPrevf = qCurrf;
			qCurrf = qNextf;
		}
		mpz_class elementToTry(pCurrf); //Converting element.
		mpz_gcd (candidate.get_mpz_t(), N.get_mpz_t(), elementToTry.get_mpz_t()); //Runs gcd on N and elementToTry, puts the answer in candidate.
		//gmp_printf("candidate: %Zd \n", candidate);


		//Here we check if candidate is a non-trivial factor.
		if(candidate != N && candidate != 1){
            ////
            if (mpz_probab_prime_p (candidate.get_mpz_t(), 15)) {
                factors->push_back(candidate);
            } else { //TODO Will this throwing a "fail" result in an error?
                //Possible mismatch between N and factors
                mpz_class non_prime_factor(candidate); // Use pnp = p, so we still have a copy of p
                while (true) { // TODO subject this subroutine to a deadline?
                    // Feels unneccessary since p <= sqrt(N)
                    try {
                        //factors = pollardsrho(pnp, factors, randoCalrissian);
                        factors = pollardsrho(non_prime_factor, factors, randoCalrissian);
                        break;
                    } catch (const char* msg) {
                        // Just try again
                    }
                }
            }
            
            N /= candidate; // Divide N by p, since we made sure factors contain all prime factors of p

            /////
            
//			//We have found a non trivial with factor! :D 
//			N = N/candidate;
//            
//			trialdivisionShanks(candidate, factors, started);
//			break;
//
			//gmp_printf("returning------------------------------ \n");
		}
		//gmp_printf("inb4 crash \n");
	}
    return pollardsrho(N, factors, started);
}
//Difficult input 23632234, 12321.
