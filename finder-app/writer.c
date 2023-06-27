/*
Task 

1) One difference from the write.sh instructions in Assignment 1:  
    * You do not need to make your "writer" utility create directories which do not exist.  
    * You can assume the directory is created by the caller.

2) Setup syslog logging for your utility using the LOG_USER facility.

3) Use the syslog capability to write a message “Writing <string> to <file>” where <string> is the text 
string written to file (second argument) and <file> is the file created by the script.  
This should be written with LOG_DEBUG level.

4) Use the syslog capability to log any unexpected errors with LOG_ERR level.

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <syslog.h>
#include <errno.h>
#include <string.h>

void usage() {
    printf("Insufficient Arguments, exiting...");
}

int main(int argc, char *argv[]) {
    int fd = -1;
    ssize_t nr = 0;
    char *file_name_with_path = argv[1];
    char *string_to_write = argv[2];
    char perr_buff[100];

    if(argc != 3) {
        usage();
        return 1;
    }

    /* Setup syslog logging for your utility using the LOG_USER facility. */
    openlog("FINDER_APP", LOG_CONS | LOG_PID, LOG_USER);

start:
    /* Open file to write */
    fd = open (file_name_with_path,                                 /* File Path  */
                O_RDWR | O_CREAT,                                   /* File Flags */
                S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);   /* File Modes */

    if (fd == -1) {
        if (errno == EINTR) {
            goto start; /* oh shush */
        }
        if (errno == EAGAIN) {
                /* resubmit later */
        } else {
            sprintf(perr_buff, "Error opening file..errno = %d\n", errno);
            perror(perr_buff); /* error */
            syslog(LOG_USER | LOG_ERR, "Error opening file..errno = %d", errno);
        }   
    }

    /* write the string in 'buf' to 'fd' */
    nr = write (fd, string_to_write, strlen (string_to_write)); 
    if (nr == -1) {
        sprintf(perr_buff, "Error writing to file..errno = %d", errno);
        perror(perr_buff); /* error */
        syslog(LOG_USER | LOG_ERR, "Error writing to file..errno = %d", errno);
        goto close;
    } else {
        syslog(LOG_USER | LOG_DEBUG, "Writing %s to %s", string_to_write, file_name_with_path);
    }
        
close:
    /* Closing file */
    if (close (fd) == -1) {
        sprintf(perr_buff, "Error closing file close...errno = %d", errno);
        perror(perr_buff); /* error */
        syslog(LOG_USER | LOG_ERR, "Error closing file close...errno = %d", errno);
    }

    /* Close Syslog interface */    
    closelog(); 

    return 0;
}