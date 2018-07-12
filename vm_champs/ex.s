.name "name"

.comment "comment"

l2:	sti	r1,%:live,%0
live:	live	%1
	zjmp	%:l2
