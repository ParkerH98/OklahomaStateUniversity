(* Parker Hague, 9/3/2020, Churchill - OPL, due:9/5/2020*)
(* ML recursive insertion sort*)

(* Evaluate x to be inserted into list. If x <= head of list then append x to the list. Else, call rinsert on the next item in the list.*)
(* The function returns a sorted list once it has compared all of the items in the list.*)

fun rinsert (x:real, [], dir) = [x]
  | rinsert(x:real, L: real list as h::T, dir) =
    if (dir(x, h)) then
       x::L

    else
        if (dir(h, x)) then
          h::rinsert(x, T, dir)
        else
          L;



(* return empty list if empty*)
(* return head if list has only one*)
(* if list isn't empty then call rinsert on the head of the list*)


fun rinsort([], dir) = [] 
  | rinsort([h], dir) = [h] 
  | rinsort (L: real list as h::T, dir) = 
  rinsert (h, rinsort(T, dir), dir);