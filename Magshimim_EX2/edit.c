#include "edit.h"
/*
Finds a frame in the list
input: the head, and the name of the frame
output: the frame
*/
FrameNode* findFrame(FrameNode* head, char* name)
{
	while (head)
	{
		if (strcmp(head->frame->name, name) == 0)//if the name is in the list
		{
			return head;
		}
		else
		{
			head = head->next;
		}
	}
	printf("The frame was not found\n\n");
	return NULL;//frame not found
}
/*
Frees the entire list
input: a pointer to the head
output: none
*/
void freeList(FrameNode** head)
{
	if ((*head)->next)
	{
		freeList(&((*head)->next));
		free((*head)->frame);
		free((*head)->next);
	}
}

/*
Prints the menu
input:none
output:none
*/
void printMenu()
{
	printf("What would you like to do?\n");
	printf("[0] Exit\n");
	printf("[1] Add new Frame\n");
	printf("[2] Remove a Frame\n");
	printf("[3] Change frame index\n");
	printf("[4] Change frame duration\n");
	printf("[5] Change duration of all frames\n");
	printf("[6] List frames\n");
	printf("[7] Play movie!\n");
	printf("[8] Save project\n");
}

/*
adds a node to the list
input: a pointer to the head and the new node
output: none
*/
void addNode(FrameNode** head, FrameNode* newNode)
{
	if ((fopen(newNode->frame->path, "r")) == NULL)//if file doesn't exist
	{
		printf("Can't find file! Frame will not be added\n");
	}
	else if (*head == NULL)//if there's no head, the new node will be the head
	{
		*head = newNode;
	}
	else
	{
		FrameNode* curr = *head;
		if (strcmp(curr->frame->name, newNode->frame->name) == 0)//incase the head has the same name as newNode
		{
			printf("The name is already taken, please enter another name\n");
			//taking a new name and trying again
			fgets(newNode->frame->name, STR_LEN, stdin);
			newNode->frame->name[strcspn(newNode->frame->name, "\n")] = 0;
			newNode->frame->name = (char*)realloc(newNode->frame->name,sizeof(char) * (strlen(newNode->frame->name) + 1));
			addNode(head, newNode);
		}
		else 
		{
			while (curr->next)//check if the rest of the list has the same name as newNode
			{
				if (strcmp(curr->frame->name, newNode->frame->name) == 0)
				{
					printf("The name is already taken, please enter another name\n");
					//taking a new name and trying again
					fgets(newNode->frame->name, STR_LEN, stdin);
					newNode->frame->name[strcspn(newNode->frame->name, "\n")] = 0;
					newNode->frame->name = (char*)realloc(newNode->frame->name, sizeof(char) * (strlen(newNode->frame->name) + 1));
					addNode(head, newNode);
				}
				curr = curr->next;
			}
			curr->next = newNode;//add the node to the end of the list
		}
	}
}


/*
Removes a frame from the list
input: a pointer to the head and it's name
output: none
*/
void removeFrame(FrameNode** head, char* name)
{
	FrameNode* curr = *head;
	if (!curr)//if the list is blank
	{
		printf("The frame was not found\n\n");
		return NULL;//Exit the function
	}
	if (curr && strcmp(curr->frame->name, name) == 0)//if the head exists and the name of the head is the name to be removed
	{
		*head = (*head)->next;
		free(curr->frame);
		free(curr);
	}
	else
	{
		while (curr->next)//check the rest of the list
		{
			if (strcmp(curr->next->frame->name, name) == 0)
			{
				FrameNode* temp = curr->next;
				curr->next = curr->next->next;
				free(temp->frame);
				free(temp);
				return NULL;  // Exit the function
			}
			curr = curr->next;
		}
		printf("The frame was not found\n\n");
	}
}

/*
Changes the index of a frame in the list
input: a pointer to the head, the name and the index
output: none
*/
void changeIndex(FrameNode** head, char* name, int index)
{
	FrameNode* changeNode = findFrame(*head, name);
	if (changeNode == NULL)
	{
		return; // no node to change
	}
	int currentIndex = 1;
	int newIndex = 1;
	FrameNode* curr = *head;
	FrameNode* prev = NULL;
	while (curr != NULL && curr != changeNode)
	{
		prev = curr;
		curr = curr->next;
		currentIndex++;
	}
	// If the desired index is the same as the current index, no need to change
	if (currentIndex == index)
	{
		return;
	}
	// Remove the node from its current position
	if (prev == NULL)
	{
		// The node is the head, update head pointer
		*head = changeNode->next;
	}
	else
	{
		prev->next = changeNode->next;
	}
	// Find the new position for the node
	if (index == 1)
	{
		// Place the node at the beginning
		changeNode->next = *head;
		*head = changeNode;
	}
	else
	{
		curr = *head;
		prev = NULL;
		while (curr != NULL && newIndex < index)
		{
			prev = curr;
			curr = curr->next;
			newIndex++;
		}
		if (curr == NULL && newIndex < index)
		{
			// The desired index exceeds the length of the list
			printf("The movie contains only %d frames!\n", newIndex);
			//reverting the changes made 
			if (changeNode->next == *head)
			{
				// if the head was taken out or the list is only one node
				changeNode->next = *head;
				*head = changeNode;
			}
			else
			{
				prev->next = changeNode;
			}
		}
		else
		{
			// Insert the node at the new position
			if (prev == NULL)
			{
				// The node becomes the new head
				changeNode->next = *head;
				*head = changeNode;
			}
			else
			{
				changeNode->next = curr;
				prev->next = changeNode;
			}
		}
	}
}


/*
Changes the duration of a frame in the list
input: a pointer to the head, the name and the duration
output:none
*/
void changeDuration(FrameNode** head, char* name, int duration)
{
	FrameNode* curr = *head;
	FrameNode* changeFrame = findFrame(*head, name);
	if (changeFrame == NULL)
	{
		return NULL;
	}
	while (curr != changeFrame)
	{
		curr = curr->next;
	}
	changeFrame->frame->duration = duration;
}

/*
Changes the duration of all the frames
input: a pointer to the head, int duration
output: none
*/
void changeAllDuration(FrameNode** head, int duration)
{
	FrameNode* curr = *head;
	while (curr)
	{
		curr->frame->duration = duration;
		curr = curr->next;
	}
}
