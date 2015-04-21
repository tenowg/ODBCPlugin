#include "ODBCPCH.h"
#include "ODBCColumnNVarChar.h"

UODBCColumnNVarChar::UODBCColumnNVarChar(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

UODBCColumnNVarChar* UODBCColumnNVarChar::ConstructODBCColumn(FString ColumnName, int32 MaxSize, FString value, bool isPrimary, EODBCString type)
{
	UODBCColumnNVarChar* column = (UODBCColumnNVarChar*)StaticConstructObject(UODBCColumnNVarChar::StaticClass());
	column->_columnName = ColumnName;
	column->Primary = isPrimary;
	column->_MaxSize = MaxSize;
	column->value = value;
	column->DataType = column->toDataType(type);
	return column;
}

UODBCColumn* UODBCColumnNVarChar::Copy(UODBCColumn* column) {
	UODBCColumnNVarChar* newColumn = static_cast<UODBCColumnNVarChar*>(column);
	auto col = (UODBCColumnNVarChar*)StaticConstructObject(UODBCColumnNVarChar::StaticClass());
	col->_columnName = newColumn->_columnName;
	col->Primary = newColumn->Primary;
	col->_MaxSize = newColumn->_MaxSize;
	col->value = newColumn->value;
	col->DataType = newColumn->DataType;
	return col;
}

void UODBCColumnNVarChar::setValue(void* newValue)
{
	//FString castValue = dynamic_cast<FString>(newValue);
	WCHAR* castValue = static_cast<WCHAR*>(newValue);

	//TCHAR* test = ANSI_TO_TCHAR(castValue);

	//if (castValue != NULL) {
	//	value = castValue;
	//}
	value = castValue;
}

FString UODBCColumnNVarChar::getValue() const {
	return FString::Printf(TEXT("'%s'"), *value);
}

EColumnTypes UODBCColumnNVarChar::getType() const 
{
	return EColumnTypes::STRING;
}

ESqlDataType UODBCColumnNVarChar::toDataType(EODBCString type)
{
	switch (type)
	{
	case EODBCString::Char: return ESqlDataType::SQLCHAR;
	case EODBCString::Varchar: return ESqlDataType::SQLVARCHAR;
	case EODBCString::LongVarchar: return ESqlDataType::SQLLONGVARCHAR;
	case EODBCString::WChar: return ESqlDataType::SQLWCHAR;
	case EODBCString::WVarchar: return ESqlDataType::SQLWVARCHAR;
	case EODBCString::WLongVarchar: return ESqlDataType::SQLWLONGVARCHAR;
	default:
		return ESqlDataType::NONE;
		break;
	}
}