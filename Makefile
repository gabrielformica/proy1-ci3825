CC= gcc -g
LIB= binlib.o timelib.o sorts.o

all: ordenArchivo-p ordenArchivo-t leaf
ordenArchivo-p: process.o ${LIB}
	${CC} process.o ${LIB} -o ordenArchivo-p 
process.o: process.c binlib.h timelib.h sorts.h
	${CC} -c process.c
ordenArchivo-t: thread.o ${LIB}
	${CC} -lpthread thread.o ${LIB} -o ordenArchivo-t
thread.o: thread.c binlib.h timelib.h sorts.h
	${CC} -lphtread -c thread.c
leaf: leaf.o ${LIB}
	${CC} leaf.o ${LIB} -o leaf
leaf.o: leaf.c sorts.h
	${CC} -c leaf.c
binlib.o: binlib.c binlib.h
	${CC} -c binlib.c
timelib.o: timelib.c timelib.h
	${CC} -c timelib.c
sorts.o: sorts.c sorts.h
	${CC} -c sorts.c
clean:
	rm -f *.o ordenArchivo-p leaf ordenArchivo-t
