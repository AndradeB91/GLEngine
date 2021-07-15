LIBS=-lGLEW -lGLFW -lassimp
FRAMEWORKS=-framework OpenGL
EXEC=GLEngine
FILES=src/*.cpp
VENDOR=vendor/imgui/*.cpp

compile: $(FILES) $(VENDOR)
	g++ -std=c++11 $(FILES) $(VENDOR) -o $(EXEC) $(LIBS) $(FRAMEWORKS)

run: $(EXEC)
	./$(EXEC)

clean: 
	$(RM) *.o* && rm $(EXEC)

all: clean compile run