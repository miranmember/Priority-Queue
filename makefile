build:
	rm -f tests.exe
	g++ tests.cpp -o tests.exe -lgtest -lgtest_main -lpthread
	
run:
	./tests.exe

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./tests.exe
	
a:
	rm -f tests.exe
	g++ tests.cpp -o tests.exe -lgtest -lgtest_main -lpthread
	./tests.exe
	
v:
	rm -f tests.exe
	g++ tests.cpp -o tests.exe -lgtest -lgtest_main -lpthread
	valgrind --tool=memcheck --leak-check=yes ./tests.exe