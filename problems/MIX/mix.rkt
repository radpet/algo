#lang racket

(define (mix a b)
  (define (solve left right rest-a rest-b step)
    (if (null? rest-a)
        (cons left (list right))
        (if (= 0 (modulo step 2))
            (solve (append left (list (car rest-a))) (append right (list (car rest-b))) (cdr rest-a) (cdr rest-b) 1)
            (solve (append left (list (car rest-b))) (append right (list (car rest-a))) (cdr rest-a) (cdr rest-b) 0)
        )
     )      
  )
  (solve '() '() a b 0)
)

(mix '(1 2 3) '(4 5 6))