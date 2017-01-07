#include <stdio.h>
#include <stdlib.h>

struct node {					//defines what a node contains
	char* course;
	int studentid;
	char* grade;
	char* name;
	char* address;
	char* phone;
	char* prereq;
	char* day;
	char* hour;
	char* room;

	struct node* next;

};

struct String{
	char* value;

};

void allocate(struct node array[]);
int hash(int Sin); 			//hashing on studentid, indicating it as the domain
int hashCourse(char* Cin);  //hashing on course, indicating it as the domain
struct node* create(char* Cin, int Sin, char* Gin, char* Nin, char* Ain, char* Pin, char* PRin, char* Din, char* Hin, char* Rin);
void insertNext (struct node* current, char* Cin, int Sin, char* Gin, char* Nin, char* Ain, char* Pin, char* PRin, char* Din, char* Hin, char* Rin);
void insert(char* Cin, int Sin, char* Gin, char* Nin, char* Ain, char* Pin, char* PRin, char* Din, char* Hin, char* Rin, struct node schema[]);
struct node* Slookup(int Sin, struct node arr[]);
struct node* Clookup(char* Cin, struct node arr[]);
void SdeleteRecursive(struct node* current, int Sin);
void Sdelete(int Sin, struct node arr[]);
void CdeleteRecursive(struct node* current, char* Cin);
void Cdelete(char* Cin, struct node arr[]);
int id(struct node* start, char* Nin);
char* gradee(struct node* start, int Sin, char* Cin);
char* gradeOfName(char* Nin, char* Cin, struct node CSG[], struct node SNAP[]);
void classes(struct node* start, int id, struct String finished[]);
char* time(struct node* start,  struct String classes[], char* Din, char* Hin);
char* rooms(char* finalCourse, struct node* start);
char* roomOfName(char* Nin, char* Hin, char* Din, struct node CSG[], struct node SNAP[], struct node CDH[], struct node CR[]);
int* ProjectionInt(struct node arr[], char column);
void ProjectionString(struct node arr[], char column, struct String finished[]);
void Selection(struct node arr[], char SA, int a, char* b, struct node finished[]);
struct node* joinNode(struct node a, struct node b);
void Join(struct node first[],struct node second[], struct node finished[]);
void Union (struct node arr1[], struct node arr2[]);
void Intersection (struct node arr1[], struct node arr2[], struct node returned[]);
void Difference (struct node arr1[], struct node arr2[], struct node returned[]);
int equals (struct node* node1, struct node* node2);
int checkSame (struct node* node1, struct node* node2);
void insertNextNode (struct node* current, struct node* n);
void insertNode(struct node* node, struct node schema[]);
