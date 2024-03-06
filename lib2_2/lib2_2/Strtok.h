#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char* mystrtok(char* str, const char* delim)
{
	static char* next;

	if (str)
	{
		next = str;
		while (*next && strchr(delim, *next))
			*next++ = '\0';
	}

	if (!*next)
		str = NULL;

	else
	{
		str = next;

		while (*next && !strchr(delim, *next))
			++next;

		while (*next && strchr(delim, *next))
			*next++ = '\0';
	}

	return str;
}
