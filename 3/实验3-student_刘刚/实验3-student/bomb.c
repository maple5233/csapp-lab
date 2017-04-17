#include <stdio.h>
#include "support.h"
#include "phases.h"

FILE *infile;

int main(int argc, char *argv[])
{
    char *input;

    if (argc == 1) 
     	infile = stdin; 
    else if (argc == 2) {
    	if (!(infile = fopen(argv[1], "r"))) {
	      printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
	      exit(8);
	    }//if
    }//else if
    else {  /* You can't call the bomb with more than 1 command line argument. */
	    printf("Usage: %s [<input_file>]\n", argv[0]);
	    exit(8);
    }//else

    initialize_bomb();

    printf("Welcome to my fiendish little bomb. You have 6 phases with\n");
    printf("which to blow yourself up. Have a nice day!\n");

    input = read_line();             /* Get input                   */
    phase_1(input);                  /* Run the phase               */
    phase_defused();                 /* Drat!  They figured it out! */
    printf("Phase 1 defused. How about the next one?\n");

    input = read_line();
    phase_2(input);
    phase_defused();
    printf("That's number 2.  Keep going!\n");

    input = read_line();
    phase_3(input);
    phase_defused();
    printf("Halfway there!\n");

    input = read_line();
    phase_4(input);
    phase_defused();
    printf("So you got that one.  Try this one.\n");
    
    input = read_line();
    phase_5(input);
    phase_defused();
    printf("Good work!  On to the next...\n");

    input = read_line();
    phase_6(input);
    phase_defused();
    
    return 0;
}
