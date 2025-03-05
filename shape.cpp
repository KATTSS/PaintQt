#include "shape.h"


Shape::Shape() : Pressed(false), width(10), height(10), isDrawing(false), isCreated(false), sameSides(false){
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}

void Shape::rotation(qreal x, Shape *currentShape)
{
    //qDebug("in function");
    setTransformOriginPoint(centerOfMass(currentShape));
    //qDebug("center is located");
    currentShape->setRotation(x);
    //qDebug("rotation should be done");
    prepareGeometryChange();
    update();
    if(scene()) {
        scene()->update();
    }
}

void Shape::mousePressEvent(QGraphicsSceneMouseEvent *event) {


    if (event->button() == Qt::LeftButton && !isCreated) {
        isDrawing = true;
        startPoint = event->scenePos();
        setPos(startPoint);
        width = 0;
        height = 0;
    }
    if (event->button() == Qt::LeftButton && scale) {
            setFlag(QGraphicsItem::ItemIsMovable, false);
            isDrawing=true;
            startPoint = event->scenePos();
            setPos(startPoint);

    }

    prepareGeometryChange();
     update();
    if(scene()) {
        scene()->update();
    }
    QGraphicsItem::mousePressEvent(event);
}

void Shape::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (isDrawing) {
        QPointF currentPoint = event->scenePos();
        // if (scale) {
        //     scalingx = qAbs(currentPoint.x() - startPoint.x()) / width;
        //     scalingy = qAbs(currentPoint.y() - startPoint.y()) / height;
        // } else {
            width = qAbs(currentPoint.x() - startPoint.x());
            height = qAbs(currentPoint.y() - startPoint.y());
            if (sameSides) {
                width = height = std::min(width, height);
            }
       // }
        prepareGeometryChange();
        update();
        if (scene()) {
            scene()->update();
        }
    }

    QGraphicsItem::mouseMoveEvent(event);
}

void Shape::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton && isDrawing) {
        isDrawing = false;
        if (!isCreated) {
            isCreated = true;
        }
        if (scale) {
            scale = false;
        }
        setFlag(ItemIsMovable, true);
        prepareGeometryChange();
        update();
        if (scene()) {
            scene()->update();
        }
    }

    QGraphicsItem::mouseReleaseEvent(event);
}

void Shape::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift) {
        sameSides=true;
    }
    if (event->key() == Qt::Key_Delete && isSelected()) {
        delete this;
        return;
    }
     QGraphicsItem::keyPressEvent(event);
}

void Shape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(widget);

    if (option->state & QStyle::State_Selected) {
        QPen pen(Qt::red);
        pen.setStyle(Qt::DashLine);
        pen.setWidth(3);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
    }

    painter->setBrush(Qt::blue);
    painter->setPen(Qt::blue);

    if (currentShapeType==Shape::Rectangle) {
        // painter->setBrush(Qt::blue);
        // painter->setPen(Qt::blue);
        painter->drawRect(boundingRect());
    }
    if (currentShapeType==Shape::Ellipse) {
        // painter->setBrush(Qt::blue);
        // painter->setPen(Qt::blue);
        painter->drawEllipse(boundingRect());
    }

   // painter->restore();
}

QRectF Shape::boundingRect() const {
    return QRectF(0, 0, this->width, this->height);
}

QPointF Shape::centerOfMass(const QGraphicsItem* item)
{
        // QPainterPath path = item->shape();
        // QPolygonF polygon = path.toFillPolygon();
        // if (polygon.isEmpty()) {
        //     QRectF rect = item->boundingRect();
        //     return mapToScene(rect.center());
        // }

        // qreal area = 0.0, x_c = 0.0, y_c = 0.0;
        // int n = polygon.size();

        // for (int i = 0; i < n; ++i) {
        //     int j = (i + 1) % n;
        //     qreal factor = polygon[i].x() * polygon[j].y() - polygon[j].x() * polygon[i].y();
        //     area += factor;
        //     x_c += (polygon[i].x() + polygon[j].x()) * factor;
        //     y_c += (polygon[i].y() + polygon[j].y()) * factor;
        // }

        // area /= 2.0;
        // if (qAbs(area) < 1e-10) {
        //     return item->boundingRect().center();
        // }

        // x_c /= (6.0 * area);
        // y_c /= (6.0 * area);

        // return mapToScene(QPointF(x_c, y_c));
        return item->boundingRect().center();
}
