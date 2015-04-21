#pragma once

#include "ODBCQueryBuilder.generated.h"

USTRUCT(BlueprintType)
struct FOrderBy
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OrderBy")
	bool DESC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OrderBy")
	UODBCColumn* Column;

	FOrderBy() {
		Column = NULL;
		DESC = false;
	}
};

UCLASS(BlueprintType, Blueprintable)
class UODBCQueryBuilder : public UObject
{
	GENERATED_UCLASS_BODY()
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "SQL Generate INSERT", CompactNodeTitle = "INSERT"), Category = "Database|ODBC|CRUD")
	static UODBCQueryBuilder* Insert(TArray<UODBCColumn*> columns, FString tableName, FString& query, bool printDebug);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "SQL Generate UPDATE", CompactNodeTitle = "UPDATE"), Category = "Database|ODBC|CRUD")
	static UODBCQueryBuilder* Update(UODBCWhereClause* whereClause, TArray<UODBCColumn*> setArray, FString tableName, FString& query, bool printDebug);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "SQL Generate DELETE", CompactNodeTitle = "DELETE"), Category = "Database|ODBC|CRUD")
	static UODBCQueryBuilder* Delete(UODBCWhereClause* whereClause, FString tableName, FString& query, bool printDebug);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "SQL Generate SELECT", CompactNodeTitle = "SELECT"), Category = "Database|ODBC|CRUD")
	static UODBCQueryBuilder* Select(UODBCWhereClause* whereClause, TArray<UODBCColumn*> selectColumnArray, TArray<FOrderBy> orderByColumns, FString tableName, FString& query, bool printDebug, int32 rowLimit = -1);

	UPROPERTY()
	FString value;
	UPROPERTY()
	int32 _rowLimit;
};