#ifndef UTILITIES_H
#define UTILITIES_H

#ifdef _WIN32
  #include <windows.h>
#else
  #include <sys/ioctl.h>
  #include <stdio.h>
  #include <unistd.h>
#endif

namespace Utils {

void sleep(unsigned int ms) {
#ifdef _WIN32
  Sleep(ms);
#else
  const unsigned int microToMs = 1000;
  usleep(microToMs * ms);
#endif
}

void GetWindowSize(int &w, int &h) {
#ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
  struct winsize win_size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &win_size);
  w = win_size.ws_col;
  h = win_size.ws_row;
#endif
}

} // namespace Utils


#endif