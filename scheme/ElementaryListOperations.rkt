(define (my_length l)
  (if (null? l) 0
      (+ 1 (my_length (cdr l)))))

(define (kth_elem l k)
  (if (null? l) #f
      (if (= k 1) (car l)
          (kth_elem (cdr l) (- k 1)))))

(define (my_append l1 l2)
  (if (null? l1) l2
      (cons (car l1) (append (cdr l1) l2))))

(define (my_reverse l)
  (if (null? l) l
      (my_append (my_reverse (cdr l)) (list (car l)))))

(define (iterative_reverse l)
  (define (help l1 result)
    (if (null? l1) result
        (help (cdr l1) (cons (car l1) result))))
  (help l `()))

(define (my_member x l)
  (cond
    ((null? l) #f)
    ((equal? x (car l)) #t)
    (else (member x (cdr l)))))