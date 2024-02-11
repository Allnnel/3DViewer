#include "settingswidget.h"

#include "ui_settingswidget.h"

SettingsWidget::SettingsWidget(QWidget* parent, SaveSettings& save,
                               glwidget& gl)
    : QWidget(parent), save_(save), gl_(gl), ui_(new Ui::SettingsWidget) {
  ui_->setupUi(this);
  SaveSetting();
  ConnectButton();
}

void SettingsWidget::SaveSetting() {
  ui_->checkBox_enge->setChecked(save_.is_on_edge);
  ui_->checkBox_vertex->setChecked(save_.is_on_vertex);
  ui_->button_drawing_type_edge->setCurrentIndex(save_.edge_type);
  ui_->button_drawing_type_vertex->setCurrentIndex(save_.vertex_type);
  ui_->button_drawing_type_projection->setCurrentIndex(save_.projection_type);
  ui_->button_size_edge->setValue(save_.size_edge);
  ui_->button_size_vertex->setValue(save_.size_vertex);
}

SettingsWidget::~SettingsWidget() { delete ui_; }

void SettingsWidget::ConnectButton() {
  connect(ui_->checkBox_enge, &QCheckBox::stateChanged, this,
          &SettingsWidget::CheckEdge);
  connect(ui_->checkBox_vertex, &QCheckBox::stateChanged, this,
          &SettingsWidget::CheckVertex);
  connect(ui_->button_drawing_type_edge, &QComboBox::currentIndexChanged, this,
          &SettingsWidget::CheckTypeEdge);
  connect(ui_->button_drawing_type_vertex, &QComboBox::currentIndexChanged,
          this, &SettingsWidget::CheckTypeVertex);
  connect(ui_->button_drawing_type_projection, &QComboBox::currentIndexChanged,
          this, &SettingsWidget::CheckTypeProjection);
  connect(ui_->button_size_edge, &QDoubleSpinBox::valueChanged, this,
          &SettingsWidget::CheckSizeEdge);
  connect(ui_->button_size_vertex, &QDoubleSpinBox::valueChanged, this,
          &SettingsWidget::CheckSizeVertex);
  connect(ui_->button_color_vertex, &QPushButton::clicked, this,
          &SettingsWidget::CheckColorVertex);
  connect(ui_->button_color_edge, &QPushButton::clicked, this,
          &SettingsWidget::CheckColorEdge);
  connect(ui_->button_backround_color, &QPushButton::clicked, this,
          &SettingsWidget::CheckColorBack);
}

void SettingsWidget::CheckEdge() {
  save_.is_on_edge = ui_->checkBox_enge->isChecked();
  gl_.Update();
}

void SettingsWidget::CheckVertex() {
  save_.is_on_vertex = ui_->checkBox_vertex->isChecked();
  gl_.Update();
}

void SettingsWidget::CheckTypeEdge() {
  save_.edge_type = ui_->button_drawing_type_edge->currentIndex();
  gl_.Update();
}

void SettingsWidget::CheckTypeVertex() {
  save_.vertex_type = ui_->button_drawing_type_vertex->currentIndex();
  gl_.Update();
}

void SettingsWidget::CheckTypeProjection() {
  save_.projection_type = ui_->button_drawing_type_projection->currentIndex();
  gl_.Update();
}

void SettingsWidget::CheckSizeEdge() {
  save_.size_edge = ui_->button_size_edge->value();
  gl_.Update();
}

void SettingsWidget::CheckSizeVertex() {
  save_.size_vertex = ui_->button_size_vertex->value();
  gl_.Update();
}

void SettingsWidget::CheckColorVertex() {
  QColor color(QColorDialog::getColor(Qt::white, this, tr("Select Color")));
  save_.color_vertex = color;
  gl_.Update();
}

void SettingsWidget::CheckColorEdge() {
  QColor color(QColorDialog::getColor(Qt::white, this, tr("Select Color")));
  save_.color_edge = color;
  gl_.Update();
}

void SettingsWidget::CheckColorBack() {
  QColor color(QColorDialog::getColor(Qt::white, this, tr("Select Color")));
  save_.color_back = color;
  gl_.Update();
}
