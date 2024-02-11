#include "opengl.h"

glwidget::glwidget(QWidget* parent, s21::Controller& controller,
                   SaveSettings& save)
    : QOpenGLWidget(parent), controller_(controller), save_(save) {
  update();
}

void glwidget::initializeGL() {
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void glwidget::paintGL() {
  glClearColor(save_.color_back.redF(), save_.color_back.greenF(),
               save_.color_back.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (save_.projection_type) {
    glFrustum(-1, 1, -1, 1, 1, 100);
    glTranslatef(0, 0, -1.5);
  } else {
    glOrtho(-1, 1, -1, 1, -1, 100);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0, controller_.GetVertices().data());

  if (save_.is_on_vertex) DrawVertex();
  if (save_.is_on_edge) DrawEdges();

  glDisableClientState(GL_VERTEX_ARRAY);
}

void glwidget::DrawVertex() {
  if (!save_.vertex_type) glEnable(GL_POINT_SMOOTH);
  glPointSize(save_.size_vertex);
  glColor3d(save_.color_vertex.redF(), save_.color_vertex.greenF(),
            save_.color_vertex.blueF());
  glDrawArrays(GL_POINTS, 0, controller_.GetVertices().size() / 3);
  if (!save_.vertex_type) glDisable(GL_POINT_SMOOTH);
}

void glwidget::DrawEdges() {
  if (save_.edge_type) {
    glLineStipple(5, 0x3333);
    glEnable(GL_LINE_STIPPLE);
  }
  glLineWidth(save_.size_edge);
  glColor3d(save_.color_edge.redF(), save_.color_edge.greenF(),
            save_.color_edge.blueF());
  glDrawElements(GL_LINES, controller_.GetEdges().size(), GL_UNSIGNED_INT,
                 controller_.GetEdges().data());
  if (save_.edge_type) glDisable(GL_LINE_STIPPLE);
}

void glwidget::Update() { update(); }
