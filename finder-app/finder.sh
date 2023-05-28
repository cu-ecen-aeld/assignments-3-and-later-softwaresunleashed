#!/bin/bash

PATH_TO_DIR=$1
STR_TO_SEARCH=$2

echo "Path to directory - $PATH_TO_DIR"
echo "String to search - $STR_TO_SEARCH"

if [ $# -lt 2 ]; then
    echo "Insufficient Arguments, exiting..."
    exit 1
fi

if [ ! -d $PATH_TO_DIR ]; then 
    echo "Directory not present, exiting..."
    exit 1
fi

NUM_OF_FILES_IN_DIRECTORY=$(find $PATH_TO_DIR -type f -name '*' | wc -l)
MATCHING_LINES=$(grep -rin $STR_TO_SEARCH $PATH_TO_DIR | wc -l)
echo "The number of files are $NUM_OF_FILES_IN_DIRECTORY and the number of matching lines are $MATCHING_LINES"

exit 0