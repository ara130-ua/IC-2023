canny: main.o canny.o HashMap.o
	g++ -O3 -o canny.out main.o canny.o HashMap.o
run: canny
	./canny.out $(image) 100 1
run_options: canny
	./canny.out $(image) $(threshold) $(sigma)
main.o: main.cpp
	g++ -O3 -c main.cpp
canny.o: canny.cpp
	g++ -O3 -c canny.cpp
HashMap.o: HashMap.cpp
	g++ -O3 -c HashMap.cpp
clean:
	rm -f *.o *.out output_images/*.pgm
sobel: sobel.o
	g++ -O3 -o sobel.out sobel.o
sobel.o: sobel.cpp
	g++ -O3 -c sobel.cpp