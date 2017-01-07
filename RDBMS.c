#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Proj4C.h"

			
int counter;
int main(int argc, char* argv[]){

	struct node CSG[101];
	struct node SNAP[101];
	struct node CP[101];
	struct node CDH[101];
	struct node CR[101];
																				
	allocate(CSG);
	allocate(SNAP);
	allocate(CP);
	allocate(CDH);
	allocate(CR);


	/*
		CALLING INSERT
		Read each line induvidually
		Read 1st word in line to determine which array to use
		Insert the correct values in spots while keeping rest blank
	*/

	FILE *ifp;
	ifp = fopen("schemas.txt", "r");

	if(ifp == NULL) {
		printf("Can't open file listed.\n");
		exit(1);
	}
	while(!feof(ifp)) {

		char type[10];

		fscanf(ifp, "%s", type);
		//printf("%s\n", type);

		if(strcmp(type, "CSG") == 0){
			char course[10];
			int studentID;
			char grade[10];
			fscanf(ifp, "%s %d %s", course, &studentID, grade);
			// printf("type- %s", type);
			// printf("    course- %s", course);
			// printf("    studentID- %d", studentID);
			// printf("    grade- %s\n", grade);

			insert(course, studentID, grade, " ", " ", " ", " ", " ", " ", " ", CSG);
		}
		else if(strcmp(type, "SNAP") == 0){
			int studentID;
			char name[20];
			char address[30];
			char phone[10];

			fscanf(ifp, "%d %s %s %s", &studentID, name, address, phone);
			// printf("type- %s", type);
			// printf("    studentID- %d", studentID);
			// printf("    name- %s", name);
			// printf("    address- %s", address);
			// printf("    phone- %s\n", phone);

			insert(" ", studentID, " ", name, address, phone, " ", " ", " ", " ", SNAP);
		}
		else if(strcmp(type, "CP") ==  0){
			char course[10];
			char prereq[10];

			fscanf(ifp, "%s %s", course, prereq);
			// printf("type- %s", type);
			// printf("    course- %s", course);
			// printf("    prereq- %s\n", prereq);

			insert(course, 0, " ", " ", " ", " ", prereq, " ", " ", " ", CP);
		}
		else if(strcmp(type, "CDH") ==  0){
			char course[10];
			char day[3];
			char hour[5];

			fscanf(ifp, "%s %s %s", course, day, hour);
			// printf("type- %s", type);
			// printf("    course- %s", course);
			// printf("    day- %s", day);
			// printf("    hour- %s\n", hour);

			insert(course, 0, " ", " ", " ", " ", " ", day, hour, " ", CDH);
		}
		else if(strcmp(type, "CR") ==  0){
			char course[10];
			char room[25];

			fscanf(ifp, "%s %s", course, room);
			// printf("type- %s", type);
			// printf("    course- %s", course);
			// printf("    room- %s\n", room);

			insert(course, 0, " ", " ", " ", " ", " ", " ", " ", room, CR);
		}
		else{
			printf("Line not formatted correctly\n");
		}

	}//end of while loop to read file

	fclose(ifp);

	FILE *wr;
	wr = fopen("output.txt", "w");

	char* x = gradeOfName("C_Brown", "CS101", CSG, SNAP);
	char* y = gradeOfName("P_Patty", "EE200", CSG, SNAP);
	fprintf(wr, "%s\n", "Grade from student name/course - Example 8.6");
	fprintf(wr, "C_Brown, CS101 - %s\n", x);
	fprintf(wr, "P_Patty, EE200 - %s\n\n", y);

	//char* roomOfName(char* Nin, char* Hin, char* Din, struct node CSG[], struct node SNAP[], struct node CDH[], struct node CR[]);
	char* n = roomOfName("C_Brown", "9AM", "M", CSG, SNAP, CDH, CR);
	fprintf(wr, "%s\n", "Room from student name, day, and time");
	fprintf(wr, "C_Brown, 9AM, M - %s\n", n);


	struct node list2[105];
	for(int i =0; i<105; i++){
		list2[i] = *(struct node*)malloc(sizeof(struct node));
		
	}

	Selection(CSG, 'C', 0, "CS101", list2);		//Testing Selection- Example 8.12
	
	fprintf(wr, "\nSelection Testing- Example 8.12\n\n");
	for(int i=0;i <101; i++){
		if(list2[i].course != NULL)
			fprintf(wr, "%s  %d  %s\n", list2[i].course, list2[i].studentid, list2[i].grade);
	
	}
	

	int* finish =ProjectionInt(list2, 'S');			//Testing Projection- Example 8.13	

	fprintf(wr, "\nProjection Testing- Example 8.13\n\n");
	int i =0;
	while (finish[i] != -1){
		fprintf(wr, "%d\n", finish[i]);
		i++;
	}

	
	struct node list3[105];
	for(int i =0; i<105; i++){
		list3[i] = *(struct node*)malloc(sizeof(struct node));
		list3[i] = *create(" ", 0, " ", " ", " ", " ", " ", " ", " ", " ");
	}

	Join(CR, CDH, list3);			//Testing Join- Example 8.14

	fprintf(wr, "\nJoin Testing- Example 8.14\n\n");
	for(int i =0; i<105; i++){
		if(list3[i].course != NULL)
			fprintf(wr, "%s  %s  %s  %s\n", list3[i].course, list3[i].room, list3[i].day, list3[i].hour);
	}


	struct node list4[105];
	for(int i =0; i<105; i++){
		list4[i] = *(struct node*)malloc(sizeof(struct node));
		list4[i] = *create(" ", 0, " ", " ", " ", " ", " ", " ", " ", " ");
	}

	Selection(list3, 'R', 0, "Turing_Aud", list4);


	fprintf(wr, "\nAll- Example 8.15\n\n");
	for(int i=0;i <105; i++){
		fprintf(wr, "%s  %s\n", list4[i].day, list4[i].hour);
	}


	fprintf(wr, "%s\n", "SNAP Table before deleting/inserting anything");
	for(int i=0; i<101; i++){						//tester, prints all id's
	 	fprintf(wr, "%d %d %s %s %s \n",i,SNAP[i].studentid,SNAP[i].name, SNAP[i].address,SNAP[i].phone);
		if (SNAP[i].next != NULL){
			fprintf(wr, "%d %d %s %s %s \n",i,SNAP[i].next->studentid,SNAP[i].next->name, SNAP[i].next->address,SNAP[i].next->phone);
			if (SNAP[i].next->next != NULL){
				fprintf(wr, "%d %d %s %s %s \n",i,SNAP[i].next->next->studentid,SNAP[i].next->next->name, SNAP[i].next->next->address,SNAP[i].next->next->phone);
				if (SNAP[i].next->next->next != NULL){
					fprintf(wr, "%d %d %s %s %s \n",i,SNAP[i].next->next->next->studentid,SNAP[i].next->next->next->name, SNAP[i].next->next->next->address,SNAP[i].next->next->next->phone);
				}
			}
		}
	 }	

	 insert(" ", 98989, " ", "T_Pawlicki", "22_John_St", "454-9093", " ", " ", " ", " ", SNAP);
	 insert(" ", 45678, " ", "G_Ferguson", "1_Blue_Rd", "287-3456", " ", " ", " ", " ", SNAP);
	 Sdelete(22222, SNAP);

	fprintf(wr, "%s\n", "SNAP Table after inserting CS173-CS172 and CS242-CS172");
	for(int i=0; i<101; i++){						//tester, prints all id's
	 	fprintf(wr, "%d %d %s %s %s \n",i,SNAP[i].studentid,SNAP[i].name, SNAP[i].address,SNAP[i].phone);
		if (SNAP[i].next != NULL){
			fprintf(wr, "%d %d %s %s %s \n",i,SNAP[i].next->studentid,SNAP[i].next->name, SNAP[i].next->address,SNAP[i].next->phone);
			if (SNAP[i].next->next != NULL){
				fprintf(wr, "%d %d %s %s %s \n",i,SNAP[i].next->next->studentid,SNAP[i].next->next->name, SNAP[i].next->next->address,SNAP[i].next->next->phone);
				if (SNAP[i].next->next->next != NULL){
					fprintf(wr, "%d %d %s %s %s \n",i,SNAP[i].next->next->next->studentid,SNAP[i].next->next->next->name, SNAP[i].next->next->next->address,SNAP[i].next->next->next->phone);
				}
			}
		}
	 }	

}//end main method

void allocate(struct node array[]){
	for(int i =0; i<101; i++){							//allocates memory for 101 nodes
		array[i] = *(struct node*)malloc(sizeof(struct node));
		array[i] = *create(" ", 0, " ", " ", " ", " ", " ", " ", " ", " ");
	}
}

int hash(int Sin){							//returns index for the node to be in
		int index = Sin%101;

		return index;
}

int hashCourse(char* Cin){
	int length = strlen(Cin);

	char* num = &Cin[2];

	int retval = atoi(num);

	retval = retval%101;

	return retval;
}


struct node* create(char* Cin, int Sin, char* Gin, char* Nin, char* Ain, char* Pin, char* PRin, char* Din, char* Hin, char* Rin){					//makes new node using inputs
	
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode-> studentid = Sin;

	newNode->course = malloc(sizeof(Cin));
	newNode->grade = malloc(sizeof(Gin));
	newNode->name = malloc(sizeof(Nin));
	newNode->address = malloc(sizeof(Ain));
	newNode->phone = malloc(sizeof(Pin));
	newNode->prereq = malloc(sizeof(PRin));
	newNode->day = malloc(sizeof(Din));
	newNode->hour = malloc(sizeof(Hin));
	newNode->room = malloc(sizeof(Rin));

	strcpy(newNode->course, Cin);
	strcpy(newNode->grade, Gin);
	strcpy(newNode->name, Nin);
	strcpy(newNode->address, Ain);
	strcpy(newNode->phone, Pin);
	strcpy(newNode->prereq, PRin);
	strcpy(newNode->day, Din);
	strcpy(newNode->hour, Hin);
	strcpy(newNode->room, Rin);
	

	newNode->next = (struct node*)malloc(sizeof(struct node));
	newNode->next->studentid = 0;
	
	newNode->next->course = malloc(sizeof(Cin));
	newNode->next->grade = malloc(sizeof(Gin));
	newNode->next->name = malloc(sizeof(Nin));
	newNode->next->address = malloc(sizeof(Ain));
	newNode->next->phone = malloc(sizeof(Pin));
	newNode->next->prereq = malloc(sizeof(PRin));
	newNode->next->day = malloc(sizeof(Din));
	newNode->next->hour = malloc(sizeof(Hin));
	newNode->next->room = malloc(sizeof(Rin));

	strcpy(newNode->next->course, " ");
	strcpy(newNode->next->grade, " ");
	strcpy(newNode->next->name, " ");
	strcpy(newNode->next->address, " ");
	strcpy(newNode->next->phone, " ");
	strcpy(newNode->next->prereq, " ");
	strcpy(newNode->next->day, " ");
	strcpy(newNode->next->hour, " ");
	strcpy(newNode->next->room, " ");

	
	return newNode;
}

void insertNext (struct node* current, char* Cin, int Sin, char* Gin, char* Nin, char* Ain, char* Pin, char* PRin, char* Din, char* Hin, char* Rin){			//recursively find end node in linked list
	
	if (current->next != NULL){
		if(current->next->studentid ==0 && strcmp(current->next->course, " ") ==0){
		current->next = create(Cin, Sin, Gin, Nin, Ain, Pin, PRin, Din, Hin, Rin);}
		else{
			insertNext(current->next, Cin, Sin, Gin, Nin, Ain, Pin, PRin, Din, Hin, Rin);
		}
		
	}
	else{
		insertNext(current->next, Cin, Sin, Gin, Nin, Ain, Pin, PRin, Din, Hin, Rin);
	}
}


void insert(char* Cin, int Sin, char* Gin, char* Nin, char* Ain, char* Pin, char* PRin, char* Din, char* Hin, char* Rin, struct node schema[]){		//initial insert method
	
	int hashNum;
	struct node* node = create(Cin, Sin, Gin, Nin, Ain, Pin, PRin, Din, Hin, Rin);
	if(Sin == 0 && (strcmp(Cin, " ") != 0)) {
		
		hashNum = hashCourse(Cin);
		if(strcmp(schema[hashNum].course, " ") == 0) {   //if index is empty		
			schema[hashNum] = *create(Cin, Sin, Gin, Nin, Ain, Pin, PRin, Din, Hin, Rin);	//insert new node in array

		}
		else{
			insertNext(&schema[hashNum], Cin, Sin, Gin, Nin, Ain, Pin, PRin, Din, Hin, Rin);
		}
	}//end outer if that hashes on course
	else if (Sin != 0){
		hashNum = hash(Sin);
		 
		 if(schema[hashNum].studentid == 0){		//if index is empty
			schema[hashNum] = *node;
			
		}
		else{
			insertNext(&schema[hashNum], Cin, Sin, Gin, Nin, Ain, Pin, PRin, Din, Hin, Rin);
		}
	}//end outer else if that hashes on student ID
	else {
		printf("WTF\n");
	}

	
}//end insert method



struct node* Slookup(int Sin, struct node arr[]){				//looks up to find node using key studentid - returns first occurrence of that id
	int index = hash(Sin);
	struct node* temp= &arr[index];
	
	int good =0;
	while (good ==0){
		if (temp == NULL){
			printf("Does not exist\n");
			good=1;
			temp = NULL;
		}
		else if(temp->studentid == Sin){
			good=1;
		}
		else if (temp->studentid ==0){
			printf("Does not exist\n");
			good=1;
			temp = NULL;
		}
		else{
			temp = temp->next;
		}

	}

	return temp;
}

struct node* Clookup(char* Cin, struct node arr[]){				//looks up to find node using key of course
	int index = hashCourse(Cin);
	struct node* temp= &arr[index];


	int good =0;
	while (good == 0){
		if (temp == NULL){
			good=1;
			temp = NULL;
		}
		else if(strcmp(temp->course, Cin) == 0){
			good=1;
		}
		else if (strcmp(temp->course," ") == 0){
			good=1;
			temp = NULL;
		}
		else{
			temp = temp->next;
		}

	}

	return temp;
}

void SdeleteRecursive(struct node* current, int Sin){
	if (current->next != NULL ){
		if(current->next->studentid == Sin){
			current->next = current->next->next;
			//SdeleteRecursive(current->next, Sin);
		}
		else{
			SdeleteRecursive(current->next, Sin);
		}

	}
}

void Sdelete(int Sin, struct node arr[]){
	

	if(arr[hash(Sin)].studentid == Sin){
		printf("this\n");
		arr[hash(Sin)] = *arr[hash(Sin)].next;
		//SdeleteRecursive(&arr[hash(Sin)], Sin);
	}
	else{
		printf("here\n");
		SdeleteRecursive(&arr[hash(Sin)], Sin);
	}

}

void CdeleteRecursive(struct node* current, char* Cin){
	if (current->next != NULL){
		if(strcmp(current->next->course, Cin) == 0){
			current->next = current->next->next;
			//CdeleteRecursive(current->next, Cin);
		}
		else{
			CdeleteRecursive(current->next, Cin);
		}

	}
}

void Cdelete(char* Cin, struct node arr[]){
	

	if(strcmp(arr[hashCourse(Cin)].course, Cin) == 0){
		arr[hashCourse(Cin)] = *arr[hashCourse(Cin)].next;
		//CdeleteRecursive(&arr[hashCourse(Cin)], Cin);
	}
	else{
		CdeleteRecursive(&arr[hashCourse(Cin)], Cin);
	}

}

int id(struct node* start, char* Nin){				//Get ID of name
	int retval =0;
	struct node* temp= start;

	int good =0;
	while (good ==0){
		if (temp == NULL){
			good=1;
		}
		else if(strcmp(temp->name,Nin)==0){
			good=1;
			retval = temp->studentid;
		}
		else if (strcmp(temp->name," ") == 0){
			good=1;
		}
		else{
			temp = temp->next;
		}

	}
	return retval;
}

char* gradee(struct node* start, int Sin, char* Cin){			//Get Grade of name in x class
	char* retval =" ";
	struct node* temp= start;

	int good =0;
	while (good ==0){
		if (temp == NULL){
			good=1;
		}
		else if(temp->studentid == Sin && strcmp(temp->course, Cin)==0){
			good=1;
			retval = temp->grade;
		}
		else if (temp->studentid == 0){
			good=1;
		}
		else{
			temp = temp->next;
		}

	}
	return retval;
}

	//SNAP -> CSG
char* gradeOfName(char* Nin, char* Cin, struct node CSG[], struct node SNAP[]){			//Part 2 part A

	int ID=0;
	for(int i =0; i<101; i++){
		if (id(&SNAP[i], Nin) != 0)
			ID = id(&SNAP[i], Nin);
	}

	char* Grade = malloc(sizeof(char)*5);
	for(int i =0; i<101; i++){
		if (strcmp(gradee(&CSG[i], ID, Cin), " ") != 0)
			Grade = gradee(&CSG[i], ID, Cin);
	}

	return Grade;
}

int num =0;

void classes(struct node* start, int id, struct String finished[]){			//Find classes he is taking


	struct node* temp= start;

	int good =0;
	int counter =0;

	
	while (good ==0){
		if (temp == NULL){
			
			good=1;
		}
		else if(temp->studentid == id){
			
			finished[counter].value = temp->course; counter++;
			temp = temp->next;

		}
		else if (temp->studentid == 0){
			
			good=1;
		}


	}
	struct String* last = (struct String*)malloc(sizeof(struct String));
	last->value = "//";
	finished[counter] =  *last;
}


char* time(struct node* start, struct String classes[], char* Din, char* Hin){			//Find a course he is taking at the date & time given
	char* retval;
	struct node* temp= start;

	int good =0;


	for(int i =0; i<105; i++){

		good=0;
		while (good ==0){
			if (temp == NULL){
				good=1;
			}
			else if(strcmp(temp->day,Din)==0 && strcmp(temp->hour, Hin)==0 && strcmp(temp->course, classes[i].value)==0){
				
				retval= temp->course;
				
				good=1;
			}
			else if (strcmp(temp->course, " ") == 0){
				good=1;
			}
			else{
				temp = temp->next;
			}

		}
	}

	return retval;
}


char* rooms(char* finalCourse, struct node* start){				//find room of class given
	char* retval=NULL;
	struct node* temp= start;

	int good =0;
	int counter =0;

	while (good ==0){
		if (temp == NULL){
			good=1;
		}
		else if(strcmp(temp->course,finalCourse)==0){
			retval = temp->room;
			good=1;
		}
		else if (temp->studentid == 0){
			good=1;
		}
		else{
			temp = temp->next;
		}

	}

	return retval;
}

	//SNAP -> CSG -> CDH-> CR
char* roomOfName(char* Nin, char* Hin, char* Din, struct node CSG[], struct node SNAP[], struct node CDH[], struct node CR[]){		//Part 2 part B
	
	int ID=0;
	for(int i =0; i<101; i++){
		if (id(&SNAP[i], Nin) != 0)
			ID = id(&SNAP[i], Nin);
	}

	struct node* temp;
	for(int i =0; i<101; i++){
		if(CSG[i].studentid !=0){
			temp = &CSG[i];
		}
	}

	struct String courses[105];
	for(int i =0; i<105; i++){
		courses[i] = *(struct String*)malloc(sizeof(struct String));
	}

	classes(&CSG[hash(ID)], ID, courses);
	
	// for(int i =0; i<105; i++){
	// 	printf("%s\n", courses[i].value);
	// }

	char* CsGood = malloc(sizeof(char)*30);
	
	for(int i =0; i<101; i++){
		if ((time(&CDH[i], courses, Din, Hin), " ") !=0)
			CsGood =time(&CDH[i], courses, Din, Hin);
	}



	for(int i =0; i<101; i++){
		if (rooms(CsGood,&CR[i]) != NULL)
			CsGood =rooms(CsGood,&CR[i]);
	}


	return CsGood;


}

int* ProjectionInt(struct node arr[], char column){		//array ends with an int of -1
	
	int* ids = malloc(sizeof(int)*100);
	counter =0;
	if(column == 'S'){								//column = student id
		for (int i =0; i<101; i++){
			//printf("%d\n", arr[i].studentid);
			if(arr[i].studentid != 0){							
				ids[counter] = arr[i].studentid; counter++;		//copy first in the array slot
			} 
			struct node* current = &arr[i];
			while(current->next != NULL){
				if(current->next->studentid !=0){
				ids[counter] = current->next->studentid; counter++;}		//copy the nodes behind the 1st node in the array slot
				
				current = current->next;
			}
		

		}
		ids[counter] = -1;
	}
	return ids;
}

void ProjectionString(struct node arr[], char column, struct String finished[]){		//array ends w String w value = "//"
	counter =0;
	if(column == 'C'){					//column = course
		
		for (int i =0; i<101; i++){
			if(strcmp(arr[i].course, " ")!=0){
				finished[counter].value = arr[i].course; counter++;		//copy first in the array slot
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){								//copy the nodes behind the 1st node in the array slot
				if(strcmp(arr[i].course, " ")!=0){
					finished[counter].value = current->next->course; counter++;
				}
				current = current->next;
			}
		}

		}
		struct String* last = (struct String*)malloc(sizeof(struct String));
		last->value = "//";
		finished[counter] =  *last;
	}

	else if(column == 'G'){							//column = grade
		for (int i =0; i<101; i++){
			if(strcmp(arr[i].grade, " ")!=0){
				finished[counter].value = arr[i].grade; counter++;
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(arr[i].grade, " ")!=0){
					finished[counter].value = current->next->grade; counter++;
				}
				current = current->next;
			}
		}

		}
		struct String* last = (struct String*)malloc(sizeof(struct String));
		last->value = "//";
		finished[counter] =  *last;
	}

	else if(column == 'N'){								//column = name
		for (int i =0; i<101; i++){
			if(strcmp(arr[i].name, " ")!=0){
				finished[counter].value = arr[i].name; counter++;
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(arr[i].name, " ")!=0){
					finished[counter].value = current->next->name; counter++;
				}
				current = current->next;
			}
		}

		}
		struct String* last = (struct String*)malloc(sizeof(struct String));
		last->value = "//";
		finished[counter] =  *last;
	}

	else if(column == 'A'){											//column = address
		for (int i =0; i<101; i++){
			if(strcmp(arr[i].address, " ")!=0){
				finished[counter].value = arr[i].address; counter++;
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(arr[i].address, " ")!=0){
					finished[counter].value = current->next->address; counter++;
				}
				current = current->next;
			}
		}

		}
		struct String* last = (struct String*)malloc(sizeof(struct String));
		last->value = "//";
		finished[counter] =  *last;
	}

	else if(column == 'P'){										//column = phone
		for (int i =0; i<101; i++){
			if(strcmp(arr[i].phone, " ")!=0){
				finished[counter].value = arr[i].phone; counter++;
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(arr[i].phone, " ")!=0){
					finished[counter].value = current->next->phone; counter++;
				}
				current = current->next;
			}
		}

		}
		struct String* last = (struct String*)malloc(sizeof(struct String));
		last->value = "//";
		finished[counter] =  *last;
	}	

	else if(column == 'E'){													//column = prerequisite
		for (int i =0; i<101; i++){
			if(strcmp(arr[i].prereq, " ")!=0){
				finished[counter].value = arr[i].prereq; counter++;
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(arr[i].prereq, " ")!=0){
					finished[counter].value = current->next->prereq; counter++;
				}
				current = current->next;
			}
		}

		}
		struct String* last = (struct String*)malloc(sizeof(struct String));
		last->value = "//";
		finished[counter] =  *last;
	}

	else if(column == 'D'){													//column = day
		for (int i =0; i<101; i++){
			if(strcmp(arr[i].day, " ")!=0){
				finished[counter].value = arr[i].day; counter++;
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(arr[i].day, " ")!=0){
					finished[counter].value = current->next->day; counter++;
				}
				current = current->next;
			}
		}

		}
		struct String* last = (struct String*)malloc(sizeof(struct String));
		last->value = "//";
		finished[counter] =  *last;
	}

	else if(column == 'H'){												//column = hour
		for (int i =0; i<101; i++){
			if(strcmp(arr[i].hour, " ")!=0){
				finished[counter].value = arr[i].hour; counter++;
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(arr[i].hour, " ")!=0){
					finished[counter].value = current->next->hour; counter++;
				}
				current = current->next;
			}
		}

		}
		struct String* last = (struct String*)malloc(sizeof(struct String));
		last->value = "//";
		finished[counter] =  *last;
	}

	else if(column == 'R'){														//column = room
		for (int i =0; i<101; i++){
			if(strcmp(arr[i].room, " ")!=0){
				finished[counter].value = arr[i].room; counter++;
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(arr[i].room, " ")!=0){
					finished[counter].value = current->next->room; counter++;
				}
				current = current->next;
			}
		}

		}
		struct String* last = (struct String*)malloc(sizeof(struct String));
		last->value = "//";
		finished[counter] =  *last;
	}

	else{
		printf("Oh Poop, didn't work\n");
	}

}

void Selection(struct node arr[], char SA, int a, char* b, struct node finished[]){
	int counter = 0;

	if (SA == 'S'){									//column = student id
			
			for (int i =0; i<101; i++){
			if(arr[i].studentid == a){
				finished[counter] = arr[i]; counter++;
			}
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(current->next->studentid == a){
					finished[counter] = *current->next; counter++;
				}
				current = current->next;
			}
		}

	}
	else if (SA == 'C'){										//column = course
			
			for (int i =0; i<101; i++){
			if(strcmp(arr[i].course,b) ==0){
				finished[counter] = arr[i]; counter++;
			}
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(current->next->course, b) ==0){
					finished[counter] = *current->next; counter++;
				}
				current = current->next;
			}
		}

	}
	else if (SA == 'G'){										//column = grade
			
			for (int i =0; i<101; i++){
			if(strcmp(arr[i].grade,b) ==0){
				finished[counter] = arr[i]; counter++;
			}
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(current->next->grade, b) ==0){
					finished[counter] = *current->next; counter++;
				}
				current = current->next;
			}
		}

	}
	else if (SA == 'N'){											//column = name
			
			for (int i =0; i<101; i++){
			if(strcmp(arr[i].name,b) ==0){
				finished[counter] = arr[i]; counter++;
			}
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(current->next->name, b) ==0){
					finished[counter] = *current->next; counter++;
				}
				current = current->next;
			}
		}

	}
	else if (SA == 'A'){										//column = address
			
			for (int i =0; i<101; i++){
			if(strcmp(arr[i].address,b) ==0){
				finished[counter] = arr[i]; counter++;
			}
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(current->next->address, b) ==0){
					finished[counter] = *current->next; counter++;
				}
				current = current->next;
			}
		}

	}
	else if (SA == 'P'){									//column = phone
			
			for (int i =0; i<101; i++){
			if(strcmp(arr[i].phone,b) ==0){
				finished[counter] = arr[i]; counter++;
			}
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(current->next->phone, b) ==0){
					finished[counter] = *current->next; counter++;
				}
				current = current->next;
			}
		}

	}
	else if (SA == 'E'){										//column = prerequisite
			
			for (int i =0; i<101; i++){
			if(strcmp(arr[i].prereq,b) ==0){
				finished[counter] = arr[i]; counter++;
			}
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(current->next->prereq, b) ==0){
					finished[counter] = *current->next; counter++;
				}
				current = current->next;
			}
		}

	}
	else if (SA == 'D'){										//column = day
			
			for (int i =0; i<101; i++){
			if(strcmp(arr[i].day,b) ==0){
				finished[counter] = arr[i]; counter++;
			}
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(current->next->day, b) ==0){
					finished[counter] = *current->next; counter++;
				}
				current = current->next;
			}
		}

	}
	else if (SA == 'H'){										//column = hour
			
			for (int i =0; i<101; i++){
			if(strcmp(arr[i].hour,b) ==0){
				finished[counter] = arr[i]; counter++;
			}
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(current->next->hour, b) ==0){
					finished[counter] = *current->next; counter++;
				}
				current = current->next;
			}
		}

	}
	else if (SA == 'R'){										//column = room
			
			for (int i =0; i<101; i++){
			if(strcmp(arr[i].room,b) ==0){
				finished[counter] = arr[i]; counter++;
			}
				
			
			struct node* current = &arr[i];
			while(current->next != NULL ){
				if(strcmp(current->next->room, b) ==0){
					finished[counter] = *current->next; counter++;
				}
				current = current->next;
			}
		}

	}
	else{
		printf("oh poop\n");
	}

}

struct node* joinNode(struct node a, struct node b){			//create the node that will be added to the array of joined arrays
	char* Cin= a.course;				//initialize node with node a
	int Sin = a.studentid;
	char* Gin = a.grade;
	char* Nin= a.name;
	char* Ain= a.address;
	char* Pin= a.phone;
	char* PRin= a.prereq;
	char* Din= a.day;
	char* Hin= a.hour;
	char* Rin= a.room;


	if(strcmp(b.course, " ") !=0){					//use node b to fill in the gaps and create new node
		Cin = b.course;	
	}
	if(b.studentid !=0){
		Sin = b.studentid;
	}
	if(strcmp(b.grade, " ") !=0){
		Gin = b.grade;
	}
	if(strcmp(b.name, " ") !=0){
		Nin = b.name;
	}
	if(strcmp(b.address, " ") !=0){
		Ain = b.address;
	}
	if(strcmp(b.phone, " ") !=0){
		Pin = b.phone;
	}
	if(strcmp(b.prereq, " ") !=0){
		Rin = b.prereq;
	}
	if(strcmp(b.day, " ") !=0){
		Din = b.day;
	}
	if(strcmp(b.hour, " ") !=0){
		Hin = b.hour;
	}
	if(strcmp(b.room, " ") !=0){
		Rin = b.room;
	}
	
	return create(Cin, Sin, Gin, Nin, Ain, Pin, PRin, Din, Hin, Rin);
	
}

/*
	Method goes through each element in the first array and compares it to 
	each element in the second array and calls joinNode with the 2 elements
	which will add it to the finished array
*/

void Join(struct node first[],struct node second[], struct node finished[]){		
	int counter =0;

	for (int i =0; i<101; i++){
		if(strcmp(first[i].course," ") !=0){


		for (int p =0; p<101; p++){
			if(strcmp(first[i].course, second[p].course) ==0){
				finished[counter] = *joinNode(first[i], second[p]); counter++;		//point of equivalence
			}
				
			
			struct node* current = &second[p];
			while(current->next != NULL ){
				if(strcmp(first[i].course, current->next->course) ==0){
					finished[counter] = *joinNode(first[i], *current->next); counter++;		//point of equivalence
				}
				current = current->next;
			}
		}
		}
			
		
		struct node* current = &first[i];
		while(current->next != NULL ){
			if(strcmp(current->next->course, " ") !=0){
				
				for (int p =0; p<101; p++){
				if(strcmp(current->next->course, second[p].course) ==0){
					finished[counter] = *joinNode(*current->next, second[p]); counter++;		//point of equivalence
				}
					
				
				struct node* current2 = &second[p];
				while(current->next != NULL && current2->next != NULL){
					if(strcmp(current->next->course, current2->next->course) ==0){
						finished[counter] = *joinNode(*current->next, *current2->next); counter++;		//point of equivalence
					}
					current2 = current2->next;
				}
			}



			}
			current = current->next;
		}
	}
}


void Union (struct node arr1[], struct node arr2[]) { //will add the elements of arr2 to arr1
	int same = 1;

	for(int i = 0; i < 101; i++) {
		for(int j = 0; j < 101; j++) {
			if (checkSame(&arr1[i], &arr2[j]) == 0)
				same = 0; // aka they are of the same type 
		}
	}

	if(same == 0) {
		for(int i = 0; i < 101; i++) {	
			insertNode(&arr2[i], arr1);
		}

	}//end of if same
	else
		printf("Union cannot be made as the schemas are of different types\n");

}//end of Union method

void Intersection (struct node arr1[], struct node arr2[], struct node returned[]) { //finds intersection of arrays and returns it in a new array
	int same = 1;

	for(int i = 0; i < 101; i++) {
		for(int j = 0; j < 101; j++) {
			if (checkSame(&arr1[i], &arr2[j]) == 0)
				same = 0;
		}
	}

	if (same == 0) {
		for(int i = 0; i < 101; i++) {
			for(int j = 0; j < 101; j++) {
				//need to check if2 nodes are the same, and then add it to returned array
				if(equals(&arr1[i], &arr2[j]) == 0)
					insertNode(&arr1[i], returned);
			}
		}
	}//end of if same 


}//end of intersection method

int equals (struct node* node1, struct node* node2) {
	//return 0 if true, 1 if false
	int retval;

	if (node1 == NULL && node2 == NULL)
		retval = 0;
	else if (node1 == NULL)
		retval = 1;
	else if (node2 == NULL)
		retval = 1;
	else {

		if (strcmp(node1->course, node2->course) != 0) 
			retval = 1;

		else if (node1->studentid != node2->studentid)
			retval = 1;

		else if (strcmp(node1->grade, node2->grade) != 0)
			retval = 1;

		else if (strcmp(node1->name, node2->name) != 0)
			retval = 1;

		else if (strcmp(node1->address, node2->address) != 0)
			retval = 1;

		else if (strcmp(node1->phone, node2->phone) != 0)
			retval = 1;

		else if (strcmp(node1->prereq, node2->prereq) != 0)
			retval = 1;

		else if (strcmp(node1->day, node2->day) != 0)
			retval = 1;

		else if (strcmp(node1->hour, node2->hour) != 0)
			retval = 1;

		else if (strcmp(node1->room, node2->room) != 0)
			retval = 1;

		else
			retval = 0; //means that they are the same

	}//end else that means both nodes are not null

	return retval;

}//end of equals method

int checkSame (struct node* node1, struct node* node2) { //sees if both nodes/arrays are of the same type
	//returns 0 if true, 1 if false
	int retval; 

	if (node1 == NULL && node2 == NULL)
		retval = 0;
	else if (node1 == NULL)
		retval = 1;
	else if (node2 == NULL)
		retval = 1;
	else {

		if (strcmp(node1->course, " ") == 0 && strcmp(node2->course, " ") != 0) 
			retval = 1;
		else if (strcmp(node1->course, " ") != 0 && strcmp(node2->course, " ") == 0) 
			retval = 1;

		else if (node1->studentid == 0 && node2->studentid != 0)
			retval = 1;
		else if (node1->studentid != 0 && node2->studentid == 0)
			retval = 1;

		else if (strcmp(node1->grade, " ") == 0 && strcmp(node2->grade, " ") != 0)
			retval = 1;
		else if (strcmp(node1->grade, " ") != 0 && strcmp(node2->grade, " ") == 0)
			retval = 1;

		else if (strcmp(node1->name, " ") == 0 && strcmp(node2->name, " ") != 0)
			retval = 1;
		else if (strcmp(node1->name, " ") != 0 && strcmp(node2->name, " ") == 0)
			retval = 1;

		else if (strcmp(node1->address, " ") == 0 && strcmp(node2->address, " ") != 0)
			retval = 1;
		else if (strcmp(node1->address, " ") != 0 && strcmp(node2->address, " ") == 0)
			retval = 1;

		else if (strcmp(node1->phone, " ") == 0 && strcmp(node2->phone, " ") != 0)
			retval = 1;
		else if (strcmp(node1->phone, " ") != 0 && strcmp(node2->phone, " ") == 0)
			retval = 1;

		else if (strcmp(node1->prereq, " ") == 0 && strcmp(node2->prereq, " ") != 0)
			retval = 1;
		else if (strcmp(node1->prereq, " ") != 0 && strcmp(node2->prereq, " ") == 0)
			retval = 1;

		else if (strcmp(node1->day, " ") == 0 && strcmp(node2->day, " ") != 0)
			retval = 1;
		else if (strcmp(node1->day, " ") != 0 && strcmp(node2->day, " ") == 0)
			retval = 1;

		else if (strcmp(node1->hour, " ") == 0 && strcmp(node2->hour, " ") != 0)
			retval = 1;
		else if (strcmp(node1->hour, " ") != 0 && strcmp(node2->hour, " ") == 0)
			retval = 1;

		else if (strcmp(node1->room, " ") == 0 && strcmp(node2->room, " ") != 0)
			retval = 1;
		else if (strcmp(node1->room, " ") != 0 && strcmp(node2->room, " ") == 0)
			retval = 1;

		else
			retval = 0; //means that they are equal types

	}//end else that means both nodes are not null



	return retval;

}//end of checkSame method


void insertNextNode (struct node* current, struct node* n){			//recursively find end node in linked list
	
	if (current->next == NULL){

		current->next = n;
		
	}
	else{
		insertNextNode(current->next, n);
	}
}

void insertNode(struct node* node, struct node schema[]) {
	int hashNum;
	
	if(node->studentid == 0 && (strcmp(node->course, " ") != 0)) {
		
		hashNum = hashCourse(node->course);
		if(strcmp(schema[hashNum].course, " ") == 0) {   //if index is empty		
			schema[hashNum] = *node;	//insert new node in array

		}
		else{
			insertNextNode(&schema[hashNum], node);
		}
	}//end outer if that hashes on course
	else if (node->studentid != 0){
		hashNum = hash(node->studentid);
		 
		 if(schema[hashNum].studentid == 0){		//if index is empty
			schema[hashNum] = *node;
			
		}
		else{
			insertNextNode(&schema[hashNum], node);
		}
	}//end outer else if that hashes on student ID

}//end insertNode method




















