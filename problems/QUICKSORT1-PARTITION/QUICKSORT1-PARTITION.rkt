#lang racket
(define (readTask n)
  
  (define (readElements i elements) 
    (if (= i n)
        elements
        (readElements (+ i 1) (append elements (list (read))))
    )
  )
  
  (define (partition elements)
    (define (iter elems pivot left equal right)
      (cond
        [(empty? elems) (append left equal right)]
        [else
         (if (= (first elems) pivot)
             (iter (rest elems) pivot left (append (list (first elems)) equal ) right)
             (if (< (first elems) pivot )
                 (iter (rest elems) pivot (append (list (first elems)) left ) equal right)
                 (iter (rest elems) pivot left equal  (append (list (first elems) ) right ))
                 )
             )]
        )
      )
    (iter elements (first elements) (list) (list) (list))
    )


  (define (printList list)
    
    (if (empty? list)
        (display "")
        (begin
          (display (first list))
          (display " ")
          (printList (rest list))
        )
    )
  )
  
   (printList (partition (readElements 0 (list))) ) 
)
(readTask (read))



            