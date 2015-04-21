#include "ODBCPCH.h"

UODBCStatement::UODBCStatement(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

UODBCStatement* UODBCStatement::CloseStatement(UODBCStatement* statement)
{
	// Check to make sure Statement is not null, if it is, it is already dead
	if (statement == NULL || statement == nullptr) {
		return statement;
	}

	if (statement->stmt != SQL_NULL_HSTMT)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, statement->stmt);
	}

	statement->ConditionalBeginDestroy();
	statement = nullptr;

	return statement;
}

UODBCStatement* UODBCStatement::ConstructODBCStatement(UODBCObject* object, bool printDebug)
{
	UODBCStatement* statement = (UODBCStatement*)StaticConstructObject(UODBCStatement::StaticClass());
	statement->connection = object;
	statement->stmt = object->GetStatementHandle();
	statement->printDebug = printDebug;
	return statement;
}

UODBCStatement* UODBCStatement::ExecuteQuery(UODBCStatement* statement, UODBCQueryBuilder* query, bool Async)
{
	if (statement == NULL || statement == nullptr) {
		UE_LOG(ModuleLog, Warning, TEXT("Statement Needs to be assigned, or created first."));
		return statement;
	}

	if (Async)
	{
		SQLSetStmtAttr(statement->stmt, SQL_ATTR_ASYNC_ENABLE, (SQLPOINTER)SQL_ASYNC_ENABLE_ON, 0);
	}

	if (query->_rowLimit > -1) {
		SQLSetStmtAttr(statement->stmt, SQL_ATTR_MAX_ROWS, (SQLPOINTER)SQL_MAX_ROWS, query->_rowLimit);
	}

	statement->ret = SQLExecDirect(statement->stmt, (SQLWCHAR*)*query->value, SQL_NTS);

	if (statement->printDebug) {
		UE_LOG(ModuleLog, Warning, TEXT("Statement: %s"), *query->value);
	}

	if (!Async) {
		statement->CheckOperation();
	}

	return statement;
}

void UODBCStatement::StatementIsValid(UODBCStatement* statement, bool& isValid)
{
	if (statement == NULL) {
		isValid = false;
	} 
	else if (statement == nullptr) {
		isValid = false;
	}
	else {
		isValid = statement->IsValidLowLevelFast();
	}
}

bool UODBCStatement::CheckOperation() {
	if (SQL_SUCCEEDED(ret)) {
		if (printDebug) {
			UE_LOG(ModuleLog, Warning, TEXT("Operation Completed Successfully"));
		}
		return false;
	}
	else
	{
		switch (ret) {
		case SQL_NO_DATA_FOUND:
			if (printDebug) {
				UE_LOG(ModuleLog, Warning, TEXT("No Data found to Update..."));
			}
			break;
		default:
			connection->extract_error("SQL Error: ", stmt, SQL_HANDLE_STMT);
			connection->extract_error("SQL Error: ", connection->hdbc, SQL_HANDLE_DBC);
			break;
		}
		return true;
	}
}

void UODBCStatement::StatementComplete(UODBCStatement* statement, bool& Result, bool& isError)
{

	if (statement->ret == SQL_STILL_EXECUTING) {
		statement->ret = SQLExecDirect(statement->stmt, (SQLWCHAR*)"", SQL_NTS);
		if (statement->ret == SQL_STILL_EXECUTING) {
			Result = false;
		}
	}

	isError = statement->CheckOperation();

	Result = true;
}

void UODBCStatement::ReadNextRow(UODBCStatement* statement, TArray<UODBCColumn*> setArray, TArray<FResultArray>& rowData)
{
	
	
	while (SQLFetch(statement->stmt) == SQL_SUCCESS) {
		int count = 0;
		FResultArray cols;
		for (const auto setColumn : setArray) {
			count++;
			void* output;
			switch (setColumn->getType()) {
			case EColumnTypes::STRING:
				output = new char[setColumn->_MaxSize];
				SQLGetData(statement->stmt, count, setColumn->getSqlType(), output, setColumn->_MaxSize + 1, NULL);
				break;
			case EColumnTypes::BOOLEAN:
				output = new bool;
				SQLGetData(statement->stmt, count, setColumn->getSqlType(), output, setColumn->_MaxSize + 1, NULL);
				break;
			default:
				SQLGetData(statement->stmt, count, setColumn->getSqlType(), &output, setColumn->_MaxSize + 1, NULL);
			}
			
			UODBCColumn* c = setColumn->Copy(setColumn);
			//SQLGetData(statement->stmt, count, /*c->getSqlType()*/SQL_C_TCHAR, output, c->_MaxSize + 1, NULL);
			c->setValue(output);
			cols.Results.Add(c);
		}
		rowData.Add(cols);
	}
	UE_LOG(ModuleLog, Warning, TEXT("Array Created"));
}

UODBCStatement::~UODBCStatement()
{
	if (printDebug) {
		UE_LOG(ModuleLog, Warning, TEXT("Closing Statement..."));
	}

	// Double check that Handle is freed should GC collect this object for Closing...
	if (stmt != SQL_NULL_HSTMT)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	}
}