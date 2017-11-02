.PHONY: clean run

SRC = src/
EXECUTABLE = othello.exe

all:
	cd $(SRC); make; mv $(EXECUTABLE) ..;

run:
	./$(EXECUTABLE);

clean:
	rm $(EXECUTABLE); cd $(SRC); make clean;
