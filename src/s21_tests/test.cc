#include "../back/modeltransform/affinetransformations.h"
#include "../back/modeltransform/parser.h"
#include "../controller/controller.h"
#include "gtest/gtest.h"

TEST(Viewer, test1) {
  s21::Parser &parser = s21::Parser::GetInstance();
  s21::AffineTransformations afin;
  s21::Controller controller(afin, parser);
  std::string str = "s21_tests/1.obj";
  controller.ReadFile(str);
  std::vector<double> vertices = controller.GetVertices();
  std::vector<double> vertices_eq = {
      0.5,  0.5,  0.5,  0.5,  0.5,  -0.5, 0.5,  -0.5, 0.5,  0.5,  -0.5, -0.5,
      -0.5, 0.5,  -0.5, -0.5, 0.5,  0.5,  -0.5, -0.5, -0.5, -0.5, -0.5, 0.5,
      -0.5, 0.5,  -0.5, 0.5,  0.5,  -0.5, -0.5, 0.5,  0.5,  0.5,  0.5,  0.5,
      -0.5, -0.5, 0.5,  0.5,  -0.5, 0.5,  -0.5, -0.5, -0.5, 0.5,  -0.5, -0.5,
      -0.5, 0.5,  0.5,  0.5,  0.5,  0.5,  -0.5, -0.5, 0.5,  0.5,  -0.5, 0.5,
      0.5,  0.5,  -0.5, -0.5, 0.5,  -0.5, 0.5,  -0.5, -0.5, -0.5, -0.5, -0.5};
  for (size_t i = 0; i < vertices.size(); ++i) {
    EXPECT_EQ(vertices[i], vertices_eq[i]);
  }
  EXPECT_EQ(vertices.size(), static_cast<std::size_t>(72));
}

TEST(Viewer, test2) {
  s21::Parser &parser = s21::Parser::GetInstance();
  s21::AffineTransformations afin;
  s21::Controller controller(afin, parser);
  std::string str = "error.obj";
  controller.ReadFile(str);
  EXPECT_EQ(controller.GetError(), 1);
}

TEST(Viewer, test3) {
  s21::Parser &parser = s21::Parser::GetInstance();
  s21::AffineTransformations afin;
  s21::Controller controller(afin, parser);
  std::string str = "s21_tests/2.obj";
  controller.ReadFile(str);
  std::vector<int> edges = parser.GetEdges();
  std::vector<int> edges_eq = {20, 0, 0, 1, 1, 22, 22, 0, 0, 20};
  for (size_t i = 0; i < edges.size(); ++i) {
    EXPECT_EQ(edges[i], edges_eq[i]);
  }
  EXPECT_EQ(parser.GetCountEdges(), static_cast<std::size_t>(1));
}
TEST(Viewer, test4) {
  s21::Parser &parser = s21::Parser::GetInstance();
  s21::AffineTransformations afin;
  s21::Controller controller(afin, parser);
  std::string str = "s21_tests/1.obj";
  controller.ReadFile(str);
  std::vector<double> vertices_eq = controller.GetVertices();
  controller.MoveX(2);
  controller.MoveY(2);
  controller.MoveZ(2);
  std::vector<double> vertices = controller.GetVertices();
  for (size_t i = 0; i < vertices.size(); ++i) {
    EXPECT_EQ(vertices[i], vertices_eq[i] + 2);
  }
}
TEST(Viewer, test5) {
  s21::Parser &parser = s21::Parser::GetInstance();
  s21::AffineTransformations afin;
  s21::Controller controller(afin, parser);
  std::string str = "s21_tests/1.obj";
  controller.ReadFile(str);
  std::vector<double> vertices_eq = controller.GetVertices();
  double angle_radians = 2 * 3.14 / 180.0;
  double cos_angle = std::cos(angle_radians);
  double sin_angle = std::sin(angle_radians);
  controller.RotateX(2);
  std::vector<double> vertices = controller.GetVertices();
  for (size_t i = 0; i < vertices.size(); i += 3) {
    EXPECT_EQ(vertices[i + 1],
              vertices_eq[i + 1] * cos_angle - vertices_eq[i + 2] * sin_angle);
  }
  for (size_t i = 0; i < vertices.size(); i += 3) {
    EXPECT_EQ(vertices[i + 2],
              vertices_eq[i + 1] * sin_angle + vertices_eq[i + 2] * cos_angle);
  }
}
TEST(Viewer, test6) {
  s21::Parser &parser = s21::Parser::GetInstance();
  s21::AffineTransformations afin;
  s21::Controller controller(afin, parser);
  std::string str = "s21_tests/1.obj";
  controller.ReadFile(str);
  std::vector<double> vertices_eq = controller.GetVertices();
  double angle_radians = 2 * 3.14 / 180.0;
  double cos_angle = std::cos(angle_radians);
  double sin_angle = std::sin(angle_radians);
  controller.RotateY(2);
  std::vector<double> vertices = controller.GetVertices();
  for (size_t i = 0; i < vertices.size(); i += 3) {
    EXPECT_EQ(vertices[i],
              vertices_eq[i] * cos_angle - vertices_eq[i + 2] * sin_angle);
  }
  for (size_t i = 0; i < vertices.size(); i += 3) {
    EXPECT_EQ(vertices[i + 2],
              vertices_eq[i] * sin_angle + vertices_eq[i + 2] * cos_angle);
  }
}
TEST(Viewer, test7) {
  s21::Parser &parser = s21::Parser::GetInstance();
  s21::AffineTransformations afin;
  s21::Controller controller(afin, parser);
  std::string str = "s21_tests/1.obj";
  controller.ReadFile(str);
  std::vector<double> vertices_eq = controller.GetVertices();
  double angle_radians = 2 * 3.14 / 180.0;
  double cos_angle = std::cos(angle_radians);
  double sin_angle = std::sin(angle_radians);
  controller.RotateZ(2);
  std::vector<double> vertices = controller.GetVertices();
  for (size_t i = 0; i < vertices.size(); i += 3) {
    EXPECT_EQ(vertices[i],
              vertices_eq[i] * cos_angle - vertices_eq[i + 1] * sin_angle);
  }
  for (size_t i = 0; i < vertices.size(); i += 3) {
    EXPECT_EQ(vertices[i + 1],
              vertices_eq[i] * sin_angle + vertices_eq[i + 1] * cos_angle);
  }
}
TEST(Viewer, test8) {
  s21::Parser &parser = s21::Parser::GetInstance();
  s21::AffineTransformations afin;
  s21::Controller controller(afin, parser);
  std::string str = "s21_tests/1.obj";
  controller.ReadFile(str);
  std::vector<double> vertices_eq = controller.GetVertices();
  controller.Scale(2);
  std::vector<double> vertices = controller.GetVertices();
  for (size_t i = 0; i < vertices.size(); ++i) {
    EXPECT_EQ(vertices[i], vertices_eq[i] * 2);
  }
}
TEST(Viewer, test9) {
  s21::Parser &parser = s21::Parser::GetInstance();
  s21::AffineTransformations afin;
  s21::Controller controller(afin, parser);
  std::string str = "s21_tests/1.obj";
  controller.ReadFile(str);
  std::vector<double> vertices_eq = {
      0.5,  0.5,  0.5,  0.5,  0.5,  -0.5, 0.5,  -0.5, 0.5,  0.5,  -0.5, -0.5,
      -0.5, 0.5,  -0.5, -0.5, 0.5,  0.5,  -0.5, -0.5, -0.5, -0.5, -0.5, 0.5,
      -0.5, 0.5,  -0.5, 0.5,  0.5,  -0.5, -0.5, 0.5,  0.5,  0.5,  0.5,  0.5,
      -0.5, -0.5, 0.5,  0.5,  -0.5, 0.5,  -0.5, -0.5, -0.5, 0.5,  -0.5, -0.5,
      -0.5, 0.5,  0.5,  0.5,  0.5,  0.5,  -0.5, -0.5, 0.5,  0.5,  -0.5, 0.5,
      0.5,  0.5,  -0.5, -0.5, 0.5,  -0.5, 0.5,  -0.5, -0.5, -0.5, -0.5, -0.5};
  controller.Centralization();
  std::vector<double> vertices = controller.GetVertices();
  for (size_t i = 0; i < vertices.size(); ++i) {
    EXPECT_EQ(vertices[i], vertices_eq[i]);
  }
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
