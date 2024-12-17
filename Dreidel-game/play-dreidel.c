# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <getopt.h>
# include <string.h>
# include "mtrand.h"
# include "dreidel.h"
# define SETTINGS "p:c:s:v"

char *players[] =
{
	"Aharon",
	"Batsheva",
	"Chanah",
	"David",
	"Ephraim",
	"Faige",
	"Gamaliel",
	"Hannah",
};
int player_count = 4, start_coins = 3;
uint64_t x = 613;
int opterr = 0;
int n_rounds;
int main(int argc, char **argv)
{
	int opt = 0;
	display = 0;
	while((opt = getopt(argc, argv, SETTINGS)) != -1)
	{
		switch(opt)
		{
			case 'p':
			{
				if(optarg != NULL && atoi(optarg) >= 2 && atoi(optarg) <= 8)
				{
					player_count = atoi(optarg);

				}
				else
				{
					exit(1);
				}
				break;
			}
			case 'c':
			{
				if(optarg != NULL && atoi(optarg) >= 1 && atoi(optarg) <= 20)
				{
					start_coins = atoi(optarg);
				}
				else
				{
					exit(1);
				}
				break;
			}
			case 's':
			{
				if(optarg != NULL && atoi(optarg) > 0 && strlen(optarg) <= 10)
				{
					x = atoi(optarg);
				}
				else
				{
					exit(1);
				}
				mtrand_seed(x);
				break;
			}
			case 'v':
			{
				display = 1;
				break;
			}
			case '?':
			{
				exit(1);
			}

		}
	}
	mtrand_seed(x);
	printf("%s %d %d %d %lu\n",players[play_game(player_count,start_coins, &n_rounds)],player_count,start_coins,n_rounds,x);
	return 0;
}
