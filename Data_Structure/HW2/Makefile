ALL:main  exe clean



main: main.o 
	g++ -o main main.o 
main.o: main.cpp 
	g++ -std=c++11 -c -O3 main.cpp 

exe:
	main.exe 
clean:
	@del *.o
	@del main.exe