#lang racket

(define (pair-compose fs)
  (define (iter rest x)
    (cond
      [(null? rest) 0]
      [(null? (cdr rest)) x] 
      [else (+ ( (car rest) ( (car (cdr rest)) x )) (iter (cdr (cdr rest) ) x)) ]
    )
   )

  (λ(x) (iter fs x))
 )


(define g (pair-compose (list (λ(x) (+ 1 x)) (λ(x) (+ 2 x)) )))
(g 1)

(define g2 (pair-compose (list (λ(x) (+ 1 x)) (λ(x) (+ 2 x)) (λ(x) (x)) )))
(g2 1)

