# ifndef _STRCLONE_H
# define _STRCLONE_H

# include <stdint.h>
# include <stdlib.h>

/*
 * Copies a string's pointer to malloc'd memory.
 *
 * @param str String to copy
 * @return Pointer to the newly allocated memory.
 */
static inline char *strclone(const char *str)
{
	uint32_t len = 0;
	while (*(str + len) != '\0')
	{
		len += 1;
	}
	
	char *tmp = malloc((sizeof(uint8_t) * len) + 1);
	char *clone = tmp;
	while ((*tmp++ = *str++));
	return clone;
}

# endif
