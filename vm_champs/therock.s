.name "The Rock"
.comment "I will kick your ass!"

# MAX 682 Mb

		add  r8,r8,r8
		zjmp %:name
zero:
		live %1
		fork %:name

zero1: 	live %1
		st   r11, -27
		st   r11, -36
		st   r11, -45
		st   r11, -54
		st   r11, -63
		st   r11, -72
		st   r11, -81
		st   r11, -90
		st   r11, -99
		st   r11, -108
		st   r11, -117
		st   r11, -126
		st   r11, -135
		st   r11, -144
		st   r11, -153
		st   r11, -162
		st   r11, -171
		st   r11, -180
		st   r11, -189
		st   r11, -198
		st   r11, -207
		st   r11, -216
		st   r11, -225
		st   r11, -234
		st   r11, -243
		st   r11, -252
		st   r11, -261
		st   r11, -270
		st   r11, -279
		st   r11, -288
		st   r11, -297
		st   r11, -306
		st   r11, -315
		st   r11, -324
		st   r11, -333
		st   r11, -342
		st   r11, -351
		st   r11, -360
		st   r11, -369
		st   r11, -378
		st   r11, -387
		st   r11, -396
		st   r11, -405
		st   r11, -414
		st   r11, -423
		st   r11, -432
		st   r11, -441
		st   r11, -450
		st   r11, -459
		st   r11, -468
		st   r11, -477
		st   r11, -486
		st   r11, -495

		add  r8,r8,r8
		zjmp  %:zero1

		# ld %16777216,r7 #  saves 01 00 00 00 to r2
name:
		ld %0,r11
		# sti r1,%:zero0,%1
		# sti r1,%:name1,%1
		# sti r1,%:zero,%1
		# sti r1,%:zero1,%1
		sti r1,%:l2,%1
		# sti r1,%:load,%1
		# sti r1,%:jump2,%1
		# sti r1,%:start,%1
		# sti r1,%:zero0,%1
		# sti r1,%:forkin2,%1
		# sti r1,%:for2,%1
		# sti r1,%:f2,%1
		sti r1,%0,%8

	    live %1


		# lfork %2000
# zero0: 	live %1
# 		st   r11, 499
# 		st   r11, 498
# 		st   r11, 497
# 		st   r11, 496
# 		st   r11, 495
# 		st   r11, 494
# 		st   r11, 493
# 		st   r11, 492
# 		st   r11, 491
# 		st   r11, 490
# 		st   r11, 489
# 		st   r11, 488
# 		st   r11, 487
# 		st   r11, 486
# 		st   r11, 485
# 		st   r11, 484
# 		st   r11, 483
# 		st   r11, 482
# 		st   r11, 481
# 		st   r11, 480
# 		st   r11, 479
# 		st   r11, 478
# 		st   r11, 477
# 		st   r11, 476
# 		st   r11, 475
# 		st   r11, 474
# 		st   r11, 473
# 		st   r11, 472
# 		st   r11, 471
# 		st   r11, 470
# 		st   r11, 469
# 		st   r11, 468
# 		st   r11, 467
# 		st   r11, 466
# 		st   r11, 465
# 		st   r11, 464
# 		st   r11, 463
# 		st   r11, 462
# 		st   r11, 461
# 		st   r11, 460
# 		st   r11, 459
# 		st   r11, 458
# 		st   r11, 457
# 		st   r11, 456
# 		st   r11, 455
# 		st   r11, 454
# 		st   r11, 453
# 		st   r11, 452
# 		st   r11, 451
# 		st   r11, 450
# 		st   r11, 449
# 		st   r11, 448
# 		st   r11, 447
        
#         add  r8,r8,r8
# 		zjmp  %:zero0

l2:
		# sti r1,%:zero10,%1
		sti r1,%:forkin,%1
		sti r1,%:for,%1
		sti r1,%:f,%1
		# sti r1,%:forkin2,%1
		# sti r1,%:for2,%1
		# sti r1,%:f2,%1
		live %1
		fork %:zero
		# 
# name1:
# 		live %1
# 		# fork %:zero10
# 		add  r8,r8,r8
# 		zjmp %:f2

# zero10:
# 		live %1
# 		fork %:name

# 		# add  r8,r8,r8
# 		# zjmp %:zero10

# start:	
# 		live %1
# 		fork %:f
		
# # 		and r8,%0,r8
# # 		zjmp %:f

# # # ######### 2 ################

# f2:
# 		live %1
# 		sti r1,%:jump2,%1
# 		fork %:forkin2

# for2:
# 		live %1
# 		sti r1,%:write2,%1
# 		sti r1,%:write21,%1
# 		fork %:write21

# write2:		
# 		live %1
# 		ld   %-191, r14	
# 		ldi  %0, %:jump2, r15

# 		and r8,%0,r8
# 		zjmp %:jump2

# write21: 
# 		live %1
# 		ld   %-187, r14	
# 		ldi  %4, %:jump2, r15

# 		and r8,%0,r8
# 		zjmp %:jump2

# forkin2:
# 		live %1
# 		sti r1,%:write22,%1
# 		sti r1,%:write23,%1
# 		fork %:write23

# write22: 
# 		live %1
# 		ld   %-183, r14	
# 		ldi  %8, %:jump2, r15
		
# 		and r8,%0,r8
# 		zjmp %:jump2

# write23: 
# 		live %1
# 		ld   %-179, r14	
# 		ldi  %12, %:jump2, r15
		
# 		and r8,%0,r8
# 		zjmp %:jump2

# jump2:
# 		live %1				# 5
# 		sti  r15,%0,r14			# 6
# 		zjmp %-200

#########  1  #############

f:	
		live %1
		sti r1,%:jump,%1
		fork %:forkin

for:
		live %1
		sti r1,%:write,%1
		sti r1,%:write1,%1
		fork %:write1

write:		
		live %1
		ld   %321, r14	
		ldi  %0, %:jump, r15

		and r8,%0,r8
		zjmp %:jump

write1: 
		live %1
		ld   %325, r14	
		ldi  %4, %:jump, r15

		and r8,%0,r8
		zjmp %:jump

forkin:
		live %1
		sti r1,%:write2,%1
		sti r1,%:write3,%1
		fork %:write3

write2: 
		live %1
		ld   %329, r14	
		ldi  %8, %:jump, r15
		
		and r8,%0,r8
		zjmp %:jump

write3: 
		live %1
		ld   %333, r14	
		ldi  %12, %:jump, r15
		
		and r8,%0,r8
		zjmp %:jump

jump:
		live %1				# 5
		sti  r15,%0,r14			# 6
		zjmp %315

# zero: 
#         live %1
# 		fork  %:zero0

        # fork  %:forkin


# zero0: 	live %1
# 		st   r11, -90
# 		st   r11, -99
# 		st   r11, -108
# 		st   r11, -117
# 		st   r11, -126
# 		st   r11, -135
# 		st   r11, -144
# 		st   r11, -153
# 		st   r11, -162
# 		st   r11, -171
# 		st   r11, -180
# 		st   r11, -189
# 		st   r11, -198
# 		st   r11, -207
# 		st   r11, -216
# 		st   r11, -225
# 		st   r11, -234
# 		st   r11, -243
# 		st   r11, -252
# 		st   r11, -261
# 		st   r11, -270
# 		st   r11, -279
# 		st   r11, -288
# 		st   r11, -297
# 		st   r11, -306
# 		st   r11, -315
# 		st   r11, -324
# 		st   r11, -333
# 		st   r11, -342
# 		st   r11, -351
# 		st   r11, -360
# 		st   r11, -369
# 		st   r11, -378
# 		st   r11, -387
# 		st   r11, -396
# 		st   r11, -405
# 		st   r11, -414
# 		st   r11, -423
# 		st   r11, -432
# 		st   r11, -441
# 		st   r11, -450
# 		st   r11, -459
# 		st   r11, -468
# 		st   r11, -477
# 		st   r11, -486
# 		st   r11, -495
# 		st   r11, -504
# 		st   r11, -513
        
# 		zjmp  %:zero0
# forkin:	
#         live %1

# forkin1: 
#         live %1
# 		fork  %:zero0


# cpy:  
#         live %1
#         ld %184549376,r10
#         ld %



