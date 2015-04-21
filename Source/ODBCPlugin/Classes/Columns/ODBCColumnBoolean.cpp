#include "ODBCPCH.h"
//#include "ODBCColumnBoolean.h"

UODBCColumnBoolean::UODBCColumnBoolean(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

UODBCColumnBoolean* UODBCColumnBoolean::ConstructODBCColumn(FString ColumnName, bool value, EODBCBoolean type)
{
	UODBCColumnBoolean* column = (UODBCColumnBoolean*)StaticConstructObject(UODBCColumnBoolean::StaticClass());
	column->_columnName = ColumnName;
	column->Primary = false;
	column->value = value;
	column->_MaxSize = 0;
	column->DataType = column->toDataType(type);
	return column;
}

UODBCColumn* UODBCColumnBoolean::Copy(UODBCColumn* column) {
	UODBCColumnBoolean* newColumn = static_cast<UODBCColumnBoolean*>(column);
	auto col = (UODBCColumnBoolean*)StaticConstructObject(UODBCColumnBoolean::StaticClass());
	col->_columnName = newColumn->_columnName;
	col->Primary = false;
	col->value = newColumn->value;
	col->_MaxSize = newColumn->_MaxSize;
	col->DataType = newColumn->DataType;
	return col;
}

FString UODBCColumnBoolean::getValue() const {
	return FString::Printf(TEXT("%s"), (value) ? "1" : "0");
}

void UODBCColumnBoolean::setValue(void* newValue)
{
	bool* castValue = static_cast<bool*>(newValue);

	if (castValue != NULL) {
		value = *castValue;
	}
}

EColumnTypes UODBCColumnBoolean::getType() const 
{
	return EColumnTypes::BOOLEAN;
}

ESqlDataType UODBCColumnBoolean::toDataType(EODBCBoolean type)
{
	switch (type)
	{
	case EODBCBoolean::Bit: return ESqlDataType::SQLBIT;
	default:
		return ESqlDataType::NONE;
		break;
	}
}