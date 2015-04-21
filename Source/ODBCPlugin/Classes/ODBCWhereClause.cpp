#include "ODBCPCH.h"

UODBCWhereClause::UODBCWhereClause(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

UODBCWhereClause* UODBCWhereClause::ConstructWhereEqualsString(UODBCColumn* Right, FString Left)
{
	UODBCWhereClause* clause = (UODBCWhereClause*)StaticConstructObject(UODBCWhereClause::StaticClass());
	clause->value = FString::Printf(TEXT("%s = '%s'"), *Right->_columnName, *Left);
	return clause;
}

UODBCWhereClause* UODBCWhereClause::ConstructWhereEqualsInteger(UODBCColumn* Right, int32 Left)
{
	UODBCWhereClause* clause = (UODBCWhereClause*)StaticConstructObject(UODBCWhereClause::StaticClass());
	clause->value = FString::Printf(TEXT("%s = %d"), *Right->_columnName, Left);
	return clause;
}

UODBCWhereClause* UODBCWhereClause::ConstructWhereEqualsBoolean(UODBCColumn* Right, bool Left)
{
	UODBCWhereClause* clause = (UODBCWhereClause*)StaticConstructObject(UODBCWhereClause::StaticClass());
	clause->value = FString::Printf(TEXT("%s = %d"), *Right->_columnName, Left ? 1 : 0);
	return clause;
}

UODBCWhereClause* UODBCWhereClause::ConstructWhereEqualsColumn(UODBCColumn* Column)
{
	UODBCWhereClause* clause = (UODBCWhereClause*)StaticConstructObject(UODBCWhereClause::StaticClass());

	clause->value = FString::Printf(TEXT("%s=%s"), *Column->_columnName, *Column->getValue());
	
	return clause;
}

UODBCWhereClause* UODBCWhereClause::ConstructWhereOr(TArray<UODBCWhereClause*> Clauses)
{
	UODBCWhereClause* clause = (UODBCWhereClause*)StaticConstructObject(UODBCWhereClause::StaticClass());
	FString f;
	bool first = true;
	for (const UODBCWhereClause* cl : Clauses)
	{
		if (!first) {
			f.Append(TEXT(" OR "));
		} else {
			first = false;
		}

		f.Append(cl->value);

		f = FString::Printf(TEXT("%s"), *f);
	}
	clause->value = FString::Printf(TEXT("(%s)"), *f);

	return clause;
}

UODBCWhereClause* UODBCWhereClause::ConstructWhereAnd(TArray<UODBCWhereClause*> Clauses)
{
	UODBCWhereClause* clause = (UODBCWhereClause*)StaticConstructObject(UODBCWhereClause::StaticClass());
	FString f;
	bool first = true;
	for (const UODBCWhereClause* cl : Clauses)
	{
		if (!first) {
			f.Append(TEXT(" AND "));
		}
		else {
			first = false;
		}

		f.Append(cl->value);

		f = FString::Printf(TEXT("%s"), *f);
	}
	clause->value = FString::Printf(TEXT("(%s)"), *f);

	return clause;
}