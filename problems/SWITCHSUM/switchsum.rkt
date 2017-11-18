#lang racket

(define (switchsum f g n)
  (define (iter pos nesting result)
    (if (>= pos n)
        result
        (if (= (modulo pos 2) 0)
            (iter (+ 1 pos) (f nesting) (+ result (f nesting)))
            (iter (+ 1 pos) (g nesting) (+ result (g nesting)))
        )
     )
  )

  ( λ(x) (iter 0 x 0) )

)

((switchsum (λ (x) (+ x 1)) (λ (x) (* x 2)) 1) 2)
((switchsum (λ (x) (+ x 1)) (λ (x) (* x 2)) 2) 2)
((switchsum (λ (x) (+ x 1)) (λ (x) (* x 2)) 3) 2) 
((switchsum (λ (x) (+ x 1)) (λ (x) (* x 2)) 4) 2)
((switchsum (λ (x) (+ x 1)) (λ (x) (* x 2)) 5) 2)