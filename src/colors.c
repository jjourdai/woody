#include <string.h>
#include <stdlib.h>
#include "colors.h"

static int init_term(void) {
	int ret;
	char *term_type = getenv("TERM");

	if (term_type == NULL)
	{
		return -1;
	}
	ret = tgetent(NULL, term_type);
	if (ret <= 0)
		return -1;
	return 1;
}

static int		*get_status(void)
{
	static int	status = 0;

	return (&status);
}

char	*get_color(int color) {
	int			*status = get_status();

	if (*status == 0)
		*status = init_term();
	if (*status < 0)
		return ("");
	return (tparm(tgetstr("AF", NULL), color));
}

char	*get_reset(void) {
	int		*status = get_status();

	if (*status < 0)
		return ("");
	return (tigetstr("sgr0"));
}
