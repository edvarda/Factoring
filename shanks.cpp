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
	mpz_class p0, q0, q1, b0, pCurr, pPrev, qNext, qCurr, qPrev, bCurr, bPrev, tmp, iCounter;
	mpf_class tmpFloat, tmpFloat2;
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
	gmp_printf("Stage 2 \n");
	//Yaaaaaaaaaaay we found a perfect square on an even iteration! Now initiate phace two!
	b0 = p0 - pPrev; //wrong?
	mpf_set_z(tmpFloat.get_mpf_t(), qCurr.get_mpz_t());
	gmp_printf("qCurr: %Zd \n", qCurr);
	gmp_printf("tmpFloat: %F \n", tmpFloat);
	mpf_sqrt(tmpFloat2.get_mpf_t(), tmpFloat.get_mpf_t());
	gmp_printf("tmpFloat2: %F \n", tmpFloat2);

	b0 = b0 / qCurr;
	
	gmp_printf("inb4 crash \n");
    return 0;
}

