#pragma once

class ODBCPlugin : public IModuleInterface
{
private:

public:
	ODBCPlugin();
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};