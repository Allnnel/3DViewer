#ifndef SRC_VIEW_WIDGET_WIDGETFACTORY_SETTINGSFACTORY_H_
#define SRC_VIEW_WIDGET_WIDGETFACTORY_SETTINGSFACTORY_H_
#include "../settingswidget.h"
#include "widgetfactory.h"

class SettingsWidgetFactory : public WidgetFactory {
 public:
  SettingsWidgetFactory(SaveSettings& save)
      : createdWidget(nullptr), gl_(nullptr), save_(save) {}
  ~SettingsWidgetFactory() {
    if (createdWidget) delete createdWidget;
    createdWidget = nullptr;
  }

  QWidget* createWidget() override {
    createdWidget = new SettingsWidget(nullptr, save_, *gl_);
    return createdWidget;
  }

  void DeleteWidget() override {
    if (createdWidget) {
      delete createdWidget;
      createdWidget = nullptr;
    }
  }

  bool isEmpty() { return createdWidget == nullptr; }

  void SetGl(glwidget* gl) { gl_ = gl; }

 private:
  QWidget* createdWidget;
  glwidget* gl_;
  SaveSettings& save_;
};

#endif  // #define SRC_VIEW_WIDGET_WIDGETFACTORY_SETTINGSFACTORY_H_
