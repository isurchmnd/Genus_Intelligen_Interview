#pragma once

struct Node
{
	int range_min;
	int range_max;
};

extern void baseFunction();
extern void processInput(int input);
extern Node makeNode(int min, int max);