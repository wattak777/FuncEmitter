#ifndef __CROOM_MANAGER_H
#define	__CROOM_MANAGER_H

#include <vector>
#include <napi.h>

class CFuncEmitter ;
class CWorkerThread : public Napi::AsyncWorker
{
private:
	CFuncEmitter* m_pFuncEmitter ;
	CFuncEmitter* m_pFuncEmitter2 ;

protected:
	void Execute() ;

public:
	CWorkerThread(const Napi::CallbackInfo&) ;
	virtual ~CWorkerThread() ;
	void startTask() ;
} ;
#endif

