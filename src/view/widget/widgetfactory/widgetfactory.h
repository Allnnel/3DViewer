#ifndef SRC_VIEW_WIDGET_WIDGETFACTORY_WIDGETFACTORY_H_
#define SRC_VIEW_WIDGET_WIDGETFACTORY_WIDGETFACTORY_H_

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class WidgetFactory {
 public:
  virtual QWidget* createWidget() = 0;
  virtual void DeleteWidget() = 0;
  virtual ~WidgetFactory() {}
};

#endif  // SRC_VIEW_WIDGET_WIDGETFACTORY_WIDGETFACTORY_H_
