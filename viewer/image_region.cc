//
// Document layout viewer.
//
// Copyright (C) 2009 Florent D'Halluin.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//

#include "image_region.hh"

ImageRegion::ImageRegion(region::RegionId id,
			 QString name,
			 QColor color,
			 QModelIndex index,
			 const QVector<QPoint>& points,
			 bool outline,
			 bool fill,
			 bool precise,
			 bool draw)
  : QGraphicsItem(0),
    id_(id),
    name_(name),
    color_(color),
    index_(index),
    shape_(),
    rect_(),
    outline_(outline),
    precise_(precise),
    fill_(fill),
    draw_(draw),
    selected_(false),
    alpha_(30)
{
  setCursor(Qt::ArrowCursor);
  setZValue(1);

  if (points.size() == 0)
    return;

  for (int i = 1; i < points.size(); ++i)
    shape_.lineTo(points[i] - points[0]);
  shape_.lineTo(QPoint(0, 0));

  rect_ = shape_.boundingRect();
  setPos(points[0]);

  prepareGeometryChange();
}

ImageRegion::~ImageRegion()
{
}

void
ImageRegion::paint(QPainter* painter,
		   const QStyleOptionGraphicsItem*,
		   QWidget*)
{
  if (!draw_ && !selected_)
    return;

  int width = 0;
  if (precise_)
    width = 1;

  if (outline_)
    painter->setPen(QPen(QBrush(color_), width, Qt::SolidLine,
			 Qt::SquareCap, Qt::MiterJoin));
  else
    painter->setPen(QColor(0, 0, 0, 0));

  QColor brush = color_;
  if (fill_)
    brush.setAlpha(alpha_);
  else
    brush.setAlpha(0);
  painter->setBrush(brush);

  painter->drawPath(shape_);

  if (selected_)
  {
    QPolygonF sceneRect = mapFromScene(scene()->sceneRect());
    QPainterPath path;
    path.addPolygon(sceneRect);
    QColor brush(255, 255, 255);
    brush.setAlpha(120);
    painter->setBrush(brush);
    painter->setPen(QColor(0, 0, 0, 0));
    painter->drawPath(path.subtracted(shape_));
  }
}

void
ImageRegion::select()
{
  if (!selected_)
  {
    selected_ = true;
    setZValue(2);
    scene()->invalidate();
    update();
  }
}

void
ImageRegion::deselect()
{
  if (selected_)
  {
    selected_ = false;
    scene()->invalidate();
    setZValue(1);
    update();
  }
}
