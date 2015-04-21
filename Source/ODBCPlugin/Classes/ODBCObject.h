#pragma once

#include "ODBCPCH.h"
#include "ODBCObject.generated.h"

//class UODBCObject;

UCLASS(BlueprintType, Blueprintable)
class UODBCObject : public UObject
{
	GENERATED_UCLASS_BODY()

	// Create ODBC Connection
    UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Create ODBC Connection", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "Database|ODBC")
	static UODBCObject* ConstructODBCObject(UObject* WorldContextObject, FString UserName, FString Password, FString DataSourceName);

	SQLHSTMT GetStatementHandle();

	~UODBCObject();

	// Data
	UPROPERTY()
	FString Username;
	UPROPERTY()
	FString Password;
	UPROPERTY()
	FString DataSourceName;
	UPROPERTY()
	FString ConnectionString;
	SQLHDBC hdbc;

	void extract_error(
		char *fn,
		SQLHANDLE handle,
		SQLSMALLINT type);
private:
	
	SQLHENV env;
	SQLSMALLINT dsn_ret;
	SQLSMALLINT desc_ret;
	SQLRETURN ret;

	void CreateConnection();
	void GenerateConnectionString();
};
