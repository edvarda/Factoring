//
//  shanks.cpp
//  Factoring
//
//  Created by Edvard Ahlsén on 20/11/16.
//  Copyright © 2016 Edvard Ahlsén. All rights reserved.
//

#include "shanks.h"

std::vector<mpz_class>* shanksFactorer(mpz_class &N, std::vector<mpz_class> *factors,
                                    gmp_randclass &randoCalrissian) {

	
	for(int param = 1 ; param < 5 ; param++){
		mpz_class k = param; //For now we just chose a k.
		mpz_class perfectSquareCriterion = 0;
		//Initialize p0, q0, q1 to the things they should be.
		mpz_class candidate, p0, q0, q1, b0, pCurr, pPrev, qNext, qCurr, qPrev, bCurr, bPrev, tmp, iCounter;
		mpf_class qCurrSqrt;

		mpz_t miscMpz;
		mpz_init(miscMpz);
		mpf_t miscMpf;
		mpf_init(miscMpf);
		int numberOfDigits = 7;

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
			if(perfectSquareCriterion != 0 && (iCounter%2) == 0){
				//gmp_printf("perfectSquareCriterion and even iteration fullfilled \n");
				break;
			}
			iCounter++; //Todo check whilel criteria.
		}

		//Yaaaaaaaaaaay we found a perfect square on an even iteration! Now initiate phace two!
		mpf_class p0f(p0), q0f(q0), q1f(q1), b0f(b0), pCurrf(pCurr), pPrevf(pPrev), 
		qNextf(qNext), qCurrf(qCurr), qPrevf(qPrev), bCurrf(bCurr), bPrevf(bPrev), 
		qCurrSqrtf, tmpf;



		//Initializing stuff for second loop.
		b0f = p0f - pPrevf; //Prolly wrong.
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
		//while(true){
		for(int i = 0 ; i < 4 ; i++) {
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
		mpz_class elementToTry(pCurrf);
		mpz_gcd (candidate.get_mpz_t(), N.get_mpz_t(), elementToTry.get_mpz_t());
		//gmp_printf("candidate: %Zd \n", candidate);

		if(candidate != N && candidate != 1){
			//We have found a non trivial with factor! :D 
			N = N/candidate;
			trialdivision(candidate, factors);
			break;

			//gmp_printf("returning------------------------------ \n");
		}



		//gmp_printf("inb4 crash \n");
	}
    return trialdivision(N, factors);
}