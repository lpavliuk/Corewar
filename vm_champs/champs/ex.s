.name "zork"
.comment ""

   l2:	sti r1 	,         	 %:live	,	%1
	and	:live,%0	,r1
live:	live %0
	zjmp	%:live
