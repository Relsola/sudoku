#pragma once

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>

inline unsigned int random(int begin, int end) {
  assert(begin <= end && begin >= 0);
  srand(time(nullptr));
  return (unsigned int)rand() % (end - begin + 1) + begin;
}

inline void message(const char* msg = "", bool lf = true) {
  std::cout << msg;
  if (lf) std::cout << std::endl;
}

inline void message(const std::string& msg, bool lf = true) {
  message(msg.c_str(), lf);
}

#ifdef _WIN32
#include <conio.h>
#else
#ifdef __linux__
#include <fcntl.h>
#include <termio.h>

#include <cstdio>
#elif __APPLE__
#include <fcntl.h>
#include <termios.h>
#endif
inline char getch(void) {
  struct termios tmtemp, tm;
  int c;
  int fd = 0;
  if (tcgetattr(fd, &tm) != 0) { /*获取当前的终端属性设置，并保存到tm结构体中*/
    return -1;
  }
  tmtemp = tm;
  cfmakeraw(&tmtemp); /*将tetemp初始化为终端原始模式的属性设置*/
  if (tcsetattr(fd, TCSANOW, &tmtemp) != 0) { /*将终端设置为原始模式的设置*/
    return -1;
  }
  c = getchar();
  if (c == 27) /* ESC返回27，上下左右为(27,91,xx) 与ESC的27冲突 */
  {
    int back_flags = fcntl(fd, F_GETFL);
    /*将fd设置为非阻塞的，没有输入时可以立即返回*/
    fcntl(fd, F_SETFL, back_flags | O_NONBLOCK);
    c = getchar();
    if (c == EOF) {
      c = 27;
    } else {
      while ((c = getchar()) != EOF) {
      }
    }
    fcntl(fd, F_SETFL, back_flags);
  }
  if (tcsetattr(fd, TCSANOW, &tm) !=
      0) { /*接收字符完毕后将终端设置回原来的属性*/
    return 0;
  }
  return static_cast<char>(c);
}

inline char _getch() { return getch(); }
#endif

inline void cls(void) {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}
