#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

// Function to get the terminal width
int get_terminal_width() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns = 80; // Default width
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return columns;
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        return w.ws_col;
    }
    return 80; // Default width
#endif
}

// Function to print centered text
void print_centered(const char *text) {
    int terminal_width = get_terminal_width();
    int text_length = strlen(text);
    int spaces = (terminal_width - text_length) / 2;
    if (spaces > 0) {
        printf("%*s%s\n", spaces, "", text);
    } else {
        printf("%s\n", text);
    }
}
