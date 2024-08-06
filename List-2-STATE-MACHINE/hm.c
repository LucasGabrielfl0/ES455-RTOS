#include <stdio.h>

typedef enum {
    CODE,    // Initial state: processing normal code
    SLASH,   // Found a '/'
    COMMENT, // Inside a comment
    STAR     // Found a '*' inside a comment
} State;

int main() {
    int c;            // Current character
    State state = CODE;  // Initial state

    printf("Enter your C code (end with Ctrl+D):\n");

    while ((c = getchar()) != EOF) {
        switch (state) {
            case CODE:
                if (c == '/') {
                    state = SLASH;
                } else {
                    putchar(c); // Print normal code
                }
                break;
            case SLASH:
                if (c == '*') {
                    state = COMMENT;
                } else {
                    putchar('/'); // Not a comment, just a normal '/'
                    putchar(c);
                    state = CODE;
                }
                break;
            case COMMENT:
                if (c == '*') {
                    state = STAR;
                }
                // Do nothing, just skip the comment characters
                break;
            case STAR:
                if (c == '/') {
                    putchar(' '); // Replace comment with a space
                    state = CODE;
                } else if (c != '*') {
                    state = COMMENT;
                }
                // Do nothing if it's '*', stay in STAR state
                break;
        }
    }

    return 0;
}
