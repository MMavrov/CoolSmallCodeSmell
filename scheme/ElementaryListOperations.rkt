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

;a variant of the deep_count function where the empty list is NOT counted as atom
(define (atom? x)
  (not (or (pair? x) (null? x) (vector? x))))

(define (deep_count_atoms l)
  (cond
    ((null? l) 0)
    ((atom? l) 1)
    (else (+ (deep_count_atoms (car l)) (deep_count_atoms (cdr l))))))

;a variant of the deep_count function where the empty list is counted as atom
(define (atom_including_empty_list? x)
  (not (or (pair? x) (vector? x))))

(define (deep_count_atoms_including_empty_list l)
  (cond
    ((null? l) 0)
    ((atom_including_empty_list? (car l)) (+
                                 1
                                 (deep_count_atoms_including_empty_list (cdr l))))
    (else (+
           (deep_count_atoms_including_empty_list (car l))
           (deep_count_atoms_including_empty_list (cdr l))))))

;higher order functions
(define (accumulate l operation initial_value)
  (if (null? l) initial_value
      (operation (car l) (accumulate (cdr l) operation initial_value))))

(define (my_map l f)
  (if (null? l) l
      (cons (f (car l)) (my_map (cdr l) f))))

(define (filter l predicate)
  (cond
    ((null? l) l)
    ((predicate (car l)) (cons (car l) (filter (cdr l) predicate)))
    (else (filter (cdr l) predicate))))

