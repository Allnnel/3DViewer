#ifndef SRC_VIEW_STRUCT_NODESAVE_H_
#define SRC_VIEW_STRUCT_NODESAVE_H_

#include <QColor>

struct SaveSettings {
  bool projection_type;
  bool edge_type, vertex_type;
  bool is_on_edge, is_on_vertex;
  double size_edge, size_vertex;
  QColor color_edge, color_vertex, color_back;
};

struct SavePosition {
  double rotate_x, rotate_y, rotate_z;
  double move_x, move_y, move_z;
  double scale;
  SavePosition()
      : rotate_x(0),
        rotate_y(0),
        rotate_z(0),
        move_x(0),
        move_y(0),
        move_z(0),
        scale(1) {}
};

#endif  // SRC_VIEW_STRUCT_NODESAVE_H_
