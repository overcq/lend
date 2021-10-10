/** =========
 qo   |)    | workplace
    _x/ ,   | utility
    |    ng | conversion
_opRWTng-rwt=

universal line ends converter to "\n", "\r\n" or "\r".
- - - - - - - - - - - - - - - - - - - -
automatycznie przełącza się do innego typu zakończenia wiersza, ale tylko wtedy gdy kolejna linia nie jest pusta.
---------------------------------------
==================================== */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "cmd_arg.h"
//=====================================
static
char *const def_output_lineend = "\n";
//=====================================
static
char *output_lineend = NULL;
//=====================================
static
enum Z_arg_proc_ret
for_sys_arg_proc(
    int switch_,
    int param_no,
    char *null[]
)
{   if( output_lineend )
        return ARG_PROC_RET_IGNORE;
    switch( param_no )
    {   case 1:
        case 3:
        case 4:
        case 5:
        case 6:
            output_lineend = "\n";
            break;
        case 0:
        case 2:
        case 8:
        case 9:
            output_lineend = "\r\n";
            break;
        case 7:
            output_lineend = "\r";
            break;
    }
    return ARG_PROC_RET_ACCEPT;
}
static
enum Z_arg_proc_ret
to_lineend_arg_proc(
    int switch_,
    int param_no,
    char *null[]
)
{   if( output_lineend )
        return ARG_PROC_RET_IGNORE;
    switch( param_no )
    {   case 0:
            output_lineend = "\n";
            break;
        case 1:
            output_lineend = "\r\n";
            break;
        case 2:
            output_lineend = "\r";
            break;
    }
    return ARG_PROC_RET_ACCEPT;
}
static
enum Z_arg_proc_ret
def_proc(
    int argc,
    char *argv[]
)
{   return ARG_PROC_RET_REJECT;
}
int
main(
    int argc,
    char *argv[]
)
{   if( isatty(0) )
        fprintf( stderr, "\"universal line end converter\" copyright (c) 2010,2021 overcq\n(DOS-type fancy program header:->)\n" );
    if( argc )
    {   argc--;
        argv++;
    }
    struct Z_avail_arg avail_args[] =
    {   "for-sys", "s", false, false, false, 10, (const char *const [] ){ "network", "unix", "Windows", "Macintosh", "Linux", "BSD", "Mac OS X", "Mac OS 9", "DOS", "DEC" }, for_sys_arg_proc, "for operating system",
        "to-lineend", "e", false, false, false, 3, ( const char *const [] ){ "lf", "crlf", "cr" }, to_lineend_arg_proc, "to line end character(s)",
    };
    parse_cmd_args( argc, argv, def_proc, sizeof( avail_args ) / sizeof( struct Z_avail_arg ), avail_args );
    if( !output_lineend )
        output_lineend = def_output_lineend;
    int c = getchar();
    do
    {   while( c != '\n'
        && c != '\r'
        )
        {   if( c == EOF )
                return 0;
            putchar(c);
            c = getchar();
        }
        int input_lineend_1, input_lineend_2;
        if( c == '\r' )
        {   c = getchar();
            if( c == '\n' )
            {   input_lineend_1 = '\r';
                input_lineend_2 = '\n';
                fputs( output_lineend, stdout );
            }else
            {   input_lineend_1 = '\r';
                input_lineend_2 = 0;
                fputs( output_lineend, stdout );
                if( c != EOF )
                    putchar(c);
            }
        }else
        {   input_lineend_1 = '\n';
            input_lineend_2 = 0;
            fputs( output_lineend, stdout );
        }
        if( input_lineend_2 )
            while( c = getchar(),
            c == '\r'
            || c == '\n'
            )
            {   int c_2 = getchar();
                if( c == input_lineend_1
                && c_2 == input_lineend_2
                )
                    fputs( output_lineend, stdout );
                else
                {   if( c != EOF )
                    {   putchar(c);
                        c = c_2;
                    }
                    break;
                }
            }
        else
            while( c = getchar(),
            c == '\r'
            || c == '\n'
            )
                if( c == input_lineend_1 )
                    fputs( output_lineend, stdout );
                else
                    if( c != EOF )
                        putchar(c);
    }while(true);
    return 0;
}
//=====================================
