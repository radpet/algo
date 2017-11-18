Задача 3. Ако f и g са числови функции и n е естествено число, да се напише функция от по-
висок ред (switchsum f g n), която връща като резултат функция, чиято стойност в дадена
точка x е равна на f(x)+g(f(x))+f(g(f(x)))+ ... (сумата включва n събираеми).
Примери:
((switchsum (lambda (x) (+ x 1))
 (lambda (x) (* x 2)) 1) 2) → 3
((switchsum (lambda (x) (+ x 1))
 (lambda (x) (* x 2)) 2) 2) → 9
((switchsum (lambda (x) (+ x 1))
 (lambda (x) (* x 2)) 3) 2) → 16
((switchsum (lambda (x) (+ x 1))
 (lambda (x) (* x 2)) 4) 2) → 30
