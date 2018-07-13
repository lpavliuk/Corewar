.name "zork"
.comment "just a basic living prog"

l1 
l2
l2:	sti	r1,%:live,%0
live:	live	%1
	zjmp	%:l2
