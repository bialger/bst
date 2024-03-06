#include <fstream>

#include "BstUnitTestSuite.hpp"

void BstUnitTestSuite::SetUp() {
  std::filesystem::create_directories(kTemporaryDirectoryName);
  std::ofstream{kTemporaryFileName.c_str()};
}

void BstUnitTestSuite::TearDown() {
  std::filesystem::remove_all(kTemporaryDirectoryName);
}
