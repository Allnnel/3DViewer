#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../back/modeltransform/affinetransformations.h"
#include "../back/modeltransform/parser.h"

namespace s21 {
class Controller {
 public:
  Controller(AffineTransformations& affine, Parser& parser)
      : affine_(affine), parser_(parser) {}
  ~Controller() {}
  void ReadFile(const std::string& str) {
    parser_.ReadFile(str);
    affine_.SetVertices(parser_.GetVertices());
  }
  const std::vector<double>& GetVertices() { return parser_.GetVertices(); }
  const std::vector<int>& GetEdges() { return parser_.GetEdges(); }
  void MoveX(double step) { affine_.MoveX(step); }
  void MoveY(double step) { affine_.MoveY(step); }
  void MoveZ(double step) { affine_.MoveZ(step); }
  void RotateX(double step) { affine_.RotateX(step); }
  void RotateY(double step) { affine_.RotateY(step); }
  void RotateZ(double step) { affine_.RotateZ(step); }
  void Scale(double step) { affine_.Scale(step); }
  bool GetError() { return parser_.GetError(); }
  void Centralization() { return affine_.Centralization(); }
  size_t GetCountEdges() { return parser_.GetCountEdges(); }

 private:
  AffineTransformations& affine_;
  Parser& parser_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_
