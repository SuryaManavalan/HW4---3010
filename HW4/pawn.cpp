#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "Pawn.h"

/**
  Creates a new Pawn object with coordinates x and y
  @param x int x coordinate
  @param y int y coordinate
  @param color QColor color of Pawn
*/
Pawn::Pawn(QColor color, const int x, const int y) {
  this->color_ = color;
  x_ = x;
  y_ = y;
}

QRectF Pawn::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);
}

QPainterPath Pawn::shape() const
{
    QPainterPath path;
    path.addEllipse(x_, y_, width_, width_);
    return path;
}


void Pawn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawEllipse(QRect(this->x_, this->y_, this->width_, this->width_));
    painter->setBrush(b);
}

void Pawn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit PawnSelected(this);
    emit DeletePawn(this);

    if(event->modifiers() == Qt::ShiftModifier){
        emit DrawLine(this);
    }

    this->color_.setRgb(rand()%256, rand()%256,rand()%256);
    update();
}

/**
  Calculates the distance between this Pawn and another Pawn.
  @param other Pawn object to calculate the distance to
*/
double Pawn::Distance(const Pawn &other) const {
  double distance = (x_ - other.get_x()) * (x_ - other.get_x());
  distance += (y_ - other.y_) * (y_ - other.y_);
  return sqrt(distance);
}


/**
  Makes it so the == operator will have the behavior that you
  expect when comparing Pawns.
  You can overload pretty much any operator in c++
  @param first Pawn left hand side of the expression
  @param other Pawn right hand side of the expression
*/
bool operator==(const Pawn &first, const Pawn &other) {
  return first.x_ == other.x_ && first.y_ == other.y_;
}
