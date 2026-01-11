#include "bfnpreviewwidget.h"
#include <QPainter>

BfnPreviewWidget::BfnPreviewWidget(QWidget *parent) : QWidget(parent)
{
    // Set size tối thiểu để không bị bé quá
    setMinimumHeight(150);
}

void BfnPreviewWidget::setText(const QString &text)
{
    m_text = text;
    update(); // Vẽ lại ngay lập tức
}

void BfnPreviewWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 1. Vẽ nền (Giả lập Message Box của game)
    painter.fillRect(rect(), Qt::black); // Nền đen

    // Vẽ khung viền trắng
    painter.setPen(QPen(Qt::white, 2));
    painter.drawRect(5, 5, width()-10, height()-10);

    // 2. Vẽ Text (Giả lập Font game)
    painter.setPen(Qt::white);

    // Dùng Font Consolas hoặc Monospace cho dễ nhìn
    QFont font("Consolas", 14);
    painter.setFont(font);

    // Vẽ chữ có tự động xuống dòng (Word Wrap)
    QRect textRect = rect().adjusted(20, 20, -20, -20); // Margin 20px
    painter.drawText(textRect, Qt::TextWordWrap, m_text);
}
