/* Copyright (c) 2012, STANISLAW ADASZEWSKI
All rights reserved.

Modified by: Maximilian Diebold
			 Hendrik Siedelmann
			 Sven Wanner

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
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
*/


#include "qnemainwindow.h"

#include "circuitviewer.h"

/*
 * 
 * SIGNALS
 * 
 */

void QNEMainWindow::createActions()
{
  
  loadAct = new QAction(QIcon(":/open.png"), tr("&Load Circuit in new Window"), this);
  loadAct->setShortcuts(QKeySequence::Open);
  loadAct->setStatusTip(tr("Open a file"));
  connect(loadAct, SIGNAL(triggered()), this, SLOT(loadFile()));
  
  saveAct = new QAction(QIcon(":/save.png"), tr("&Save"), this);
  saveAct->setShortcuts(QKeySequence::Save);
  saveAct->setStatusTip(tr("Save a file"));
  connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));
  
  newAct = new QAction(QIcon(":/circuit.png"), tr("&New Circuit in new Window"), this);
  //saveAct->setShortcuts(QKeySequence::Save);
  newAct->setStatusTip(tr("New circuit"));
  connect(newAct, SIGNAL(triggered()), this, SLOT(new_circuit_viewer()));
  
  tabViewAct = new QAction(tr("&Use Tabs"), this);
  tabViewAct->setCheckable(true);
  tabViewAct->setChecked(true);
  connect(tabViewAct, SIGNAL(toggled(bool)), this, SLOT(view_mode_changed(bool)));
}
