/** =========
 qo   |)    | workplace
    _x/ ,   | library
    |    ng | user interface
_opRWTng-rwt=

command line parser.
---------------------------------------
(atrybuty)
==================================== */
#define _GNU_SOURCE
#include <stdbool.h>
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//=====================================
enum Z_arg_proc_ret
{	ARG_PROC_RET_ACCEPT,
	ARG_PROC_RET_REJECT,
	ARG_PROC_RET_IGNORE,
};
typedef
enum Z_arg_proc_ret
Z_arg_proc(
	int switch_,
	int argc,
	char *argv[]
);
typedef
enum Z_arg_proc_ret
Z_arg_def_proc(
	int argc,
	char *argv[]
);
struct Z_avail_arg
{	const char *const long_text;
	const char *const short_text;
	const unsigned switchable : 1;
	const unsigned value_list : 1;
	const unsigned other_value : 1;
	const unsigned values_count;
	const char *const *const values;
	Z_arg_proc *const proc;
	const char *const desc_text;
};
//=====================================
void
parse_cmd_args(
	int argc,
	char *argv[],
	Z_arg_def_proc *def_proc,
	int avail_args_len,
	struct Z_avail_arg avail_args[]
);
//=====================================
