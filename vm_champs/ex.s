.name "
tralalala"
.comment "coool!"
		
l2:	sti r1,%:live,%0
	and	:live,%0,r1
live:	live %0
	zjmp	%:live
