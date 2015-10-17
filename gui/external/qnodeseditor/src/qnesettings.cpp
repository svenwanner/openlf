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
  
  for(int i=0;i<_component->GetParameterCount();i++) {
    const DspParameter *param = _component->GetParameter(i);
    switch (param->Type()) {
      case DPPT::String :
        QHBoxLayout *hbox = new QHBoxLayout(_layout_w);
        
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
        
        actual_layout->addRow(tr(comp->GetParameterName(i).c_str()), hbox);
        break;
    }
  }
}


void QNESettings::textSettingChanged(QString text)
{
  DspComponent *comp = (DspComponent*)sender()->property("component").value<void*>();
  int idx = sender()->property("idx").value<int>();
  
  comp->SetParameter(idx, DspParameter(DPPT::String, text.toStdString()));
}

void QNESettings::selFileClicked()
{
  QString path = QFileDialog::getSaveFileName(this, tr("select file or directory"));
  
  QLineEdit *ed = sender()->property("ed").value<QLineEdit*>();
  
  ed->setText(path);
}