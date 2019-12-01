(define (remove_first mylist)
;Returns the list with the first value removed
  (if (list? mylist)
      (cdr mylist)
      'remove_first_requires_a_list_argument
      )
  )
(define (remove_last mylist)
;Returns the list with the last value removed
  (if (list? mylist)
      (if (null? (cdr mylist))
	  '()
	  (cons (car mylist) (remove_last (cdr mylist)))
	  )
      'remove_last_requires_a_list_argument
      )
  )
(define (list_reverse mylist)
;Returns the list in reverse order
  (define (list_reverse2 mylist acc)
      (if (null? mylist)
	  acc
	  (if (list? (car mylist))
	      (list_reverse2 (cdr mylist) (cons (list_reverse (car mylist)) acc))
	      (list_reverse2 (cdr mylist) (cons (car mylist) acc)))))
  (list_reverse2 mylist '()))
(define (absolute x)
  (if (< x 0)
      (* -1 x)
      x
      )
  )
