#lang racket

(define (digit? x)
  (and (> (- (char->integer x) (char->integer #\0)) -1 ) (< (- (char->integer x) (char->integer #\0)) 10 ))
)

(define (as-digit x)
  (- (char->integer x) (char->integer #\0))
)

;(map as-digit (filter ( λ(x) (digit? x) ) (string->list "123")))

(define (to-num list)
  (define (iter rem result)
    (if (null? rem)
        result
        (iter (cdr rem) (+ (car rem) (* result 10)))
     )
   )
  (iter list 0)

 )

;(to-num '(12345555555555555555555555555555555555555555555555555555555))

(define (extract-num str)
  (define (iter rest buffer result)
    (if (null? rest)
        (cons (reverse buffer) result)

        (if (digit? (car rest))
            (iter (cdr rest) (cons (car rest) buffer) result)
            (iter (cdr rest) '() (cons (reverse buffer) result))
        )
     )
   )
  (iter str '() '())
)

;(extract-num (string->list "123a54"))

(define (sum-numbers str)
  (apply + (map to-num (map (λ(x) (map as-digit x) ) (extract-num (string->list str)) ) ) )
)
(sum-numbers "a123b2c56")
(sum-numbers "a1b2c3")
(sum-numbers "a1b2c3d4")
