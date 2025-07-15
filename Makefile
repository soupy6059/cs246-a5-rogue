all:
	rm -rf gcm*
	~/.compile order.txt main 1>/dev/null

run:
	./main

.PHONY: run
