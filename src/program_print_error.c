#include "philo.h"

// Converts error code to a string.
static	char const	*code2err(int err)
{
	if (err == 0)
		return ("No error.\n");
	else if (err == ENOMEM)
		return ("Out of memory.\n");
	return (NULL);
}

void	program_print_error(t_prog const *p)
{
	char const *const	str = code2err(p->err);

	if (str)
	{
		if (print_err("Error: ") && print_err(str))
			;
	}
	else
		print_err("Unknown error has occurred.\n");
}
