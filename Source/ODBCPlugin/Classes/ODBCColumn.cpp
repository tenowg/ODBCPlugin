#include "ODBCPCH.h"
//#include "ODBCColumn.h"

UODBCColumn::UODBCColumn(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

SQLINTEGER UODBCColumn::getSqlType()
{
	switch (DataType)
	{
		// Boolean Types
		case ESqlDataType::SQLBIT: return SQL_C_BIT;
		// String Types
		case ESqlDataType::SQLCHAR: return SQL_C_CHAR;
		case ESqlDataType::SQLVARCHAR: return SQL_C_CHAR;
		case ESqlDataType::SQLLONGVARCHAR: return SQL_C_CHAR;
		case ESqlDataType::SQLWCHAR: return SQL_C_WCHAR;
		case ESqlDataType::SQLWVARCHAR: return SQL_C_WCHAR;
		case ESqlDataType::SQLWLONGVARCHAR: return SQL_C_WCHAR;
		// Integer Types
		case ESqlDataType::SQLINTEGER: return SQL_C_SLONG;
		case ESqlDataType::SQLTINYINT: return SQL_C_TINYINT;
		case ESqlDataType::SQLSMALLINT: return SQL_C_SHORT;
		case ESqlDataType::SQLBIGINT: return SQL_C_SBIGINT;
		default: return -1;
	}
}

FString UODBCColumn::getValue() const {
	return FString();
}

void UODBCColumn::setValue(void* newValue) {}

EColumnTypes UODBCColumn::getType() const 
{
	return EColumnTypes::NONE;
}

UODBCColumn* UODBCColumn::Copy(UODBCColumn* column) {
	return nullptr;
}