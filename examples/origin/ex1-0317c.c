/*
  pre:  16 > x >= 0
  post: ((0 <= x <= 1)  implies (y == x + 6)) 
    and ((1 < x <= 6)   implies (y == 3 - x))
    and ((6 < x < 10)   implies (y == 6))
    and ((10 <= x < 16) implies (y == -1)) 
*/

int y;

int foo (int x) {
  int a, b, u, v;

  if (x < 10) {
    a = 4; b = 1;
  } else {
    a = 1; b = 4;
  }

  if (x + a > 10) {
    u = a + b; v = b;
  } else if (x + a <= 5) {
    u = a + b; v = x + b;
  } else {
    u = x + b; v = a;
  }

  if (v < 2) {
    y = u + v;
  } else {
    y = v - u;
  }

  return(y);
}

