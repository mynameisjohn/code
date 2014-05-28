#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <SDL2/SDL.h>

int main(){
	std::ifstream in;
	in.open("square.geom");
	if (!in.good())
		return -1;
	std::string str;
	std::getline(in, str);
	int nVert = std::stoi(str);
	float vertices [nVert * 2];
	std::cout << nVert << std::endl;

	for (int i=0; i<nVert; i++){
		std::getline(in, str, ' ');
		vertices[i*2]=std::stof(str);
		std::getline(in, str, ' ');
      vertices[i*2+1]=std::stof(str);
	}

	for (int i=0; i<nVert*2; i++)
		std::cout << vertices[i] << std::endl;

	int indices [nVert];

	for (int i=0; i<nVert; i++){
      std::getline(in, str, ' ');
      indices[i]=std::stoi(str);
	}

	for (int i=0; i<nVert; i++)
      std::cout << indices[i] << std::endl;

	std::getline(in, str);
	std::getline(in, str);

	int nSubCol = std::stoi(str);

	std::cout << nSubCol << std::endl;
	
	SDL_Rect top;
	std::getline(in, str, ' ');
	top.x=std::stoi(str);
   
	std::getline(in, str, ' ');
   top.y=std::stoi(str);

   std::getline(in, str, ' ');
   top.w=std::stoi(str);

   std::getline(in, str, ' ');
   top.h=std::stoi(str);

	std::cout << top.x << " " << top.y << " " << top.w << " " << top.h << std::endl;

	std::vector<SDL_Rect> subCol;

	for (int i=0; i<nSubCol; i++){
		SDL_Rect tmp;
	   std::getline(in, str, ' ');
		tmp.x=std::stoi(str);

		std::getline(in, str, ' ');
		tmp.y=std::stoi(str);

		std::getline(in, str, ' ');
		tmp.w=std::stoi(str);

		std::getline(in, str, ' ');
		tmp.h=std::stoi(str);
		
		subCol.push_back(tmp);
	}
	
	return 1;
}
