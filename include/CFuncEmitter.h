#ifndef __CFUNCEMITTER_H
#define	__CFUNCEMITTER_H

#include <string>
#include <vector>
#include <napi.h>

class CFuncEmitter : public Napi::AsyncWorker
{
private:
	Napi::ObjectReference m_this ;
	Napi::FunctionReference m_func ;
	std::string m_strEmitFunc ;
	std::vector<std::string> m_vArg ;

protected:
	void Execute() ;
	void OnOK() ;

public:
	CFuncEmitter(const Napi::CallbackInfo&, std::string) ;
	virtual ~CFuncEmitter() {}

	Napi::Object getThis() { return m_this.Value() ; }
	Napi::Function getFunc() { return m_func.Value() ; }

	void emitQueue(std::vector<std::string>) ;
} ;
#endif

