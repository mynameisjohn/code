#include "baseFunc.h"
#include "SDLincludes.h"

int main(int argc, char ** argv){
	SDL_Window mWindow;
	SDL_GLContext mContext;
	if (!init(mWindow, mContext)){
		printf("failed to initialize\n");
		return -1;
	}

	bool quit = false;
	SDL_Event e;
	SDL_StartTextInput();

	while (!quit){
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT)
				quit = true;
			else if (e.type == SDL_TEXTINPUT){
				int x = 0, y = 0;
				SDL_GetMouseState(&x, &y);
				handleKeys(e.text.text[0], x, y);
			}
		}
		render();
		SDL_GL_SwapWindow(mWindow);
	}
	SDL_StopTextInput();
	close(mWindow);
	return 0;
}
