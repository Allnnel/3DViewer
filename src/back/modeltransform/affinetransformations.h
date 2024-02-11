#ifndef SRC_BACK_MODELTRANSFORM_AFFINETRANSFORMATIONS_H_
#define SRC_BACK_MODELTRANSFORM_AFFINETRANSFORMATIONS_H_

#include <cmath>
#include <vector>

namespace s21 {
class AffineTransformations {
 public:
  void MoveX(double step) noexcept;
  void MoveY(double step) noexcept;
  void MoveZ(double step) noexcept;
  void RotateX(double axisX) noexcept;
  void RotateY(double axisY) noexcept;
  void RotateZ(double axisZ) noexcept;
  void Scale(double step) noexcept;
  void Centralization();
  void SetVertices(std::vector<double>& vertices);
  AffineTransformations() = default;
  ~AffineTransformations(){};

 private:
  std::vector<double>* vertices_;
};
}  // namespace s21
#endif  // SRC_BACK_MODELTRANSFORM_AFFINETRANSFORMATIONS_H_
