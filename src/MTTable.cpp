#include <Rcpp.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include "MTDataFrame.h"
#include "MTSubTable.h"
#include "MTTable.h"
using namespace Rcpp;

MTTable::MTTable(std::vector<int> x, std::vector<int> y, std::vector<std::string> filepath){
  this->x = x;
  this->y = y;
  this->filepath = filepath;
}

// not defined in the class, but helper for csv line reading
void process_csv_line(MTSubTable& subtable, const char* start, const char* end) {
  std::string line(start, end);

  // vector to store the individual values
  std::vector<MTTable::DataType> values;

  // use stringstream to parse the line
  std::stringstream ss(line);
  std::string item;

  while (std::getline(ss, item, ',')) {
    values.push_back(item);
  }

  // add newly read row into data frame
  const std::vector<MTTable::DataType>& vals = values;
  df.add_row(vals);

  // // print the parsed values
  // for(const auto& value : values) {
  //   Rcout << value << " ";
  // }
  // Rcout << std::endl;
}

int MTTable::CsvToMTBin(std::string filepath){

  MTSubTable subtable(4, 3, 0.0, 0, 0);

  int fd = open(filepath.c_str(), O_RDONLY);
  if (fd == -1) {
    perror("open");
    return 1;
  }

  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    perror("fstat");
    close(fd);
    return 1;
  }

  size_t length = sb.st_size;
  void* addr = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
  if (addr == MAP_FAILED) {
    perror("mmap");
    close(fd);
    return 1;
  }

  char* data = static_cast<char*>(addr);
  const char* start = data;
  const char* end = data + length;

  while (start < end) {
    const char* newline = static_cast<const char*>(memchr(start, '\n', end - start));
    if (newline) {
      process_csv_line(subtable, start, newline);
      start = newline + 1;
    } else {
      process_csv_line(subtable, start, end);
      break;
    }
  }

  if (munmap(addr, length) == -1) {
    perror("munmap");
  }

  close(fd);

  return 0;

}
