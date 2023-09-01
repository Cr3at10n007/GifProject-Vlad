#ifndef LINKEDLISTH
#define LINKEDLISTH
#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE !FALSE
#define STR_LEN 200
// Frame struct
typedef struct Frame
{
	char*		name;
	unsigned int	duration;
	char*		path;  
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

Frame* createFrame();
FrameNode* createNode();


#endif
