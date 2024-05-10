#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    int src_fd, dst_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

  
    src_fd = open("source.txt", O_RDONLY);
    if (src_fd == -1) {
        perror("open source.txt");
        return 1;
    }

    
    dst_fd = open("destination.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (dst_fd == -1) {
        perror("open destination.txt");
        close(src_fd);
        return 1;
    }

    
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dst_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("write");
            close(src_fd);
            close(dst_fd);
            return 1;
        }
    }

    if (bytes_read == -1) {
        perror("read");
        close(src_fd);
        close(dst_fd);
        return 1;
    }


    close(src_fd);
    close(dst_fd);

    printf("File copied successfully.\n");
    return 0;
}
