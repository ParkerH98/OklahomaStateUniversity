[phague@csx8 ML]$ sml
Standard ML of New Jersey, Version 110.0.7, September 28, 2000 [CM; autoload enabled]
- fun epoly([], x:real) = 0.0 |
= epoly(L:real list as h::T, x:real) = h + x * epoly(T, x);
val epoly = fn : real list * real -> real
- (* This function returns zero if an empty list is entered. Else, this function will evaluate a list of real nums as a polynomial while taking an a real number               for the x variable*)



