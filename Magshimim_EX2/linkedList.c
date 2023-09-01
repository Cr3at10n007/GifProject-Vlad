#include "linkedList.h"

/*
Creates a frame
input:none
output: a pointer to a frame
*/
Frame* createFrame()
{
	Frame* frame = (Frame*)malloc(sizeof(Frame));
	frame->duration = 0;
	frame->name = NULL;
	frame->path = NULL;
	return frame;
}

/*
Creates a node
input:none
output: a new node
*/
FrameNode* createNode()
{
	FrameNode* newNode = (FrameNode*)malloc(sizeof(FrameNode));
	newNode->frame = createFrame();
	newNode->next = NULL;
	return newNode;
}

/*
Prints the list
input: the head
output: none
*/
void printList(FrameNode* head)
{
	FrameNode* curr = head;
	printf("                Name            Duration        Path\n");
	while (curr)
	{
		printf("                %s          %d ms          %s\n", curr->frame->name, curr->frame->duration, curr->frame->path);
		curr = curr->next;
	}
}


