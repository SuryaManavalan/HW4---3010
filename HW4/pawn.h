#ifndef PAWN_H
#define PAWN_H

#include <QColor>
#include <QGraphicsItem>

class Pawn : public QObject, public QGraphicsItem {

    Q_OBJECT

public:
    Pawn(QColor color, const int x, const int y);  // constructor

    int get_x() const { return x_; }  // inline member function
    int get_y() const { return y_; }  // inline member function

    double Distance(const Pawn &other) const;  // member function

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    static int get_width() { return width_; };

// Day 2, Task 5, Step 1 here.
// @TODO:  Add a custom signal and the mousePressEvent function.
// Refer to Canvas to get started.

private:
  int x_;
  int y_;
  QColor color_;

  // all our Pawns will have a radius of 10 (they are circles)
  static const int width_ = 20;

  // if you declare the operator as a friend, then it isn't
  // part of the object
  // friend will let this method access the private fields
  friend bool operator==(const Pawn &first, const Pawn &other);

signals:
    // for distance
    void PawnSelected(Pawn * p);

    void DeletePawn(Pawn * p);

    void DrawLine(Pawn * p);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};  // class Pawn



#endif // Pawn_H
