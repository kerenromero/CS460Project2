(define (last mylist)
;Returns the last value withing the list
  (if (list? mylist)
      (if (null? (cdr mylist))
	  (car mylist)
	  (last (cdr mylist))
	  )
      'last_requires_a_list_argument
      )
  )
(define (insert_last myvalue mylist)
;Returns the list mylist with myvalue appended to the end
  (if (list? mylist)
      (if (null? mylist)
	  (list myvalue)
	  (cons (car mylist) (insert_last myvalue (cdr mylist)))
	  )
      'insert_last_requires_a_list_argument
      )
  )
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
