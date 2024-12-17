# include <stdio.h>
# include "shell.h"
# include "quick.h"
# include "stats.h"

void quick_sort(Stats *stats, uint32_t *arr, uint32_t n_elements)
{
	if (n_elements < 8)
	{
		shell_sort(stats,arr,n_elements);
		return;
	}

	uint32_t left = 0;
	uint32_t last = 0;
	swap(stats,&arr[0],&arr[(n_elements / 2)]);
	for (uint32_t i = 1; i < n_elements; i++)
	{
		if (cmp(stats, arr[i], arr[left]) == -1)
		{
			last++;
			swap(stats,&arr[last],&arr[i]);
		}
	}
	swap(stats,&arr[left],&arr[last]);
	quick_sort(stats, arr, last);
	quick_sort(stats, arr + (last + 1), n_elements - (last + 1));
}	
