#pragma once

#include <stdio.h>
#include <ctype.h>
#include <errno.h>

#include "rpc/list.h"

// represents an RPC call signature, this is used to add some interface segregation into the app itself.
typedef double *(*rpc_sigcall_t)(items*, CLIENT*);

// represents an executable RPC call
// this is malloc'd by the line parser
typedef struct {
	rpc_sigcall_t fn;
	items *items;
} pgrm;

