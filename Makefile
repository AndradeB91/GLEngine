LIBS=-lGLEW -lGLFW -lassimp
FRAMEWORKS=-framework OpenGL
EXEC=GLEngine
FILES=src/*.cpp vendor/imgui/*.cpp

compile: $(FILES)
	g++ -std=c++11 $(FILES) -o $(EXEC) $(LIBS) $(FRAMEWORKS)

run: $(EXEC)
	./$(EXEC)

clean: 
	$(RM) *.o* && rm $(EXEC)

all: clean compile run