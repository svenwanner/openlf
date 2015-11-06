/* Copyright (c) 2012, STANISLAW ADASZEWSKI
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of STANISLAW ADASZEWSKI nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL STANISLAW ADASZEWSKI BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "qneblock.h"

#include <QPen>
#include <QGraphicsScene>
#include <QFontMetrics>
#include <QPainter>
#include <QLabel>

#include <assert.h>

#include "qneport.h"

QNEBlock::QNEBlock(QGraphicsItem *parent) : QGraphicsPathItem(parent)
{
	QPainterPath p;
	p.addRoundedRect(-50, -15, 100, 30, 5, 5);
	setPath(p);
	setPen(QPen(Qt::darkGreen));
	setBrush(Qt::green);
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges);
	horzMargin = 20;
	vertMargin = 5;
	width = horzMargin;
	height = vertMargin;
}

QNEBlock::QNEBlock(DspComponent *comp, QGraphicsScene *scene, QGraphicsItem *parent)
: QNEBlock(parent)
{
  if (!std::isnan(comp->x) && !std::isnan(comp->y))
    this->setPos(comp->x,comp->y);
  scene->addItem(this);
  
  component = comp;
  
  //input and output ports MUST come first! (for getPortIdx!)
  for(int i=0;i<comp->GetInputCount();i++) {
    QNEPort *p = addPort(comp->GetInputName(i).c_str(), false, 0, 0);
    p->setNEBlock(this);
  }
  
  for(int i=0;i<comp->GetOutputCount();i++) {
    QNEPort *p = addPort(comp->GetOutputName(i).c_str(), true, 0, 0);
    p->setNEBlock(this);
  }
  
  addPort(comp->GetComponentName().c_str(), 0, QNEPort::NamePort);
}

QVariant QNEBlock::itemChange(GraphicsItemChange change, const QVariant &value)
{
  if (component && change == QGraphicsItem::ItemPositionHasChanged) {
    component->x = pos().x();
    component->y = pos().y();
  }
  return value;
}

QNEBlock::QNEBlock(DspCircuit *c, QGraphicsScene *scene, BlockType type, QPointF *pos, QGraphicsItem *parent)
: QNEBlock(parent)
{
  if (pos)
    this->setPos(*pos);
  scene->addItem(this);
  
  _blockType = type;
  circuit = c;
  
  if (_blockType == BlockType::Source) {
    for(int i=0;i<c->GetInputCount();i++) {
      QNEPort *p = addPort(c->GetInputName(i).c_str(), true);
      p->setNEBlock(this);
    }
  }
  else if (_blockType == BlockType::Sink) {
    for(int i=0;i<c->GetOutputCount();i++) {
      QNEPort *p = addPort(c->GetOutputName(i).c_str(), false);
      p->setNEBlock(this);
    }
  }
}

QNEBlock::BlockType QNEBlock::blockType()
{
  return _blockType;
}

void QNEBlock::removeFromCircuit()
{
  //FIXME how are connections handled?
  if (!component) {
    if (circuit) {
      if (_blockType == BlockType::Source)
        circuit->RemoveAllInputs();
      else if (_blockType == BlockType::Sink)
        circuit->RemoveAllOutputs();
    }
    return;
  }
  
  if (component) {
    DspCircuit *c = component->GetParentCircuit();
    assert(c);
    
    c->RemoveComponent(component);
  }
}

QNEPort* QNEBlock::addPort(const QString &name, bool isOutput, int flags, int ptr)
{  
	QNEPort *port = new QNEPort(this);
	port->setName(name);
	port->setIsOutput(isOutput);
	port->setNEBlock(this);
	port->setPortFlags(flags);
	port->setPtr(ptr);

	QFontMetrics fm(scene()->font());
	int w = fm.width(name);
	int h = fm.height();
	// port->setPos(0, height + h/2);
	if (w > width - horzMargin)
		width = w + horzMargin;
	height += h;

	QPainterPath p;
	p.addRoundedRect(-width/2, -height/2, width, height, 5, 5);
	setPath(p);

	int y = -height / 2 + vertMargin + port->radius();
    foreach(QGraphicsItem *port_, childItems()) {
		if (port_->type() != QNEPort::Type)
			continue;

		QNEPort *port = (QNEPort*) port_;
		if (port->isOutput())
			port->setPos(width/2 + port->radius(), y);
		else
			port->setPos(-width/2 - port->radius(), y);
		y += h;
	}

	return port;
}

int QNEBlock::getPortIdx(QNEPort *port)
{
  int port_idx = 0;
  QVector<QNEPort*> portlist = ports();
  for(auto it=portlist.begin();it!=portlist.end() && *it != port;it++)
    if ((*it)->isOutput() == port->isOutput())
      port_idx++;
    
  return port_idx;
}

QNEPort *QNEBlock::getPortByIdx(int idx, bool isOutput)
{
  int cur_idx = -1;
  QVector<QNEPort*> portlist = ports();
  for(int i=0;i<portlist.size();i++) {
    if (portlist[i]->isOutput() == isOutput)
      cur_idx++;
    if (cur_idx == idx)
      return portlist[i];
  }

  return NULL;
}

void QNEBlock::addInputPort(const QString &name)
{
	addPort(name, false);
}

void QNEBlock::addOutputPort(const QString &name)
{
	addPort(name, true);
}

void QNEBlock::addInputPorts(const QStringList &names)
{
	foreach(QString n, names)
		addInputPort(n);
}

void QNEBlock::addOutputPorts(const QStringList &names)
{
	foreach(QString n, names)
		addOutputPort(n);
}

#include <QStyleOptionGraphicsItem>

void QNEBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)
  
  if (component && component->hasError()) {
      if (isSelected()) {
        painter->setPen(QPen(Qt::darkRed));
        painter->setBrush(QColor(255,127,127));
      } else {
        painter->setPen(QPen(Qt::darkRed));
        painter->setBrush(Qt::red);
      }
  }
  else {
      if (isSelected()) {
        painter->setPen(QPen(Qt::darkYellow));
        painter->setBrush(Qt::yellow);
      } else {
        painter->setPen(QPen(Qt::darkGreen));
        painter->setBrush(Qt::green);
      }
    }
    
    painter->drawPath(path());
}

QNEBlock* QNEBlock::clone()
{
    QNEBlock *b = new QNEBlock(0);
    this->scene()->addItem(b);

	foreach(QGraphicsItem *port_, childItems())
	{
		if (port_->type() == QNEPort::Type)
		{
			QNEPort *port = (QNEPort*) port_;
			b->addPort(port->portName(), port->isOutput(), port->portFlags(), port->ptr());
		}
	}

	return b;
}

QVector<QNEPort*> QNEBlock::ports()
{
	QVector<QNEPort*> res;
	foreach(QGraphicsItem *port_, childItems())
	{
		if (port_->type() == QNEPort::Type)
			res.append((QNEPort*) port_);
	}
	return res;
}
/*
QVariant QNEBlock::itemChange(GraphicsItemChange change, const QVariant &value)
{

    Q_UNUSED(change);

	return value;
}*/

void QNEBlock::checkError()
{
  int text_w;
  if (!component)
    return;
  
  if (component->hasError() && !_error_label) {
    std::string msg = component->errorMsg();
    if (msg.size())
      _error_label = new QGraphicsTextItem(msg.c_str(), this);
    else
      _error_label = new QGraphicsTextItem("<UNKNOWN ERROR>", this);
    text_w = _error_label->boundingRect().width();
    _error_label->setTextWidth(2*boundingRect().width());
    if (text_w <= 2*boundingRect().width())
      _error_label->setPos(-text_w/2, height/2);
    else 
      _error_label->setPos(-width, height/2);
    scene()->addItem(_error_label);
    update(boundingRect());
  }
  else if (!component->hasError() && _error_label) {
    scene()->removeItem(_error_label);
    delete _error_label;
    _error_label = NULL;
    update(boundingRect());
  }
}

