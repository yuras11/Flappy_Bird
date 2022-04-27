#include "bird.h"

Bird::Bird(QPoint point_for_bird)
{
    rect.setRect(point_for_bird.x(), point_for_bird.y(), 2*radius, 2*radius);
}

void Bird::DrawBird(QPainter *painter, QPoint point, QImage image)
{
    painter->drawImage(point, image);
}
