
int main() {

    int x; 
    int y;
    
    assert(x>0);
    
    
	if(x==0) 
		x = 1;
	else
		x = x * 4;
    
	y = x - 1;
    
    assert(y==0);
	return 0;
}

