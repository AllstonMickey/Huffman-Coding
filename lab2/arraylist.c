# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <errno.h>

int main(void)
{
	uint32_t cap = 1;
	uint32_t len = 0;
	uint32_t *nums = (uint32_t *) calloc(cap, sizeof(uint32_t));

	char action = 0;
	while (action != 'Q')
	{
		printf("Action? (Insert, Print, or Quit): ");
		scanf(" %c", &action);
		switch (action)
		{
			case 'I':
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
						printf("realloc error: {temp == NULL} [%d]\n", errno);
					}
					else
					{
						nums = temp;
					}
				}
				nums[len++] = num;
				break;
			}
			case 'P':
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
			case 'Q':
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}
	free(nums);
	return 0;
}
