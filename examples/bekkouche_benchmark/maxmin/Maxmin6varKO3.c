/*
The program Maxmin6var (implemented in function foo) takes 
six poxisitve values as input and assigns to the variable max 
the maximum value and to the variable min the minimum value. 

There is two errors in this program, one in the conditions 
((a>b) && (a>c) && (b>d)  && (a>e) && (a>f)) and in the 
condition ((b<c) && (c<d) && (b<e) && (b<f)). 
By taking as input {a=1, b=-3, c=0, d=-2, e=-1, f=-2}, 
these errors trigger two wrong branching; the program 
returns {max=0,min=-3} instead of {max=1,min=-3}.

@author: Mohammed Bekkouche
@Web:    http://www.i3s.unice.fr
*/

#include <sniper/sniper.h>

/*
 * Find the maximum and minimum of six values.
 */
void foo (int a, int b, int c, int d, int e, int f) {//__CPROVER_assume((a==1) && (b==-3) && (c==0) && (d==-2) && (e==-1) && (f==-2)); assume((a==1) && (b==-3) && (c==0) && (d==-2) && (e==-1) && (f==-2));
    //assume((a==2) && (b==0) && (c==1) && (d==1) && (e==1) && (f==1));
	int max;
    int min;
	if ((a>b) && (a>c) && (b>d)  && (a>e) && (a>f)){ // error, the instruction should be ((a>b) && (a>c) && "(a>d)" && (a>e) && (a>f))
        max=a;
        if ((b<c) && (c<d) && (b<e) && (b<f)){ // error, the instruction should be ((b<c) && "(b<d)" && (b<e) && (b<f))
            min=b;
        }
        else{
            if ((c<d) && (c<e) && (c<f)){
                min=c;
            }
            else{
                if ((d<e) && (d<f)){
                    min=d;
                }
                else{
                    if (e<f){
                        min=e;
                    }
                    else{
                        min=f;
                    }
                }
            }  
        }
        
	}else{ 
	    if ((b>c) && (b>d) && (b>e) && (b>f)){
            max=b;
            
            if ((a<c) && (a<d) && (a<e) && (a<f)){
                min=a;
            }else{
                if ((c<d) && (c<e) && (c<f)){
                    min=c;
                }
                else{
                    if ((d<e) && (d<f)){
                        min=d; 
                    }
                    else{
                        if (e<f){
                            min=e;
                        }
                        else{
                            min=f;
                        }
                    }
                }  
            }
            
        }    
	    else{
            if ((c>d) && (c>e) && (c>f)){ 
                max=c;
                
                if ((a<b) && (a<d) && (a<e) && (a<f)){
                    min=a;
                }else{
                    if ((b<d) && (b<e) && (b<f)){
                        min=b;
                    }
                    else{
                        if ((d<e) && (d<f)){
                            min=d; 
                        }
                        else{
                            if (e<f){
                                min=e;
                            }
                            else{
                                min=f;
                            }
                        }
                    }  
                }
                
            }
            else{
                if ((d>e) && (d>f)){
                    max=d;
                    
                    if ((a<b) && (a<c) && (a<e) && (a<f)){
                        min=a;
                    }else{
                        if ((b<c) && (b<e) && (b<f)){
                            min=b;
                        }
                        else{
                            if ((c<e) && (c<f)){
                                min=c; 
                            }
                            else{
                                if (e<f){
                                    min=e;
                                }
                                else{
                                    min=f;
                                }
                            }
                        }  
                    }
                }
                else{
                    if (e>f){
                        max=e;
                        
                        if ((a<b) && (a<c) && (a<d) && (a<f)){
                            min=a;
                        }else{
                            if ((b<c) && (b<d) && (b<f)){
                                min=b;
                            }
                            else{
                                if ((c<d) && (c<f)){
                                    min=c; 
                                }
                                else{
                                    if (d<f){
                                        min=d;
                                    }
                                    else{
                                        min=f;
                                    }
                                }
                            }  
                        }       
                    }
                    else{
                        max=f;
                        
                        if ((a<b) && (a<c) && (a<d) && (a<e)){
                            min=a;
                        }else{
                            if ((b<c) && (b<d) && (b<e)){
                                min=b;
                            }
                            else{
                                if ((c<d) && (c<e)){
                                    min=c; 
                                }
                                else{
                                    if (d<e){
                                        min=d;
                                    }else{
                                        min=e;
                                    }
                                }
                            }  
                        } 
                    }
                }
            }
	    }
    }
   /*assert(((a<b && a<c && a<d && a<e && a<f && min==a) ||
           (b<a && b<c && b<d && b<e && b<f && min==b) ||
           (c<a && c<b && c<d && c<e && c<f && min==c) ||
           (d<a && d<b && d<c && d<e && d<f && min==d) ||
           (e<a && e<b && e<c && e<d && e<f && min==e) ||
           (f<a && f<b && f<c && f<d && f<e && min==f))
            &&
           ((a>b && a>c && a>d && a>e && a>f && max==a) ||
            (b>a && b>c && b>d && b>e && b>f && max==b) ||
            (c>a && c>b && c>d && c>e && c>f && max==c) ||
            (d>a && d>b && d>c && d>e && d>f && max==d) ||
            (e>a && e>b && e>c && e>d && e>f && max==e) ||
            (f>a && f>b && f>c && f>d && f>e && max==f)));
    */
    /*assert(
           ((a<=b && a<=c && a<=d && a<=e && a<=f && min==a) ||
            (b<=a && b<=c && b<=d && b<=e && b<=f && min==b) ||
            (c<=a && c<=b && c<=d && c<=e && c<=f && min==c) ||
            (d<=a && d<=b && d<=c && d<=e && d<=f && min==d) ||
            (e<=a && e<=b && e<=c && e<=d && e<=f && min==e) ||
            (f<=a && f<=b && f<=c && f<=d && f<=e && min==f))
           &&
           ((a>=b && a>=c && a>=d && a>=e && a>=f && max==a) ||
            (b>=a && b>=c && b>=d && b>=e && b>=f && max==b) ||
            (c>=a && c>=b && c>=d && c>=e && c>=f && max==c) ||
            (d>=a && d>=b && d>=c && d>=e && d>=f && max==d) ||
            (e>=a && e>=b && e>=c && e>=d && e>=f && max==e) ||
            (f>=a && f>=b && f>=c && f>=d && f>=e && max==f)));*/
    
    
    sniper_assert( (max >= a) && (max >= b) && (max >= c) && (max >= d) && (max >= e) && (max >= f) && (min <= a) && (min <= b) && (min <= c) && (min <= d) && (min <= e) && (min <= f));
}





