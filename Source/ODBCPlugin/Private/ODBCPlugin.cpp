#include "ODBCPCH.h"
//#include "ODBCPlugin.h"

#define LOCTEXT_NAMESPACE "ODBC"

//ODBCPlugin::ODBCPlugin()
//{
//}
//
//void ODBCPlugin::StartupModule()
//{
//	UE_LOG(ModuleLog, Warning, TEXT("ODBCPlugin: Starting"));
//}
//
//void ODBCPlugin::ShutdownModule()
//{
//	UE_LOG(ModuleLog, Warning, TEXT("ODBCPlugin: ShutDown"));
//}

class FODBCPlugin : public IODBCPlugin
{
	virtual void StartupModule() override
	{
		UE_LOG(ModuleLog, Warning, TEXT("ODBCPlugin: Starting"));
		UODBCObject::StaticClass();
		UODBCStatement::StaticClass();
		UODBCColumn::StaticClass();
	}

	virtual void ShutdownModule() override
	{
		UE_LOG(ModuleLog, Warning, TEXT("ODBCPlugin: ShutDown"));
	}
};

DEFINE_LOG_CATEGORY(ModuleLog)

IMPLEMENT_MODULE(FODBCPlugin, ODBCPlugin);

