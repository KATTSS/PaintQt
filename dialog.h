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
#include  <QObject>


#include <ellipse.h>
#include <rectangle.h>


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
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::Dialog *ui;

    QGraphicsScene* scene;
    QGraphicsView* view;
    QWidget* sidePanel;

    QPushButton*  createEllipseButton;
    QPushButton*  createRectButton;
    QPushButton* rotationButton;
    QPushButton* scaleButton;
    Shape *currentShape;

    //Ellipse* el;
    bool isCreatingEllipse = false;
    bool isCreatingRect = true;

private slots:
    void onCreateEllipseClicked();
    void onCreateRectClicked();
    void onRotateShapeClicked();
    void onScaleShapeClicked();
};
#endif // DIALOG_H
