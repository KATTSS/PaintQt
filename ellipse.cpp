#include "ellipse.h"

Ellipse::Ellipse() : radius(10)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setPos(startPoint);
}

double Ellipse::countArea()
{
    return 3.14*radius*radius;
}

double Ellipse::countPerimetr()
{
    return 3.14*2*radius;
}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Q_UNUSED(option);
    Q_UNUSED(widget);

    if (option->state & QStyle::State_Selected) {
        QPen pen(Qt::red);
        pen.setStyle(Qt::DashLine);
        QPointF com = centerOfMass(this);
        QPointF localCom = mapFromScene(com);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
        pen.setStyle(Qt::SolidLine);
        painter->setPen(pen);
        painter->drawPoint(localCom);
    }

        painter->setBrush(Qt::blue);
        painter->setPen(Qt::blue);

    painter->drawEllipse(boundingRect());

}

QRectF Ellipse::boundingRect() const
{
     return QRectF(-radius, -radius, 2 * radius, 2 * radius);
}

QPainterPath Ellipse::shape() const {
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Ellipse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !isDrawing &&!isCreated) {
        isDrawing = true;
        startPoint = event->scenePos();
        setPos(startPoint);
        radius = 0;
        update();
    }
    // if (Rotate) {
    //     Shape::mousePressEvent(event);
    // }
    if(isDrawing){
        setFlag(QGraphicsItem::ItemIsMovable, false);
    }
    QGraphicsItem::mousePressEvent(event);
}

void Ellipse::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (isDrawing || !isCreated) {
        QPointF currentPoint = event->scenePos();
        radius = QLineF(startPoint, currentPoint).length();
        update();
        if (scene()) {
            scene()->update();
        }
    }
    // if (Rotate) {
    //     Shape::mouseMoveEvent(event);
    // }
     QGraphicsItem::mouseMoveEvent(event);
}

void Ellipse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && (isDrawing || !isCreated)) {
        isDrawing = false;
        isCreated = true;
        setFlag(QGraphicsItem::ItemIsMovable, true);
        update();
        if (scene()) {
            scene()->update();
        }
    }
    // if (Rotate) {
    //     Shape::mouseReleaseEvent(event);
    // }
        QGraphicsItem::mouseReleaseEvent(event);
}


