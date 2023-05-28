# Test command : ./writer.sh /tmp/aesd/assignment1/sample.txt ios

FILE_TO_CREATE=$1
WRITESTR=$2

if [ $# -lt 2 ]; then
    echo "Insufficient Arguments, exiting..."
    exit 1
fi

# if file doesn't exist, create it first
touch $FILE_TO_CREATE 2>/dev/null
if [ ! -f $FILE_TO_CREATE ]; then 
    CHECKDIR=$( dirname "$FILE_TO_CREATE" )

    # The directory with the file must exist
    mkdir -p "$CHECKDIR"

    # try creating the file again after creating the directory path
    touch $FILE_TO_CREATE
fi

echo "$WRITESTR" > $FILE_TO_CREATE
if [ ! $? -eq 0 ]; then
    echo "File could not be created...Exiting with failure status"
    exit 1
fi

echo "File created...$FILE_TO_CREATE with Contents = $WRITESTR"
exit 0
