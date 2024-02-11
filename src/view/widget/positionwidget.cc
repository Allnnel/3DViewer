#include "positionwidget.h"

#include "ui_positionwidget.h"

PositionWidget::PositionWidget(QWidget* parent, SavePosition& save_pos,
                               glwidget& gl, s21::Controller& controller)
    : QWidget(parent),
      save_pos_(save_pos),
      gl_(gl),
      controller_(controller),
      ui_(new Ui::PositionWidget) {
  ui_->setupUi(this);
  SaveMove();
  ConnectFunc();
}

PositionWidget::~PositionWidget() { delete ui_; }

void PositionWidget::SaveMove() {
  ui_->spinbox_move_x->setValue(save_pos_.move_x);
  ui_->spinbox_move_y->setValue(save_pos_.move_y);
  ui_->spinbox_move_z->setValue(save_pos_.move_z);
  ui_->spinbox_rotate_x->setValue(save_pos_.rotate_x);
  ui_->spinbox_rotate_y->setValue(save_pos_.rotate_y);
  ui_->spinbox_rotate_z->setDecimals(save_pos_.rotate_z);
  ui_->spinbox_scale->setValue(save_pos_.scale);
}

void PositionWidget::ConnectFunc() {
  connect(ui_->spinbox_move_x, &QDoubleSpinBox::valueChanged, this,
          &PositionWidget::SetMoveX);
  connect(ui_->spinbox_move_y, &QDoubleSpinBox::valueChanged, this,
          &PositionWidget::SetMoveY);
  connect(ui_->spinbox_move_z, &QDoubleSpinBox::valueChanged, this,
          &PositionWidget::SetMoveZ);
  connect(ui_->spinbox_rotate_x, &QDoubleSpinBox::valueChanged, this,
          &PositionWidget::SetRotateX);
  connect(ui_->spinbox_rotate_y, &QDoubleSpinBox::valueChanged, this,
          &PositionWidget::SetRotateY);
  connect(ui_->spinbox_rotate_z, &QDoubleSpinBox::valueChanged, this,
          &PositionWidget::SetRotateZ);
  connect(ui_->spinbox_scale, &QDoubleSpinBox::valueChanged, this,
          &PositionWidget::SetScale);
}

void PositionWidget::SetMoveX() {
  controller_.MoveX(ui_->spinbox_move_x->value() - save_pos_.move_x);
  save_pos_.move_x = ui_->spinbox_move_x->value();
  gl_.Update();
}

void PositionWidget::SetMoveY() {
  controller_.MoveY(ui_->spinbox_move_y->value() - save_pos_.move_y);
  save_pos_.move_y = ui_->spinbox_move_y->value();
  gl_.Update();
}

void PositionWidget::SetMoveZ() {
  controller_.MoveZ(ui_->spinbox_move_z->value() - save_pos_.move_z);
  save_pos_.move_z = ui_->spinbox_move_z->value();
  gl_.Update();
}

void PositionWidget::SetRotateX() {
  controller_.RotateX(ui_->spinbox_rotate_x->value() - save_pos_.rotate_x);
  save_pos_.rotate_x = ui_->spinbox_rotate_x->value();
  gl_.Update();
}
void PositionWidget::SetRotateY() {
  controller_.RotateY(ui_->spinbox_rotate_y->value() - save_pos_.rotate_y);
  save_pos_.rotate_y = ui_->spinbox_rotate_y->value();
  gl_.Update();
}
void PositionWidget::SetRotateZ() {
  controller_.RotateZ(ui_->spinbox_rotate_z->value() - save_pos_.rotate_z);
  save_pos_.rotate_z = ui_->spinbox_rotate_z->value();
  gl_.Update();
}

void PositionWidget::SetScale() {
  controller_.Scale(ui_->spinbox_scale->value() / save_pos_.scale);
  save_pos_.scale = ui_->spinbox_scale->value();
  gl_.Update();
}
