(DEFUN test-1 ()
       (SET 'A '12))

(DEFUN test-2 ()
       (SETF A '12))

(DEFUN test-3 ()
       (SETF A '(A B C)))

(DEFUN test-4 (A)
       (SETF A (+ A 2)))

(DEFUN test-5 (A)
       (SETF A 12))
