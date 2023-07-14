all:
	gcc -g -Wall -o main testr-03-main.c vector.c binary_tree.c
	
clean:
	rm -f main 
run:
	./main
val:
	valgrind --leak-check=full --show-leak-kinds=all ./main