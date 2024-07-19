#ifndef AXISTAG_H
#define AXISTAG_H

#include <QObject>
#include "qcustomplot.h"

class AxisTag : public QObject
{
  Q_OBJECT
public:
  explicit AxisTag(QCPAxis *parentAxis);
  virtual ~AxisTag();

  // 设置画笔画刷:
  void setPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setText(const QString &text);

  // 获取画笔画刷:
  QPen pen() const { return mLabel->pen(); }
  QBrush brush() const { return mLabel->brush(); }
  QString text() const { return mLabel->text(); }

  // 更新位置:
  void updatePosition(double value);

protected:
  QCPAxis *mAxis;
  QPointer<QCPItemTracer> mDummyTracer;
  QPointer<QCPItemLine> mArrow;
  QPointer<QCPItemText> mLabel;
};

#endif // AXISTAG_H
