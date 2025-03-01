#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <shape.h>

class Ellipse : public Shape
{
public:
    Ellipse ();
    // Ellipse(double _radius);
    // Ellipse(int _x, int _y, double _radius);
    // Ellipse(QGraphicsScene* scene);

    double countArea() override;
    double countPerimetr() override;
    //void mousePressEvent(QGraphicsSceneMouseEvent *event) override; // отдично всё двигается и без переопределения
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    //
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    //

private:
    double radius=0;

    //QGraphicsScene* scene;
        // int x;
    // int y;
};

#endif // ELLIPSE_H
