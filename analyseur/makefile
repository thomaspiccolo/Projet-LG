analyse: *.l *.y makefile
	flex  -Pdtd dtd.l
	bison -pdtd  --debug --verbose --defines=dtd.tab.h dtd.y

	flex  -Pxml xml.l
	bison -pxml  --debug --verbose --defines=xml.tab.h xml.y
		
	g++ -g -Wall -Wextra -DDTDDEBUG=1 -DXMLDEBUG=1 -o analyse  *.c *.cpp 
	
test: *.l *.y makefile
	flex  -Pdtd dtd.l
	bison -pdtd  --debug --verbose --defines=dtd.tab.h dtd.y

	flex  -Pxml xml.l
	bison -pxml  --debug --verbose --defines=xml.tab.h xml.y
		
	g++ -g -Wall -Wextra -D DEBUGTEST -DDTDDEBUG=1 -DXMLDEBUG=1 -o analyse_test *.c *.cpp 
	
clean:
	-rm -rf *.o *.tab.c lex.*.c *.tab.h *.output analyse analyse_test *.stackdump

