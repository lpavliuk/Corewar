.name "Death"
.comment "Fork"


f1:	fork	%:f2
f2:	fork	%:f3
f3:	fork	%:f4
f4:	fork	%:f5
f5:	fork	%:f6
f6:	fork	%:f7
f7:	fork	%:f8
f8:	fork	%:f9
f9:	fork	%:f10
f10:

l1:	live	%1
l2:	live	%1
l3:	live	%1
l4:	live	%1
	zjmp	%:l1

