#include "qnesettings.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>

#include <assert.h>

#define DPPT DspParameter::ParamType

void QNESettings::attach(DspComponent *comp, std::vector<DspCircuit*> &circuits)
{
  if (_layout_w)
    delete _layout_w;
  
  _layout_w = new QWidget(this);
  _layout.addWidget(_layout_w);
  
  QFormLayout *actual_layout = new QFormLayout(_layout_w);
  _layout_w->setLayout(actual_layout);
      
  _component = comp;
  
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
          if (val) {
            spinbox->setValue(*val);
            printf("comb %p %d\n", _component, *val);
          }
          connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(intSettingChanged(int)));

          break;
      }
      case DPPT::Pointer : {
          QComboBox *combox = new QComboBox(_layout_w);
          hbox->addWidget(combox);
          combox->setProperty("component", QVariant::fromValue((void*)_component));
          combox->setProperty("idx", i);
          
          DspComponent *c;
          int found = -1;
          param->GetPointer(c);
          
          for(int i=0;i<circuits.size();i++) {
            if (comp->GetParentCircuit() == circuits[i])
              continue;
            //FIXME typename clash?
            if (circuits[i] == c)
              found = i;
            const char *name = circuits[i]->GetComponentName().c_str();
            const char *type = circuits[i]->getTypeName().c_str();
            char label[128];
            if (strlen(name)+strlen(type) == 0)
              continue;
            if (!strlen(name))
              name = "(unnamed)";
            if (!strlen(type))
              type = "(no type)";
            sprintf(label, "%s (%s)", name, type);
            combox->addItem(label, QVariant::fromValue((void*)circuits[i]));
          }
          
          if (found != -1)
            combox->setCurrentIndex(found);
          else {
            combox->addItem("unknown circuit", QVariant::fromValue((void*)c));
            //combox->addItem(c->GetComponentName().c_str(), QVariant::fromValue((void*)c));
            combox->setCurrentIndex(combox->count()-1);
          }
          
          
          connect(combox, SIGNAL(currentIndexChanged(int)), this, SLOT(circuitSelected(int)));

          break;
      }
    }
    
    
    QLineEdit *ed = new QLineEdit(_layout_w);
    hbox->addWidget(ed);
    ed->setProperty("component", QVariant::fromValue((void*)_component));
    ed->setProperty("idx", i);
    ed->setText(QString(_component->GetParentCircuit()->GetComponentParameterAlias(_component, i).c_str()));
    connect(ed, SIGNAL(textChanged(QString)), this, SLOT(aliasChanged(QString)));
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
      block->circuit->AddInput(buf);
      block->addOutputPort(buf);
    }
    else {
      sprintf(buf, "output_%d", i);
      block->circuit->AddOutput(buf);
      block->addInputPort(buf);
    }
}

void QNESettings::circuitSelected(int idx)
{
  DspComponent *comp = (DspComponent*)sender()->property("component").value<void*>();
  int set_idx = sender()->property("idx").value<int>();
    
  bool succ = comp->SetParameter(set_idx, DspParameter(DPPT::Pointer, (DspComponent*)(((QComboBox*)sender())->itemData(idx).value<void*>())));
  
  DspCircuit *cc;
  comp->GetParameter(set_idx)->GetPointer(cc);
  
  assert(succ);
  
  emit settingChanged();
}