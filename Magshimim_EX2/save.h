#pragma once
#ifndef SAVEH
#define SAVEH
#define _CRT_SECURE_NO_WARNINGS
#include "linkedList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void saveProject(FrameNode* head, char* path);
char* toString(int num);
int toInt(char* str);
FrameNode* loadProject(char* path);
#endif // !SAVEH