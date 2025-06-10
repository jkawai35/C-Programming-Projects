# include <stdlib.h>
# include <stdio.h>
# include <gmp.h>
# include <stdbool.h>
# include "randstate.h"
# include "numtheory.h"

void gcd(mpz_t d, mpz_t a, mpz_t b)
{
	//set variable copies
	mpz_t acopy, bcopy;
	mpz_inits(acopy, bcopy, NULL);
	mpz_set(acopy, a);
	mpz_set(bcopy, b);

	while(mpz_cmp_ui(bcopy, 0) != 0)
	{
		mpz_set(d, bcopy);
		mpz_mod(bcopy, acopy, bcopy);
		mpz_set(acopy,d);
	}
	mpz_set(d, acopy);
	mpz_clears(acopy, bcopy, NULL);
	return;
}

void mod_inverse(mpz_t o, mpz_t a, mpz_t n)
{
	//make var copies and vars needed for calculation
	mpz_t r, rp, t, q, diff, prod, temp, temp2;
	mpz_inits(r, rp, t, q, diff, prod, temp, temp2, NULL);
	mpz_set(r, n);
	mpz_set(rp, a);
	mpz_set_ui(o, 0);
	mpz_set_ui(t, 1);
	
	while (mpz_cmp_ui(rp, 0) != 0)
	{
		mpz_fdiv_q(q, r, rp);
		mpz_mul(prod, rp, q);
		mpz_set(temp, r);
		mpz_set(r, rp);
		mpz_sub(rp, temp, prod);
		mpz_mul(prod, q, t);
		mpz_set(temp2, t);
		mpz_sub(t, o, prod);
		mpz_set(o, temp2);
	}
	if (mpz_cmp_ui(r, 1) > 0)
	{
		mpz_set_ui(o, 0);
		mpz_clears(r, rp, t, q, diff, prod, temp, temp2, NULL);
		return;
	}
	if (mpz_cmp_ui(o, 0) < 0)
	{
		mpz_add(o, o, n);
	}
	mpz_clears(r, rp, t, q, diff, prod, temp, temp2, NULL);
	return;
}

void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n)
{
	//make var copies
	mpz_t acopy, dcopy;
	mpz_inits(acopy, dcopy, NULL);
	mpz_set(acopy, a);
	mpz_set(dcopy, d);
	mpz_set_ui(o, 1);

	while (mpz_cmp_ui(dcopy, 0) > 0)
	{
		if (mpz_odd_p(dcopy) != 0)
		{
			mpz_mul(o, o, acopy);
			mpz_mod(o, o, n);
		}
        	mpz_mul(acopy, acopy, acopy);
        	mpz_mod(acopy, acopy, n);
        	mpz_fdiv_q_ui(dcopy, dcopy, 2);
	}
	mpz_clears(acopy, dcopy, NULL);
	return;
}

bool is_prime(mpz_t n, uint64_t iters)
{
	uint64_t mathn;
	mathn = mpz_get_ui(n);
	mpz_t s, r, test, nb, y, nm, j;
	mpz_inits(s, r, test, nb, y, nm, j, NULL);
	mpz_sub_ui(nb, n, 3); //n-3
	mpz_sub_ui(nm, n, 1); //n-1
	uint64_t st = 0;
	
	//find s and r
	mathn = mathn - 1;
	uint64_t nmod = mathn % 2;
	while(nmod == 0)
	{
		st++;
		mathn /= 2;
		nmod = mathn % 2;
	}
	mpz_set_ui(s, st);
	mpz_sub_ui(s, s, 1);
	mpz_set_ui(r, mathn);
	//miller rabin test
	for (uint32_t i = 1; i < iters; i++)
	{
		mpz_urandomm(test, state, nb);
		mpz_add_ui(test, test, 2);
		pow_mod(y, test, r, n);
		if (mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, nm) != 0) // nm is n - 1
		{
			mpz_set_ui(j, 1);
			while (mpz_cmp(j, s) <= 0 && mpz_cmp(y, nm) != 0) //s is s - 1
			{
				mpz_mul(y, y, y);
				mpz_mod(y, y, n);
				if (mpz_cmp_ui(y, 1) == 0)
				{
					mpz_clears(s, r, test, nb, y, nm, j, NULL);
					return false;
				}
				mpz_add_ui(j, j, 1);
			}
			if (mpz_cmp(y, nm) != 0)
			{
				mpz_clears(s, r, test, nb, y, nm, j, NULL);
				return false;
			}	
		}
	}
	mpz_clears(s, r, test, nb, y, nm, j, NULL);
	return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters)
{
	//make random number, make odd if even
	mpz_urandomb(p, state, bits);
	if (mpz_even_p(p) != 0)
	{
		mpz_add_ui(p, p , 1);
	}
	while (is_prime(p, iters) == false)
	{
		mpz_urandomb(p, state, bits);
		if (mpz_even_p(p) != 0)
		{
			mpz_add_ui(p, p, 1);
		}
	}
	return;
}



