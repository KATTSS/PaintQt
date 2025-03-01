#ifndef SHAPE_H
#define SHAPE_H

#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>


class Shape : public QGraphicsItem {
public:
    Shape();

    virtual double countPerimetr() = 0; // Периметр
    virtual double countArea() = 0;     // Площадь
    //virtual void moveItmoveIt();    // Передвижение за мышкой
    //virtual void deformatoin();     // Изменение формы
   // void rotation();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override;
    QPointF centerOfMass(const QGraphicsItem* item);

    bool Pressed;
    // int x;
    // int y;
    double width;
    double height;
    bool isDrawing=false;
    bool isCreated=false;
    bool Rotate=false;


protected:
    //bool isDrawing=false;     // Флаг рисования
    QPointF startPoint; // Начальная точка
    QPointF start; //начальная точка для угла при вращении
    //QLine startLine;
private:
    Shape* currentShape;

};

#endif // SHAPE_H
