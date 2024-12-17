# include <stdio.h>
# include <stdint.h>
# include "stats.h"
# include "shell.h"

uint32_t temp;
uint32_t gap(uint32_t n)
{
	if (n == 1)
	{
		return 0;
	}
	if (n > 2)
	{
		return ((5 * n) / 11);
	}
	else
	{
		return 1;
	}
	
}
void shell_sort(Stats *stats, uint32_t *arr, uint32_t n_elements)
{
	uint32_t j;
	for (uint32_t ngap = gap(n_elements); ngap > 0; ngap = gap(ngap))
	{
		for (uint32_t i = ngap; i < n_elements; i++)
		{
			j = i;
			temp = move(stats,arr[i]);
			while ((j >= ngap) && cmp(stats,temp, arr[j - ngap]) == -1)
			{
				arr[j] = move(stats,arr[j]);
				arr[j] = move(stats,arr[j - ngap]);
				j -= ngap;
			}
			arr[j] = move(stats, arr[j]);
			arr[j] = temp;
		}
	}
}

