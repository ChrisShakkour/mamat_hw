/*
mamat HW4
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "grades.h"
#include "linked-list.h"


#define SUCCESS 0
#define ERROR -1
#define ZERO 0


/*
 * struct to hold 
 * students pointers
 * of type list.
 */
struct grades {
  struct list* students;
};


/*
 * struct to hold id,
 * name and course list 
 * data for each student.
 */
struct student {
  int id;
  char* name;
  struct list* courses;
};


/*
 * course struct
 * holds name and 
 * grade of a course
 */
struct course{
  char* name;
  int grade;
};


/**
 * @brief  Clones element to output.
 * @returns Zero on success
 */
static int student_clone(void *element, void **output){
  //
  if(element==NULL) return ERROR;
  if(output==NULL)  return ERROR;

  // casting
  struct student* student = (struct student*)element;
  struct student** cloned_student = (struct student**)output;

  // put student struct
  // pointer into the value
  // of cloned_student pointer
  // of type pointer, sort of
  // referencing instead of creating
  // a new student and copying the feilds!  
  *cloned_student = student;
  return SUCCESS;
}


/**
 * @brief  Clones element to output.
 * @returns Zero on success
 */
static void student_destroy(void *element){
  //
  if(element == NULL) return;
  
  struct student* student = element;
  list_destroy(student->courses);
  free(student->name);
  free(student);
};


/**
 * @brief  Clones element to output.
 * @returns Zero on success
 */
static int course_clone(void *element, void **output){
  //
  if(element==NULL) return ERROR;
  if(output==NULL)  return ERROR;

  struct course*  course = (struct course*)element;
  struct course** cloned_course = (struct course**)output;

  *cloned_course = course;
  return SUCCESS;
}


/**
 * @brief  destroys course
 * @returns Zero on success
 */
static void course_destroy(void *element){
  //
  if(element == NULL) return;
  
  struct course* course = element;
  free(course->name);
  free(course);
};



/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, of NULL in case of an error
 */
struct grades* grades_init(){
  struct grades* ptr =
    (struct grades*)malloc(sizeof(struct grades));
  if(ptr==NULL) return NULL;
  
  struct list* stud = list_init(student_clone, student_destroy);
  ptr->students=stud;
  return ptr;
}




/**
 * @brief Destroys "grades", de-allocate all memory!
 */
void grades_destroy(struct grades *grades){
  //
  if(grades==NULL) return;
  
  list_destroy(grades->students);
  free(grades);
}


/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with 
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id){
  //
  if(grades == NULL) return ERROR;
  
  struct iterator* iT;
  for( iT=list_begin(grades->students); iT!=NULL; iT=list_next(iT)){
    struct student* ptr = list_get(iT);
    if(ptr->id==id) return ERROR;
  }
  
  // create a new student.
  struct student* Sptr=
    (struct student*)malloc(sizeof(struct student));
  if(Sptr==NULL) return ERROR;

  // assign name, id, and
  // create a course list;
  Sptr->id = id;
  Sptr->name = (char*)malloc(sizeof(char)*strlen(name)+1);
  if(Sptr->name==NULL) {
    free(Sptr);
    return ERROR;
  }
  strcpy(Sptr->name, name);  
  struct list* courses_list = list_init(course_clone, course_destroy);
  Sptr->courses = courses_list;
  
  // push student to grades list.
  list_push_back(grades->students, Sptr);
  return SUCCESS;
}


/**
 * @brief Adds a course with "name" and "grade" to the student with "id"
 * @return 0 on success
 * @note Failes if "grades" is invalid, if a student with "id" does not exist
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
  //
  if(grades==NULL) return ERROR;
  if(grade<0 || grade>100) return ERROR;

  struct student* student=NULL;
  struct iterator* iT;
  for( iT=list_begin(grades->students); iT!=NULL; iT=list_next(iT)){
    struct student* ptr = list_get(iT);
    if(ptr->id==id){
      student = ptr;
      //break;
    }
  }
  if(student==NULL) return ERROR;
  struct iterator* cT;
  for( cT=list_begin(student->courses); cT!=NULL; cT=list_next(cT)){
    struct course* course = list_get(cT);
    if(!strcmp(course->name, name)) return ERROR;
  }

  // create a new course.
  struct course* Cptr=
    (struct course*)malloc(sizeof(struct course));
  if(Cptr==NULL) return ERROR;

  // assign name and grade
  Cptr->grade = grade;
  Cptr->name = (char*)malloc(sizeof(char)*strlen(name)+1);
  if(Cptr->name==NULL){
    free(Cptr);
    return ERROR;
  }
  strcpy(Cptr->name, name);  
  list_push_back(student->courses, Cptr);  
  return SUCCESS;  
}


/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average is 0.
 * @note On error, sets "out" to NULL.
 */
float grades_calc_avg(struct grades *grades, int id, char **out){

  //
  if(grades==NULL) return ERROR;

  struct student* student=NULL;
  struct iterator* iT;
  for( iT=list_begin(grades->students); iT!=NULL; iT=list_next(iT)){
    struct student* ptr = list_get(iT);
    if(ptr->id==id){
      student = ptr;
    }
  }
  if(student==NULL) return ERROR;

  char** cloned_ptr = out;
  char*  cloned_name =
    (char*)malloc(sizeof(char)*(strlen(student->name))+1);
  if(cloned_name==NULL) return ERROR;
  strcpy(cloned_name, student->name);
  *cloned_ptr = cloned_name;
  
  int sum=0;
  struct iterator* cT;
  for( cT=list_begin(student->courses); cT!=NULL; cT=list_next(cT)){
    struct course* course = list_get(cT);
    sum+=course->grade;
  }
  int num= list_size(student->courses); 
  if(num==0) return ZERO;
  return (float)sum/(float)num;
}


/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id){
  //
  if(grades==NULL) return ERROR;
  
  struct iterator* iT;
  for( iT=list_begin(grades->students); iT!=NULL; iT=list_next(iT)){
    struct student* student = list_get(iT);
    if(student->id==id) {
      printf("%s %d:", student->name, student->id);
      struct iterator* cT;
      for( cT=list_begin(student->courses); cT!=NULL; cT=list_next(cT)){
	struct course* course = list_get(cT);
	printf(" %s %d", course->name, course->grade);
	if(list_next(cT)!=NULL)
	  printf(",");
      }
      printf("\n");
      return SUCCESS;
    }
  }
  return ERROR;
}


/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order 
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_all(struct grades *grades){
  //
  if(grades==NULL) return ERROR;
  
  struct iterator* iT;
  for( iT=list_begin(grades->students); iT!=NULL; iT=list_next(iT)){
    //
    struct student* student = list_get(iT);
    printf("%s %d:", student->name, student->id);
    struct iterator* cT;
    for( cT=list_begin(student->courses); cT!=NULL; cT=list_next(cT)){
      //
      struct course* course = list_get(cT);
      printf(" %s %d", course->name, course->grade);
      if(list_next(cT)!=NULL)
	printf(",");
    }
    printf("\n");
  }
  return SUCCESS;
}

