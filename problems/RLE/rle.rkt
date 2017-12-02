#lang racket

(define (encode _list)
  (define (iter rest buffer result)
    (if (null? rest)
        (append result (list buffer))
        (if (not (eqv? (first rest) (first buffer)))
            (iter (cdr rest) (list (first rest) 1) (append result (list buffer)))
            (iter (cdr rest) (list (first buffer) (+ 1 (second buffer))) result  )
         )
     )
   )
  (if (null? _list)
      _list
      (iter (cdr _list) (list (first _list) 1) '())
   )
)

;(encode '())
;(encode '(a))
;(encode '(a a a a b c c a a d e e e e))
;(encode '(m i s s i s s i p p i))
