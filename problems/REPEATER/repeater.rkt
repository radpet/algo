#lang racket

(define (repeater x)
  (define (iter count glue result)
    (if (= count 0)
        result
        (if (= count 1)
            (string-append result x)
            (iter (- count 1) glue (string-append result x glue))
        )
     )
   )

  (λ(count glue) (iter count glue ""))
)


((repeater "I love Racket") 3 " ")
((repeater "Quack") 5 "!")
((repeater "") 2 "!")