#ifndef SRC_VIEW_WIDGET_WIDGETFACTORY_POSITIONFACTORY_H_
#define SRC_VIEW_WIDGET_WIDGETFACTORY_POSITIONFACTORY_H_
#include "../positionwidget.h"
#include "widgetfactory.h"

class PositionWidgetFactory : public WidgetFactory {
 public:
  PositionWidgetFactory()
      : controller_(nullptr),
        gl_(nullptr),
        created_widget_(nullptr),
        pos_save_(nullptr) {}
  ~PositionWidgetFactory() {
    if (created_widget_) delete created_widget_;
    created_widget_ = nullptr;
    if (pos_save_) delete pos_save_;
  }
  QWidget* createWidget() override {
    created_widget_ =
        new PositionWidget(nullptr, *pos_save_, *gl_, *controller_);
    return created_widget_;
  }

  void DeleteWidget() override {
    if (created_widget_) {
      delete created_widget_;
      created_widget_ = nullptr;
    }
  }

  void InitPosSave() {
    if (pos_save_) {
      delete pos_save_;
      pos_save_ = nullptr;
    }
    pos_save_ = new SavePosition;
  }

  void SetGl(glwidget* gl) { gl_ = gl; }
  void SetController(s21::Controller& controller) { controller_ = &controller; }
  bool isEmpty() { return created_widget_ == nullptr; }

 private:
  s21::Controller* controller_;
  glwidget* gl_;
  QWidget* created_widget_;
  SavePosition* pos_save_;
};

#endif  // SRC_VIEW_WIDGET_WIDGETFACTORY_POSITIONFACTORY_H_
