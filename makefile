.PHONY: run clean run-dev clean-dev

./banker: ./src/main.c
	gcc $^ -o $@

./banker-dev: ./dev/main.c
	gcc $^ -o $@

run: 
	./banker

clean:
	rm banker

run-dev:
	./dev/banker

clean-dev:
	rm ./dev/banker

dev: ./banker

build: ./banker