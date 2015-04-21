#pragma once

#include "ODBCWhereClause.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UODBCWhereClause : public UObject
{
	GENERATED_UCLASS_BODY()
	
	UFUNCTION(BlueprintPure, meta = (FriendlyName = "SQL Where [Equals (String)]", CompactNodeTitle = "=="), Category = "Database|ODBC|Where")
	static UODBCWhereClause* ConstructWhereEqualsString(UODBCColumn* Right, FString Left);

	UFUNCTION(BlueprintPure, meta = (FriendlyName = "SQL Where [Equals (Integer)]", CompactNodeTitle = "=="), Category = "Database|ODBC|Where")
	static UODBCWhereClause* ConstructWhereEqualsInteger(UODBCColumn* Right, int32 Left);

	UFUNCTION(BlueprintPure, meta = (FriendlyName = "SQL Where [Equals (Boolean)]", CompactNodeTitle = "=="), Category = "Database|ODBC|Where")
	static UODBCWhereClause* ConstructWhereEqualsBoolean(UODBCColumn* Right, bool Left);

	UFUNCTION(BlueprintPure, meta = (FriendlyName = "SQL Where [Equals (Column)]", CompactNodeTitle = "=="), Category = "Database|ODBC|Where")
	static UODBCWhereClause* ConstructWhereEqualsColumn(UODBCColumn* Column);

	UFUNCTION(BlueprintPure, meta = (FriendlyName = "SQL Where [OR]", CompactNodeTitle = "OR"), Category = "Database|ODBC|Where")
	static UODBCWhereClause* ConstructWhereOr(TArray<UODBCWhereClause*> Clauses);

	UFUNCTION(BlueprintPure, meta = (FriendlyName = "SQL Where [AND]", CompactNodeTitle = "AND"), Category = "Database|ODBC|Where")
	static UODBCWhereClause* ConstructWhereAnd(TArray<UODBCWhereClause*> Clauses);

	UPROPERTY()
	FString value;
};