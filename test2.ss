(define (list_copy ls)
  (if (list? ls)
      ls
      'list_copy1_requires_a_list_argument
      )
  )
(define (odd_copy ls)
  (if (list? ls)
      (if (or (null? ls) (null? (cdr ls)))
	  ls
	  (cons (car ls) (odd_copy (cddr ls)))
	  )
      'odd_copy__requires_a_list_argument
      )
  )
(define (even_copy mylist)
  ;Returns a list of all the even positions of the original list
  (if (list? mylist)
      (if (null? mylist)
	  mylist
	  (if (null? (cdr mylist))
	      '()
	      (cons (cadr mylist) (even_copy (cddr mylist)))
	      )
	  )
      'even_copy_requires_a_list_argument
      )
  )
