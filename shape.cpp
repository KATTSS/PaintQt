#include "shape.h"
#include <QPainter>

Shape::Shape() : Pressed(false), width(10), height(10), isDrawing(false), isCreated(false) {
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, false);
}

// void Shape::rotation()
// {
//     Rotate=true;
// }

// void Shape::rotation()
// {
//     setTransformOriginPoint(centerOfMass(this));
//     qreal angle = 30;
//     setRotation(angle);
//     update();
//     if(scene()) {
//         scene()->update();
//     }
// }

void Shape::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton && !isCreated) {
        isDrawing = true;
        //startPoint = event->pos();
        startPoint = event->scenePos();
        setPos(startPoint);
        width = 0;
        height = 0;
        prepareGeometryChange();
        update();
        if(scene()) {
            scene()->update();
        }
    }
    // if (event->button() == Qt::LeftButton && Rotate){
    //     setFlag(QGraphicsItem::ItemIsMovable, false);
    //     currentShape=this;
    //     //setTransformOriginPoint(centerOfMass(this));
    //     start =event->scenePos();
    // }

}

void Shape::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (isDrawing) {

        QPointF currentPoint = event->scenePos();
        width = qAbs(currentPoint.x() - startPoint.x());
        height = qAbs(currentPoint.y() - startPoint.y());
        prepareGeometryChange();
        update();
        if(scene()) {
            scene()->update();
        }
    }
    // else
    // if(Rotate) {
    //     setTransformOriginPoint(centerOfMass(this));

    //     QLineF line(start, event->scenePos());
    //     setRotation(line.angle());
    //     update();
        // if(scene()) {
        //     scene()->update();
        // }

    //}
    QGraphicsItem::mouseMoveEvent(event);
}

void Shape::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton && isDrawing && !isCreated) {
        isDrawing = false;
        isCreated=true;
        setFlag(ItemIsMovable, true);
        prepareGeometryChange();
        update();
        if(scene()) {
            scene()->update();
        }

    }
    QGraphicsItem::mouseReleaseEvent(event);
}

void Shape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // if (option->state & QStyle::State_Selected) {
    //     QPen pen(Qt::red);
    //     pen.setStyle(Qt::DashLine);
    //     painter->setPen(pen);
    //     painter->drawRect(boundingRect());
    // }

    painter->setBrush(Qt::blue);
    painter->setPen(Qt::blue);

    painter->drawRect(boundingRect());
    if (option->state & QStyle::State_Selected) {
        QPen pen(Qt::red);
        pen.setStyle(Qt::DashLine);
        pen.setWidth(3);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
    }
}

// QRectF Shape::boundingRect() const {
//     return QRectF(startPoint.x()-width/2, startPoint.y()-height/2, width, height);
// }
QRectF Shape::boundingRect() const {
    return QRectF(0, 0, width, height);
}

QPointF Shape::centerOfMass(const QGraphicsItem* item)
{
        QPainterPath path = item->shape();
        QPolygonF polygon = path.toFillPolygon();
        if (polygon.isEmpty()) {
            QRectF rect = item->boundingRect();
            return mapToScene(rect.center());
        }

        qreal area = 0.0, x_c = 0.0, y_c = 0.0;
        int n = polygon.size();

        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            qreal factor = polygon[i].x() * polygon[j].y() - polygon[j].x() * polygon[i].y();
            area += factor;
            x_c += (polygon[i].x() + polygon[j].x()) * factor;
            y_c += (polygon[i].y() + polygon[j].y()) * factor;
        }

        area /= 2.0;
        if (qAbs(area) < 1e-10) {
            return item->boundingRect().center();
        }

        x_c /= (6.0 * area);
        y_c /= (6.0 * area);

        return mapToScene(QPointF(x_c, y_c));
}
