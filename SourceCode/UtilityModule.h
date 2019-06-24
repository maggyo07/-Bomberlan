#include "GameHead.h"

Node Dijkstra(float start_object_x,float start_object_y,float goal_object_x,float goal_object_y,bool bom_hit_test,bool breakable_block_hit_test);

int GetRandom(int min,int max);

void HitTestInformation(float x,float y,bool *up,bool *down,bool *left,bool *right,bool bom_hit_test,bool breakable_block_hit_test);

void MovableTargetRandomByMove(float *vx,float *vy,float speed_power,bool up,bool down,bool left,bool right);