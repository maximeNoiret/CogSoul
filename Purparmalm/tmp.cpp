#include <termios.h>

struct termios saved_attributes;

const unsigned KReset   = 0;
const unsigned KBlack   = 30;
const unsigned KRed     = 31;
const unsigned KGreen   = 32;
const unsigned KYellow  = 33;
const unsigned KBlue    = 34;
const unsigned KMagenta = 35;
const unsigned KCyan    = 36;

const char KTokenPlayer1     = 'X';
const unsigned KColorPlayer1 = KYellow;

void reset_input_mode() {
    tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode() {
    struct termios tattr;

    /* Make sure stdin is a terminal. */
    if (!isatty (STDIN_FILENO))
    {
        cerr << "Not a terminal.\n";
        exit (EXIT_FAILURE);
    }

    /* Save the terminal attributes so we can restore them later. */
    tcgetattr (STDIN_FILENO, &saved_attributes);
    atexit (reset_input_mode);

    /* Set the funny terminal modes. */
    tcgetattr (STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
    tattr.c_cc[VMIN] = 0;
    tattr.c_cc[VTIME] = 1;
    tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

void clearScreen () {
    cout << "\033[H\033[2J";
}


void color (const unsigned & col) {
    cout << "\033[" << col <<"m";
}
