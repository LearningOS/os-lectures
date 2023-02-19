// list.c: list file names in the current directory
#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) { // Only list regular files
                printf("%s\n", ent->d_name);
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
        return 1;
    }
    return 0;
}

/* Here is the explanation for the code above:
1. All the required header files are included. The dirent.h header file is required for the DIR, struct dirent and the dirent functions. The stdio.h header file is required for the printf() function.

2. The main() function opens the current directory using the opendir() function. The opendir() function returns a pointer to the directory stream. If the directory stream is successfully opened, then the while loop is executed. The readdir() function returns a pointer to the next directory entry. The d_type member of the struct dirent structure indicates the type of the directory entry. The DT_REG constant indicates a regular file. The printf() function is used to print the name of the file. The closedir() function closes the directory stream.

3. If the directory stream could not be opened, then an error message is printed and the program returns 1. If the directory stream is successfully opened, then the program returns 0. */