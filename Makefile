LIBS=-lGLEW -lGLFW
FRAMEWORKS=-framework OpenGL
EXEC=GLEngine

compile: main.cpp
	g++ main.cpp -o $(EXEC) $(LIBS) $(FRAMEWORKS)

run: $(EXEC)
	./$(EXEC)

clean: 
	$(RM) *.o* && rm $(EXEC)

all: clean compile run