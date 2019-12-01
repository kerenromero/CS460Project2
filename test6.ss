(define (merge lst1 lst2)
;Mergesort helper function
  (if (null? lst1) lst2
      (if (null? lst2) lst1
	  (if (< (car lst1) (car lst2))
	      (cons (car lst1) (merge (cdr lst1) lst2))
	      (cons (car lst2) (merge (cdr lst2) lst1))))))
(define (odd lst)
;Mergesort helper function
  (if (null? lst)
      '()
      (if (null? (cdr lst))
	  (list (car lst))
	  (cons (car lst) (odd (cddr lst))))))
(define (even lst)
;Mergesort helper function
  (if (null? lst)
      '()
      (if (null? (cdr lst))
	  '()
	  (cons (cadr lst) (even (cddr lst))))))
(define (split lst)
;Mergesort helper function
  (cons (odd lst) (cons (even lst) '())))
(define (merge_t lst)
;Returns a sorted list via merge sort algorithm
  (if (null? lst)
      lst
      (if (null? (cdr lst))
	  lst
	  (merge (merge_t (car (split lst))) (merge_t (cadr (split lst)))))))
(define (mergesort lst)
  (list_reverse (merge_t (numbers_only lst)))
  )

