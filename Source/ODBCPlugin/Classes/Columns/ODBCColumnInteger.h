#pragma once

//#include <string>
#include "ODBCColumnInteger.generated.h"

UENUM(BlueprintType)
enum class EODBCInteger
{
	INTEGER,
	BIT,
	TINYINT,
	SMALLINT,
	BIGINT
};

UCLASS(BlueprintType, Blueprintable)
class UODBCColumnInteger : public UODBCColumn
{
	GENERATED_UCLASS_BODY()
	
	UFUNCTION(BlueprintPure, meta = (FriendlyName = "SQL Column [Integer]"), Category = "Database|ODBCColumn")
	static UODBCColumnInteger* ConstructODBCColumn(FString ColumnName, int32 value, EODBCInteger type, bool isPrimary);

	EColumnTypes getType() const;
	ESqlDataType toDataType(EODBCInteger type);
	FString getValue() const;
	UODBCColumn* Copy(UODBCColumn* column);
	void setValue(void* value);

	//UPROPERTY();
	int32 value;	
};