#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

void center_text(const char *text) {
    struct winsize w;
    
    // Get terminal size
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("ioctl");
        return;
    }
    
    int terminal_width = w.ws_col; // Terminal width in columns
    int text_length = strlen(text); // Length of the text
    int padding = (terminal_width - text_length) / 2; // Calculate left padding
    
    // Ensure padding is not negative
    if (padding < 0) {
        padding = 0;
    }
    
    // Print spaces for padding and then the text
    printf("%*s%s\n", padding, "", text);
}

void logo(){
        printf("\t\t\t\t\t\t       *       *   * * * * *   * * * * *   * * *         * * * \n");
        center_text(" *       *   *       *   *       *   *     *     *       *");
        printf("\t\t\t\t\t\t       *       *   *       *   *       *   *       *   *\n");
        center_text("* * * * *   * * * * *   * * * * *   *       *     * * *  ");
        center_text("*       *   *       *   *   *       *       *           *");
        center_text("*       *   *       *   *     *     *     *     *       *");
        center_text("*       *   *       *   *       *   * * *         * * *  ");
        printf("\n");
        printf("\n");
        printf("\n");
}

