#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "redirection.h"

int apply_redirection(struct Command *cmd, struct RedirectBackup *backup) {
    backup->saved_stdin = -1;
    backup->saved_stdout = -1;

    if (cmd->input_file != NULL) {
        // fd - file descriptor / 文件描述符
        int fd = open(cmd ->input_file, O_RDONLY);
        if (fd < 0) {
            perror("open");
            return -1;
        }

        // int a = dup(b) - a->b' | b->b'
        // dup2(a,b) - a->a' | b->a'
        backup->saved_stdin = dup(STDIN_FILENO);
        if (backup->saved_stdin < 0) {
            perror("dup");
            close(fd);
            return -1;
        }

        if (dup2(fd, STDIN_FILENO) < 0) {
            perror("dup2");
            close(fd);
            close(backup->saved_stdin);
            backup->saved_stdin = -1;
            return -1;
        }

        close(fd);
    }

    if (cmd->output_file != NULL) {
        int flags = O_WRONLY | O_CREAT;
        int fd;

        // > / >>
        if (cmd->append_output) {
            flags |= O_APPEND;  // >>
        } else {
            flags |= O_TRUNC;   // >
        }

        fd = open(cmd->output_file, flags, 0644);
        if (fd < 0) {
            perror("open");
            return -1;
        }

        backup->saved_stdout = dup(STDOUT_FILENO);
        if (backup->saved_stdout < 0) {
            perror("dup");
            return -1;
        }

        if (dup2(fd, STDOUT_FILENO) < 0) {
            perror("dup2");
            close(fd);
            close(backup->saved_stdout);
            backup->saved_stdout = -1;
            return -1;
        }

        close(fd);
    }

    return 0;
}

void restore_redirection(struct RedirectBackup *backup) {
    if (backup->saved_stdin >= 0) {
        dup2(backup->saved_stdin, STDIN_FILENO);
        close(backup->saved_stdin);
        backup->saved_stdin = -1;
    }

    if (backup->saved_stdout >= 0) {
        dup2(backup->saved_stdout, STDOUT_FILENO);
        close(backup->saved_stdout);
        backup->saved_stdout = -1;
    }
}