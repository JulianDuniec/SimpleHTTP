all: build test

build:
	c++ impl/*.cpp test/main.cpp -o test/main

test:
	./test/main

.PHONY: build, test