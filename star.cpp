#include "star.h"
#include<QBrush>
#include<QPainter>
#include <QtMath>

//Star::Star() {}

Star::Star(QGraphicsItem *parent) : Shape{parent}
{}



void Star::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Shape::paint(painter, option, widget);

    painter->setBrush(Qt::yellow);

    QPointF center = centerOfMass(this);
    int points = amountVert();
    qreal innerRadius = myRadius;
    qreal angleStep = 2 * M_PI / points;
    qreal a = boundingRect().width();
    qreal b = boundingRect().height();
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
    painter->drawPolygon(starPolygon);
}

double Star::countArea()
{
    qreal R = boundingRect().width()/2;
    qreal r = R * myRadius;
    return myAmountVert * (R*R - r*r) * qSin(M_PI/myAmountVert);
}

double Star::countPerimetr()
{
     return 2*myAmountVert * boundingRect().width()/2 * qSin(M_PI/myAmountVert);
}

