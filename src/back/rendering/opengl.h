#ifndef SRC_BACK_RENDERING_GLWIDGET_H_
#define SRC_BACK_RENDERING_GLWIDGET_H_

#include <OpenGL/gl.h>

#include <QOpenGLWidget>
#include <QtOpenGL>

#include "../../controller/controller.h"
#include "../../view/struct/nodesave.h"

class glwidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit glwidget(QWidget* parent, s21::Controller& controller,
                    SaveSettings& save);
  ~glwidget(){};
  void Update();

 private:
  s21::Controller& controller_;
  SaveSettings& save_;
  void initializeGL();
  void paintGL();
  void DrawVertex();
  void DrawEdges();
};

#endif  // SRC_BACK_RENDERING_GLWIDGET_H_
