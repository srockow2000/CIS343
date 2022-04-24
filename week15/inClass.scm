(define shortList (list 1 2 3 4))
(define longList (list 4 3 2 1 0))

;;; #5 - return the length of a list
(define (lngth l n)
  (cond
    ((and (null? l)(eq? n 0)) #f)
    ((null? l) n)
    (else (lngth (cdr l)(+ n 1)))
    )
  )

;;; #4 - checks whether first list is shorter than the second
(define (shorter l1 l2)
  (cond
  ((<= (lngth l1) (lngth l2)) #t)
  (else #f)
  )
  )

(define (shorter l1 l2)
  (cond
    ((and (null? l1)(null? l2)) #f)
    ((null? l1) #t)
    ((null? l2) #f)
    (else shorter (cr l1) (cdr l2))
    )
  )


;;; #3 - write the n-th digit of a multi-digit number
(define (index num i)
  (cond
    ;;; check if index < lngth
    (> i (lngth num)) #f

    ;;; check if number is a single digit
    (< num 10) num
    
    ;;; check if index is correct
    (eq? (lngth (quotient num 10)) i) (modulo num 10)

    ;;; run function recursively
    (else (index (quotient num 10) i)
    )`
  )
  )

  (define (nthdigit d n)
    (if (= n 0)
	(modulo d 10)
	(nthdigit (quotient d 10)(-n 1))
	)
    )


;;; #2 - give the nth element of a list
(define listElement l i
  (cond
    ((and (null? l)) #f)
    (> i (lngth l) #f)
    (+ count 1)
    (eq? count i) (cdr l)
    )
  )

(define (nth l n)
  (cond
    ((and (not (eq? n 0))(null? l)) #f)
    ((eq? n 0) (car l))
    (else (nth (cdr l) (- n 1)))
    )
  )



