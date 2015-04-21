#include "ODBCPCH.h"

UODBCQueryBuilder::UODBCQueryBuilder(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

UODBCQueryBuilder* UODBCQueryBuilder::Insert(TArray<UODBCColumn*> columns, FString databaseName, FString& query, bool printDebug)
{
	UODBCQueryBuilder* clause = (UODBCQueryBuilder*)StaticConstructObject(UODBCQueryBuilder::StaticClass());

	FString names; // = FString();
	FString values = FString();
	bool first = true;
	for (const UODBCColumn* a : columns) {
	
		if (!first) {
			names.Append(TEXT(", "));
			values.Append(TEXT(", "));
		}
		else
		{
			first = false;
		}
	
		names.Append(FString::Printf(TEXT("%s"), *a->_columnName));
		values.Append(a->getValue());
	}
		
	clause->value = FString::Printf(TEXT("INSERT INTO %s (%s) VALUES (%s)"), *databaseName, *names, *values);

	if (printDebug) {
		UE_LOG(ModuleLog, Warning, TEXT("%s"), *clause->value);
	}

	query = clause->value;

	return clause;
}

UODBCQueryBuilder* UODBCQueryBuilder::Update(UODBCWhereClause* whereClause, TArray<UODBCColumn*> setArray, FString tableName, FString& query, bool printDebug)
{
	UODBCQueryBuilder* clause = (UODBCQueryBuilder*)StaticConstructObject(UODBCQueryBuilder::StaticClass());
	// Build first part of UPDATE statement
	FString update = FString::Printf(TEXT("UPDATE %s "), *tableName);

	// Build the SET clause
	bool first = true;
	FString setValue = TEXT("SET ");
	for (const UODBCColumn* set : setArray)
	{
		if (!first) {
			setValue.Append(TEXT(", "));
		}
		else
		{
			first = false;
		}

		setValue.Append(FString::Printf(TEXT("%s=%s"), *set->_columnName, *set->getValue()));
	}

	FString wClause;
	// Build Where Clause
	if (whereClause != NULL || whereClause != nullptr) {
		wClause = FString::Printf(TEXT("WHERE %s"), *whereClause->value);
	}

	// Build final UPDATE statement
	clause->value = FString::Printf(TEXT("%s %s %s"), *update, *setValue, *wClause);

	if (printDebug) {
		UE_LOG(ModuleLog, Warning, TEXT("%s"), *clause->value);
	}
	
	query = clause->value;

	return clause;
}

UODBCQueryBuilder* UODBCQueryBuilder::Delete(UODBCWhereClause* whereClause, FString tableName, FString& query, bool printDebug) 
{
	UODBCQueryBuilder* clause = (UODBCQueryBuilder*)StaticConstructObject(UODBCQueryBuilder::StaticClass());
	// Build first part of UPDATE statement
	FString deleteQuery = FString::Printf(TEXT("DELETE FROM %s "), *tableName);

	FString wClause;
	// Build Where Clause
	if (whereClause != NULL || whereClause != nullptr) {
		wClause = FString::Printf(TEXT("WHERE %s"), *whereClause->value);
	}

	// Build final DELETE statement
	clause->value = FString::Printf(TEXT("%s %s"), *deleteQuery, *wClause);

	if (printDebug) {
		UE_LOG(ModuleLog, Warning, TEXT("%s"), *clause->value);
	}

	query = clause->value;

	return clause;
}

UODBCQueryBuilder* UODBCQueryBuilder::Select(UODBCWhereClause* whereClause, TArray<UODBCColumn*> selectColumnArray, TArray<FOrderBy> orderByColumns, FString tableName, FString& query, bool printDebug, int32 rowLimit)
{
	UODBCQueryBuilder* clause = (UODBCQueryBuilder*)StaticConstructObject(UODBCQueryBuilder::StaticClass());
	clause->_rowLimit = rowLimit;

	FString columns;
	bool first = true;
	for (const auto column : selectColumnArray) {
		if (!first) {
			columns.Append(TEXT(", "));
		}
		else
		{
			first = false;
		}
		columns.Append(FString::Printf(TEXT("%s"), *column->_columnName));
	}

	FString wClause;
	// Build Where Clause
	if (whereClause != NULL || whereClause != nullptr) {
		wClause = FString::Printf(TEXT(" WHERE %s"), *whereClause->value);
	}

	FString orderBy;
	// Build Where Clause
	FString oColumn;
	first = true;
	for (auto column : orderByColumns) {
		if (column.Column == NULL) {
			continue;
		}
		if (!first) {
			oColumn.Append(TEXT(", "));
		}
		else
		{
			oColumn.Append(TEXT(" ORDER BY "));
			first = false;
		}
		oColumn.Append(FString::Printf(TEXT("%s %s"), *column.Column->_columnName, column.DESC ? TEXT("DESC") : TEXT("ASC")));
	}
	orderBy = oColumn;

	// Build the SELECT statement
	clause->value = FString::Printf(TEXT("SELECT %s FROM %s%s%s"), *columns, *tableName, *wClause, *orderBy);
	
	query = clause->value;

	if (printDebug) {
		UE_LOG(ModuleLog, Warning, TEXT("%s"), *clause->value);
	}

	return clause;
}
