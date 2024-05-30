$(info $(SHELL))
makefile: orw.out forw.out fmap.out

orw.out: Z:\project4_PJWELCH\orw.c
	gcc -o orw.out Z:\project4_PJWELCH\orw.c
	
forw.out: Z:\project4_PJWELCH\forw.c
	gcc -o forw.out Z:\project4_PJWELCH\forw.c
	
fmap.out: Z:\project4_PJWELCH\fmap.c
	gcc -o fmap.out Z:\project4_PJWELCH\fmap.c
	
clean:
	rm *.out
