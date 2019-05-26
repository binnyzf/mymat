#
# In order to execute this "Makefile" just type "make"
#	A. Delis (ad@di.uoa.gr)
#

OBJS	= mat.o handler.o mymat.o
SOURCE	= mat.c handler.c mymat.c
HEADER	= mat.h
OUT	= mymat
CC	 = gcc
FLAGS	 = -g -c -Wall  -ansi -pedantic
# -g option enables debugging mode 
# -c flag generates object code for separate files


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)


# create/compile the individual files &gt;&gt;separately&lt;&lt;
mat.o: mat.c
	$(CC) $(FLAGS) mat.c -std=c90

handler.o: handler.c
	$(CC) $(FLAGS) handler.c -std=c90

mymat.o: mymat.c
	$(CC) $(FLAGS) mymat.c -std=c90


# clean house
clean:
	rm -f $(OBJS) $(OUT)

# run the program
run: $(OUT)
	./$(OUT) >output.txt
