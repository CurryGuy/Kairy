#include <Kairy/System/Value.h>
#include <Kairy/Util/ToString.h>

NS_KAIRY_BEGIN

//=============================================================================

Value::Value(void)
{
	_type = Type::Null;
	clear();
}

//=============================================================================

Value::Value(byte v)
{
	clear();
	_type = Type::Byte;
	_primVal.byteVal = v;
}

//=============================================================================

Value::Value(int v)
{
	clear();
	_type = Type::Integer;
	_primVal.intVal = v;
}

//=============================================================================

Value::Value(float v)
{
	clear();
	_type = Type::Float;
	_primVal.floatVal = v;
}

//=============================================================================

Value::Value(double v)
{
	clear();
	_type = Type::Double;
	_primVal.doubleVal = v;
}

//=============================================================================

Value::Value(bool v)
{
	clear();
	_type = Type::Boolean;
	_primVal.boolVal = v;
}

//=============================================================================

Value::Value(const std::string & v)
{
	clear();
	_type = Type::String;
	_strVal = v;
}

//=============================================================================

byte Value::asByte() const
{
	switch (_type)
	{
	case Type::Boolean: return _primVal.boolVal ? 1 : 0;
	case Type::Byte: return _primVal.byteVal;
	case Type::Double: return (byte)_primVal.doubleVal;
	case Type::Float: return (byte)_primVal.floatVal;
	case Type::Integer: return (byte)_primVal.intVal;
	case Type::String: return (byte)atoi(_strVal.c_str());
	default: return 0;
	}
}

//=============================================================================

int Value::asInt() const
{
	switch (_type)
	{
	case Type::Boolean: return _primVal.boolVal ? 1 : 0;
	case Type::Byte: return (int)_primVal.byteVal;
	case Type::Double: return (int)_primVal.doubleVal;
	case Type::Float: return (int)_primVal.floatVal;
	case Type::Integer: return _primVal.intVal;
	case Type::String: return atoi(_strVal.c_str());
	default: return 0;
	}
}

//=============================================================================

float Value::asFloat() const
{
	switch (_type)
	{
	case Type::Boolean: return _primVal.boolVal ? 1.0f : 0.0f;
	case Type::Byte: return (float)_primVal.byteVal;
	case Type::Double: return (float)_primVal.doubleVal;
	case Type::Float: return _primVal.floatVal;
	case Type::Integer: return (float)_primVal.intVal;
	case Type::String: return (float)atof(_strVal.c_str());
	default: return 0.0f;
	}
}

//=============================================================================

double Value::asDouble() const
{
	switch (_type)
	{
	case Type::Boolean: return _primVal.boolVal ? 1.0 : 0.0;
	case Type::Byte: return (double)_primVal.byteVal;
	case Type::Double: return _primVal.doubleVal;
	case Type::Float: return (double)_primVal.floatVal;
	case Type::Integer: return (double)_primVal.intVal;
	case Type::String: return atof(_strVal.c_str());
	default: return 0.0;
	}
}

//=============================================================================

bool Value::asBool() const
{
	switch (_type)
	{
	case Type::Boolean: return _primVal.boolVal;
	case Type::Byte: return _primVal.byteVal != 0;
	case Type::Double: return _primVal.doubleVal != 0.0;
	case Type::Float: return _primVal.floatVal != 0.0f;
	case Type::Integer: return _primVal.intVal != 0;
	case Type::String:
	{
		if (_strVal == "true")
			return true;
		else if (_strVal == "false")
			return false;
		else
			return atoi(_strVal.c_str()) != 0;
	}
	default: return 0;
	}
}

//=============================================================================

std::string Value::asString() const
{
	switch (_type)
	{
	case Type::Boolean: return util::to_string(_primVal.boolVal);
	case Type::Byte: return util::to_string(_primVal.byteVal);
	case Type::Double: return util::to_string(_primVal.doubleVal);
	case Type::Float: return util::to_string(_primVal.floatVal);
	case Type::Integer: return util::to_string(_primVal.intVal);
	case Type::String: return _strVal;
	default: return "";
	}
}

//=============================================================================

void Value::clear()
{
	memset(&_primVal, 0, sizeof(_primVal));
	_strVal.clear();
}

//=============================================================================

Value& kairy::Value::operator=(byte v)
{
	clear();
	_type = Type::Byte;
	_primVal.byteVal = v;

	return *this;
}

//=============================================================================

Value & Value::operator=(int v)
{
	clear();
	_type = Type::Integer;
	_primVal.intVal = v;

	return *this;
}

//=============================================================================

Value & Value::operator=(float v)
{
	clear();
	_type = Type::Float;
	_primVal.floatVal = v;

	return *this;
}

//=============================================================================

Value & Value::operator=(double v)
{
	clear();
	_type = Type::Double;
	_primVal.doubleVal = v;

	return *this;
}

//=============================================================================

Value & Value::operator=(const std::string & v)
{
	clear();

	_type = Type::String;
	_strVal = v;

	return *this;
}

//=============================================================================

bool Value::equals(const Value & other) const
{
	return *this == other;
}

//=============================================================================

bool Value::operator==(const Value & other) const
{
	return equals(other);
}

//=============================================================================

bool Value::operator!=(const Value & other) const
{
	return !equals(other);
}

//=============================================================================

NS_KAIRY_END
