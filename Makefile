all:
	rm -rf gcm*
	./.compile.sh order.txt main 1>/dev/null
	rm *.o

run:
	./main

test:
	echo todo

.PHONY: run test
