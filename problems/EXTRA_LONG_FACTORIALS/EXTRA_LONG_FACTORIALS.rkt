#lang racket

(define (fact n) 
  (define (helper i result)
    (if (= i 1)
        result
        (helper (- i 1) (* result i ) )
    )
  )

  (helper n 1)
 )

(display (fact (read)))

