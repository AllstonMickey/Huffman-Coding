# ifndef _STRCLONE_H
# define _STRCLONE_H

# include <stdint.h>
# include <stdlib.h>
# include <string.h>

/*
 * Copies a string's pointer to malloc'd memory.
 *
 * @param str String to copy
 * @return Pointer to the newly allocated memory.
 */
static inline char *strClone(const char *str)
{
	char *copy = malloc(strlen(str) + 1);
	for (uint32_t i = 0; i < strlen(str); i += 1)
	{
		*(copy + i) = *(str + i);
	}
	return copy;
}

# endif
