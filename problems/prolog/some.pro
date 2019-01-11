%count(list,X,N)
count([], _, 0).
count([H|T],H,N):- count(T,H,N1),N is N1+1 .
count([H|T],X,N):- H\=X, count(T,X,N).

% most_freq(X,N,L)
most_freq(_,0,[]).
most_freq(X,N,L):- member(X,L), count(L,X,N),not((member(Y,L),count(L,Y,YN),N<YN)).

least_freq(_,0,[]).
least_freq(X,N,L):- member(X,L),count(L,X,N), not((member(Y,L), count(L,Y,YN), N > YN)).

%diam(list,R)
diam([],0).
diam(L,R):- most_freq(_,M,L), least_freq(_,N,L), R is M - N.

%p([[]])
p(L):- member(X,L),diam(X,DX),not((member(Y,L),diam(Y,DY),DX=\=DY)).

% unique(L)
unique(L):- not((member(X,L), count(L,X,N), N \= 1)).
%q([[]])
q(L):- member(X,L),diam(X,DX), not((member(Y,L),X\=Y,diam(Y,DY),DX=:=DY)).

%my_append(A,B,R)
my_append([],B,B).
my_append([H|T],B,[H|R]):-my_append(T,B,R).

%my_member(X,L)
%my_member(X,L):-append(_,[X|_],L).

nat(0).
nat(N):-nat(N1), N is N1 + 1.

min(L,R):- member(R,L),not((member(Y,L),R>Y)).
max(L,R):- member(R,L),not((member(Y,L),R<Y)).

%get_max_els([[]],LX)
get_max_elems([],[]).
get_max_elems([H|T],[MAXH|R]):-max(H,MAXH),get_max_elems(T,R).

get_min_elems([],[]).
get_min_elems([H|T],[MINH|R]):-min(H,MINH),get_min_elems(T,R).

balance(L,R):- get_min_elems(L,MIN), get_max_elems(L,MAX), min(MAX,LMAX), max(MIN, LMIN), R is LMAX - LMIN.

containsBalanceAll(L):- balance(L,X), member(LSUB, L), member(X,LSUB).

%?- most_freq(X,N,[1,2,3,1])
%?- least_freq(X,N,[1,2,3,1])
%?- diam([1,2,3,1],R)
%?- p([[1,2,3],[1,2,3]])
%?- p([[1,2,3],[1,2,3,1]])
%?- unique([1,2,3])
%?- q([[1,2,3],[1,2,3,1]])
%?- my_append([1,2],[3,4],R)
%?- my_member(1,[1,2,3])
%?- my_member(12,[1,2,3])
%?- nat(R)
%?- min([1,2,3,4],R)
%?- max([1,2,3,4],R)
%?- get_max_elems([[1,2,3],[5,6]],R)
%?- get_min_elems([[1,2,3],[5,6]],R)
%?- balance([[1,2,3],[1,2,3]],R)
%?- containsBalanceAll([[1,2,3],[1,2,3]])
