/*********************************
* Class: MAGSHIMIM C2			 *
* openCV template      			 *
**********************************/
#define CV_IGNORE_DEBUG_BUILD_GUARD
#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <stdio.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include "view.h"
#include "edit.h"
#include "linkedList.h"
#include "save.h"


enum menuChoices{exitProj, add, deleteFrame, changeindex, changeDur,changeAllDur,list,playVid,save};
enum projChoice{newProj,existingProj};


int main(void)
{
	char* path = (char*)malloc(sizeof(char) * STR_LEN);
	int duration = 0;
	char* name = (char*)malloc(sizeof(char) * STR_LEN);
	int index = 0;
	FrameNode* head = NULL;
	FrameNode* newNode = NULL;
	int choice = 0;
	printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
	do {
		printf("	[0] Create a new project\n	[1] Load existing project\n");
		scanf("%d", &choice);
		getchar();
		switch (choice)
		{
		case newProj:
			printf("Working on a new project.\n");
			break;
		case existingProj:
			printf("Enter the path of the project (including project name):\n");
			fgets(path, STR_LEN, stdin);
			path[strcspn(path, "\n")] = 0;
			path = (char*)realloc(path, sizeof(char) * (strlen(path) + 1));//+1 for the terminating null
			head = loadProject(path);
			if (head != NULL)
			{
				printf("Project loaded successfully\n");
			}
			path=(char*)malloc(sizeof(char)*STR_LEN);
			break;
		default:
			printf("Invalid choice, try again:\n");
			break;
		}
	} while (choice != newProj && choice != existingProj);
	do {
		printMenu();
		scanf("%d", &choice);
		getchar();
		switch (choice)
		{
		case add:
			printf("*** Creating new frame ***\n");
			printf("Please insert frame path:\n");
			fgets(path, STR_LEN, stdin);
			path[strcspn(path, "\n")] = 0;
			path = (char*)realloc(path, (strlen(path) + 1)* sizeof(char));//+1 for the terminating null
			printf("Please insert frame duration(in miliseconds):\n");
			scanf("%d", &duration);
			getchar();
			printf("Please choose a name for that frame:\n");
			fgets(name, STR_LEN, stdin);
			name[strcspn(name, "\n")] = 0;
			name = (char*)realloc(name, sizeof(char) * (strlen(name) + 1));//+1 for the terminating null
			newNode = createNode();
			newNode->frame->duration = duration;
			newNode->frame->name = name;
			newNode->frame->path = path;
			addNode(&head, newNode);
			duration = 0;
			name = (char*)malloc(sizeof(char)*STR_LEN);
			path = (char*)malloc(sizeof(char)*STR_LEN);//resetting the strings
			break;
		case deleteFrame:
			printf("Enter the name of the frame you wish to erase\n");
			fgets(name, STR_LEN, stdin);
			name[strcspn(name, "\n")] = 0;
			removeFrame(&head, name);
			break;
		case changeindex:
			printf("Enter the name of the frame\n");
			fgets(name, STR_LEN, stdin);
			name[strcspn(name, "\n")] = 0;
			printf("Enter the new index in the movie you wish to place the frame\n");
			scanf("%d", &index);
			changeIndex(&head, name, index);
			break;
		case changeDur:
			printf("enter the name of the frame\n");
			fgets(name, STR_LEN, stdin);
			name[strcspn(name, "\n")] = 0;
			printf("Enter the new duration\n");
			scanf("%d", &duration);
			changeDuration(&head, name, duration);
			break;
		case changeAllDur:
			printf("Enter the duration for all frames:\n");
			scanf("%d", &duration);
			changeAllDuration(&head, duration);
			break;
		case list:
			printList(head);
			break;
		case playVid:
			play(head);
			break;
		case save:
			printf("Where to save the project? enter a full path and file name\n");
			fgets(path, STR_LEN, stdin);
			path[strcspn(path, "\n")] = 0;
			path = (char*)realloc(path, sizeof(char) * (strlen(path) + 1));//+1 for the terminating null
			saveProject(head, path);
			break;
		}
	} while (choice != 0);
	return 0;
} 