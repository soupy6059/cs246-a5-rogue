all:
	rm -rf gcm*
	~/.compile order.txt main
	rm *.o

run:
	./main

.PHONY: run
