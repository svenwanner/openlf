#ifndef QNODESTHREAD_H
#define QNODESTHREAD_H

#include <QObject>
#include "qnesettings.h"
#include "DspCircuit.h"

class Circuic_Thread : public QObject
{
  Q_OBJECT
public:
  Circuic_Thread(DspCircuit *_circuit) : _circuit(_circuit){};
  
signals:
    
    void done();
    
public slots:
  
  void run(){
    _circuit->Reset();
    _circuit->Tick();
    emit done();
    printf("done!\n");
  };
  
private:
  DspCircuit *_circuit;
  
};


#endif // QNODESTHREAD_H