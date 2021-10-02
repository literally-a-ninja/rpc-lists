#include "rpc/list.h"


double * sum_1_svc(items *argp, struct svc_req *rqstp)
{
	printf("D: -> sum_1_svc(items *argp, struct svc_req *rqstp)\n");
	static double bufa;

	bufa = 0; /* reset variable in the global section */
	unsigned i;
	for (i = 0; i < argp->items_len; ++i) {
		bufa += argp->items_val[i];
	}


	return &bufa;
}

double * max_1_svc(items *argp, struct svc_req *rqstp)
{
	printf("D: -> max_1_svc(items *argp, struct svc_req *rqstp)\n");
	static double bufb;

	bufb = 0; /* reset variable in the global section */
	bufb = argp->items_val[0] ? argp->items_val[0] : 0;

	unsigned i;
	for (i = 0; i < argp->items_len; ++i) {
		if (bufb > argp->items_val[i]) continue;

		bufb = argp->items_val[i];
	}


	return &bufb;
}

double * min_1_svc(items *argp, struct svc_req *rqstp)
{
	printf("D: -> min_1_svc(items *argp, struct svc_req *rqstp)\n");
	static double bufc;

	bufc = 0; /* reset variable in the global section */
	bufc = argp->items_val[0] ? argp->items_val[0] : 1 << 20;
	unsigned i;
	for (i = 0; i < argp->items_len; ++i) {
		if (bufc < argp->items_val[i]) continue;

		bufc = argp->items_val[i];
	}

	return &bufc;
}
