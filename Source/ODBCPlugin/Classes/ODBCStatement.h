#pragma once

#include "ODBCPCH.h"
#include "ODBCStatement.generated.h"

USTRUCT(BlueprintType)
struct FResultArray {
	
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Results")
	TArray<UODBCColumn*> Results;
	
	FResultArray() {

	}
};

UCLASS(BlueprintType, Blueprintable)
class UODBCStatement : public UObject
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintPure, meta = (FriendlyName = "SQL Statement"), Category = "Database|ODBC|Statement")
	static UODBCStatement* ConstructODBCStatement(UODBCObject* object, bool printDebug);

	UFUNCTION(BlueprintCallable, meta = (CompactNodeTitle = "EXECUTE"), Category = "Database|ODBC|Statement")
	static UODBCStatement* ExecuteQuery(UODBCStatement* statement, UODBCQueryBuilder* query, bool Async);

	UFUNCTION(BlueprintCallable, Category = "Database|ODBC|Statement")
	static UODBCStatement* CloseStatement(UODBCStatement* statement);

	UFUNCTION(BlueprintPure, Category = "Database|ODBC|Statement")
	static void StatementIsValid(UODBCStatement* statement, bool& isValid);

	/**
	 * Checks a State for completetion
	 *
	 * Checks the status of the running statement, if it is still
	 * marked as SQL_STILL_EXECUTING it will return a result of
	 * false, if the RETCODE is anything not handled than an Error
	 * is returned as true.
	 */
	UFUNCTION(BlueprintPure, Category = "Database|ODBC|Statement")
	static void StatementComplete(UODBCStatement* statement, bool& Result, bool& isError);

	UFUNCTION(BlueprintCallable, Category = "Database|ODBC|Statement")
	static void ReadNextRow(UODBCStatement* statement, TArray<UODBCColumn*> setArray, TArray<FResultArray>& rowData);

	bool CheckOperation();

	~UODBCStatement();

private:
	UPROPERTY()
	UODBCObject* connection;

	SQLHSTMT stmt;
	SQLRETURN ret;

	bool printDebug;
};
