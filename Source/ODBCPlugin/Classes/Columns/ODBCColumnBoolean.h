#pragma once

//#include <string>
#include "ODBCColumnBoolean.generated.h"

UENUM(BlueprintType)
enum class EODBCBoolean
	{
		Bit
	};

UCLASS(BlueprintType, Blueprintable)
class UODBCColumnBoolean : public UODBCColumn
{
	GENERATED_UCLASS_BODY()
	
	UFUNCTION(BlueprintPure, meta = (FriendlyName = "SQL Column [Boolean]"), Category = "Database|ODBCColumn")
	static UODBCColumnBoolean* ConstructODBCColumn(FString ColumnName, bool value, EODBCBoolean type);

	FString getValue() const;
	ESqlDataType toDataType(EODBCBoolean type);
	EColumnTypes getType() const;
	UODBCColumn* Copy(UODBCColumn* column);
	void setValue(void* value);

	UPROPERTY()
	bool value;
};