# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include "shell.h"
# include "bubble.h"
# include "stats.h"
# include "quick.h"
# include "set.h"
# include "heap.h"
# include <getopt.h>
# include <string.h>
# include <unistd.h>
# define OPTIONS "abhqsi:n:p:r:H"
# include "mtrand.h"
# include <inttypes.h>

void copy_sort(uint32_t *sort, uint32_t *copy, uint32_t length)
{
	for (uint32_t i = 0; i < length; i++)
	{
		copy[i] = sort[i];
	}
}

int main(int argc, char **argv)
{
	Stats stats;
	Set tracker = set_empty();

	enum Sorts
	{
		Bubble,
		Heap,
		Quick,
		Shell
	};

	uint32_t seed = 13371453;
	uint32_t length = 100;
	int opt = 0;
	uint32_t print_length = 100;
	int print_opt = 0;
        while((opt = getopt(argc, argv, OPTIONS)) != -1)
        {
                switch(opt)
                {
                        case 'a':
			{
				tracker = set_insert(tracker, Shell);
				tracker = set_insert(tracker, Bubble);
				tracker = set_insert(tracker, Quick);
				tracker = set_insert(tracker, Heap);
                                break;
                        }
			case 'b':
			{
				tracker = set_insert(tracker, Bubble);
				break;
			}
			case 'h':
			{
				tracker = set_insert(tracker, Heap);
				break;
			}
			case 'q':
			{
				tracker = set_insert(tracker, Quick);
				break;
			}
			case 's':
			{
				tracker = set_insert(tracker, Shell);
				break;
			}
			case 'r':
			{
				if (optarg != NULL && atoi(optarg) > 0)
				{
					seed = atoi(optarg);
				}
				else
				{
					exit(1);
				}
				break;
			}
			case 'n':
			{
				if (optarg != NULL && atoi(optarg) >= 1 && atoi(optarg) <= 250000000)
				{
					length = atoi(optarg);
				}
				else
				{
					exit(1);
				}
				break;
			}
			case 'p':
			{
				if (optarg != NULL && atoi(optarg) >= 0)
				{
					print_length = atoi(optarg);
					print_opt = 1;
				}
				break;
			}
			case 'H':
			{
				printf("SYNOPSIS");
				printf("\n%55s\n","A collection of comparison-based sorting algorithms.");
				printf("\n");
				printf("USAGE");
				printf("\n%58s\n","./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]");
				printf("\n");
				printf("OPTIONS");
				printf("\n%5s %44s","-H","Display program help and usage.");
                                printf("\n%5s %30s","-a","Enable all sorts.");
                                printf("\n%5s %32s","-b","Enable Bubble Sort.");
                                printf("\n%5s %30s","-h","Enable Heap Sort.");
                                printf("\n%5s %31s","-q","Enable Quick Sort.");
                                printf("\n%5s %31s","-s","Enable Shell Sort.");
                                printf("\n%12s %54s","-n length","Specify number of array elements (default: 100).");
                                printf("\n%14s %55s","-p elements","Specify number of elements to print (default: 100).");
                                printf("\n%10s %48s\n","-r seed","Specify random seed (default: 13371453).");
				exit(0);
				break;
			}
			default:
			{
                                printf("SYNOPSIS");
                                printf("\n%55s\n","A collection of comparison-based sorting algorithms.");
                                printf("\n");
                                printf("USAGE");
                                printf("\n%58s\n","./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]");
                                printf("\n");
                                printf("OPTIONS");
                                printf("\n%5s %44s","-H","Display program help and usage.");
                                printf("\n%5s %30s","-a","Enable all sorts.");
                                printf("\n%5s %32s","-b","Enable Bubble Sort.");
                                printf("\n%5s %30s","-h","Enable Heap Sort.");
                                printf("\n%5s %31s","-q","Enable Quick Sort.");
                                printf("\n%5s %31s","-s","Enable Shell Sort.");
                                printf("\n%12s %54s","-n length","Specify number of array elements (default: 100).");
                                printf("\n%14s %55s","-p elements","Specify number of elements to print (default: 100).");
                                printf("\n%10s %48s\n","-r seed","Specify random seed (default: 13371453).");
				exit(1);
				break;
			}
		}
	}
        uint32_t* sort = (uint32_t*) malloc(sizeof(uint32_t)*length);
	mtrand_seed(seed);
	for (uint32_t i = 0; i < length; i++)
	{
		sort[i] = (mtrand_rand64() & 0x3FFFFFFF);
	}
	if (print_opt == 0)
	{
		print_length = length;
	}
	if (print_length > length)
	{
		print_length = length;
	}
	for (int j = 0; j < 4; j++)
	{
		if (set_member(tracker, j))
		{
			switch (j)
			{
				case 0:
				{
        				uint32_t* copy = (uint32_t*) malloc(sizeof(uint32_t)*length);
					copy_sort(sort, copy, length);
					bubble_sort(&stats, copy, length);
					printf("%s%d%s%lu%s%lu%s","Bubble Sort, ",length," elements, ", stats.moves," moves, ", stats.compares," compares");
        				for (uint32_t i = 0; i < print_length; i++)
       				{	
                				if (i % 5 == 0)
						{
							printf("\n%13" PRIu32, copy[i]);
						}
						else
						{	
							printf("%13" PRIu32, copy[i]);
						}
        				}
					printf("\n");
					reset(&stats);
					free(copy);
					break;
				}
				case 1:
				{
                                        uint32_t* copy = (uint32_t*) malloc(sizeof(uint32_t)*length);
                                        copy_sort(sort, copy, length);
					heap_sort(&stats, copy, length);
                                        printf("%s%d%s%lu%s%lu%s","Heap Sort, ",length," elements, ", stats.moves," moves, ", stats.compares," compares");					
        				for (uint32_t i = 0; i < print_length; i++)
        				{
						if (i % 5 == 0)
						{
							printf("\n%13" PRIu32, copy[i]);
						}
						else
						{
	               					printf("%13" PRIu32, copy[i]);
						}
	       				}
					printf("\n");
					reset(&stats);		
					free(copy);		
					break;
				}
				case 2:
				{
                                        uint32_t* copy = (uint32_t*) malloc(sizeof(uint32_t)*length);
                                        copy_sort(sort, copy, length);
					quick_sort(&stats, copy, length);
                                        printf("%s%d%s%lu%s%lu%s","Quick Sort, ",length," elements, ", stats.moves," moves, ", stats.compares," compares");
        				for (uint32_t i = 0; i < print_length; i++)
        				{	
						if (i % 5 == 0)
						{
							printf("\n%13" PRIu32, copy[i]);
						}			
						else
						{
                					printf("%13" PRIu32, copy[i]);
        					}
					}
					printf("\n");
					reset(&stats);
					free(copy);				
					break;
				}
				case 3:
				{
                                        uint32_t* copy = (uint32_t*) malloc(sizeof(uint32_t)*length);
                                        copy_sort(sort, copy, length);
					shell_sort(&stats, copy, length);
                                        printf("%s%d%s%lu%s%lu%s","Shell Sort, ",length," elements, ", stats.moves," moves, ", stats.compares," compares");
        				for (uint32_t i = 0; i < print_length; i++)
        				{
						if (i % 5 == 0)
						{
							printf("\n%13" PRIu32, copy[i]);
						}	
						else
						{
              					printf("%13" PRIu32, copy[i]);
						}
					}
					printf("\n");
					reset(&stats);
					free(copy);
					break;
				}

			}
		}
	}
	free(sort);
	return 0;
}
