/*
The program AbsMinus (implemented in function foo) takes 
two integers i and j as input and returns the absolute value of i-j.

There is an error in this program that is in the assignment 
"result=i+1", which should be "result=i. By putting as input 
{i=0, j=1}, the program returns the value 0, however, 
the returned value should be 1 as the absolute value of i-j. 
This program shows a a case where all if-condition are free 
from faults. 

@author: Mohammed Bekkouche
@Web:    http://www.i3s.unice.fr
*/

#include <sniper/sniper.h>

/* returns |i-j|, the absolute value of i minus j */
int foo (int i, int j) {//__CPROVER_assume((i==0) && (j==1));
    int result=i+1; // error in the assignment : result = i instead of result = i+1
    int k = 0;
    if (i <= j) {
        k = k+1;
    }
    if (k == 1 && i != j) {
        result = j-result; 		
    }
    else {
        result = result-j;
    }
    //assert(result==1);
    sniper_assert( (i<j && result==j-i) || (i>=j && result==i-j));
}
