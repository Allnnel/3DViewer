#ifndef SRC_VIEW_WIDGET_POSITIONWIDGET_H_
#define SRC_VIEW_WIDGET_POSITIONWIDGET_H_

#include <QWidget>

#include "../../back/rendering/opengl.h"
#include "../../controller/controller.h"
#include "../struct/nodesave.h"

namespace Ui {
class PositionWidget;
}

class PositionWidget : public QWidget {
  Q_OBJECT

 public:
  explicit PositionWidget(QWidget* parent, SavePosition& save_pos, glwidget& gl,
                          s21::Controller& controller);
  ~PositionWidget();

 private:
  SavePosition& save_pos_;
  glwidget& gl_;
  s21::Controller& controller_;
  Ui::PositionWidget* ui_;
  void ConnectFunc();
  void SetMoveX();
  void SetMoveY();
  void SetMoveZ();
  void SetRotateX();
  void SetRotateY();
  void SetRotateZ();
  void SetScale();
  void SaveMove();
};

#endif  // SRC_VIEW_WIDGET_POSITIONWIDGET_H_
