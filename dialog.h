#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>

#include <QHBoxLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include  <QObject>
#include <QInputDialog>


#include <ellipse.h>
#include <rectangle.h>
#include <star.h>
#include <heart.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::Dialog *ui;

    QGraphicsScene* scene;
    QGraphicsView* view;
    QWidget* sidePanel;

    QPushButton*  createEllipseButton;
    QPushButton*  createRectButton;
    QPushButton* createStarButton;
    QPushButton* createHeartButton;
    QPushButton* rotationButton;
    QPushButton* scaleButton;
    QDoubleSpinBox *rotatinAngle;
    Shape *currentShape;

    //Ellipse* el;
    bool isCreatingEllipse = false;
    bool isCreatingRect = false;
    bool isCreatingStar = false;
    bool isCreatingHeart = false;

private slots:
    void onCreateEllipseClicked();
    void onCreateRectClicked();
    void onCreateStarClicked();
    void onCreateHeartClicked();
    void onRotateShapeClicked();
    void onScaleShapeClicked();
};
#endif // DIALOG_H
