#lang racket

(define (encode list)
  (define (iter rest buffer result)
    (if (null? rest)
        (cons buffer result)
        (if (not (eqv? (car rest) (car buffer)))
            (iter (cdr rest) (cons (car rest) 1) (cons buffer result))
            (iter (cdr rest) (cons (car buffer) (+ 1 (cdr buffer))) result  )
         )
     )
   )
  (if (null? list)
      list
      (reverse (iter (cdr list) (cons (car list) 1) '()))
   )
)

(encode '())
(encode '(a))
(encode '(a a a a b c c a a d e e e e))
(encode '(m i s s i s s i p p i))
