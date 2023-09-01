#pragma once
#ifndef EDITH
#define EDITH
#define _CRT_SECURE_NO_WARNINGS
#include "linkedList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CV_IGNORE_DEBUG_BUILD_GUARD

FrameNode* findFrame(FrameNode* head, char* name);
void freeList(FrameNode** head);
void printMenu();
void addNode(FrameNode** head, FrameNode* newNode);
void removeFrame(FrameNode** head, char* name);
void changeIndex(FrameNode** head, char* name, int index);
void changeDuration(FrameNode** head, char* name, int duration);
void changeAllDuration(FrameNode** head, int duration);

#endif // !EDITH