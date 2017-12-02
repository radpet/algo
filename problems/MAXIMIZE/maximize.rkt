#lang racket

(define (maximize list)
 (define (abs x)
   (if (< x 0)
       (- x)
       x
       )
   )
  
  (define (iter rest result x)
           (if (null? rest)
               result
               (if (< (abs ((car rest) x) ) (abs result) )
                   (iter (cdr rest) result x)
                   (iter (cdr rest) ((car rest) x) x)
               )
            )
    )
  
  (λ(x) (iter list ( (car list) x) x) )
)

;((maximize (list (λ (x) (- x 10)) (λ (x) (- x 5))) ) 5)
;((maximize (list (λ (x) (- x 10)) (λ (x) (- x 5)))) 9)
