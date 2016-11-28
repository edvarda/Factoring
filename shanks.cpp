//
//  dixon.cpp
//  Factoring
//
//  Created by Edvard Ahlsén on 20/11/16.
//  Copyright © 2016 Edvard Ahlsén. All rights reserved.
//

#include "shanks.h"

std::vector<mpz_class>* shanksFactorer(mpz_class &N, std::vector<mpz_class> *factors,
                                    gmp_randclass &randoCalrissian) {
	gmp_printf("---------------------------------- \n");

	mpz_class k = 1; //For now we just chose a k.
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
	gmp_printf("k * N: %Zd \n", tmp);
	mpz_sqrt(p0.get_mpz_t(), tmp.get_mpz_t());
	


	q0 = 1;
	mpz_pow_ui(tmp.get_mpz_t(), p0.get_mpz_t(), 2);
	q1 = k*N - tmp;




	//Init of first repeat step.
	pPrev = p0;
	qCurr = q1;
	qPrev = q0;
	gmp_printf("pPrev: %Zd \n", pPrev);


	bCurr = p0 + pPrev;
	gmp_printf("bi: %Zd \n", bCurr);
	bCurr = bCurr / qCurr;
	gmp_printf("bi: %Zd \n", bCurr);
	pCurr = bCurr * qCurr - pPrev;
	qNext = qPrev + bCurr * (pPrev-pCurr);

	perfectSquareCriterion =  mpz_perfect_square_p(qCurr.get_mpz_t());
	while(true){
		perfectSquareCriterion = 0; //Reset perfectSquareCriterion;
		gmp_printf("ANS------------------------------ \n");
		gmp_printf("pCurr: %Zd \n", pCurr);
		gmp_printf("qCurr: %Zd \n", qCurr);
		gmp_printf("qNext: %Zd \n", qNext);
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
			gmp_printf("perfectSquareCriterion and even iteration fullfilled \n");
			break;
		}
		iCounter++; //Todo check whilel criteria.
	}














	
	gmp_printf("Stage 2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
	gmp_printf("Stage 2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
	gmp_printf("Stage 2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");

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

	gmp_printf("ANS------------------------------ \n");
	gmp_printf ("p0f:  %.*Ff \n", numberOfDigits, p0f);
	gmp_printf ("q0f:  %.*Ff \n", numberOfDigits, q0f);
	gmp_printf ("q1f:  %.*Ff \n", numberOfDigits, q1f);


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



		gmp_printf("ANS------------------------------ \n");
		gmp_printf ("pPrevf:  %.*Ff \n", numberOfDigits, pPrevf);
		gmp_printf ("qCurrf:  %.*Ff \n", numberOfDigits, qCurrf);
		gmp_printf ("qNextf:  %.*Ff \n", numberOfDigits, qNextf);

		if(pCurrf == pPrevf){
			gmp_printf("criterion met! We should now have a gcd-able value in pCurrf \n");
			break;
		}

		pPrevf = pCurrf;
		qPrevf = qCurrf;
		qCurrf = qNextf;
	}
	mpz_class elementToTry(pCurrf);
	mpz_gcd (candidate.get_mpz_t(), N.get_mpz_t(), elementToTry.get_mpz_t());
	gmp_printf("candidate: %Zd \n", candidate);

	if(candidate != N && candidate != 1){
		//We have found a non trivial with factor! :D 
		N = N/candidate;
		factors->push_back(candidate);
        return factors;
	}



	gmp_printf("inb4 crash \n");
    return factors;
}




	/*
	mpf_t p0f, q0f, q1f, b0f, pCurrf, pPrevf, qNextf, qCurrf, qPrevf, qCurrSqrtf, bCurrf, bPrevf, tmpf;
	mpf_init(p0f);
	mpf_init(q0f);
	mpf_init(q1f); //The mpf_class is completely messed up so here we are...
	mpf_init(b0f);
	mpf_init(pCurrf);
	mpf_init(pPrevf);
	mpf_init(qNextf);
	mpf_init(qCurrf);
	mpf_init(qPrevf);
	mpf_init(qCurrSqrtf);
	mpf_init(bCurrf);
	mpf_init(bPrevf);
	mpf_init(tmpf);



	mpf_set_z(qCurrf, qCurr.get_mpz_t());
	mpf_set_z(p0f, p0.get_mpz_t());
	mpf_set_z(pPrevf, pPrev.get_mpz_t());
	gmp_printf ("fixed point qCurrf:  %.*Ff with %d digits\n", numberOfDigits, qCurrf, numberOfDigits);
	gmp_printf ("fixed point p0f:  %.*Ff with %d digits\n", numberOfDigits, p0f, numberOfDigits);
	gmp_printf ("fixed point pPrevf:  %.*Ff with %d digits\n", numberOfDigits, pPrevf, numberOfDigits);


	
	mpf_add (b0f, p0f, pPrevf); // b0f = p0f + pPrevf;
	mpf_class kalle(b0f);

	gmp_printf ("fixed point kalle:  %.*Ff with %d digits\n", numberOfDigits, kalle, numberOfDigits);
	gmp_printf ("fixed point b0f:  %.*Ff with %d digits\n", numberOfDigits, b0f, numberOfDigits);
	mpf_sqrt(qCurrSqrtf, qCurrf); // qCurrsqrtf = square root of qCurrf;
	mpf_div(b0f, b0f, qCurrSqrtf); // b0f = b0f / qCurrsqrtf
	//Truncate b0f;
	mpf_mul (p0f, b0f, qCurrSqrtf);
	*/




	/*
	mpf_set_z(miscMpf,qCurr.get_mpz_t());	 //Convert mpz to float
	mpf_sqrt(qCurrSqrt.get_mpf_t(), miscMpf); //Take sqrt of flaot
	gmp_printf ("fixed point qCurrSqrt:  %.*Ff with %d digits\n", numberOfDigits, qCurrSqrt, numberOfDigits);

	b0 = p0 - pPrev; //wrong?
	b0 = b0 / qCurrSqrt;
	gmp_printf("b0: %Zd \n", b0);

	p0 = b0 * qCurrSqrt;
	*/