// using read/write to copy input to output.
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

#define BUFSIZE 512

int main(int argc, char* argv[])
{
    int fd1, fd2, n;
    char buf[BUFSIZE];

    if(argc != 3)
    {
        fprintf(stderr, "usage: copy file1 file2\n");
        return 1;
    }

    // open file1 for reading
    if((fd1 = open(argv[1], O_RDONLY)) < 0)
    {
        fprintf(stderr, "cannot open %s\n", argv[1]);
        return 1;
    }

    // open/create file2 for writing
    if((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
    {
        fprintf(stderr, "cannot open %s\n", argv[2]);
        return 1;
    }

    // copy file1 to file2
    while((n = read(fd1, buf, BUFSIZE)) > 0)
        write(fd2, buf, n);

    close(fd1);
    close(fd2);
    return 0;
}


// The code is fairly simple. The first thing is to open the files. The first file is opened for reading, and the second file is opened for writing. If the second file does not exist, it is created. If the file does exist, it is truncated to zero length. The while loop reads from the first file and writes to the second file. The read() function returns the number of bytes read. If it returns zero, the end of file has been reached. If it returns a negative number, an error has occurred. The second file is closed, then the program exits.