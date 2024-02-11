#include "affinetransformations.h"

namespace s21 {

void AffineTransformations::SetVertices(std::vector<double>& vertices) {
  vertices_ = nullptr;
  vertices_ = &vertices;
}

void AffineTransformations::MoveX(double step) noexcept {
  for (std::size_t i = 0; i < vertices_->size(); i += 3) {
    (*vertices_)[i] += step;
  }
}
void AffineTransformations::MoveY(double step) noexcept {
  for (std::size_t i = 1; i < vertices_->size(); i += 3) {
    (*vertices_)[i] += step;
  }
}
void AffineTransformations::MoveZ(double step) noexcept {
  for (std::size_t i = 2; i < vertices_->size(); i += 3) {
    (*vertices_)[i] += step;
  }
}
void AffineTransformations::RotateX(double axisX) noexcept {
  double angle_radians = axisX * 3.14 / 180.0;
  double cos_angle = std::cos(angle_radians);
  double sin_angle = std::sin(angle_radians);

  for (size_t i = 0; i < vertices_->size(); i += 3) {
    double y = (*vertices_)[i + 1];
    double z = (*vertices_)[i + 2];

    (*vertices_)[i + 1] = y * cos_angle - z * sin_angle;
    (*vertices_)[i + 2] = y * sin_angle + z * cos_angle;
  }
}
void AffineTransformations::RotateY(double axisY) noexcept {
  double angle_radians = axisY * 3.14 / 180.0;
  double cos_angle = std::cos(angle_radians);
  double sin_angle = std::sin(angle_radians);

  for (size_t i = 0; i < vertices_->size(); i += 3) {
    double x = (*vertices_)[i];
    double z = (*vertices_)[i + 2];

    (*vertices_)[i] = x * cos_angle - z * sin_angle;
    (*vertices_)[i + 2] = x * sin_angle + z * cos_angle;
  }
}
void AffineTransformations::RotateZ(double axisZ) noexcept {
  double angle_radians = axisZ * 3.14 / 180.0;
  double cos_angle = std::cos(angle_radians);
  double sin_angle = std::sin(angle_radians);

  for (size_t i = 0; i < vertices_->size(); i += 3) {
    double x = (*vertices_)[i];
    double y = (*vertices_)[i + 1];

    (*vertices_)[i] = x * cos_angle - y * sin_angle;
    (*vertices_)[i + 1] = x * sin_angle + y * cos_angle;
  }
}
void AffineTransformations::Scale(double step) noexcept {
  if (!vertices_->size()) {
    return;
  }
  for (double& vertic : (*vertices_)) {
    vertic *= step;
  }
}

void AffineTransformations::Centralization() {
  if (!vertices_->size()) {
    return;
  }
  double maxX = (*vertices_)[0];
  double maxY = (*vertices_)[1];
  double maxZ = (*vertices_)[2];
  double minX = (*vertices_)[0];
  double minY = (*vertices_)[1];
  double minZ = (*vertices_)[2];

  for (size_t i = 3; i < vertices_->size(); i += 3) {
    if (maxX < (*vertices_)[i]) maxX = (*vertices_)[i];
    if (maxY < (*vertices_)[i + 1]) maxY = (*vertices_)[i + 1];
    if (maxZ < (*vertices_)[i + 2]) maxZ = (*vertices_)[i + 2];
    if (minX > (*vertices_)[i]) minX = (*vertices_)[i];
    if (minY > (*vertices_)[i + 1]) minY = (*vertices_)[i + 1];
    if (minZ > (*vertices_)[i + 2]) minZ = (*vertices_)[i + 2];
  }

  double centerX = ((maxX - minX) / 2.0);
  double centerY = ((maxY - minY) / 2.0);
  double centerZ = ((maxZ - minZ) / 2.0);

  for (size_t i = 0; i < vertices_->size(); i += 3) {
    (*vertices_)[i] -= centerX;
    (*vertices_)[i + 1] -= centerY;
    (*vertices_)[i + 2] -= centerZ;
  }

  double maxDifference =
      std::max(std::max(maxX - minX, maxY - minY), maxZ - minZ);

  for (size_t i = 0; i < vertices_->size(); i += 3) {
    (*vertices_)[i] = ((*vertices_)[i] - minX) / maxDifference;
    (*vertices_)[i + 1] = ((*vertices_)[i + 1] - minY) / maxDifference;
    (*vertices_)[i + 2] = (((*vertices_)[i + 2] - minZ) / maxDifference);
  }
}
}  // namespace s21