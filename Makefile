LIBS=-lGLEW -lGLFW
FRAMEWORKS=-framework OpenGL
EXEC=GLEngine
FILES=src/main.cpp src/Mesh.cpp src/Shader.cpp src/Window.cpp

compile: $(FILES)
	g++ $(FILES) -o $(EXEC) $(LIBS) $(FRAMEWORKS)

run: $(EXEC)
	./$(EXEC)

clean: 
	$(RM) *.o* && rm $(EXEC)

all: clean compile run