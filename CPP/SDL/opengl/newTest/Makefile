CXX = g++
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm -lGL -lGLU -lGLEW 

all: helloGL

helloGL: ShaderProgram.o JShader.o Drawable.o main.cpp
	$(CXX) ShaderProgram.o JShader.o Drawable.o main.cpp $(LIBS) -o helloGL

#BaseFunc.o: BaseFunc.cpp BaseFunc.h
#	$(CXX) -c BaseFunc.cpp $(LIBS)

Drawable.o: Drawable.cpp Drawable.h
	$(CXX) -c $(LIBS) Drawable.cpp

JShader.o: JShader.cpp JShader.h ShaderProgram.cpp ShaderProgram.h
	$(CXX) -c $(LIBS) JShader.cpp

ShaderProgram.o: ShaderProgram.cpp ShaderProgram.h
	$(CXX) -c $(LIBS) ShaderProgram.cpp

clean:
	rm -rf *.o helloGL
