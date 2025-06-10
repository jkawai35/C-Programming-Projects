# include <stdlib.h>
# include <stdio.h>
# include <gmp.h>
# include <unistd.h>
# include "rsa.h"
# define SETTINGS "i:o:n:vh"

int main(int argc, char **argv)
{
        int opt = 0, vo = 0;
	mpz_t n, e, s;
	mpz_inits(n, e, s, NULL);
	char *input = NULL;
	char *output = NULL;
	FILE *pbfile = NULL;
	FILE *infile = NULL;
	FILE *outfile = NULL;
	char *pkey = "rsa.pub";
	
	char *vars = (char *)malloc(128 * sizeof(char));
        mpz_t username;
        mpz_init(username);

        while((opt = getopt(argc, argv, SETTINGS)) != -1)
        {
                switch(opt)
                {
                        case 'i':
                        {
                                //input file to encrypt
				//set here
				if (optarg != NULL)
				{
					input = optarg;
				}
				if (input != NULL && fopen(input, "r") == NULL)
				{
					printf("Error opening %s \n ", input);
					exit(1);
				}
				if (input != NULL && fopen(input, "r") != NULL)
				{
					infile = fopen(input, "r");
				}

                                break;
                        }
			case 'o':
			{
				//output file to encrypt
				//set here
				if (optarg != NULL)
				{
					output = optarg;
				}
				if (output != NULL && fopen(output, "w") == NULL)
				{
					printf("Error opening %s\n", output);
					exit(1);
				}
				if (output != NULL && fopen(output, "w") != NULL)
				{
					outfile = fopen(output, "w");
				}

				break;
			}
			case 'n':
			{
				//file for public key
				//rsa.pub is default
				if (optarg != NULL)
				{
					pkey = optarg;
				}
				if (pkey != NULL & fopen(pkey, "r") == NULL)
				{
					printf("Error opening %s\n", pkey);
					exit(1);
				}
			}
			case 'v':
			{
				//verbose output
				vo = 1;
				break;
			}
			case 'h':
			{
				//program usage message
                                fprintf(stderr, "Usage: ./encrypt [options]\n");
                                fprintf(stderr, "%71s\n", "./encrypt encrypts an input file using the specified public key file,");
                                fprintf(stderr, "%50s\n", "writing the result to the specified output file.");
                                fprintf(stderr, "%15s %52s\n", "-i <infile>", ": Read input from <infile>. Default: standard input.");
                                fprintf(stderr, "%16s%51s\n", "-o <outfile>", ": Write output to <outfile>. Default: standard output.");
				fprintf(stderr, "%16s%47s\n", "-n <keyfile>",": Public key is in <keyfile>. Default: rsa.pub.");
				fprintf(stderr, "%6s %33s\n", "-v", ": Enable verbose output.");
                                fprintf(stderr, "%6s %46s\n", "-h", ": Display program synopsis and usage.");
                                return 0;
				break;
			}
		}
	}
	if (input == NULL)
	{
		infile = stdin;
	}
	if (output == NULL)
	{
		outfile = stdout;
	}
	if (fopen(pkey, "r") != NULL)
	{
		pbfile = fopen(pkey, "r");
	}
        rsa_read_pub(n, e, s, vars, pbfile);
	//verbose message
	if (vo == 1)
	{
        	gmp_printf("username: %s\n", vars);
        	gmp_printf("user signature (%d bits) : %Zd\n", mpz_sizeinbase(s, 2), s);
        	gmp_printf("n - modulus (%d bits) : %Zd\n", mpz_sizeinbase(n, 2), n);
        	gmp_printf("e - public exponent (%d bits) : %Zd\n", mpz_sizeinbase(e, 2), e);
	}
	//convert username to mpz_t set string
	mpz_set_str(username, vars, 62);
	//rsa_verify
	if (rsa_verify(username, s, e, n) == false)
	{
		printf("Error, username was not verifiedi\n");
	        mpz_clears(n, e, s, username, NULL);
		exit(1);
	
	}
	rsa_encrypt_file(infile, outfile, n, e);
	mpz_clears(n, e, s, username, NULL);
	fclose(infile);
	fclose(outfile);
	fclose(pbfile);
	free(vars);
	vars = NULL;
	return 0;
}
