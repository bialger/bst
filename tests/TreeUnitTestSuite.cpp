#include <fstream>
#include <filesystem>

#include "TreeUnitTestSuite.hpp"

void TreeUnitTestSuite::SetUp() {
  std::filesystem::create_directories(kTemporaryDirectoryName);
  std::ofstream temp_file{kTemporaryFileName.c_str()};
}

void TreeUnitTestSuite::TearDown() {
  std::filesystem::remove_all(kTemporaryDirectoryName);
}
