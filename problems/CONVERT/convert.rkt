#lang racket

(define (convert x from to)
  (define (iter rem pos result)
    (if ( = (quotient rem to) 0)
        (+ (* (modulo rem to) pos) result)
        (iter (quotient rem to) (* pos from) (+ (* (modulo rem to) pos) result))
     )
   )

  (iter x 1 0)
)

;(convert 111 2 10)
;(convert 1000 2 10)
;(convert 1 2 10)
;(convert 444 5 10)
;(convert 324 6 10)
;(convert 174 8 10)
;(displayln "")
;(convert 7 10 2)
;(convert 8 10 2)
;(convert 124 10 5)
;(convert 124 10 6)
;(convert 120 10 9)


  