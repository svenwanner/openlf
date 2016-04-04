#include "qnesettings.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMetaObject>

#include <assert.h>
#include "types.hpp"
#include "clif/datastore.hpp"
#include "clif/core.hpp"
#include <QHeaderView>

#include "circuitviewer.h"

#define DPPT DspParameter::ParamType

static const int header_lines = 1;

void attachTreeItem(QTreeWidgetItem *w, clif::StringTree<clif::Attribute*, clif::Datastore*> *t)
{
	for (int i = 0; i<t->childCount(); i++) {
		QTreeWidgetItem *item = new QTreeWidgetItem(w, QStringList(QString(t->childs[i].val.first.c_str())));
		attachTreeItem(item, &t->childs[i]);
	}
}

void _load_existing_param(QGridLayout *layout, DspComponent *comp, int i, std::vector<DspCircuit*> &circuits)
{
  QLayoutItem *item = layout->itemAtPosition(i+header_lines, 2);
  if (!item || !item->widget())
    return;
  QWidget *w = item->widget();
  
  w->blockSignals(true);
  
  const DspParameter *param = comp->GetParameter(i);
  
  switch (param->Type()) {
    case DPPT::String : {
      QLineEdit *ed = static_cast<QLineEdit*>(w);
      const std::string *text = param->GetString();
      if (text)
        ed->setText(QString(text->c_str()));
      break;
    }
    case DPPT::Float : {      
      QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*>(w);
      const float *val = param->GetFloat();
      if (val)
        spinbox->setValue(*val);
      break;
    }
    case DPPT::Int : {
      QSpinBox *spinbox = static_cast<QSpinBox*>(w);
      const int *val = param->GetInt();
      if (val) {
        spinbox->setValue(*val);
      }
      break;
    }
    case DPPT::Pointer : {
      
		openlf::LF *d;
		param->GetPointer(d);
		if (d){
			QTreeWidget *treeWidget = static_cast<QTreeWidget*>(w);
			QHeaderView * pHeader = treeWidget->header();
			pHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
			pHeader->setStretchLastSection(false);

			clif::StringTree<clif::Attribute*, clif::Datastore*> tree = d->data->getTree();
			for (int i = 0; i<tree.childCount(); i++) {
				QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget, QStringList(QString(tree.childs[i].val.first.c_str())));
				item->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
				attachTreeItem(item, &tree.childs[i]);
			}
		}


      DspComponent *c;
      param->GetPointer(c);
	  if (c){
		  int found = -1;
		  QComboBox *combox = static_cast<QComboBox*>(w);
		  combox->clear();
		  int idx = 0;
		  for (int i = 0; i < circuits.size(); i++) {
			  if (comp->GetParentCircuit() == circuits[i])
				  continue;
			  //FIXME typename clash?
			  if (circuits[i] == c)
				  found = idx;
			  const char *name = circuits[i]->GetComponentName().c_str();
			  const char *type = circuits[i]->getTypeName().c_str();
			  char label[128];
			  if (strlen(name) + strlen(type) == 0) {
				  sprintf(label, "unknown %p", circuits[i]);
			  }
			  else {
				  if (!strlen(name))
					  name = "(unnamed)";
				  if (!strlen(type))
					  type = "(no type)";
				  sprintf(label, "%s (%s)", name, type);
			  }
			  combox->addItem(label, QVariant::fromValue((void*)circuits[i]));
			  idx++;
		  }

		  if (found != -1)
			  combox->setCurrentIndex(found);
		  else {
			  char label[128];
			  sprintf(label, "unknown %p", c);
			  combox->addItem(label, QVariant::fromValue((void*)c));
			  //combox->addItem(c->GetComponentName().c_str(), QVariant::fromValue((void*)c));
			  combox->setCurrentIndex(combox->count() - 1);
		  }
	  }
      break;
    }

    case DPPT::Bool : {
      QCheckBox *chk = static_cast<QCheckBox*>(w);
      const bool *val = param->GetBool();
      chk->setChecked(*val);
      break;
    }
  } 
  
  w->blockSignals(false);
}


void QNESettings::reload()
{
  attach(_viewer, _component, _circuits);
}


void QNESettings::attach(Circuit_Viewer *viewer, DspComponent *comp, std::vector<DspCircuit*> &circuits)
{
  if (_layout_w)
    delete _layout_w;
  
  _viewer = viewer;
  if (&_circuits != &circuits)
    _circuits = circuits;
  
  _layout_w = new QWidget(this);
  _layout.addWidget(_layout_w);
  
  QGridLayout *actual_layout = new QGridLayout(_layout_w);

  _layout_w->setLayout(actual_layout);
      
  _component = comp;
  
  for(int i=0;i<_component->GetParameterCount();i++) {
    int xpos = 0;
    const DspParameter *param = _component->GetParameter(i);
    
    QPushButton *chk = new QPushButton("reset");
    chk->setProperty("row", i+header_lines);
    chk->setProperty("idx", i);
    chk->setProperty("component", QVariant::fromValue((void*)_component));
	chk->setMinimumWidth(40);
	chk->setMaximumWidth(40);
    connect(chk, SIGNAL(clicked()), this, SLOT(settingOnOffReset()));
    actual_layout->addWidget(chk, i+header_lines, xpos++);
    actual_layout->addWidget(new QLabel(comp->GetParameterName(i).c_str()), i+header_lines, xpos++);
    
    switch (param->Type()) {
        case DPPT::String : {
          QLineEdit *ed = new QLineEdit(_layout_w);
          actual_layout->addWidget(ed, i+header_lines, xpos++);
          ed->setProperty("component", QVariant::fromValue((void*)_component));
          ed->setProperty("idx", i);
		  ed->setMinimumWidth(180);
		  ed->setMaximumWidth(180);
          connect(ed, SIGNAL(textChanged(QString)), this, SLOT(textSettingChanged(QString)));
          
		  QPushButton *btn = new QPushButton(_layout_w);
		  btn->setText("...");
		  btn->setMinimumWidth(25);
		  btn->setMaximumWidth(25);
          actual_layout->addWidget(btn, i+header_lines, xpos++);		  
          btn->setProperty("ed", QVariant::fromValue(ed));
          connect(btn, SIGNAL(clicked()), this, SLOT(selFileClicked()));
          break;
        }
      case DPPT::Float : {
          QDoubleSpinBox *spinbox = new QDoubleSpinBox(_layout_w);
          spinbox->setMinimum(-100000000000);
          spinbox->setMaximum(100000000000);
		  spinbox->setDecimals(5);
		  spinbox->setMinimumWidth(180);
		  spinbox->setMaximumWidth(180);
          actual_layout->addWidget(spinbox, i+header_lines, xpos++);
          spinbox->setProperty("component", QVariant::fromValue((void*)_component));
          spinbox->setProperty("idx", i);
          connect(spinbox, SIGNAL(valueChanged(double)), this, SLOT(floatSettingChanged(double)));
          break;
      }
      case DPPT::Int : {
          QSpinBox *spinbox = new QSpinBox(_layout_w);
          actual_layout->addWidget(spinbox, i+header_lines, xpos++);
          spinbox->setProperty("component", QVariant::fromValue((void*)_component));
		  spinbox->setMinimumWidth(180);
		  spinbox->setMaximumWidth(180);
          spinbox->setProperty("idx", i);
          spinbox->setMinimum(INT_MIN);
          spinbox->setMaximum(INT_MAX);
          connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(intSettingChanged(int)));
          break;
      }
      case DPPT::Pointer : {

		openlf::LF *d;
		param->GetPointer(d);
		if (d){
			QTreeWidget *treeWidget = new QTreeWidget();
			treeWidget->setProperty("component", QVariant::fromValue((void*)_component));
			treeWidget->setProperty("idx", i);
			treeWidget->setHeaderHidden(true);
			treeWidget->setMinimumWidth(180);
			treeWidget->setMaximumWidth(180);
			treeWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
			treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		    actual_layout->addWidget(treeWidget, i + header_lines, xpos++);
			connect(treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(slot_treedoubleclicked(QTreeWidgetItem*, int)));
		}

		DspComponent *c;
		param->GetPointer(c);
		if (c){
			QComboBox *combox = new QComboBox(_layout_w);
			combox->setMinimumWidth(180);
			combox->setMaximumWidth(180);
			actual_layout->addWidget(combox, i + header_lines, xpos++);
			combox->setProperty("component", QVariant::fromValue((void*)_component));
			combox->setProperty("idx", i);
			connect(combox, SIGNAL(currentIndexChanged(int)), this, SLOT(circuitSelected(int)));
		}

		else{
			QLineEdit *combox = new QLineEdit(_layout_w);
			combox->setMinimumWidth(180);
			combox->setMaximumWidth(180);
			combox->setEnabled(false);
			actual_layout->addWidget(combox, i + header_lines, xpos++);
			combox->setProperty("component", QVariant::fromValue((void*)_component));
			combox->setProperty("idx", i);
		}

		break;
      }
      case DPPT::Bool : {
          QCheckBox *chk_box = new QCheckBox(_layout_w);
          actual_layout->addWidget(chk_box, i+header_lines, xpos++);
          chk_box->setProperty("component", QVariant::fromValue((void*)_component));
          chk_box->setProperty("idx", i);
          connect(chk_box, SIGNAL(stateChanged(int)), this, SLOT(boolChanged(int)));

          break;
      }
    }
    
    //FIXME this emits setting changed signals!
    _load_existing_param(actual_layout, _component, i, _circuits);
    
    QLineEdit *ed = new QLineEdit(_layout_w);
    actual_layout->addWidget(ed, i+header_lines, xpos++);
    ed->setProperty("component", QVariant::fromValue((void*)_component));
    ed->setProperty("idx", i);
	ed->setMinimumWidth(120);
	ed->setMaximumWidth(120);
    ed->setText(QString(_component->GetParentCircuit()->GetComponentParameterAlias(_component, i).c_str()));
    connect(ed, SIGNAL(textChanged(QString)), this, SLOT(aliasChanged(QString)));

    /*for(int n=1;n<actual_layout->columnCount();n++) {
      QLayoutItem *l = actual_layout->itemAtPosition(i+header_lines, n);
      if (l && l->widget())
        l->widget()->setEnabled(false);
    }*/
  }
}

QTreeWidgetItem* getTreeRoot(QTreeWidgetItem* item, int column, std::vector<std::string> *tmp){

	QTreeWidgetItem* item2 = item->parent();
	if (item2){
		//printf(item2->text(column).toStdString().c_str());
		tmp->push_back(item2->text(column).toStdString());
		item2 = getTreeRoot(item2, column, tmp);
		delete item2;
	}
	else
		return item2;
}

void QNESettings::slot_treedoubleclicked(QTreeWidgetItem* item, int column){

	//printf(item->text(column).toStdString().c_str());
	//printf("\n");
	clif::cpath tmpRoot;
	std::vector<std::string> tmp;
	QTreeWidgetItem* item2 = getTreeRoot(item, column, &tmp);
	for (int i = 0; i < tmp.size(); i++){
		tmpRoot /= tmp[tmp.size() - i - 1];
	}
	tmpRoot /= item->text(column).toStdString();
	QString tmp33(tmpRoot.generic_string().c_str());
	DspComponent *comp = (DspComponent*)sender()->property("component").value<void*>();
	//FIXME:Dynamically detection of correct widget!?
	comp->SetParameter(0, DspParameter(DPPT::String, tmp33.toStdString()));
	emit settingChanged();

}


void QNESettings::attach(QNEBlock *block)
{
  assert(block->blockType() != QNEBlock::BlockType::Regular);
  
  if (_layout_w)
    delete _layout_w;
  
  _layout_w = new QWidget(this);
  _layout.addWidget(_layout_w);

   QFormLayout *actual_layout = new QFormLayout(_layout_w);
  _layout_w->setLayout(actual_layout);
  
  QSpinBox *spinbox = new QSpinBox(_layout_w);
  QHBoxLayout *hbox = new  QHBoxLayout;
  hbox->addWidget(spinbox);
  spinbox->setProperty("block", QVariant::fromValue((void*)block));
  int portcount = block->ports().size();
  spinbox->setValue(portcount);
  spinbox->setMinimum(portcount);
  connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(portCountChanged(int)));
  
  actual_layout->addRow(tr("Pad Count"), hbox);
}

void QNESettings::textSettingChanged(QString text)
{
  DspComponent *comp = (DspComponent*)sender()->property("component").value<void*>();
  int idx = sender()->property("idx").value<int>();

  comp->SetParameter(idx, DspParameter(DPPT::String, text.toStdString()));
  
  emit settingChanged();
}

void QNESettings::aliasChanged(QString text)
{
  DspComponent *comp = (DspComponent*)sender()->property("component").value<void*>();
  int idx = sender()->property("idx").value<int>();

  comp->GetParentCircuit()->SetComponentParameterAlias(text.toUtf8().constData(), comp, idx);
  
  emit settingChanged();
}

void QNESettings::floatSettingChanged(double val)
{
  DspComponent *comp = (DspComponent*)sender()->property("component").value<void*>();
  int idx = sender()->property("idx").value<int>();
  
  comp->SetParameter(idx, DspParameter(DPPT::Float, (float)val));
  
  emit settingChanged();
}


void QNESettings::intSettingChanged(int val)
{
  DspComponent *comp = (DspComponent*)sender()->property("component").value<void*>();
  int idx = sender()->property("idx").value<int>();
  
  comp->SetParameter(idx, DspParameter(DPPT::Int, val));
  
  emit settingChanged();
}

void QNESettings::boolChanged(int val)
{
  DspComponent *comp = (DspComponent*)sender()->property("component").value<void*>();
  int idx = sender()->property("idx").value<int>();
  
  comp->SetParameter(idx, DspParameter(DPPT::Bool, val));
  
  emit settingChanged();
}

void QNESettings::selFileClicked()
{
  QString path = QFileDialog::getOpenFileName(this, tr("select file or directory"));
  
  QLineEdit *ed = sender()->property("ed").value<QLineEdit*>();
  
  ed->setText(path);
}

//FIXME change circuit input count on delete input port item!
void QNESettings::portCountChanged(int val)
{
  QNEBlock *block = (QNEBlock*)sender()->property("block").value<void*>();
  char buf[64];
  
  //FIXME update when special ports (name,type) are gone!
  for(int i=block->ports().size();i<val;i++) 
    if (block->blockType() == QNEBlock::BlockType::Source) {
      sprintf(buf, "input_%d", i);
      block->circuit->AddInput(buf);
      block->addOutputPort(buf);
    }
    else {
      sprintf(buf, "output_%d", i);
      block->circuit->AddOutput(buf);
      block->addInputPort(buf);
    }
}

void QNESettings::settingOnOffReset()
{
  int row = sender()->property("row").value<int>();
    
  QGridLayout *grid = static_cast<QGridLayout*>(_layout_w->layout());
  
  /*for(int i=1;i<grid->columnCount();i++) {
    QLayoutItem *l = grid->itemAtPosition(row, i);
    if (l && l->widget())
      l->widget()->setEnabled(state);
  }*/
  
  //if (state == 0) {
    DspComponent *comp = (DspComponent*)sender()->property("component").value<void*>();
    int idx = sender()->property("idx").value<int>();
    printf("do unset!\n");
    comp->UnsetParameter(idx);
    printf("done unset!\n");
    
    _viewer->configure();
    _load_existing_param(grid, comp, idx, _circuits);
  //}
}

void QNESettings::circuitSelected(int idx)
{
  DspComponent *comp = (DspComponent*)sender()->property("component").value<void*>();
  int set_idx = sender()->property("idx").value<int>();
    
  bool succ = comp->SetParameter(set_idx, DspParameter(DPPT::Pointer, (DspComponent*)(((QComboBox*)sender())->itemData(idx).value<void*>())));
  assert(succ);
  
  DspCircuit *cc;
  comp->GetParameter(set_idx)->GetPointer(cc);
  
  _viewer->configure();
  //FIXME need updated circuit list?
  QMetaObject::invokeMethod(this, "reload", Qt::QueuedConnection);
}
