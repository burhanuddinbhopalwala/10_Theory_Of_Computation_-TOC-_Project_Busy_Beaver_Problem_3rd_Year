/* DFB's busy beaver (initially  the 3 card case */
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define UPBTAPE 25
#define LWBTAPE 1
#define FALSE 0
#define TRUE 1


//prints a single 1 and moves to the right
char * tm1 [4] [2] = {"0000", "1000","0110", "1000"};
// simple example of 2-state with optimal score of 4.
char * tm2 [4] [2] = {"0000", "1000", "0112", "1102", "1101", "1110"};
//another permutation of tm3 which terminates but has a score of only 2
char * tm3 [4] [2] = {"0000", "1000", "0102", "1113"
		     "0112", "1100", "0111", "1102"};
//classic 4-state tm producing a score of 23 in 107 moves
char * tm4 [5] [2] = {"0000", "1000", "0112", "1102", "0101",
		    "1003", "0110", "1104", "0114", "1011" };


char tape [25] = "0000000000000000000000000";
int tapelen = UPBTAPE - LWBTAPE - 1;
int  headpos, currtcard = 1, steps = 0;


void printtape ( )
{
int i;
for (i = 0; i < tapelen; i++)
	printf ("%c  ", tape[i] );
putchar ('\n');
for( i=0 ; i < headpos ; i++)
printf("   ") ;
putchar('^');
putchar('\n');
}

// TM Logic for Busy Beaver Solution ...
int runtm (char* thistm [] [2], int n)
{
//local variables
char currtchar, chtowrite;
int i, hdstate, nextcard, incdec;


//print out initial deck of cards
for (i = 0; i <= n; i++)
	  printf ("Card %d is %s  %s\n", i, thistm[i][0], thistm[i][1]);

headpos = tapelen / 2;
printf("\nInitial tape is shown below: Note that head position at each step is marked by ^\n\n");
printtape();

printf("\nGame started\n");

do {
currtchar = tape[headpos]; steps++;
hdstate = currtchar - '0'; //denotes whether a 0 or a 1 has just been read
chtowrite = thistm[currtcard][hdstate][1];
char shift = thistm[currtcard][hdstate][2];
nextcard =  thistm[currtcard][hdstate][3] - '0';
int incdec = (shift == '0') ? -1 : +1;
// shift headpos left or right after next write

//printf ("starting char from C1 column 0 is %c \n", currtchar);
//sanity check
if ((headpos < LWBTAPE-1) || (headpos == UPBTAPE - 2))
	{printf ("tape too short and/or TM may be looping\n"); return(1);}

#ifdef DEBUG
printf ("char to print is %c \n", chtowrite);
printf ("shiftchar is %c \n", shift);
printf ("nextcard is  %d \n", nextcard);
printf ("headpos is  now %d \n", headpos);
#endif

tape[headpos] = chtowrite;
printtape();
headpos = headpos + incdec; currtcard = nextcard;
  } while (currtcard != 0);

}



int main (char argc, char *argv[])

{
	clrscr();
	int i, j , retcode, ncards, score =0;
	char **currentgame;

printf("Enter the states of TM less than 4 : ");
scanf("%d",&ncards);
if( ncards == 1 )
currentgame = (char **) tm1;
else if( ncards == 2 )
currentgame = (char **) tm2;
else if( ncards == 3 )
currentgame = (char **) tm3;
else if( ncards == 4 )
currentgame = (char **) tm4;

retcode = runtm ((char *(*)[2]) currentgame, ncards);
if (retcode == 0) printf("The TM has halted\n");
printf ("\nFinal tape config is:\n\n"); printtape();

if (retcode != 1)
	{
		for (i == LWBTAPE; i<= UPBTAPE; i++)
			if (tape[i] == '1') score++;
		printf("\nsteps = %d    score = %d\n", steps, score);
	}
	getch();
	return 0 ;
}