#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PASS 55

struct CourseGrades {
  unsigned int students;  // [0-(2^32)-1]    Natural
  unsigned int max;       // [1,100]         Natural
  unsigned int min;       // [1,100]         Natural
  unsigned int median;    // [1,100]         Natural
  float        average;   // [1.000,100.000] Real
  float        pass;      // [1.0,100.0]     Real
  unsigned int histogram[100]; // [1,100]    Natural
};

void ScanGrades(struct CourseGrades *ptr, FILE *file);
void PrintStats(struct CourseGrades *ptr, FILE *file);


/**
 * @brief:  main function. 
 * @param:  num of args.
 * @param:  ptr to a string aguments.
 * @return: 0.
 * @note:
 */
int main(int argc, char *argv[]) {
    if (argc < 1 || argc > 3) {
        fprintf(stderr, "Error\n");
        return 1;
    }

    /* file reading and handeling routine */
    FILE *grades_file;
    grades_file = fopen(argv[1], "r");
    if(grades_file == NULL){
      fprintf(stderr, "Error: unable to open grades file\n");
      return 1;
    }
    
    struct CourseGrades CourseStats = {
      .students=0,
      .max=0,
      .min=100,
      .average=0.0,
      .median=0.0,
      .pass=0.0,
      .histogram={0}
    };
    ScanGrades(&CourseStats, grades_file);

    if(fclose(grades_file) != 0){
      fprintf(stderr, "Error: unable to close grades file\n");
      return 1;
    }
    

    /* file printing routine */
    FILE *print_file;
    print_file = fopen(argv[2], "w");
    if(print_file == NULL){
      fprintf(stderr, "Error: unable to open print file\n");
      return 1;
    }
    
    PrintStats(&CourseStats, print_file);
    
    if(fclose(print_file) != 0){
      fprintf(stderr, "Error: unable to close printing file\n");
      return 1;
    }
    
    return 0;
}



/**
 * @brief:  calculating statistics.
 * @param:  ptr to a struct.
 * @param:  ptr to a file.
 * @return: None.
 * @note:
 */
void ScanGrades(struct CourseGrades *ptr, FILE *file){

  unsigned int num=0;
  unsigned int sum=0;
  unsigned int passed=0;
  int med=0;

  while(fscanf(file, "%u\n", &num) != EOF){
    ptr->histogram[num-1] += 1;
    ptr->students += 1;
    sum += num;
    passed += (num<PASS) ? 0 : 1;
    if(num<ptr->min) ptr->min = num;
    if(num>ptr->max) ptr->max = num;
  }

  ptr->average = (float)sum/(float)ptr->students;
  ptr->pass = ((float)passed/(float)ptr->students)*100;
  
  med=(ptr->students+1)/2;
  for(int i=0; i<100; i++){
    med -= (ptr->histogram[i]);
    if(med <= 0){
      ptr->median = i+1;
      break;
    }
  }
}




/**
 * @brief:  printing statistics.
 * @param:  ptr to a struct.
 * @param:  ptr to a file.
 * @return: None
 * @note:
 */
void PrintStats(struct CourseGrades *ptr, FILE *file){

  fprintf(file, "num of students = %u\n",           (ptr->students));
  fprintf(file, "avg = %.3f\n",                     (ptr->average));
  fprintf(file, "the median is - %u\n",             (ptr->median));
  fprintf(file, "max grade = %u, min grade = %u\n", (ptr->max), (ptr->min));
  fprintf(file, "pass rate = %.2f%%\n",               (ptr->pass));

  for(int i=0; i<10; i++){
    for(int j=0; j<10; j++)
      fprintf(file, "%u ", ptr->histogram[(i*10)+j]); 
    fprintf(file, "\n");
  }
}
