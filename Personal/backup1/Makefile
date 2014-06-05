CXX = g++
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm -lGL -lGLU -lGLEW 
CFLAGS = -O1 -std=gnu++11 -MMD

#thanks to bobah on SO
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

all: 3dTest

3dTest: $(OBJ_FILES)
	$(CXX) -o $@ $^ $(LIBS)

obj/%.o: src/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

clean:
	rm obj/* 3dTest

#main.cpp Drawable.o JShader.o BaseFunc.o Entity.o
#	$(CXX) main.cpp Drawable.o JShader.o BaseFunc.o Entity.o ShaderProgram.o Collider.o $(LIBS) $(CFLAGS) -o 3dTest

#BaseFunc.o: BaseFunc.cpp BaseFunc.h
#	$(CXX) -c BaseFunc.cpp $(LIBS) $(CFLAGS)

#Entity.o: Entity.cpp Entity.h Collider.o
#	$(CXX) -c Entity.cpp $(LIBS) $(CFLAGS)

#Drawable.o: Drawable.cpp Drawable.h
#	$(CXX) -c $(LIBS) $(CFLAGS) Drawable.cpp

#Collider.o: Collider.cpp Collider.h iRect.h
#	$(CXX) -c $(LIBS) $(CFLAGS) Collider.cpp

#JShader.o: JShader.cpp JShader.h ShaderProgram.o
#	$(CXX) -c $(LIBS) $(CFLAGS) JShader.cpp

#ShaderProgram.o: ShaderProgram.cpp ShaderProgram.h
#	$(CXX) -c $(LIBS) $(CFLAGS) ShaderProgram.cpp

#clean:
#	rm -rf *.o 3dTest
