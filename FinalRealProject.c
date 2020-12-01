#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define BOOL_LEN 5		// boolean(yes or no) length
#define DATE_LEN 15		// Date string length
#define JOB_LEN 15		// Job string length
#define NAME_LEN 25		// Name string length
#define ORG_LEN 35		// Organization string length 
#define RECORD_NUM 30	// the number of registration data

typedef struct _data {
	int tagNum;
	char date[DATE_LEN];
	char fee_paid[BOOL_LEN];
	char name[NAME_LEN];
	int age;
	char organization[ORG_LEN];
	char job[JOB_LEN];
} Data;

typedef struct _node {
	Data dat;
	struct _node* next;
} Node;

/**** Print functions ****/
void PrintDataNode(Data dt);
void PrintStructArray(Data* dt);
void PrintListNode(Node* node);
void PrintLinkedList(Node* head);

/**** Setup functions ****/
int StoreIntoStructArray(FILE* file, Data* dt);
void StoreIntoLinkedList(FILE* file, Node* head);

/**** Search, Reorganize functions ****/
int SearchNameFromStructArray(Data dt, char* name);
int SearchNameFromLinkedList(Node* node, char* name);
int SearchUnivFromStructArray(Data dt, char* univ);
int SearchUnivFromLinkedList(Node* head, char* univ);
void SortArrayInTag(Data* dt);
void CreateSortedLinkedList(Node* head, Data* dt);
void SelectionSortInAge(Data* dt);
int StoreSortedDataToFile(FILE* file, Data* dt);

/**** Update functions ****/
void RemoveNameFromStructArray(Data* dt, char* name);
void RemoveNameFromLinkedList(Node* head, char* name);
void InsertPaikIntoStructArray(Data* dt);
void InsertPaikIntoLinkedList(Node* head, Data* insert);
int CalCheckSum(FILE* file, Data* dt);

int main(void)
{
	/******************************************* Setup *******************************************/
	printf("\n========================================== Setup  ==========================================\n\n");

	// Read a text file registration.txt
	FILE* fp = fopen("C:\\registration.txt", "rt");
	if (fp == NULL)
	{
		printf("This file can't open!(registration.txt)\n");
		exit(0);
	}

	// Store the data in a struct array
	printf("********** Store the data into struct array **********\n");
	Data data[RECORD_NUM];
	memset(data, 0, sizeof(data));

	int res = StoreIntoStructArray(fp, data);
	if (res == 1)
		printf("Storing into struct array is successful!\n");
	else if (res == -1)
		printf("Storing into struct array is not successful!\n");
	printf("\n");

	// Close the file and reopen the file 
	fclose(fp);
	fp = fopen("C:\\registration.txt", "rt");

	// Store the data in a linkedlist
	printf("********** Store the data into linkedlist **********\n");
	Node* head = (Node*)malloc(sizeof(Node));
	if (head == (Node*)NULL)
	{
		printf("Malloc Failed!\n");
		exit(1);
	}
	StoreIntoLinkedList(fp, head);
	printf("Store successful! Check whether storing successful or not.\n");
	printf("\n");

	/******************************************* Search/Reorganize *******************************************/
	printf("\n========================================== Search/Reorganize  ==========================================\n\n");

	// Search for "Choi" in the array
	printf("********** Search for \"Choi\" from the array **********\n");
	for (int i = 0; i < RECORD_NUM; i++)
	{
		int srcVal = SearchNameFromStructArray(data[i], "Choi");
		if (srcVal == 1)
			PrintDataNode(data[i]);
		else if (srcVal == -1)
			continue;
	}
	printf("\n");

	// Search for "Choi" in the linkedlist
	printf("********** Search for \"Choi\" from the linkedlist **********\n");
	Node* pptr = head->next;
	while (pptr != NULL)
	{
		int srcVal = SearchNameFromLinkedList(pptr, "Choi");
		if (srcVal == 1)
		{
			PrintListNode(pptr);
			pptr = pptr->next;
		}
		else if (srcVal == -1)
			pptr = pptr->next;
	}
	printf("\n");

	// Search for "Gachon University" from the array
	printf("********** Search for \"Gachon University\" from the array **********\n");
	for (int i = 0; i < RECORD_NUM; i++)
	{
		int srcVal = SearchUnivFromStructArray(data[i], "Gachon University");
		if (srcVal == 1)
			PrintDataNode(data[i]);
		else if (srcVal == -1)
			continue;
	}
	printf("\n");

	// Search for all from Gachon University in the linkedlist
	printf("********** Search for \"Gachon University\" from the linkedlist **********\n");
	Node* pptr2 = head->next;
	while (pptr2 != NULL)
	{
		int srcVal = SearchUnivFromLinkedList(pptr2, "Gachon University");
		if (srcVal == 1)
		{
			PrintListNode(pptr2);
			pptr2 = pptr2->next;
		}
		else if (srcVal == -1)
			pptr2 = pptr2->next;
	}
	printf("\n");

	// Sort the data in the array in tag# order
	printf("********** Sort the data in the array in tag# order **********\n");
	printf("Sorting the data in the array in tag# order....\n");
	SortArrayInTag(data);
	printf("Sorting is successful. Check the sorted data!\n\n");
	PrintStructArray(data);

	// Create a linkedlist using the sorted data
	printf("********** Create a linkedlist using the sorted data **********\n");
	Node* newhead = (Node*)malloc(sizeof(Node));
	CreateSortedLinkedList(newhead, data);
	printf("Create successful! Check whether creating successful or not.\n\n");
	PrintLinkedList(newhead);

	// Sort the data in the array in age group order (selection sort)
	printf("********** Sort the data in the array in age group order (selection sort) **********\n");
	printf("Sorting using selection sort...\n");
	SelectionSortInAge(data);
	printf("Sorting is successful. Check the sorted data!\n\n");
	PrintStructArray(data);

	// Write the sorted data to a text file
	printf("********** Write the sorted data to a text file **********\n");
	FILE* newFile = fopen("C:\\sorted.txt", "wt");
	int storedVal = StoreSortedDataToFile(newFile, data);
	if (storedVal == 1)
		printf("Store successful. Check the sorted.txt file!\n");
	else if (storedVal == -1)
		printf("Store unsuccessful. Please try again!\n");
	printf("\n");

	/******************************************* Update *******************************************/
	printf("\n========================================== Update  ==========================================\n\n");

	// Remove all "Choi" data from the array (fill the memory)
	printf("********** Remove all \"Choi\" from the array **********\n");
	RemoveNameFromStructArray(data, "Choi");
	printf("Remove successful. Check the array again!\n\n");
	PrintStructArray(data);
	printf("\n");

	// Remove all "Choi" data from the linkedlist
	printf("********** Remove all \"Choi\" from the linkedlist **********\n");
	RemoveNameFromLinkedList(newhead, "Choi");
	printf("Remove successful. Check the linkedlist again!\n\n");
	PrintLinkedList(newhead);
	printf("\n");

	// Insert "Paik" into the array (tag# sorted order)
	printf("********** Insert \"Paik\" into the array **********\n");
	printf("First, sort the array in tag#\n");
	SortArrayInTag(data);
	printf("Inserting...\n");
	InsertPaikIntoStructArray(data);
	printf("Insert successful. Check the array again!\n\n");
	PrintStructArray(data);
	printf("\n");

	// Insert "Paik" into the linkedlist (sorted order)
	printf("********** Insert \"Paik\" into the linkedlist **********\n");
	printf("Inserting...\n");
	InsertPaikIntoLinkedList(newhead, &data[29]);
	printf("Insert successful. Check the linkedlist again!\n\n");
	PrintLinkedList(newhead);
	printf("\n");

	// close the file variable and reopen the file
	fclose(fp);
	fp = fopen("C:\\registration.txt", "rt");

	// Confirm that original data and copied data are the same or not
	printf("********** Confirm that the two data's checksum ar the same or not **********\n");

	int checkVal = CalCheckSum(fp, data);
	if (checkVal == 1)
		printf("The original data is same with update data!\n");
	else if (checkVal == 0)
		printf("The original data is different from update data!\n");
	printf("\n");

	// Close the file variables, free and finish the program 
	printf("All tests are over!! Thank you.\n");

	fclose(fp);
	fclose(newFile);
	free(head);
	free(newhead);
	return 0;
}

/******************************************* Print functions *******************************************/

/*
	Input: Data struct array's one element you want to print
	Output: Print the element's information

	This function displays the element's information.
*/
void PrintDataNode(Data dt)
{
	printf("Tag#: %d\n", dt.tagNum);
	printf("Date Registered: %s\n", dt.date);
	printf("Fee-paid: %s\n", dt.fee_paid);
	printf("Name: %s\n", dt.name);
	printf("Age: %d\n", dt.age);
	printf("Organizaton: %s\n", dt.organization);
	printf("Job: %s\n", dt.job);
}

/*
	Input: Data struct array
	Output: Print the struct array

	This function displays the struct array.
	If the tagNum is -1, then continue the loop.
*/
void PrintStructArray(Data* dt)
{
	for (int i = 0; i < RECORD_NUM; i++)
	{
		if (dt[i].tagNum == -1)
			continue;

		PrintDataNode(dt[i]);
	}
}

/*
	Input: One pointer of node in the linkedlist
	Output: Print the node's information

	This function displays the node's information.
*/
void PrintListNode(Node* node)
{
	printf("Tag#: %d\n", (node->dat).tagNum);
	printf("Date Registered: %s\n", (node->dat).date);
	printf("Fee-paid: %s\n", (node->dat).fee_paid);
	printf("Name: %s\n", (node->dat).name);
	printf("Age: %d\n", (node->dat).age);
	printf("Organizaton: %s\n", (node->dat).organization);
	printf("Job: %s\n", (node->dat).job);
}

/*
	Input: head of the linkedlist
	Output: Print all elements of linkedlist

	This function displays all elements of linkedlist.
*/
void PrintLinkedList(Node* head)
{
	Node* ptr = head->next;
	while (ptr != NULL)
	{
		PrintListNode(ptr);
		ptr = ptr->next;
	}
}

/******************************************* Setup functions *******************************************/

/*
	Input: File variable and Data struct array
	Output: No output

	This function stores all data of file into the struct array.
*/
int StoreIntoStructArray(FILE* file, Data* dt)
{
	char buffer[200];
	int idx = 0;

	while (fgets(buffer, sizeof(buffer), file) != NULL)		// read each one line
	{
		// Store into struct array 
		int ref = sscanf(buffer, "%d/%[^/]/%[^/]/%[^/]/%d/%[^/]/%[^/]",
			&dt[idx].tagNum, dt[idx].date, dt[idx].fee_paid,
			dt[idx].name, &dt[idx].age, dt[idx].organization, dt[idx].job);

		idx++;
	}

	if (idx == RECORD_NUM)
		return 1;
	else
		return -1;
}

/*
	Input: File variable and head of linkedlist
	Output: No output

	This function stores all data of file onto the linkedlist.
*/
void StoreIntoLinkedList(FILE* file, Node* head)
{
	char buffer[200];
	int count = 0;
	Node* cursor = NULL;

	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		Node* newNode = (Node*)malloc(sizeof(Node));
		if (newNode == (Node*)NULL)		// malloc failed
		{
			printf("Malloc Failed!\n");
			exit(1);
		}
		newNode->next = NULL;

		// Store onto linkedlist
		int ref = sscanf(buffer, "%d/%[^/]/%[^/]/%[^/]/%d/%[^/]/%[^/]",
			&((newNode->dat).tagNum), (newNode->dat).date, (newNode->dat).fee_paid,
			(newNode->dat).name, &((newNode->dat).age), (newNode->dat).organization,
			(newNode->dat).job);

		if (count == 0)	  // first
		{
			head->next = newNode;
			cursor = newNode;
			count++;
		}
		else	// not first
		{
			cursor->next = newNode;
			cursor = cursor->next;
			count++;
		}
	}
}

/******************************************* Search/Reorganize functions *******************************************/

/*
	Input: Data struct array's one element and name you want to search
	Output: If return value is 1, it means "Searching is successful"
			else if return value is -1, it means "Searching is not successful"

	This function searches the name you want to search.
*/
int SearchNameFromStructArray(Data dt, char* name)
{
	char temp_name[NAME_LEN];
	strcpy(temp_name, dt.name);

	char* ptr = strtok(temp_name, " ");
	ptr = strtok(NULL, " ");	// pick the first name

	if (!strcmp(ptr, name))   // found
		return 1;
	else
		return -1;
}

/*
	Input: head of the linkedlist and name you want to search
	Output: If return value is 1, it means "Searching is successful"
			else if return value is -1, it means "Searching is not successful"

	This function searches the name you want to search.
*/
int SearchNameFromLinkedList(Node* head, char* name)
{
	Node* curr = head;

	char temp_name[NAME_LEN];
	strcpy(temp_name, (curr->dat).name);

	char* ptr = strtok(temp_name, " ");
	ptr = strtok(NULL, " ");

	if (!strcmp(ptr, name))
		return 1;
	else
		return -1;
}

/*
	Input: Data struct array's one element and university name
	Output: If return value is 1, it means "Searching is successful"
			else if return value is -1, it means "Searching is not successful"

	This function searches the university name you want to search.
*/
int SearchUnivFromStructArray(Data dt, char* univ)
{
	if (!strcmp(dt.organization, univ))   // found
		return 1;
	else
		return -1;
}

/*
	Input: head of the linkedlist and university name
	Output: If return value is 1, it means "Searching is successful"
			else if return value is -1, it means "Searching is not successful"

	This function searches the university name you want to search.
*/
int SearchUnivFromLinkedList(Node* head, char* univ)
{
	Node* curr = head;

	if (!strcmp((curr->dat).organization, univ))
		return 1;
	else
		return -1;
}

/*
	Input: Data struct array
	Output: No output

	This function sorts the array in tag# order.
	(Bubble Sort)
*/
void SortArrayInTag(Data* dt)
{
	Data temp;	// variable for swaping

	for (int i = 0; i < RECORD_NUM - 1; i++)
	{
		for (int j = 0; j < RECORD_NUM - i - 1; j++)
		{
			if (dt[j].tagNum > dt[j + 1].tagNum)
			{
				temp = dt[j];
				dt[j] = dt[j + 1];
				dt[j + 1] = temp;
			}
		}
	}
}

/*
	Input: head of the linkedlist and data struct array
	Output: No output

	This function creates the new linkedlist by age group ordered data.
*/
void CreateSortedLinkedList(Node* head, Data* dt)
{
	int count = 0;
	Node* cursor = NULL;

	for (int i = 0; i < RECORD_NUM; i++)
	{
		Node* newNode = (Node*)malloc(sizeof(Node));
		if (newNode == (Node*)NULL)
		{
			printf("Malloc failed!\n");
			exit(1);
		}

		newNode->next = NULL;
		(newNode->dat).tagNum = dt[i].tagNum;
		strcpy((newNode->dat).date, dt[i].date);
		strcpy((newNode->dat).fee_paid, dt[i].fee_paid);
		strcpy((newNode->dat).name, dt[i].name);
		(newNode->dat).age = dt[i].age;
		strcpy((newNode->dat).organization, dt[i].organization);
		strcpy((newNode->dat).job, dt[i].job);

		if (count == 0)
		{
			head->next = newNode;
			cursor = newNode;
			count++;
		}
		else
		{
			cursor->next = newNode;
			cursor = cursor->next;
			count++;
		}
	}
}

/*
	Input: Data struct array
	Output: No output

	This function sorts the array in age group order.
	(Selection sort)
*/
void SelectionSortInAge(Data* dt)
{
	int least;
	for (int i = 0; i < RECORD_NUM - 1; i++)
	{
		least = i;
		for (int j = i + 1; j < RECORD_NUM; j++)
		{
			if (dt[j].age < dt[least].age)
				least = j;
		}

		if (i != least)
		{
			Data temp = dt[i];
			dt[i] = dt[least];
			dt[least] = temp;
		}
	}
}

/*
	Input: File variable and Data struct array
	Output: If count is 7, then return 1 --> Store successful!
			else if count is not 7, then return -1 --> Store unsuccessful!

	This function stores the sorted data to new file.
*/
int StoreSortedDataToFile(FILE* file, Data* dt)
{
	int i = 0;
	int cnt = 0;

	for (int a = 10; a != 80; a += 10)
	{
		fprintf(file, "Age from %d to %d\n", a, a + 9);
		fprintf(file, "------------------------------------------------------------------\n");

		while (dt[i].age >= a && dt[i].age < a + 10)
		{
			fprintf(file, "%d/%s/%s/%s/%d/%s/%s", dt[i].tagNum, dt[i].date, dt[i].fee_paid, dt[i].name,
				dt[i].age, dt[i].organization, dt[i].job);

			i++;
		}
		fprintf(file, "\n");
		cnt++;
	}

	if (cnt == 7)
		return 1;
	else
		return -1;
}

/******************************************* Update functions *******************************************/

/*
	Input: Data struct array and name you want to search
	Output: No output

	This function removes all "Choi" data from the array.
	If you remove the data, you must fill the memory.
*/
void RemoveNameFromStructArray(Data* dt, char* name)
{
	int total = RECORD_NUM;

	for (int i = 0; i < RECORD_NUM; i++)
	{
		char temp_name[NAME_LEN];
		strcpy(temp_name, dt[i].name);

		char* ptr = strtok(temp_name, " ");
		ptr = strtok(NULL, " ");   // pick the first name

		if (!strcmp(ptr, name))
		{
			for (int j = i; j < total - 1; j++)
				dt[j] = dt[j + 1];

			total--;
		}
	}

	// Fill the memory
	for (int i = total + 1; i <= RECORD_NUM; i++)
	{
		dt[i - 1].tagNum = -1;
		strcpy(dt[i - 1].date, "");
		strcpy(dt[i - 1].fee_paid, "");
		strcpy(dt[i - 1].name, "");
		dt[i - 1].age = -1;
		strcpy(dt[i - 1].organization, "");
		strcpy(dt[i - 1].job, "");
	}
}

/*
   Input: The head of linked list and name you want to search
   Output: No output (link the head of linked list except for delete node)

   This function removes the name you want to search onto the linked list.
*/
void RemoveNameFromLinkedList(Node* head, char* name)
{
	Node* prev = head;
	Node* curr = head->next;

	while (curr != NULL)
	{
		char temp_name[NAME_LEN];
		strcpy(temp_name, (curr->dat).name);

		char* ptr = strtok(temp_name, " ");
		ptr = strtok(NULL, " ");

		if (!strcmp(ptr, name))
			prev->next = curr->next;
		else
			prev = curr;

		curr = curr->next;
	}
}

/*
	Input: Data struct array
	Output: No output

	This function inserts "Paik" first name information
	into the struct array.
*/

void InsertPaikIntoStructArray(Data* dt) {
	int count = 0;
	int success = 0;

	Data temp;
	temp.tagNum = 31;
	strcpy(temp.date, "2020-11-03");
	strcpy(temp.fee_paid, "yes");
	strcpy(temp.name, "Jongwon Paik");
	temp.age = 52;
	strcpy(temp.organization, "Theborn");
	strcpy(temp.job, "CEO");

	for (int i = 0; i < RECORD_NUM; i++) {
		if (dt[i].tagNum == -1) {
			count++;
			continue;
		}
		if (temp.tagNum < dt[i].tagNum) {
			for (int j = count - 1; j < i - 1; j++) {
				dt[j] = dt[j + 1];
			}
			dt[i - 1] = temp;
			success = 1;
			break;
		}
	}

	if (success == 0) {
		for (int i = count - 1; i < RECORD_NUM; i++) {
			dt[i] = dt[i + 1];
		}

		dt[RECORD_NUM - 1] = temp;
	}
}

/*
	Input: head of the linked list and insert the data of data struct array's 29th element
	Output: No output

	This function inserts the data struct array's 29th element into the linked list.
	29th element -> Jongwon Paik (This data is inserted in "InsertPaikIntoStructArray")
	Insert the data into the linkedlist too.
*/
void InsertPaikIntoLinkedList(Node* head, Data* insert)
{
	Node* prev = head;
	Node* p = head->next;
	Node* new_node;
	int found = 0;

	while (p) {
		if ((p->dat).tagNum > insert->tagNum) {
			found = 1;
			break;
		}
		prev = p;
		p = p->next;
	}

	if ((prev->dat).tagNum < insert->tagNum) {
		new_node = (Node*)malloc(sizeof(Node));
		if (new_node == (Node*)NULL) {
			printf("Malloc failed");
		}

		new_node->dat = *insert;
		new_node->next = NULL;
		prev->next = new_node;
	}

	if (found) {
		new_node = (Node*)malloc(sizeof(Node));
		if (new_node == (Node*)NULL) {
			printf("Malloc failed");
		}
		new_node->dat = *insert;
		prev->next = new_node;
		new_node->next = p;
	}
}

/*
	Input: File variable and data struct array
	Output: if function returns 1, it means the two data are the same
			else if function returns 0, it means the two data are not same

	This function calculates the original and copied data's checksum.
	And, confirm that the two data are the same or not.
*/
int CalCheckSum(FILE* file, Data* dt)
{
	// Copy struct array variable
	Data temp[RECORD_NUM];

	int tagNum;
	char date[DATE_LEN];
	char fee_paid[BOOL_LEN];
	char name[NAME_LEN];
	int age;
	char organization[ORG_LEN];
	char job[JOB_LEN];
	char tag[10];
	char ages[3];

	// Copy
	for (int i = 0; i < RECORD_NUM; i++)
	{
		temp[i].tagNum = dt[i].tagNum;
		strcpy(temp[i].date, dt[i].date);
		strcpy(temp[i].fee_paid, dt[i].fee_paid);
		strcpy(temp[i].name, dt[i].name);
		temp[i].age = dt[i].age;
		strcpy(temp[i].organization, dt[i].organization);
		strcpy(temp[i].job, dt[i].job);
	}

	unsigned char org_checkSum = 0;
	unsigned char copy_checkSum = 0;
	char c;

	// Original data checksum
	int idx = 0;
	int j = 0;
	for (int i = 0; i < RECORD_NUM; i++) {
		sprintf(tag, "%d", dt[i].tagNum);
		while (tag[idx] != NULL) {
			c = tag[idx];
			org_checkSum = c ^ org_checkSum;
			idx++;
		}
		for (j = 0; j < DATE_LEN; j++) {
			c = dt[i].date[j];
			if (c == '-')
				continue;
			org_checkSum = c ^ org_checkSum;
		}
		for (j = 0; j < BOOL_LEN; j++) {
			c = dt[i].fee_paid[j];
			org_checkSum = c ^ org_checkSum;
		}
		for (j = 0; j < NAME_LEN; j++) {
			c = dt[i].name[j];
			if (c == ' ')
				continue;
			org_checkSum = c ^ org_checkSum;
		}
		sprintf(ages, "%d", dt[i].age);
		while (ages[idx] != NULL) {
			c = ages[idx];
			org_checkSum = c ^ org_checkSum;
			idx++;
		}
		for (j = 0; j < ORG_LEN; j++) {
			c = dt[i].organization[j];
			if (c == ' ')
				continue;
			org_checkSum = c ^ org_checkSum;
		}
		for (j = 0; j < JOB_LEN; j++) {
			c = dt[i].job[j];
			org_checkSum = c ^ org_checkSum;
		}
	}

	// Copy data checksum
	idx = 0;
	j = 0;
	for (int i = 0; i < RECORD_NUM; i++) {
		sprintf(tag, "%d", temp[i].tagNum);
		while (tag[idx] != NULL) {
			c = tag[idx];
			copy_checkSum = c ^ copy_checkSum;
			idx++;
		}
		for (j = 0; j < DATE_LEN; j++) {
			c = temp[i].date[j];
			if (c == '-')
				continue;
			copy_checkSum = c ^ copy_checkSum;
		}
		for (j = 0; j < BOOL_LEN; j++) {
			c = temp[i].fee_paid[j];
			copy_checkSum = c ^ copy_checkSum;
		}
		for (j = 0; j < NAME_LEN; j++) {
			c = temp[i].name[j];
			if (c == ' ')
				continue;
			copy_checkSum = c ^ copy_checkSum;
		}
		sprintf(ages, "%d", temp[i].age);
		while (ages[idx] != NULL) {
			c = ages[idx];
			copy_checkSum = c ^ copy_checkSum;
			idx++;
		}
		for (j = 0; j < ORG_LEN; j++) {
			c = temp[i].organization[j];
			if (c == ' ')
				continue;
			copy_checkSum = c ^ copy_checkSum;
		}
		for (j = 0; j < JOB_LEN; j++) {
			c = temp[i].job[j];
			copy_checkSum = c ^ copy_checkSum;
		}
	}

	if (org_checkSum == copy_checkSum)
		return 1;
	else
		return 0;
}