#include <string>
#include <vector>
#include <napi.h>
#include <iostream>
#include "CFuncEmitter.h"

CFuncEmitter::CFuncEmitter(const Napi::CallbackInfo& info, std::string _emit)
	: Napi::AsyncWorker(info.Env())
{
	Napi::Object _this = info.This().As<Napi::Object>() ;
	// イベント発生関数（emit）の実体を取得
	Napi::Function _func = _this.Get("emit").As<Napi::Function>() ;

	m_this = Napi::Persistent(_this) ;
	m_this.SuppressDestruct() ;
	m_func = Napi::Persistent(_func) ;
	m_func.SuppressDestruct() ;
	m_strEmitFunc = _emit ;
}

void CFuncEmitter::Execute()
{
	// ここで_func.Callすると落ちる
}

void CFuncEmitter::OnOK()
{
	Napi::Function _func = m_func.Value() ;
	Napi::Object _this = m_this.Value() ;
	Napi::Env _env = Env() ;

	Napi::HandleScope scope(_env) ;

	std::vector<napi_value> _arg = {
		Napi::String::New(_env, m_strEmitFunc),
	} ;
	for (uint32_t idx = 0 ; idx < m_vArg.size() ; idx++) {
		_arg.push_back(Napi::String::New(_env, m_vArg.at(idx))) ;
	}
	_func.Call(_this, _arg) ;
}

void CFuncEmitter::emitQueue(std::vector<std::string> _arg)
{
	m_vArg = _arg ;
	Queue() ;
}

