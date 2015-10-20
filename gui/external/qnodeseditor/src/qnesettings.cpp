#include "qnesettings.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>

#define DPPT DspParameter::ParamType

void QNESettings::attach(DspComponent *comp)
{
  if (_layout_w)
    delete _layout_w;
  
  _layout_w = new QWidget(this);
  _layout.addWidget(_layout_w);
  
  QFormLayout *actual_layout = new QFormLayout(_layout_w);
  _layout_w->setLayout(actual_layout);
      
  _component = comp;
  
  DspCircuit *c = comp->GetParentCircuit();
  c->configure();
  
  for(int i=0;i<_component->GetParameterCount();i++) {
    const DspParameter *param = _component->GetParameter(i);
    QHBoxLayout *hbox = new QHBoxLayout(_layout_w);
    actual_layout->addRow(tr(comp->GetParameterName(i).c_str()), hbox);
    
    switch (param->Type()) {
        case DPPT::String : {
          QLineEdit *ed = new QLineEdit(_layout_w);
          hbox->addWidget(ed);
          ed->setProperty("component", QVariant::fromValue((void*)_component));
          ed->setProperty("idx", i);
          const std::string *text = param->GetString();
          if (text)
            ed->setText(QString(text->c_str()));
          connect(ed, SIGNAL(textChanged(QString)), this, SLOT(textSettingChanged(QString)));
          
          QPushButton *btn = new QPushButton(_layout_w);
          hbox->addWidget(btn);
          btn->setProperty("ed", QVariant::fromValue(ed));
          connect(btn, SIGNAL(clicked()), this, SLOT(selFileClicked()));
          
          break;
        }
      case DPPT::Float : {
          QDoubleSpinBox *spinbox = new QDoubleSpinBox(_layout_w);
          hbox->addWidget(spinbox);
          spinbox->setProperty("component", QVariant::fromValue((void*)_component));
          spinbox->setProperty("idx", i);
          const float *val = param->GetFloat();
          if (val)
            spinbox->setValue(*val);
          connect(spinbox, SIGNAL(valueChanged(double)), this, SLOT(floatSettingChanged(double)));

          break;
      }
      case DPPT::Int : {
          QSpinBox *spinbox = new QSpinBox(_layout_w);
          hbox->addWidget(spinbox);
          spinbox->setProperty("component", QVariant::fromValue((void*)_component));
          spinbox->setProperty("idx", i);
          spinbox->setMaximum(INT_MAX);
          const int *val = param->GetInt();
          if (val)
            spinbox->setValue(*val);
          connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(intSettingChanged(int)));

          break;
      }
    }
  }
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
}


void QNESettings::textSettingChanged(QString text)
{
  DspComponent *comp = (DspComponent*)sender()->property("component").value<void*>();
  int idx = sender()->property("idx").value<int>();
  
  comp->SetParameter(idx, DspParameter(DPPT::String, text.toStdString()));
  
  DspCircuit *c = comp->GetParentCircuit();
  c->configure();
}

void QNESettings::floatSettingChanged(double val)
{
  DspComponent *comp = (DspComponent*)sender()->property("component").value<void*>();
  int idx = sender()->property("idx").value<int>();
  
  comp->SetParameter(idx, DspParameter(DPPT::Float, (float)val));
  
  DspCircuit *c = comp->GetParentCircuit();
  c->configure();
}


void QNESettings::intSettingChanged(int val)
{
  DspComponent *comp = (DspComponent*)sender()->property("component").value<void*>();
  int idx = sender()->property("idx").value<int>();
  
  comp->SetParameter(idx, DspParameter(DPPT::Int, val));
  
  DspCircuit *c = comp->GetParentCircuit();
  c->configure();
}

void QNESettings::selFileClicked()
{
  QString path = QFileDialog::getSaveFileName(this, tr("select file or directory"));
  
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
      block->addOutputPort(buf);
    }
    else {
      sprintf(buf, "output_%d", i);
      block->addInputPort(buf);
    }    
}