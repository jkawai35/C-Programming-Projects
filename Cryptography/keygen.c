# include <stdlib.h>
# include <stdio.h>
# include <gmp.h>
# include <stdint.h>
# include <getopt.h>
# include "rsa.h"
# include "randstate.h"
# include "numtheory.h"
# include <time.h>
# include <sys/stat.h>
# define SETTINGS "b:i:n:d:s:vh"

int main(int argc, char **argv)
{
	int opt = 0, vo = 0;
	mpz_t n, e, s, d, p, q, username;
	mpz_inits(n, e, s, d, q, p, username, NULL);
	uint64_t iters = 50, seed = time(NULL), bits = 1024;
	char *public = "rsa.pub";
	char *private = "rsa.priv";
	FILE *pv = NULL;
	FILE *pb = NULL;
	

	while((opt = getopt(argc, argv, SETTINGS)) != -1)
	{
		switch(opt)
		{
			case 'b':
			{
				if(optarg != NULL && atoi(optarg) >= 50 && atoi(optarg) <= 4096)
				{
					bits = atoi(optarg);
				}
				if(optarg != NULL && atoi(optarg) <= 0)
				{
					exit(1);
				}
				break;
			}
			case 'i':
			{
				if(optarg != NULL && atoi(optarg) >= 1 && atoi(optarg) <= 500)
				{
					iters = atoi(optarg);
				}
				if(optarg != NULL && atoi(optarg) <= 0)
				{
					exit(1);
				}
				break;
			}
			case 'n':
			{
				//pbfile
				if(optarg != NULL)
				{
					public = optarg;
				}
				break;
			}
			case 'd':
			{
				//pvfile
				if(optarg != NULL)
				{
					private = optarg;
				}
				break;
			}
			case 's':
			{
				if(optarg != NULL && atoi(optarg) > 0)
				{
					seed = atoi(optarg);
				}
				if(optarg != NULL && atoi(optarg) <= 0)
				{
					exit(1);
				}
				break;
			}
			case 'v':
			{
				//verbose output
				vo = 1;
				break;
			}
			case 'h':
			{
				//print program usage
				fprintf(stderr, "Usage: ./keygen [options]\n");
				fprintf(stderr, "%94s\n", "./keygen generates a public / private key pair, placing the keys into the public and private");
				fprintf(stderr, "%88s\n", "key files as specified below. The keys have a modulus (n) whose length is specified in");
				fprintf(stderr, "%22s\n", "the program options.");
				fprintf(stderr, "%13s %57s\n", "-s <seed>", ": Use <seed> as the random number seed. Default: time()");
				fprintf(stderr, "%13s %66s\n", "-b <bits>", ": Public modulus n must have at least <bits> bits. Default: 1024");
				fprintf(stderr, "%14s %73s\n", "-i <iters>",": Run <iters> Miller-Rabin iterations for primality testing. Default: 50");
				fprintf(stderr, "%15s %46s\n", "-n <pbfile>", ": Public key file is <pbfile>. Default: rsa.pub");
				fprintf(stderr, "%15s %10s\n", "-d <pvfile>", ": Private key file is <pvfile>. Default: rsa.priv");
				fprintf(stderr, "%6s %33s\n", "-v", ": Enable verbose output.");
				fprintf(stderr, "%6s %46s\n", "-h", ": Display program synopsis and usage.");
				mpz_clears(n, e, s, d, p, q, username, NULL);	
				exit(0);
				break;
			}
			default:
			{
				exit(1);
			}

		}
	}
	pb = fopen(public, "w");
	pv = fopen(private, "w");
	uint64_t fd = fileno(pv);
	fchmod(fd, S_IRUSR | S_IWUSR);
	randstate_init(seed);
	rsa_make_pub(p, q, n, e, bits, iters);
	rsa_make_priv(d, e, p, q);
	char *uname = getenv("USER");
	mpz_set_str(username, uname, 62);
	rsa_sign(s, username, d, n);
	rsa_write_pub(n, e, s, uname, pb);
	rsa_write_priv(n, d, pv);
	if (vo == 1)
	{
                gmp_printf("username: %s\n", uname);
                gmp_printf("user signature (%d bits) : %Zd\n", mpz_sizeinbase(s, 2), s);
                gmp_printf("p (%d bits) : %Zd\n", mpz_sizeinbase(p, 2), p);
                gmp_printf("q (%d bits) : %Zd\n", mpz_sizeinbase(q, 2), q);
                gmp_printf("n - modulus (%d bits) : %Zd\n", mpz_sizeinbase(n, 2), n);
                gmp_printf("e - public exponenet (%d bits) : %Zd\n", mpz_sizeinbase(e, 2), e);
                gmp_printf("d - private exponenet (%d bits) : %Zd\n", mpz_sizeinbase(d, 2), d);
	}
	randstate_clear();
	mpz_clears(n, e, s, d, p, q, username, NULL);
	fclose(pb);
	fclose(pv);
	return 0;
}
