/*
The program Minmax (implemented in function foo) takes 
three integers as input and assigns the smallest value 
to the variable least and the biggest value to the variable most.

There is an error in this program in the assignment "most = in2",
the assignment should be "least = in2". For an input equal to 
{in1=2, in2=1, in3=3}, and we should obtain an output with 
least=1 and most=3, which is not conform with the given post-condition 
"(least<=most)".

@author: Mohammed Bekkouche
@Web:    http://www.i3s.unice.fr
 */

#include <sniper/sniper.h>
    
void foo(int in1,int in2,int in3){
	int least;//sniper_assume((in1==2) && (in2==1) && (in3==3));
	int most;
    least = in1;
	most = in1;
	if (most < in2){
	    most = in2;
	}
	if (most < in3){
	    most = in3;
	}
	if (least > in2){ 
	    most = in2; // error in the assignment : most = in2 instead of least = in2
	}
	if (least > in3){ 
	    least = in3; 
	}
    sniper_assert(least <= most);
}

      
      

