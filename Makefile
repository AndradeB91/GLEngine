LIBS=-lGLEW -lGLFW -lassimp
FRAMEWORKS=-framework OpenGL
EXEC=GLEngine
FILES=src/*.cpp
C_PLUSPLUS_VERSION=c++11
VENDOR=vendor/imgui/*.cpp vendor/tecgraf/*.cpp

# needed files for mshsurf to work
# mshsurf3dmain.cpp 
# topsurfbin.cpp 
# topology.cpp 
# surf3d_auxfunc.cpp 
# surf3d_analt_auxfunc.cpp 
# amr3bind.cpp 
# surf3d_octree.cpp 
# surf3d_main.cpp 
# surf3d_advfront.cpp
# surf3d_geom.cpp 
# msh_quadsurf.cpp 
# msh_gensurf.cpp 
# msh_bdrsurf.cpp 
# amr3tree.cpp

compile: $(FILES) $(VENDOR)
	g++ -std=$(C_PLUSPLUS_VERSION) $(FILES) $(VENDOR) -o $(EXEC) $(LIBS) $(FRAMEWORKS)

run: $(EXEC)
	./$(EXEC)

clean: 
	$(RM) *.o* && rm $(EXEC)

all: clean compile run