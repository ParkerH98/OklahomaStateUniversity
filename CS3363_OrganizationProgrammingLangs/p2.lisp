
; <p2.lisp>
; author: <Parker Hague>
; course: <CS3363>, <Fall 2020>
; assignment: <Program 2>
; due: <9/19/2020>, <11:59 PM>
; submitted: <9/18/2020>

; method takes in a list as an argument and returns a list without duplicates
(defun eliminate-duplicates (L)
  (cond ((null L) L)
        ((member (car L) (cdr L))
         (eliminate-duplicates (cdr L)))
        (t (cons (car L) (eliminate-duplicates (cdr L))))))

; inserts item into working sorting list
(defun insert (item lst) 
  (if (null lst) ; checks empty condition
    (list item) ; executes if list is empty
    (if (> item (car lst)) ; executes if list isn't empty
          (cons item lst)  ; if the item is > the first iteme in the list then add the item to the front of the list
          (cons (car lst) (insert item (cdr lst)))))) ; else, add the rest of the list to the next first item
  

; takes list as argument and returns sorted list
(defun lins (lst)
  (if (null lst) ; checks empty condition
    (setq lst '()) ; returns an empty list if the inserted list is empty
    (eliminate-duplicates(insert (car lst) (lins (cdr lst)))))) ; else, removes the duplicates from the list and begins sorting by the first element

