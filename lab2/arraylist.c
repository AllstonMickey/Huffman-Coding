# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <errno.h>

int main(void)
{
	uint32_t cap = 8; // max number of integers to store
	uint32_t len = 0; // current number of integers stored
	uint32_t *nums = (uint32_t *) calloc(cap, sizeof(uint32_t));
	if (nums == NULL)
	{
		printf("Calloc failure: {nums == NULL} [%d]\n", errno);
		return errno;
	}

	char action = 0;
	while (action != 'Q')
	{
		printf("Action? (Insert, Print, or Quit): ");
		scanf(" %c", &action);
		switch (action)
		{
			case 'I': // store an int in an array, reallocate double memory if needed
			{
				uint32_t num;
				printf("Enter an integer: ");
				scanf(" %u", &num);
				if (len == cap)
				{
					cap *= 2;
					uint32_t *temp = nums;
					temp = (uint32_t *) realloc(nums, cap * sizeof(uint32_t));
					if (temp == NULL)
					{
						printf("Realloc failure: {temp == NULL} [%d]\n", errno);
					}
					else
					{
						nums = temp;
					}
				}
				nums[len++] = num;
				break;
			}
			case 'P': // print the stored ints
			{
				printf("Length = %u:", len);
				if (len)
				{
					for (uint32_t i = 0; i < len; ++i)
					{
						printf(" %u", nums[i]);
					}
				}
				printf("\n");
				break;
			}
			case 'Q': // do nothing and break out --> stop asking for input
			{
				break;
			}
			default: // do nothing and break out --> ask for more input
			{
				break;
			}
		}
	}

	free(nums);
	nums = NULL;

	return 0;
}
