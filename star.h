#ifndef STAR_H
#define STAR_H
#include <shape.h>

class Star : public Shape
{

public:
    Star(QGraphicsItem *parent = nullptr);
   // QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    int amountVert() const { return myAmountVert; }
    void setAmountVert(int x=10) { myAmountVert = x; }
    qreal innerRadius() { return myRadius * 100.0; }
    void setInnerRadius(qreal x) { myRadius = x / 100.0; }

protected:
    double  countArea() override;
    double countPerimetr() override;
    // qreal innerRadius() { return myRadius * 100.0; }
    // int amountVert() const { return myAmountVert; }
private:
    int myAmountVert=5;
    qreal myRadius = 0.4;
};

#endif // STAR_H
