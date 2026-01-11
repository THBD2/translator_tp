#ifndef BFNPREVIEWWIDGET_H
#define BFNPREVIEWWIDGET_H

#include <QWidget>

class BfnPreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BfnPreviewWidget(QWidget *parent = nullptr);
    void setText(const QString &text);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString m_text;
};

#endif // BFNPREVIEWWIDGET_H
