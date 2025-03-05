#ifndef SHAPE_H
#define SHAPE_H

#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QKeyEvent>
#include <cmath>

class Shape : public QGraphicsItem {
public:

    enum ShapeType {
        Rectangle, Ellipse
    };
    ShapeType currentShapeType;
    Shape();

    virtual double countPerimetr() = 0; // Периметр
    virtual double countArea() = 0;     // Площадь
    //virtual void deformatoin();     // Изменение формы
    void rotation(qreal x,Shape *currentShape);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPointF centerOfMass(const QGraphicsItem* item);


    double width;
    double height;
    bool isDrawing=false;
    bool isCreated=false;
    bool Pressed;
    bool sameSides=false;
    bool scale=false;


protected:

    QPointF startPoint; // Начальная точка

private:
    Shape* currentShape;

};

#endif // SHAPE_H
