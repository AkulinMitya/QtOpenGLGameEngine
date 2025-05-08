#ifndef LABELS_H
#define LABELS_H
#include <QString>
#include <QPointF>
#include <QFont>
#include <QColor>
#include <QPainter>
#include <vector>


struct UILabel {
    QString text;
    QPointF position; // 0.0 - 1.0 нормализованные координаты относительно окна
    QFont font;
    QColor color;
};

class UILabelManager {
public:
    void addLabel(const QString& text, const QPointF& pos, const QFont& font = QFont(), const QColor& color = Qt::white) {
        labels.push_back({text, pos, font, color});
    }

    void clear() {
        labels.clear();
    }

    void render(QPainter& painter, const QSize& windowSize) {
        for (const auto& label : labels) {
            painter.setPen(label.color);
            painter.setFont(label.font);
            QPoint pixelPos(label.position.x() * windowSize.width(), label.position.y() * windowSize.height());
            painter.drawText(pixelPos, label.text);
        }
    }

private:
    std::vector<UILabel> labels;
};

#endif // LABELS_H
