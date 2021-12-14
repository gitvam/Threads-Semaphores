ask2: ask2.o
	gcc ask2.o -lpthread -o ask2.out
ask2.o: ask2.c
	gcc -c ask2.c
clean:
	@echo ‘Cleaning files...’
	@rm -f *.o *.out
all:
	gcc -c ask2.c
	gcc ask2.o -lpthread -o ask2.out
	
