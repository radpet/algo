#lang racket

(define (sum-numbers a b)
  (define (good? x)
    (define (iter rem)
      (if (= (quotient rem 10) 0)
          #t
          (if (>  (modulo rem 10) (modulo (quotient rem 10) 10))
              #f
              (iter (quotient rem 10))
           )
      )
     )
    (iter x)
   )

  ;(good? 210)
  ;(good? 23)

  ;(print (range a (+ 1 b)))
  (apply + (filter good? (range a (+ 1 b) )))
 )

;(sum-numbers 1 9)
;(sum-numbers 199 203)
;(sum-numbers 219 225)