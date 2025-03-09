#ifndef SHAPE_H
#define SHAPE_H

#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QMenu>
#include <cmath>

class Shape : public QGraphicsItem {
public:

    enum ShapeType {
        Rectangle, Ellipse, Star, Heart, Hexagon
    };
    ShapeType currentShapeType;
    Shape(QGraphicsItem *parent = nullptr);

    virtual double countPerimetr() = 0;
    virtual double countArea() = 0;
    void organiseScaling (Shape* currentShape);
    void rotation(qreal x,Shape *currentShape);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPointF centerOfMass(const QGraphicsItem* item) const;

    double width;
    double height;
    bool isDrawing=false;
    bool isCreated=false;
    bool sameSides=false;
    bool scale=false;
    QPointF startPoint;

protected:
    void updateAll();
    void scaling(qreal scalex, qreal scaley);


private:
    Shape* currentShape;

};

#endif // SHAPE_H
