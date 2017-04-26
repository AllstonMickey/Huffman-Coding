# include <stdio.h>
# include <stdint.h>

int main(void)
{
	uint32_t maxLength = 8;
	uint32_t currentLength = 0;
	uint32_t *array = (uint32_t *) calloc(maxLength, sizeof(uint32_t));

	char action = NULL;
	while (action != 'Q')
	{
		printf("Action? (Insert, Print, or Quit): ");
		scanf(" %c", &action);
		switch (action)
		{
			case 'I':
			{
				// append number to array
				break;
			}		
			case 'P':
			{
				// print array contents in format "Length = k: x1 x2 x3 ... xn"
				break;
			}
			case 'Q':
			{
				break;
			}
			default:
			{
				// errno
				break;
			}
		}
	}
	return 0;
}
