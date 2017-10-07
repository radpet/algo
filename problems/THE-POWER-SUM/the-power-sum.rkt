#lang racket

(define (pow a n)
  (if (= n 1)
      a
      (if (= 0 (modulo n 2))
      (pow (* a a) (/ n 2))
      (* a (pow (* a a) (quotient n 2) )) 
      )
  )
)

(define (readX x)
  (define (readN n)
    (define (solve sum i)
      (if (< (- sum (pow i n)) 0)
          0
          (if (= (- sum (pow i n)) 0)
              1
              (+ (solve (- sum (pow i n)) (+ i 1))
                 (solve sum (+ i 1))
              )
          )  
       )      
     )
    (solve x 1)
  )

  (readN (read))
)

(readX (read))