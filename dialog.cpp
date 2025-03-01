#include "dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScreen>
#include <QApplication>

Dialog::Dialog(QWidget *parent) : QDialog(parent) {
    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    const int panelWidth = 200;
    int sceneWidth = screenWidth - panelWidth;

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, sceneWidth, screenHeight);
   // scene->setBackgroundBrush(Qt::white);

    view = new QGraphicsView(scene, this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    sidePanel = new QWidget(this);
    sidePanel->setFixedWidth(panelWidth);
    sidePanel->setStyleSheet("background-color: lightgray;");

    QVBoxLayout* panelLayout = new QVBoxLayout(sidePanel);
    createEllipseButton = new QPushButton("Создать эллипс", sidePanel);
    panelLayout->addWidget(createEllipseButton);
    panelLayout->addStretch();

    createRectButton = new QPushButton("Создать прямоугольник", sidePanel);
    panelLayout->addWidget(createRectButton);
    panelLayout->addStretch();

    rotationButton = new QPushButton("Вращать", sidePanel);
    panelLayout->addWidget(rotationButton);
    panelLayout->addStretch();

    scaleButton = new QPushButton("Изменить масштаб", sidePanel);
    panelLayout->addWidget(scaleButton);
    panelLayout->addStretch();

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(sidePanel);
    layout->addWidget(view);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    connect(createEllipseButton, &QPushButton::clicked, this, &Dialog::onCreateEllipseClicked);
    connect(createRectButton, &QPushButton::clicked, this, &Dialog::onCreateRectClicked);
   // connect(rotationButton, &QPushButton::clicked, this, &Dialog::onRotateShapeClicked);
   // connect(scaleButton, &QPushButton::clicked, this, &Dialog::onScaleShapeClicked);
    // Перехватываем события сцены
    view->viewport()->installEventFilter(this);

    setGeometry(0, 0, screenWidth, screenHeight);
    showMaximized();
}

Dialog::~Dialog() {}

bool Dialog::eventFilter(QObject *obj, QEvent *event)
{

        if (obj == view->viewport() && (isCreatingEllipse || isCreatingRect)) {
            if (event->type() == QEvent::MouseButtonPress) {
                QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
                if (mouseEvent->button() == Qt::LeftButton) {
                    QPointF clickPos = view->mapToScene(mouseEvent->pos());
                    if (isCreatingEllipse) {
                        Ellipse* ellipse = new Ellipse();
                        ellipse->setPos(clickPos);
                        scene->addItem(ellipse);
                        //ellipse->isDrawing = true;
                        isCreatingEllipse = false;
                        return true;
                    }
                    else if(isCreatingRect) {
                        Rectangle* rectangle = new Rectangle();
                        rectangle->setPos(clickPos);
                        scene->addItem(rectangle);
                        isCreatingRect=false;
                        return true;
                    }
                }
            }}
         return QDialog::eventFilter(obj, event);
}
void Dialog::onCreateEllipseClicked() {
    isCreatingEllipse = true;
}

void Dialog::onCreateRectClicked()
{
    isCreatingRect = true;
}

void Dialog::onRotateShapeClicked()
{
    if(currentShape) {
        currentShape->rotation();

    }
}

void Dialog::onScaleShapeClicked()
{
    if(currentShape) {
        currentShape->isDrawing=true;

    }
}
