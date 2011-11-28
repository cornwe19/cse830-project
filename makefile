
APP = solve-USPS 
OBJS = Graph.o Node.o solve-USPS.o
DOTHS = Graph.h 
GCC = g++ -Wall -I.

.SILENT:

.SUFFIXES: .h .cpp .o

.cpp.o: ${DOTHS}
	echo "Compiling \"$<\"..."
	${GCC} -c -O3 $<

${APP}: ${OBJS}
	echo "Linking project..."
	${GCC} ${OBJS} -o $@
	echo "Project \"$@\" built successfully."
	
clean:
	${RM} *.o *.~ ${APP}
