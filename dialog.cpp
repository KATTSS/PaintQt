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

    createStarButton = new QPushButton("Создать звезду", sidePanel);
    panelLayout->addWidget(createStarButton);
    panelLayout->addStretch();

    createHeartButton = new QPushButton("Создать сердце", sidePanel);
    panelLayout->addWidget(createHeartButton);
    panelLayout->addStretch();

    QHBoxLayout *rotationParametr = new QHBoxLayout(sidePanel);
    rotationButton = new QPushButton("Вращать", sidePanel);
    rotationParametr->addWidget(rotationButton);
    //rotationParametr->addStretch();

    rotatinAngle = new QDoubleSpinBox(sidePanel);
    rotatinAngle->setMaximum(360.0);
    rotatinAngle->setMinimum(-360.0);
    rotationParametr->addWidget(rotatinAngle, 1, Qt::AlignCenter);
    panelLayout->addLayout(rotationParametr);
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
    connect(createStarButton, &QPushButton::clicked, this, &Dialog::onCreateStarClicked);
    connect(createHeartButton, &QPushButton::clicked, this, &Dialog::onCreateHeartClicked);
    connect(rotationButton, &QPushButton::clicked, this, &Dialog::onRotateShapeClicked);
    connect(scaleButton, &QPushButton::clicked, this, &Dialog::onScaleShapeClicked);
    // Перехватываем события сцены
    view->viewport()->installEventFilter(this);

    setGeometry(0, 0, screenWidth, screenHeight);
   // showMaximized();
}

Dialog::~Dialog() {}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPointF clickPos = event->pos() - view->pos();
        // qInfo() << clickPos;
        // QPointF clickPos = scene.;
        if (isCreatingEllipse) {
            Shape* ellipse = new Ellipse();
            ellipse->currentShapeType=Shape::Ellipse;
            ellipse->setPos(clickPos);
            // qInfo() << ellipse->pos();
            scene->addItem(ellipse);
            //ellipse->isDrawing = true;
            isCreatingEllipse = false;
        }
        else if(isCreatingRect) {
            Shape* rectangle = new Rectangle();
            rectangle->currentShapeType=Shape::Rectangle;
            rectangle->setPos(clickPos);
            scene->addItem(rectangle);
            isCreatingRect=false;
        }
        else if(isCreatingHeart) {
            Shape* heart = new Heart();
            heart->currentShapeType=Shape::Heart;
            heart->setPos(clickPos);
            scene->addItem(heart);
            isCreatingHeart=false;
        }
        else if(isCreatingStar) {
            Shape* star = new Star();
            star->currentShapeType=Shape::Star;
            bool ok;
            int vertices = QInputDialog::getInt(this, tr("Create Star"),
                                                tr("Enter number of vertices:"),
                                                5,
                                                3,
                                                50,
                                                1,
                                                &ok);
            Star* starr = dynamic_cast<Star*>(star);
            if (starr) {
                starr->setAmountVert(vertices);
            }
            starr->setPos(clickPos);
            scene->addItem(starr);
            isCreatingStar=false;
        }
    }
    QWidget::mousePressEvent(event);
}

void Dialog::onCreateEllipseClicked() {
    isCreatingEllipse = true;
}

void Dialog::onCreateRectClicked()
{
    isCreatingRect = true;
}

void Dialog::onCreateStarClicked()
{
    isCreatingStar = true;
}

void Dialog::onCreateHeartClicked()
{
    isCreatingHeart = true;
}

void Dialog::onRotateShapeClicked()
{
    if (scene->selectedItems().size() == 1) {
        QGraphicsItem *selectedItem = scene->selectedItems().first();

        currentShape = dynamic_cast<Shape*>(selectedItem);
    }
    if(currentShape) {
        qDebug("rotation button and object");
        currentShape->rotation(rotatinAngle->value(), currentShape);
        qDebug("rotation should be done and gone from func");
    }
}
void Dialog::onScaleShapeClicked() {
    if (scene->selectedItems().size() == 1) {
        QGraphicsItem *selectedItem = scene->selectedItems().first();
        currentShape = dynamic_cast<Shape*>(selectedItem);
        if (currentShape) {
            currentShape->organiseScaling(currentShape);
        }
    }
}
