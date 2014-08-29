#ifndef LEVEL_H
#define LEVEL_H

#include "JShader.h"
#include "Population.h"
#include "Geom.h"

void initPlayer(glm::mat4 MV, vec3 color, JShader& shader, Player * playerPtr);
Obstacle initObstacle(glm::mat4 MV, vec3 color, JShader& shader);
ActiveEnt initAe(glm::mat4 MV, vec3 color, JShader& shader);
Obstacle initWall(glm::mat4 MV, vec3 color, JShader& shader);
std::unique_ptr<Population> initLevel(JShader& shader);

#endif
