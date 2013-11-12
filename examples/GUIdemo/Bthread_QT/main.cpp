#include <iostream>
#include "appthread.h"

int main(int argc, char *argv[]) {
  InputArgs args = {argc, argv};
  StartAppThread(args);
  sleep(10);
  return 0;
}