#include "common.h"
#include "util.h"
#include <ctype.h>

rpc_sigcall_t execline_parse_fn(int args, char **argv)
{
	char* cmd = argv[0];
	unsigned cmdlen = strlen(cmd);

	unsigned i; 
	for (i = 0; i < cmdlen; ++i)
		*(cmd + i) = tolower(*(cmd + i));

	if (!strcmp(cmd, "sum"))		return sum_1;
	else if (!strcmp(cmd, "max"))	return max_1;
	else if (!strcmp(cmd, "min"))	return min_1;
	

	fprintf(stderr, "parse err: tried to invoke an unknown method, '%s'.\n", cmd);
	return 0;
}

items *execline_parse_list(int args, char **argv)
{
	items *it = malloc(sizeof(items));
	it->items_val = malloc(sizeof(double) * (args - 1));  /* first arg is fn */
	unsigned i; 
	double d;

	for(i = 0; i < args - 1; i++)
	{
		int err = errno;
		d = strtod(argv[i + 1], NULL);
		
		if (err == EILSEQ || err == EDOM || err == ERANGE)
		{
			fprintf(stderr, "parse err: numberic list is malformed.\n");
			free(it->items_val);
			free(it);
			return 0;
		}

		it->items_val[i] = d;
	}

	it->items_len = i;

	return it;
}

pgrm *execline_parse(char *line)
{
	char *word = malloc(strlen(line)), *ptr;
	unsigned c = 0;

	strcpy(word, line);
	char *token = strtok(word, " ");
	while (++c && strtok(NULL, " "));
	
	if (c < 3)
	{
		fprintf(stderr, "parse err: your input is malformed.\n\n");
		fprintf(stderr, " > sum <n1> <n2> <n..>: The sum of a numeric list.\n");
		fprintf(stderr, " > max <n1> <n2> <n..>: The max in a numeric list.\n");
		fprintf(stderr, " > min <n1> <n2> <n..>: The min in a numeric list.\n\n");
		return 0;
	}

	char **argv = malloc(sizeof(char *) * c);
	unsigned args = c, i = 0;

	word = realloc(word, strlen(line));
	strcpy(word, line);
	token = strtok(word, " ");

	do { 
		argv[i] = malloc(strlen(token));
		strcpy(argv[i], token);
		i++;
	}
	while ((token = strtok(NULL, " ")));


	pgrm *p = malloc(sizeof(pgrm));

	p->fn = execline_parse_fn(args, argv);
	if (!p->fn) {
		dtor_argv(argv, c);
		dtor_pgrm(p);
		return 0;
	}

	p->items = execline_parse_list(args, argv);
	if (!p->items) {
		dtor_argv(argv, c);
		dtor_pgrm(p);
		return 0;
	}

	dtor_argv(argv, c);

	return p;
}


void run(char *host)
{

	CLIENT *cl;
	char line[1 << 21];

	char *eof;
	pgrm *p;
	while (1) 
	{
		printf("] ");
		line[0] = '\0'; 
		line[sizeof(line)-1] = ~'\0';

		eof = fgets(line, sizeof(line), stdin);
		if ((p = execline_parse(line))) {
			cl = ctor_cl(host);
			double *result;
			if ((result = p->fn(p->items, cl)))
			{
				printf(" -> %f\n", *result);
			} else {
				clnt_perror (cl, "call failed");
			}
			 
			dtor_cl(cl);
		}

		dtor_pgrm(p);
	}
}



int main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		fprintf (stderr, "usage: %s <host>\n", argv[0]);
		return 1;
	}

	host = argv[1];
	run (host);
	return 0;
}
