#include "ODBCPCH.h"
//#include "ODBCObject.h"

//DEFINE_LOG_CATEGORY(ModuleLog)

UODBCObject::UODBCObject(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

UODBCObject* UODBCObject::ConstructODBCObject(UObject* WorldContextObject, FString Username, FString Password, FString DataSourceName)
{
	UODBCObject* object = (UODBCObject*)StaticConstructObject(UODBCObject::StaticClass());
	object->Username = Username;
	object->Password = Password;
	object->DataSourceName = DataSourceName;

	object->GenerateConnectionString();
	object->CreateConnection();

	object->SetFlags(RF_RootSet);
	return object;
}

UODBCObject::~UODBCObject()
{
	// Clean up the Database Connections
	UE_LOG(ModuleLog, Warning, TEXT("UODBCObject: Closing..."));
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, env);
}

void UODBCObject::CreateConnection() 
{
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
	SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	SQLAllocHandle(SQL_HANDLE_DBC, env, &hdbc);

	try {
		ret = SQLDriverConnect(hdbc, NULL, (SQLWCHAR*)*ConnectionString, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

		if (SQL_SUCCEEDED(ret)) {
			UE_LOG(ModuleLog, Warning, TEXT("Connected Successfully to Database"));
		}
		else
		{
			extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
			UE_LOG(ModuleLog, Warning, TEXT("Failed to Connect to Database. Check your Connection Settings and ODBC settings."));
		}
	}
	catch (...) {
		UE_LOG(ModuleLog, Warning, TEXT("Failed to Connect to Database. Check your Connection Settings and ODBC settings. (EXCEPTION)"));
	}
}

SQLHSTMT UODBCObject::GetStatementHandle()
{
	SQLHSTMT handle;
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &handle);
	return handle;
}

void UODBCObject::GenerateConnectionString() 
{
	ConnectionString = FString::Printf(TEXT("DSN=%s;Uid=%s;Pwd=%s;"), *DataSourceName, *Username, *Password);
}

void UODBCObject::extract_error(
	char* fn,
	SQLHANDLE handle,
	SQLSMALLINT type)
{
	SQLINTEGER	 i = 0;
	SQLINTEGER	 native;
	SQLWCHAR	 state[7];
	SQLWCHAR	 text[256];
	SQLSMALLINT	 len;
	SQLRETURN	 ret;
	
	TCHAR* test = ANSI_TO_TCHAR(fn);
	FString output = FString::Printf(test);
	UE_LOG(ModuleLog, Warning, TEXT("%s"), *output);

	do
	{
		ret = SQLGetDiagRec(type, handle, ++i, state, &native, text,
			sizeof(text), &len);
		if (SQL_SUCCEEDED(ret))
			UE_LOG(ModuleLog, Warning, TEXT("%s:%ld:%ld:%s"), state, i, native, text)
	} while (ret == SQL_SUCCESS);
}

