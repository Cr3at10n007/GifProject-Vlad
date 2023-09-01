#include "save.h"

char* toString(int num)
{
	char* str = (char*)malloc(sizeof(char));
	int rem = 0;
	int len = 0;
	int n = num;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	str = (char*)realloc(str, (len+1) * sizeof(char));
	for (int i = 0; i < len; i++)
	{
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
	return str;
}

int toInt(char* str)
{
	int len = strlen(str);
	int num = 0;
	int digit = 0;
	for (int i = 0; i < len; i++)
	{
		int digit = str[i] - '0';
		num = num * 10 + digit;
	}

	return num;
}

void saveProject(FrameNode* head, char* path)
{
	FILE* project = fopen(path, "w");
	FrameNode* curr = head;
	char* duration = NULL;
	if (project == NULL)
	{
		printf("Error! cannot create file\n");
		return; // exit the function
	}
	while (curr)
	{
		duration = toString(curr->frame->duration);
		fwrite(curr->frame->path, 1, strlen(curr->frame->path), project);
		fputc(',', project);
		fwrite(duration, 1, strlen(duration), project);
		fputc(',', project);
		fwrite(curr->frame->name, 1, strlen(curr->frame->name), project);
		fputc('\n', project);
		curr = curr->next;
	}
	free(duration);
	fclose(project);
}

FrameNode* loadProject(char* projectPath)
{
	FILE* project = fopen(projectPath, "r");
	FrameNode* head = NULL;
	FrameNode* newNode = NULL;
	char* path;
	char* name;
	char* duration;
	int offset = 0;
	int fileLen = 0;
	char ch;
	if (project == NULL)
	{
		printf("Error! Cannot open file. Creating a new project.\n");
		return NULL;
	}
	while ((ch = fgetc(project)) != EOF)
	{
		if (ch == '\n')
			fileLen++;
	}
	fseek(project, 0, SEEK_SET);

	while ((fgetc(project) != EOF))
	{
		fseek(project, offset, SEEK_SET);
		path = (char*)malloc(sizeof(char) * STR_LEN);
		name = (char*)malloc(sizeof(char) * STR_LEN);
		duration = (char*)malloc(sizeof(char) * STR_LEN);

		fgets(path, STR_LEN, project);
		path[strcspn(path, ",")] = 0;
		path = (char*)realloc(path, strlen(path) + 1);
		offset += strlen(path) + 1;
		fseek(project, offset, SEEK_SET);

		fgets(duration, STR_LEN, project);
		duration[strcspn(duration, ",")] = 0;
		duration = (char*)realloc(duration, strlen(duration) + 1);
		offset += strlen(duration) + 1;
		fseek(project, offset, SEEK_SET);

		fgets(name, STR_LEN, project);
		name[strcspn(name, "\n")] = 0;
		name = (char*)realloc(name, strlen(name) + 1);
		offset += strlen(name) + 1;
		fseek(project, offset, SEEK_SET);

		newNode = createNode();
		newNode->frame->duration = toInt(duration);
		newNode->frame->name = name;
		newNode->frame->path = path;
		addNode(&head, newNode);
		fgetc(project);
		offset += 1;

	}
	fclose(project);
	return head;
}
