#!/bin/bash

COURSE_NUM=$1

# validate num of arguments
if [[ $# != 1 ]]; then
    echo "Wrong number of arguments" 1>&2
    exit 1
fi

# searching for course
if [[ ! -e "$1.txt" ]]; then
    echo "Course not found" 1>&2
    exit 2
fi

# Search for dir
# and rm if available
if [[ -d "$1_stat" ]]; then
    rm -Rf "$1_stat"
fi
mkdir "$1_stat"

# cut second column
tail -n+2 $1.txt | cut -f2  > $1_stat/grades.txt
# create course_statistics.txt file
touch $1_stat/course_statistics.txt

#compile gcc
gcc -g -Wall calc_statistics.c -o prog.exe
./prog.exe $1_stat/grades.txt $1_stat/course_statistics.txt
cat $1_stat/course_statistics.txt
