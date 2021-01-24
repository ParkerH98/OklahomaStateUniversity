
(*p0v2.sml*)
(*Parker Hague*)
(*CS3363*)
(*Program 0*)
(*Due: 8/27/20*)
(*Submitted: 9/21/20*)

(* This function returns zero if an empty list is entered. Else, this function will evaluate a list of real nums as a polynomial while taking an a real number               for the x variable*)
fun epoly([], x:real) = 0.0 |
 epoly(L:real list as h::T, x:real) = h + x * epoly(T, x); 


