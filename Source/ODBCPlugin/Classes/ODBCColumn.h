#pragma once

#include "ODBCColumn.generated.h"

/**
 * Represents all SQL TYPES currently Allowed
 */
UENUM(BlueprintType)
enum class ESqlDataType : uint8
	{
		NONE,
		// Boolean Types
		SQLBIT,
		// String Types
		SQLCHAR,
		SQLVARCHAR,
		SQLLONGVARCHAR,
		SQLWCHAR,
		SQLWVARCHAR,
		SQLWLONGVARCHAR,
		// Integer Types
		SQLINTEGER,
		SQLTINYINT,
		SQLSMALLINT,
		SQLBIGINT
	};

UENUM(BlueprintType)
enum class EColumnTypes
{
	NONE,
	BOOLEAN,
	INTEGER,
	STRING
};

UCLASS(BlueprintType, Blueprintable)
class UODBCColumn : public UObject
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintPure, Category = "Database|ODBC")
	virtual FString getValue() const;
	virtual EColumnTypes getType() const;
	virtual UODBCColumn* Copy(UODBCColumn* column);
	virtual void setValue(void* value);
	SQLINTEGER getSqlType();

	UPROPERTY()
	bool Primary;
	UPROPERTY()
	FString _columnName;
	UPROPERTY()
	ESqlDataType DataType;
	UPROPERTY()
	int32 _MaxSize;
};