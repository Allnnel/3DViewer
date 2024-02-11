#ifndef SRC_BACK_MODELTRANSFORM_PARSER_H_
#define SRC_BACK_MODELTRANSFORM_PARSER_H_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
class Parser {
 public:
  static Parser& GetInstance();
  void ReadFile(const std::string& filename);
  std::vector<double>& GetVertices() noexcept;
  std::vector<int>& GetEdges() noexcept;
  bool GetError() const noexcept;
  size_t GetCountEdges() const noexcept;

 private:
  Parser() : error(false), vertices_size_(0), edges_size_(0){};
  ~Parser(){};
  std::vector<double> vertices_;
  std::vector<int> edges_;
  bool error;
  int vertices_size_;
  size_t edges_size_;
  void ParserVertices(const std::string& line);
  void ParserEdges(const std::string& line);
  Parser(const Parser&) = delete;
  Parser& operator=(const Parser&) = delete;
};

}  // namespace s21
#endif  // SRC_BACK_MODELTRANSFORM_PARSER_H_