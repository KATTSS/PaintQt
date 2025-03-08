#include "shape.h"
#include <QDebug>

Shape::Shape(QGraphicsItem *parent) :QGraphicsItem(parent), width(10), height(10), isDrawing(false), isCreated(false), sameSides(false){
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}

void Shape::scaling(qreal scalex, qreal scaley)
{
    setTransformOriginPoint(centerOfMass(this));
    QTransform trans;
    trans.scale(scalex, scaley);
    setTransform(trans);
    updateAll();

}

void Shape::organiseScaling(Shape *currentShape)
{
    currentShape->scale=true;
    currentShape->setFlag(QGraphicsItem::ItemIsMovable, false);
   // setTransformOriginPoint(mapToScene(boundingRect().topLeft()));
   // setTransformOriginPoint(centerOfMass(currentShape));
}

void Shape::rotation(qreal x, Shape *currentShape)
{
    //qDebug("in function");
    setTransformOriginPoint(centerOfMass(currentShape));
    //qDebug("center is located");
    currentShape->setRotation(x);
    updateAll();
}

void Shape::mousePressEvent(QGraphicsSceneMouseEvent *event) {


    if (event->button() == Qt::LeftButton && !isCreated) {
        isDrawing = true;
        startPoint = event->scenePos();
        setPos(startPoint);
        width = 0;
        height = 0;
    }
    // qInfo() << event->pos().x();
    // qInfo() << boundingRect().right();
    qInfo() << this->pos();
    qInfo() << this->boundingRect().topLeft();

    if (event->button() == Qt::LeftButton && scale && (qAbs(event->pos().x() - boundingRect().right()) < 5 || qAbs(event->pos().y() - boundingRect().bottom()) < 5 || qAbs(event->pos().x() - boundingRect().left()) < 5 || qAbs(event->pos().y() - boundingRect().height()) < 5)) {
            setFlag(QGraphicsItem::ItemIsMovable, false);
            isDrawing=true;
            //startPoint = event->pos();
            startPoint = this->pos();
            setPos(startPoint);


    }
    updateAll();
    // QGraphicsItem::mousePressEvent(event);
}
void Shape::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    if (isDrawing) {

        QPointF currentPoint = event->scenePos();
        if (scale) {

            qreal newWidth = qAbs(currentPoint.x() - startPoint.x());
            qreal newHeight = qAbs(currentPoint.y() - startPoint.y());
            qreal scaleX = newWidth / width;
            qreal scaleY = newHeight / height;
            scaling(scaleX, scaleY);

            width *= scaleX;
            height *= scaleY;
            if (sameSides) {
                width = height = std::min(width, height);
            }
        } else {
            width = qAbs(currentPoint.x() - startPoint.x());
            height = qAbs(currentPoint.y() - startPoint.y());
            if (sameSides) {
                width = height = std::min(width, height);
            }
        }
        //updateAll();
    }
    updateAll();
    QGraphicsItem::mouseMoveEvent(event);
}


void Shape::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton && isDrawing ) {
        isDrawing = false;
        if (!isCreated) {
            isCreated = true;
        }
        if (scale) {
            scale= false;
        }
    }
    setFlag(ItemIsMovable, true);
    updateAll();
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
        painter->drawRect(boundingRect());
    }
    if (currentShapeType==Shape::Ellipse) {
        painter->drawEllipse(boundingRect());
    }
}

QRectF Shape::boundingRect() const {
    return QRectF(0, 0, this->width, this->height);
}

QPointF Shape::centerOfMass(const QGraphicsItem* item) const {
    return item->boundingRect().center();
}

void Shape::updateAll()
{
    prepareGeometryChange();
    update();
    if (scene()) {
        scene()->update();
    }

}
