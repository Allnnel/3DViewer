#include "parser.h"

#include <iostream>
namespace s21 {
void Parser::ReadFile(const std::string& filename) {
  std::locale::global(std::locale("C"));
  std::ifstream file(filename);
  std::string line;
  if (!file.is_open()) {
    error = true;
    return;
  }
  vertices_.clear();
  error = 0;
  vertices_size_ = 0;
  edges_size_ = 0;
  edges_.clear();
  edges_.reserve(57222);
  while (std::getline(file, line)) {
    if (!line.find("v ")) {
      ParserVertices(line);
    }
    if (!line.find("f ")) {
      ParserEdges(line);
    }
  }
  file.close();
}

void Parser::ParserVertices(const std::string& line) {
  double x = 0.0, y = 0.0, z = 0.0;
  if (sscanf(line.c_str(), "v %lf %lf %lf", &x, &y, &z) == 3) {
    vertices_.push_back(x);
    vertices_.push_back(y);
    vertices_.push_back(z);
    vertices_size_++;
  }
}

void Parser::ParserEdges(const std::string& line) {
  std::istringstream iss(line);
  std::string token;
  int first_elem = -1;
  int index = 0;
  int first_step = -1;
  int vsize = vertices_size_;
  while (iss >> token && vsize) {
    if (!(index = std::atoi(token.c_str()))) {
      continue;
    }
    if (index < 0) {
      index += vsize + 1;
      if (index < 0) {
        continue;
      }
    } else if (index > vertices_size_) {
      continue;
    }
    --index;
    if (first_step == -1) {
      edges_.push_back(index);
      first_elem = index;
      first_step = 0;
    } else {
      edges_.push_back(index);
      edges_.push_back(index);
    }
  }
  if (vsize && edges_.size()) {
    edges_.push_back(first_elem);
    edges_size_++;
  }
}
Parser& Parser::GetInstance() {
  static Parser instance;
  return instance;
}
std::vector<double>& Parser::GetVertices() noexcept { return vertices_; }
std::vector<int>& Parser::GetEdges() noexcept { return edges_; }
bool Parser::GetError() const noexcept { return error; }
size_t Parser::GetCountEdges() const noexcept { return edges_size_; }

}  // namespace s21
