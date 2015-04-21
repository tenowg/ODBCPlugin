#include "ODBCPCH.h"

UODBCColumnInteger::UODBCColumnInteger(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

UODBCColumnInteger* UODBCColumnInteger::ConstructODBCColumn(FString ColumnName, int32 value, EODBCInteger type, bool isPrimary)
{
	UODBCColumnInteger* column = (UODBCColumnInteger*)StaticConstructObject(UODBCColumnInteger::StaticClass());
	column->_columnName = ColumnName;
	column->Primary = isPrimary;
	column->value = value;
	column->_MaxSize = 0;
	column->DataType = column->toDataType(type);
	return column;
}

UODBCColumn* UODBCColumnInteger::Copy(UODBCColumn* column) {
	UODBCColumnInteger* newColumn = static_cast<UODBCColumnInteger*>(column);
	auto col = (UODBCColumnInteger*)StaticConstructObject(UODBCColumnInteger::StaticClass());
	col->_columnName = newColumn->_columnName;
	col->Primary = newColumn->Primary;
	col->value = newColumn->value;
	col->_MaxSize = newColumn->_MaxSize;
	col->DataType = newColumn->DataType;
	return col;
}

void UODBCColumnInteger::setValue(void* newValue)
{
	int32* castValue = static_cast<int32*>(newValue);

	if (castValue != NULL) {
		value = *castValue;
	}
}

FString UODBCColumnInteger::getValue() const {
	return FString::Printf(TEXT("%s"), value);
}

EColumnTypes UODBCColumnInteger::getType() const 
{
	return EColumnTypes::INTEGER;
}

ESqlDataType UODBCColumnInteger::toDataType(EODBCInteger type)
{
	switch (type)
	{
	case EODBCInteger::INTEGER: return ESqlDataType::SQLINTEGER;
	case EODBCInteger::SMALLINT: return ESqlDataType::SQLSMALLINT;
	case EODBCInteger::BIT: return ESqlDataType::SQLBIT;
	case EODBCInteger::TINYINT: return ESqlDataType::SQLTINYINT;
	case EODBCInteger::BIGINT: return ESqlDataType::SQLBIGINT;
	default:
		return ESqlDataType::NONE;
		break;
	}
}