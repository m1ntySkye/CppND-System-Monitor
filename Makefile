SOURCEFILES=$(wildcard include/*.cpp src/*.cpp)

default: build

.PHONY: all
all: format test build

format: $(SOURCEFILES)
	clang-format src/* include/* -i

build: $(SOURCEFILES)
	mkdir -p build
	cd build && \
	cmake .. && \
	make

debug: $(SOURCEFILES)
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make

.PHONY: clean
clean:
	rm -rf build
