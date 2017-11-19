#lang racket

(define (where list-elements list-predicates)
  (define (iter rest-pred result)
    (if (null? rest-pred)
        result
        (iter (cdr rest-pred) (filter (car rest-pred) result))
    )
  )
  (iter list-predicates list-elements)
)

(where '(3 4 5 6 7 8 9 10) (list even? (lambda (x) (> x 5))))
(where '(3 4 5 7) (list even? (lambda (x) (> x 5))))
