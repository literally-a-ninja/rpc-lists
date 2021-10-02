#include "util.h"

void dtor_argv(char **argv, size_t len)
{
	if (!argv) return;

	unsigned i;
	for (i = 0; i < len; i++)
	{
		if (argv[i]) free(argv[i]);
	}
}

void dtor_pgrm(pgrm *p)
{
	if (!p) return;

	if (p->items) 
	{
		if (p->items->items_val) free(p->items->items_val);
		free(p->items);
	}

	free(p);
}

CLIENT *ctor_cl(char *host)
{
	CLIENT *cl;
#ifndef	DEBUG
	cl = clnt_create (host, LIST_MANI_PROG, DATE_VERS, "udp");
	if (cl == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	return cl;
}

// client dtor
void dtor_cl(CLIENT * cl)
{
#ifndef	DEBUG
	clnt_destroy (cl);
#endif	 /* DEBUG */
}

