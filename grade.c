// Homework 3: 2.6.21
// Course: CS 451, Winter 2021
// Instructor: Il-Hyung Cho
// Student: Jarin Musarrat
// Program Description:
// This program takes a txt file of inputs that contains how many students and their name, ID, English, and History score.
// The program then calculates the average of the grade for the class in a sorted order and also shows the letter grade of 
// the student in both classes.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int num_students;
int input;
struct StudentGrade {
    int number;     // student number
    char* name;		// student name;
    int eng101;	
    int hist201;
};

//function declaration

void read_data();
void print_result();
struct StudentGrade *stud_list;
void swap(struct StudentGrade *xp, struct StudentGrade *yp);
void bubbleSort(struct StudentGrade *stud_list, int num_students);


int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("./a.out inputfile\n");     
       return 0;
    }       
    printf("Sort by:\n 1-Name\n 2-English Score\n 3-History Score\n");
    printf("Enter the number for the choice(1 or 2 or 3):\n");
    scanf("%d", &input);
if (input != 1 && input != 2 && input != 3)
    {
        printf("Error: Invalid input.\n"); // Print Invalid Input
        return -1; 
    }

    read_data(argv[1]);
    print_result();    

}

void read_data(char *filename)
{
    FILE* fp;
    int i;
    char line[80];
    int stud_num;
    char *name;
    int score; 

    fp  = fopen(filename, "r"); 
    if (fp == NULL) {
	printf("Error while opening the file.\n");
	exit(1);
    }

    fscanf(fp, "%d", &num_students);
    stud_list = (struct StudentGrade *) 
	malloc(num_students * sizeof(struct StudentGrade));

    for (i = 0; i < num_students; i++) {
	fscanf(fp, "%d", &stud_num);
	stud_list[i].number = stud_num;
	fscanf(fp, "%s", line);
	stud_list[i].name = (char *) malloc(strlen(line));
	strcpy(stud_list[i].name, line);
	fscanf(fp, "%d", &score);
	stud_list[i].eng101 = score;
	fscanf(fp, "%d", &score);
	stud_list[i].hist201 = score;
    }
}

//the follwoing method I had help from https://www.geeksforgeeks.org/c-program-for-bubble-sort/ 
//swap method for bubble sort function 
void swap(struct StudentGrade *xp, struct StudentGrade *yp){
    struct StudentGrade temp; 
    temp= *xp;
    *xp = *yp;
    *yp = temp;
}

//bubble sort method for having the list prinetd based on names alphabetic order
void bubbleSort(struct StudentGrade *stud_list, int num_students){
    int i;
    int j;
    for (i=0; i<num_students;i++){
        for (j =i+1; j<(num_students);j++){ 
            // compares name strings to see which one is greater   
            if (input ==1){
            if (strcmp(stud_list[i].name,stud_list[j].name)>0){       
                swap(&stud_list[i], &stud_list[j]);       
             }}
             else if (input ==2){
                 
            if ((stud_list[i].eng101<stud_list[j].eng101)){       
                swap(&stud_list[i], &stud_list[j]);       
             }}
             else if (input ==3){
            if ((stud_list[i].hist201<stud_list[j].hist201)){       
                swap(&stud_list[i], &stud_list[j]);       
             }}
        }
    }
}

//function to print result with grade and format
void print_result()
{
    printf("%11s\t%10s\t%6s\t%8s\n", "Student Name", "Student ID", "Eng101","Hist201");  
    printf("%11s\t%10s\t%6s\t%8s\n", "------------", "----------", "------","-------");  
   
    int i;
    float engTotal = 0;
    float histTotal = 0;
    char *engGrade ;
    char *histGrade;

//bubblesort method call
bubbleSort(stud_list,num_students);

//determining grade based on number
for(i=0;i<num_students;i++)
     {if (stud_list[i].eng101  < 60) {
        engGrade = "(F)";}
    else if (stud_list[i].eng101  >=60 && stud_list[i].eng101 <70){
        engGrade = "(D)";}
    else if (stud_list[i].eng101  >= 70 && stud_list[i].eng101  <80){
        engGrade = "(C)";}
    else if (stud_list[i].eng101  >=80 && stud_list[i].eng101  <90){
        engGrade = "(B)";}
    else if (stud_list[i].eng101  >=90){
        engGrade = "(A)";}

    if (stud_list[i].hist201  < 60) {
        histGrade=  "(F)";}
    else if (stud_list[i].hist201  >=60 && stud_list[i].hist201 <70){
        histGrade = "(D)";}
    else if (stud_list[i].hist201  >= 70 && stud_list[i].hist201  <80){
        histGrade = "(C)";}
    else if (stud_list[i].hist201  >=80 && stud_list[i].hist201  <90){
        histGrade = "(B)";}
    else if (stud_list[i].hist201  >=90){
        histGrade = "(A)";}

    engTotal = engTotal+stud_list[i].eng101;
    histTotal = histTotal+stud_list[i].hist201;

    printf("%11s\t%10d\t%3d%s\t%5d%s\n", stud_list[i].name, stud_list[i].number, stud_list[i].eng101,engGrade,stud_list[i].hist201,histGrade); 
    
    }
    printf("\n ");
    printf("%2s\t%19s\t %.2f\t   %.2f\n", " ", "Class Average:", engTotal/num_students,histTotal/num_students);  
}
