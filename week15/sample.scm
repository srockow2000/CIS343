
;;; Number 5
(define l (list 1 2 3 4))
(define (length l)
  (cond
  	((null? l) count)
  	;;; if not null
	(else 
	  (+ count 1)
	  (- (car l) 1)
	  )
	)
  )

(length l)
