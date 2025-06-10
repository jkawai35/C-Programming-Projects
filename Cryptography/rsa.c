# include <stdlib.h>
# include <stdio.h>
# include <gmp.h>
# include <stdbool.h>
# include "numtheory.h"
# include "randstate.h"

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters)
{
	uint64_t pb, qb;
	mpz_t pgcd, qgcd, maingcd, lambda, check, lambdan;
	mpz_inits(pgcd, qgcd, maingcd, lambda, check, lambdan, NULL);

        pb = (nbits / 4) + (random() % (3 * nbits / 4 - nbits / 4 + 1)); 
        qb = nbits - pb;
	make_prime(p, pb, iters);
	make_prime(q, qb, iters);

	mpz_sub_ui(pgcd, p, 1);
	mpz_sub_ui(qgcd, q, 1);
	mpz_mul(lambdan, qgcd, pgcd);
	mpz_abs(lambdan, lambdan);

	mpz_mul(n, p, q);
	gcd(maingcd, pgcd, qgcd);
	mpz_fdiv_q(lambda, lambdan, maingcd);
	gcd(check, e, lambda);
	while (mpz_cmp_ui(check, 1) != 0)
	{
		mpz_urandomb(e, state, nbits);
		gcd(check, e, lambda);
	}	
	mpz_clears(pgcd, qgcd, maingcd, lambda, check, lambdan, NULL);
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile)
{
	//check how to do this
	gmp_fprintf(pbfile, "%Zx\n", n);
	gmp_fprintf(pbfile, "%Zx\n", e);
	gmp_fprintf(pbfile, "%Zx\n", s);
	fprintf(pbfile, "%s", username);
}


void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile)
{
	//read n, e, s, then username
	//read username
	gmp_fscanf(pbfile, "%Zx", n);
	gmp_fscanf(pbfile, "%Zx", e);
	gmp_fscanf(pbfile, "%Zx", s);
	fscanf(pbfile, "%s", username);


}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q)
{
	//create prime numbers for p and q
	//find inverse of e mod lambda (pq)/gcd(p,q)
	mpz_t t, lambda, g, pgcd, qgcd;
	mpz_inits(t, lambda, g, pgcd, qgcd, NULL);
	mpz_sub_ui(pgcd, p, 1);
	mpz_sub_ui(qgcd, q, 1);
	mpz_mul(t, pgcd, qgcd);
	gcd(g, pgcd, qgcd);
	mpz_fdiv_q(lambda, t, g); 
	mod_inverse(d, e, lambda);
	mpz_clears(t, lambda, g, pgcd, qgcd, NULL);
}


void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile)
{
	//write to file n, then d
        gmp_fprintf(pvfile, "%Zx\n", n);
        gmp_fprintf(pvfile, "%Zx\n", d);
	
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile)
{
	gmp_fscanf(pvfile, "%Zx\n", n);
	gmp_fscanf(pvfile, "%Zx\n", d);
}


void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n)
{
	//find m^e mod n
	//store result in c
	pow_mod(c, m, e, n);
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e)
{
	//create blocks
	//write to outfile in blocksi
	uint64_t k;
	size_t bitsr;
	mpz_t m, c;
	mpz_inits(m, c, NULL);
	k = (mpz_sizeinbase(n, 2) - 1) / 8;
	uint8_t *block = (uint8_t*)malloc(k * sizeof(uint8_t));
	block[0] = 0xFF;

	while ((bitsr = fread(&block[1], sizeof(uint8_t), k - 1, infile)) > 0)
	{
		mpz_import(m, bitsr + 1, 1, sizeof(uint8_t), 1, 0, block);
		rsa_encrypt(c, m, e, n);
		gmp_fprintf(outfile, "%Zx\n", c);
	}
	free(block);
	mpz_clears(m, c, NULL);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n)
{
	//find c^d mod n
	//store result in m
	pow_mod(m, c, d, n);
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d)
{
        uint64_t k;
	size_t j;
        mpz_t m, c;
        mpz_inits(m, c, NULL);
 	k = (mpz_sizeinbase(n, 2) - 1) / 8;
        uint8_t *block = (uint8_t*)malloc(k * sizeof(uint8_t));
	block[0] = 0xFF;

        while (gmp_fscanf(infile, "%Zx\n", c) != EOF)
        {
		rsa_decrypt(m, c, d, n);
		mpz_export(block, &j, 1, sizeof(uint8_t), 1, 0, m);
		fwrite(&block[1], sizeof(uint8_t), j - 1, outfile);	
        }
        free(block);
	mpz_clears(c, m, NULL);
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n)
{
	//find m^d mod n
	//store value in s
	pow_mod(s, m, d, n);
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n)
{
	//find s^e mod n
	//return true only if s^e mod n is equal to m
	mpz_t t;
	mpz_init(t);
	pow_mod(t, s, e, n);
	if (mpz_cmp(m, t) == 0)
	{
		mpz_clear(t);
		return true;
	}
	mpz_clears(t, NULL);
	return false;
}

