#include "tuplePrinter.hpp"
#include "CSVParser.hpp"
#include <string>

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cout << "Usage: ./CSVParser <filePath> <startLine> '<delimeter>'(optional)" << std::endl;
    return 1;
  }
  const std::string filePath(argv[1]);
  const int startLine = std::stoi(argv[2]);
  char delim = ',';
  if (argc >= 4)
    delim = *argv[3];
  std::ifstream file(filePath);
  CSVParser<int, double, std::string> parser(&file, startLine, delim);
  for (auto& t: parser) {
    std::cout << t << std::endl;
  }
  file.close();
  return 0;
}