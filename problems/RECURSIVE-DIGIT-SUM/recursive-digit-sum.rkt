#lang racket

; correct but slow

 (define (sum_of_digit p sum)
    (if (= p 0)
        sum
       (sum_of_digit ( quotient p 10) (+ sum (modulo p 10)))
     )
  )

(define (readInput n k)

  (define (super_digit p)
    (if (= ( quotient p 10) 0)
        p
        (super_digit (sum_of_digit p 0))
     )
  )

  (super_digit (* (sum_of_digit n 0) k))
)

(readInput (read) (read))
