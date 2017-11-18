#lang racket

(define (num-bigger-elements list)
  (define (count x rest result)
    (if (null? rest)
        (cons x result)
        (if (< x (car rest))
            (count x (cdr rest) (+ 1 result))
            (count x (cdr rest) result)
        )
     )
   )

  (map (λ(x) (count x list 0) ) list)
  
)

(num-bigger-elements '(5 6 3 4))
(num-bigger-elements '(1 1 1))
(num-bigger-elements '())