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

public slots:

	void run(){
		_circuit->Tick();
		_circuit->Reset();
	};

private:
	DspCircuit *_circuit;

};


#endif // QNODESTHREAD_H