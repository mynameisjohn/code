#include "Obstacle.h"

Obstacle::Obstacle(){
	colorOsc=0.f;
}

void Obstacle::update(){
   std::vector<Drawable>::iterator drIt;
	float color = 0.5f + 0.5f*sin(colorOsc);
	colorOsc += 0.05f;
   for (drIt=mDrawables.begin(); drIt!=mDrawables.end(); drIt++)
		drIt->setColor(vec3(color, 1.f-color, 0.5f*color));
}
