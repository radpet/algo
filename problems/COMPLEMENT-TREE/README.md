Задача. Казваме, че двоичното дърво t1 допълва двоичното дърво t2, ако
Дървото t2 е празно, или
Ако t1 е дърво с корен x, ляво поддърво L1 и дясно поддърво R1, а t2 е дърво с корен y, ляво поддърво L2 и дясно поддърво R2, то x=y, L1 допълва L2 и R1 допълва R2.
Нека е дадена следната структура, описваща възел в двоично дърво: 
struct Node { int x; Node *left, *right;};
Да се дефинира функция 
bool  complement([подходящ тип]t1, [подходящ тип]t2)
която проверява дали t1 допълва t2.