CXX = g++
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm -lGL -lGLU -lGLEW 
CFLAGS = -O1 -std=gnu++0x

all: helloGL

helloGL: ShaderProgram.o JShader.o Drawable.o BaseFunc.o main.cpp
	$(CXX) ShaderProgram.o JShader.o Drawable.o Player.o NPC.o BaseFunc.o main.cpp $(LIBS) $(CFLAGS) -o helloGL

BaseFunc.o: BaseFunc.cpp BaseFunc.h
	$(CXX) -c BaseFunc.cpp $(LIBS) $(CFLAGS)

Player.o: Player.cpp Player.h Drawable.o
	$(CXX) -c Player.cpp $(LIBS) $(CFLAGS)

NPC.o: NPC.cpp NPC.h Drawable.o
	$(CXX) -c NPC.cpp $(LIBS) $(CFLAGS)

Drawable.o: Drawable.cpp Drawable.h
	$(CXX) -c $(LIBS) $(CFLAGS) Drawable.cpp

JShader.o: JShader.cpp JShader.h ShaderProgram.cpp ShaderProgram.h
	$(CXX) -c $(LIBS) $(CFLAGS) JShader.cpp

ShaderProgram.o: ShaderProgram.cpp ShaderProgram.h
	$(CXX) -c $(LIBS) $(CFLAGS) ShaderProgram.cpp

clean:
	rm -rf *.o helloGL
