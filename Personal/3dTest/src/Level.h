#ifndef LEVEL_H
#define LEVEL_H

#include "JShader.h"
#include "Drawable.h"
#include "Population.h"
#include "Geom.h"

Drawable initPlayer(glm::mat4 MV, JShader& shader, Population& pop);
Drawable initObstacle(glm::mat4 MV, JShader& shader, Population& pop);
Drawable initAe(glm::mat4 MV, JShader& shader, Population& pop);
std::vector<Drawable> initLevel(JShader& shader, Population& pop);

#endif
