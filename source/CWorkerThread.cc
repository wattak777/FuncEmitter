#include <iostream>
#include <string>
#include <napi.h>
#include "CWorkerThread.h"
#include "CFuncEmitter.h"

CWorkerThread::CWorkerThread(const Napi::CallbackInfo& info)
	: Napi::AsyncWorker(info.Env())
{
	std::cout << "call WorkerThread constructor" << std::endl ;
	m_pFuncEmitter = new CFuncEmitter(info, "EmitSample1") ;
	m_pFuncEmitter->SuppressDestruct() ;
	m_pFuncEmitter2 = new CFuncEmitter(info, "EmitSample2") ;
	m_pFuncEmitter2->SuppressDestruct() ;
}

CWorkerThread::~CWorkerThread()
{
	std::cout << "call WorkerThread destructor" << std::endl ;
}

void CWorkerThread::startTask()
{
	std::cout << "startTask" << std::endl ;

	// Create Worker Thread.
	Queue() ;
}

void CWorkerThread::Execute()
{
	std::string	str_input ;

	std::cout << "mainLoop" << std::endl ;
	while ( true ) {
		// prompt
		std::cout << "% " ;

		// get string
		std::getline(std::cin, str_input) ;
		if (str_input == "call" ) {
			m_pFuncEmitter2->emitQueue({"call func2."}) ;
		} else {
			m_pFuncEmitter->emitQueue({str_input}) ;
		}
	}
}

