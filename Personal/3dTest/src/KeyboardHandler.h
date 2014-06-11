#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <stdio.h>

class KeyboardHandler{
public:
	KeyboardHandler(){
	   for (int i=0; i<256; i++)
			keyState[i]=false;
	}

	inline int getKeyState(int key){
		if (key>0 && key<255)
			return keyState[key];
	}

	//just toggles for now	
	inline void handleKey(int key){
		if (key>0 && key<255)
			keyState[key] = !keyState[key];
	}

private:
	bool keyState[256];
};

#endif
