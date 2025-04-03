#include <iostream>
#include <sys/stat.h>

int main(void) {
  if (chdir("app") != 0) {
    std::cout << "AAAA";
    bool b; std::cin >> b;
    exit(EXIT_FAILURE);
  }
  system("cmake ..");
  system("cmake --build . -v");
}