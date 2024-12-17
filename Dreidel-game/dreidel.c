#include <stdio.h>
#include "mtrand.h"
#include "dreidel.h"

char *names_abc[] =
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
int display;

char spin_dreidel(void)
{
	char letters[4] = {'G','H','N','S'};
	uint64_t rnum = mtrand_rand64();
	uint64_t roll = (rnum % 4);
	switch (roll)
	{
		case 0:
			return letters[0];
			break;
		case 1:
			return letters[1];
			break;
		case 2:
			return letters[2];
			break;
		default:
			return letters[3];
	}
}

int play_game(int n_players, int coins_per_player, int *n_rounds)
{
	int sub;
	int coins[n_players];
	int standing[n_players];
	int winner = 0, pot = 0, players_left = n_players;
	char letter;

	*n_rounds = 1;
	for (int i = 0; i < n_players; i++)
	{
		coins[i] = coins_per_player;
		standing[i] = 1;
	}
	while (players_left > 1)
	{
		for (int j = 0; j < n_players; j++)
		{
			if (standing[j] == 1)
			{
				letter = spin_dreidel();
				switch (letter)
				{
					case 'G':
						coins[j] += pot;
						pot = 0;
						break;
					case 'H':
						sub = pot / 2;
						coins[j] += sub;
						pot -= sub;
						break;
					case 'N':
						break;
					default:
						if (coins[j] == 0)
						{
							standing[j] = 0;
							if (display == 1)
							{
								printf("%s%s%d%s%d%s\n",names_abc[j],": was eliminated in round ", *n_rounds," of a ", n_players, " player game.");

							}
							players_left = players_left - 1;
							if (players_left == 1)
							{
								for (int k = 0; k < n_players; k++)
								{
									if (standing[k] == 1)
									{
										winner = k;
										return winner;
									}
								}							
							}
							continue;
						}
						coins[j] = coins[j] - 1;
						pot = pot + 1;
				}
			}
		}
		*n_rounds += 1;
	}
	return winner;	
}




