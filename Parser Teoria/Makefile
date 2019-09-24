TARGET=sample1
C_SRCFILES=main.cpp lexer.cpp parser.cpp
OBJ_FILES=${C_SRCFILES:.cpp=.o}
.PHONY: clean run
.SUFFIXES:

$(TARGET): $(OBJ_FILES)
	g++ -g -o $@ $^

%.o: %.cpp
	g++ -std=c++14 -g -c -o $@ $<

run: $(TARGET)
	./$(TARGET) example1.lpp

clean:
	rm -f *.o
	rm -f $(TARGET)