CXX = g++
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm -lGL -lGLU -lGLEW 

all: helloGL

helloGL: ShaderProgram.o SimpleShader.o main.cpp
	$(CXX) ShaderProgram.o SimpleShader.o main.cpp $(LIBS) -o helloGL

SimpleShader.o: SimpleShader.cpp SimpleShader.h
	$(CXX) -c $(LIBS) SimpleShader.cpp

ShaderProgram.o: ShaderProgram.cpp ShaderProgram.h
	$(CXX) -c $(LIBS) ShaderProgram.cpp

clean:
	rm -rf *.o helloGL
