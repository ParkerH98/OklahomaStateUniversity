% Filename: p6.pl
% Author: Parker Hague
% Course: CS3363
% Assignment: Program6
% Due: Nov. 14th, 2020, 11:59 PM
% Submitted: Nov. 11th 2020, 11:50

% facts
parent(warren, dan).
parent(warren, david).
parent(david, robert).
parent(david, charyl).
parent(charyl, ashlyn).
parent(charyl, austin).
parent(robert, parker).
parent(robert, brin).

% fact asserting that a is the parent of b
parent(a, b).

% rule asserting that a is an ancestor of 
% b if a is a parent of b
ancestor(A, B) :- parent(A, B).

% establishes grandpa relationship
% rule asserting a is an ancestor of c if a
% is a parent of b and if b is an ancestor of c
ancestor(A, C) :-
    ancestor(B, C), 
    parent(A, B).

% establishes sibling relationship
% rule asserting b is an sibling of c is a 
% is a parent of b and a is a parent of c
sibling(B, C) :-
    parent(A, B),
    parent(A, C).

% establishes cousin relationship if parents are 
% siblings and 
cousin(E, F) :-
    parent(A, E),
    parent(B, F),
    not(sibling(E, F)),
    sibling(A, B).

