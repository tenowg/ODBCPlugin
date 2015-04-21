#pragma once

#include "ODBCColumnNVarChar.generated.h"

UENUM(BlueprintType)
enum class EODBCString
{
	Char,
	Varchar,
	LongVarchar,
	WChar,
	WVarchar,
	WLongVarchar
};

UCLASS(BlueprintType, Blueprintable)
class UODBCColumnNVarChar : public UODBCColumn
{
	GENERATED_UCLASS_BODY()
	
	UFUNCTION(BlueprintPure, meta = (FriendlyName = "SQL Column [String]"), Category = "Database|ODBCColumn")
	static UODBCColumnNVarChar* ConstructODBCColumn(FString ColumnName, int32 MaxSize, FString value, bool isPrimary, EODBCString type);
	
	ESqlDataType toDataType(EODBCString type);
	EColumnTypes getType() const;
	FString getValue() const;
	UODBCColumn* Copy(UODBCColumn* column);
	void setValue(void* value);

	UPROPERTY()
	FString value;
};