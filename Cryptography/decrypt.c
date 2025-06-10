# include <stdio.h>
# include <stdlib.h>
# include <gmp.h>
# include <unistd.h>
# include <getopt.h>
# include "rsa.h"
# define SETTINGS "i:o:n:vh"

int main(int argc, char **argv)
{
        int opt = 0, vo = 0;
	mpz_t n, d;
	mpz_inits(n, d, NULL);
	char *input = NULL;
	char *output = NULL;
	FILE *infile = NULL;
	FILE *outfile = NULL;
	FILE *pvfile = NULL;
	char *pfile = "rsa.priv";



        while((opt = getopt(argc, argv, SETTINGS)) != -1)
        {
                switch(opt)
                {
                        case 'i':
                        {
                                //input file to decrypt
                                //set here
				if (optarg != NULL)
				{
					input = optarg;
				}
				if (input != NULL && fopen(input, "r") == NULL)
				{
					printf("Error opening %s\n", input);
					exit(1);
				}
				if (input != NULL && fopen(input, "r") != NULL)
				{
					infile = fopen(input, "r");
				}
				else
				{
					infile = stdin;
				}
				
                                break;
                        }
                        case 'o':
                        {
                                //output file to decrypt
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
                                //file for private key
                                //rsa.priv is default
				if (optarg != NULL)
				{
					pfile = optarg;
				}
				if (pfile != NULL && fopen(pfile, "r") == NULL)
				{
					printf("Error opening %s\n", pfile);
					exit(1);
				}
				if (pfile != NULL && fopen(pfile, "r") != NULL)
				{
					pvfile = fopen(pfile, "r");
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
                                //program usage message
                                fprintf(stderr, "Usage: ./decrypt [options]\n");
                                fprintf(stderr, "%72s\n", "./decrypt decrypts an input file using the specified private key file,");
                                fprintf(stderr, "%50s\n", "writing the result to the specified output file.");
                                fprintf(stderr, "%15s %52s\n", "-i <infile>", ": Read input from <infile>. Default: standard input.");
                                fprintf(stderr, "%16s%51s\n", "-o <outfile>", ": Write output to <outfile>. Default: standard output.");
                                fprintf(stderr, "%16s%47s\n", "-n <keyfile>",": Private key is in <keyfile>. Default: rsa.priv.");
                                fprintf(stderr, "%6s %33s\n", "-v", ": Enable verbose output.");
                                fprintf(stderr, "%6s %46s\n", "-h", ": Display program synopsis and usage.");
				return(0);
                                break;
                        }
                }
        }
	if (fopen(pfile, "r") != NULL)
	{
		pvfile = fopen(pfile, "r");
	}
	if (output == NULL)
	{
		outfile = stdout;
	}
	if (input == NULL)
	{
		infile = stdin;
	}
        //read_private function
	rsa_read_priv(n, d, pvfile);
        //verbose message
	if (vo == 1)
	{
		//print verbose output
                gmp_printf("n - modulus (%d bits) : %Zd\n", mpz_sizeinbase(n, 2), n);
                gmp_printf("d  - private exponenet : (%d bits) : %Zd\n", mpz_sizeinbase(d, 2), d);
	}	
        //rsa_decrypt_file
	rsa_decrypt_file(infile, outfile, n, d);
        //close public key and clear made variables
	fclose(pvfile);
	fclose(infile);
	fclose(outfile);
	mpz_clears(n, d, NULL);
	return 0;
}

