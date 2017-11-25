#lang racket

(define (replace l change)
  (map (λ(c) 
              (if (= 0 (length (filter (λ(p) (= c (car p)) ) change)))
                  c
                  (car (map (λ(x) (cdr x) ) (filter (λ(p) (= c (car p)) ) change) ))
              )
                                     
        ) l
   )
)

(replace '(1 2 3) '( (1 . 11) (2 . 22) (4 . 5)))