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

//vigra wants to be first...
#include "clif/flexmav.hpp"

#include "qnodeseditor.h"

#include <QGraphicsScene>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QProcess>
#include <QTemporaryFile>

#include "qneport.h"
#include "qneconnection.h"
#include "qneblock.h"

#include "openlf.hpp"
#include "openlf/types.hpp"
#include "clif/clif.hpp"
#include "clif/clifviewcaller.hpp"

using namespace clif;
using namespace openlf;

QNodesEditor::QNodesEditor(QObject *parent) :
    QObject(parent)
{
	conn = 0;
}

void QNodesEditor::install(QGraphicsScene *s)
{
	s->installEventFilter(this);
	scene = s;
}

QGraphicsItem* QNodesEditor::itemAt(const QPointF &pos)
{
	QList<QGraphicsItem*> items = scene->items(QRectF(pos - QPointF(1,1), QSize(3,3)));

	foreach(QGraphicsItem *item, items)
		if (item->type() > QGraphicsItem::UserType)
			return item;

	return 0;
}

bool QNodesEditor::eventFilter(QObject *o, QEvent *e)
{
	QGraphicsSceneMouseEvent *me = (QGraphicsSceneMouseEvent*) e;

	switch ((int) e->type())
	{
	case QEvent::GraphicsSceneMousePress:
	{
		switch ((int) me->button())
		{
		case Qt::LeftButton:
		{
			QGraphicsItem *item = itemAt(me->scenePos());
			if (item && item->type() == QNEPort::Type)
                        {
                          conn = new QNEConnection(0);
                          scene->addItem(conn);
                          conn->setPort1((QNEPort*) item);
                          conn->setPos1(item->scenePos());
                          conn->setPos2(me->scenePos());
                          conn->updatePath();
                          
                          if (((QNEPort*)item)->isOutput()) {
                            if (_sel_port)
                              _sel_port->setSelected(false);

                            item->setSelected(true);
                            _sel_port = (QNEPort*)item;
                            emit portSelected((QNEPort*)item);
                          }
                          
				return true;
			} else if (item && item->type() == QNEBlock::Type)
			{
                                if ((dynamic_cast<QNEBlock*>(item))->blockType() == QNEBlock::BlockType::Regular)
                                  emit compSelected((dynamic_cast<QNEBlock*>(item))->component);
                                else
                                  emit compSelected((dynamic_cast<QNEBlock*>(item)));
			}
			break;
		}
		case Qt::RightButton:
		{
			QGraphicsItem *item = itemAt(me->scenePos());
                        if (item) {
                          if (item->type() == QNEConnection::Type) {
                            ((QNEConnection*)item)->removeCircuitConnection();
                            delete item;
                          }
                          else if (item->type() == QNEBlock::Type) {
                            ((QNEBlock*)item)->removeFromCircuit();
                            delete item;
                          }
                        }

			break;
		}
		}
	}
	case QEvent::GraphicsSceneMouseMove:
	{
		if (conn)
		{
			conn->setPos2(me->scenePos());
			conn->updatePath();
			return true;
		}
		break;
	}
	case QEvent::GraphicsSceneMouseRelease:
	{
		if (conn && me->button() == Qt::LeftButton)
		{
			QGraphicsItem *item = itemAt(me->scenePos());
			if (item && item->type() == QNEPort::Type)
			{
				QNEPort *port1 = conn->port1();
				QNEPort *port2 = (QNEPort*) item;

				if (port1->block() != port2->block() && port1->isOutput() != port2->isOutput() && !port1->isConnected(port2))
				{
					conn->setPos2(port2->scenePos());
					conn->setPort2(port2);
					conn->updatePath();
					conn = 0;
					return true;
				}
			}

			delete conn;
			conn = 0;
			return true;
		}
		break;
	}
        case QEvent::GraphicsSceneMouseDoubleClick:
        {
          QGraphicsItem *item = itemAt(me->scenePos());
          if (item && item->type() == QNEPort::Type && ((QNEPort*)item)->isOutput()) {
            show_in_clifview((QNEPort*)item);
          }
        }
        break;
	}
	return QObject::eventFilter(o, e);
}

void show_in_clifview(LF *lf)
{
  QTemporaryFile tmpfile;
  tmpfile.setAutoRemove(false);
  bool succ = tmpfile.open();
  char *filename = strdup(tmpfile.fileName().toUtf8().constData());
  tmpfile.close();

  if (!succ)
    abort();
  
  {
    ClifFile f_out;
    f_out.create(filename);
    Dataset out_set;
    out_set.link(f_out, lf->data);
    out_set.writeAttributes();
  }

  char* path = strdup(lf->path.generic_string().c_str());
  
  new ExternalClifViewer(filename, "default", path, true);
  
  free(filename);
  free(path);
}

void show_in_clifview(FlexMAV<3> *mav)
{
  QTemporaryFile tmpfile;
  tmpfile.setAutoRemove(false);
  bool succ = tmpfile.open();
  char *filename = strdup(tmpfile.fileName().toUtf8().constData());
  tmpfile.close();
  
  if (!succ)
    abort();
  
  {
    ClifFile f_out;
    f_out.create(filename);
    Dataset *dataset = f_out.createDataset();
    
    mav->write(dataset, "data");
    delete dataset;
  }
  
  new ExternalClifViewer(filename,"default","data", true);
  
  free(filename);
}

void show_in_clifview(QNEPort *port)
{
  LF *lf = NULL;
  FlexMAV<3> *mav = NULL;
  assert(port->isOutput());
  
  int idx = port->block()->getPortIdx(port);
  DspSignal* signal = port->block()->component->GetOutputSignal(idx);
  
  if (signal) {
    signal->GetValue(lf);
    signal->GetValue(mav);

    if (lf)
      show_in_clifview(lf);
    else if (mav)
      show_in_clifview(mav);
  }
}
