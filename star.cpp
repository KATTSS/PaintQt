#include "star.h"
#include<QBrush>
#include<QPainter>
#include <QtMath>

//Star::Star() {}

Star::Star(QGraphicsItem *parent) : Shape{parent}
{}

QPainterPath Star::shape() const
{
    QPainterPath path;
    QPointF center = centerOfMass(this);
    int points = amountVert();
    qreal innerRadius = myRadius;
    qreal angleStep = 2 * M_PI / points;
    qreal a = width; //boundingRect().width();
    qreal b = height; //boundingRect().height();
    QVector<QPointF> starPoints;

    for (int i = 0; i < points; ++i) {
        qreal outerAngle = i * angleStep - M_PI / 2;
        qreal xOuter = a / 2 * qCos(outerAngle);
        qreal yOuter = b / 2 * qSin(outerAngle);
        starPoints.append(QPointF(xOuter + center.x(), yOuter + center.y()));

        if(this->currentShapeType == Shape::Star)
        {
            qreal innerAngle = outerAngle + angleStep / 2;
            qreal xInner = innerRadius * a / 2 * qCos(innerAngle);
            qreal yInner = innerRadius * b / 2 * qSin(innerAngle);
            starPoints.append(QPointF(xInner + center.x(), yInner + center.y()));
        }
    }
    QPolygonF starPolygon(starPoints);
    path.addPolygon(starPolygon);

    return path;
}

void Star::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Shape::paint(painter, option, widget);

    // Применяем текущий масштаб
    qreal scale = painter->transform().m11(); // Получаем текущий масштаб по оси X
    painter->setBrush(Qt::yellow);

    QPointF center = centerOfMass(this);
    int points = amountVert();
    qreal innerRadius = myRadius; // * scale; // Учитываем масштаб
    qreal angleStep = 2 * M_PI / points;
    qreal a = boundingRect().width() ;//* scale; // Учитываем масштаб
    qreal b = boundingRect().height() ; //* scale; // Учитываем масштаб
    QVector<QPointF> starPoints;

    for (int i = 0; i < points; ++i) {
        qreal outerAngle = i * angleStep - M_PI / 2;
        qreal xOuter = a / 2 * qCos(outerAngle);
        qreal yOuter = b / 2 * qSin(outerAngle);
        starPoints.append(QPointF(xOuter + center.x(), yOuter + center.y()));

        if (this->currentShapeType == Shape::Star) {
            qreal innerAngle = outerAngle + angleStep / 2;
            qreal xInner = innerRadius * a / 2 * qCos(innerAngle);
            qreal yInner = innerRadius * b / 2 * qSin(innerAngle);
            starPoints.append(QPointF(xInner + center.x(), yInner + center.y()));
        }
    }

    QPolygonF starPolygon(starPoints);
    painter->scale(scale, scale);
    painter->drawPolygon(starPolygon);
}

// void Star::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
// {
//     Q_UNUSED(option);
//     Q_UNUSED(widget);
//       Shape::paint(painter, option, widget);
//     painter->setBrush(Qt::yellow);

//     QPointF center = centerOfMass(this);
//     int points = amountVert();
//     qreal innerRadius = myRadius;
//     qreal angleStep = 2 * M_PI / points;
//     qreal a = boundingRect().width();
//     qreal b = boundingRect().height();
//     QVector<QPointF> starPoints;

//     for (int i = 0; i < points; ++i) {
//         qreal outerAngle = i * angleStep - M_PI / 2;
//         qreal xOuter = a / 2 * qCos(outerAngle);
//         qreal yOuter = b / 2 * qSin(outerAngle);
//         starPoints.append(QPointF(xOuter + center.x(), yOuter + center.y()));


//         if(this->currentShapeType == Shape::Star)
//         {
//             qreal innerAngle = outerAngle + angleStep / 2;
//             qreal xInner = innerRadius * a / 2 * qCos(innerAngle);
//             qreal yInner = innerRadius * b / 2 * qSin(innerAngle);
//             starPoints.append(QPointF(xInner + center.x(), yInner + center.y()));
//         }
//     }
//     QPolygonF starPolygon(starPoints);
//     painter->drawPolygon(starPolygon);


//     //Shape::paint(painter, option, widget);
// }

double Star::countArea()
{
    return 0.0;
}

double Star::countPerimetr()
{
    return 0.0;
}

