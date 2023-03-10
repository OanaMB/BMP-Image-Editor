build: task0.c task1.c task2.c task3.c task4.c task5.c
	gcc -Wall task0.c task1.c task2.c task3.c task4.c task5.c -o bmp -g

run:
	./bmp

clean:
	rm -rf bmp
