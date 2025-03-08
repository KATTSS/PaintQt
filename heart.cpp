#include "heart.h"


double Heart::countArea()
{
    return 0.0;
}

double Heart::countPerimetr()
{
    return 0.0;
}

void Heart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Shape::paint(painter, option, widget);

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen(Qt::black, 2);
    painter->setPen(pen);

   // painter->translate(this->width/ 2, this->height/ 2);
  //  painter->scale(scaleFactor, scaleFactor);
    QRectF rect = boundingRect();
    QPointF center (centerOfMass(this).x(), boundingRect().bottom()-height*0.1);
    QPainterPath path;
    path.moveTo(center);

    path.cubicTo(
        QPointF(center.x() - width * 0.4, center.y() + height * 0.2),  // Контрольная точка 1
        QPointF(center.x() - width * 0.3, center.y() - height * 0.3),  // Контрольная точка 2
        QPointF(center.x(), rect.top() + height * 0.3)                 // Верхняя точка
        );

    // Правая кривая
    path.cubicTo(
        QPointF(center.x() + width * 0.3, center.y() - height * 0.3),  // Контрольная точка 1
        QPointF(center.x() + width * 0.4, center.y() + height * 0.2),  // Контрольная точка 2
       center                                                   // Возврат в нижнюю точку
        );

    painter->setBrush(Qt::darkRed);
    painter->drawPath(path);
    updateAll();
}
