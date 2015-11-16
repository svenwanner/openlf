/************************************************************************
DSPatch - Cross-Platform, Object-Oriented, Flow-Based Programming Library
Copyright (c) 2012-2015 Marcus Tomlinson

This file is part of DSPatch.

GNU Lesser General Public License Usage
This file may be used under the terms of the GNU Lesser General Public
License version 3.0 as published by the Free Software Foundation and
appearing in the file LGPLv3.txt included in the packaging of this
file. Please review the following information to ensure the GNU Lesser
General Public License version 3.0 requirements will be met:
http://www.gnu.org/copyleft/lgpl.html.

Other Usage
Alternatively, this file may be used in accordance with the terms and
conditions contained in a signed written agreement between you and
Marcus Tomlinson.

DSPatch is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
************************************************************************/

#ifndef DSPPARAMETER_H
#define DSPPARAMETER_H

//-------------------------------------------------------------------------------------------------

#include <dspatch/DspThread.h>
#include <string>
#include <vector>
#include <typeinfo>

//=================================================================================================
/// Value container used to hold non-transient component IO

/**
DspParameters are similar to DspSignals in that they provide a generic means of inputting and
outputting data to and from DspComponents. However, unlike signals, parameters are non-transient
inputs and outputs (such as enable / disable, bias, offset, etc.) that allow for a component's
behaviour to be manipulated via direct set / get methods. The parameter type (ParamType) must be
specified on construction of a DspParameter. Any type mismatches on subsequent set / get calls will
immediatly return false.

NOTE: Abstracting component parameters behind the generic DspParameter container allows a
component to be entirely controllable via the DspComponent base class.
*/

class DLLEXPORT DspParameter
{
public:
    enum ParamType
    {
        Null,
        Bool,
        Int,
        Float,
        String,
        FilePath, // this is essentially just a string, but helps when determining an appropriate user input method
        List,     // this type acts as a vector (available items), an int (index selected), and a string (item selected)
        Trigger,   // this type has no value, SetParam(triggerParam) simply represents a trigger. E.g. a button press
        Pointer
    };

    DspParameter();
    DspParameter(ParamType const& type);
    DspParameter(ParamType const& type, int const& initValue, std::pair<int, int> const& valueRange = std::make_pair(-1, -1));
    DspParameter(ParamType const& type, float const& initValue, std::pair<float, float> const& valueRange = std::make_pair(-1.0f, -1.0f));
    DspParameter(ParamType const& type, std::string const& initValue);
    DspParameter(ParamType const& type, const char * const initValue);
    DspParameter(ParamType const& type, std::vector<std::string> const& initValue);
    template<typename T> DspParameter(ParamType const& type, T *initValue);

    ParamType Type() const;
    bool IsSet() const;

    bool const* GetBool() const;
    int const* GetInt() const;
    std::pair<int, int> const* GetIntRange() const;
    float const* GetFloat() const;
    std::pair<float, float> const* GetFloatRange() const;
    std::string const* GetString() const;
    std::vector<std::string> const* GetList() const;
    template<typename T> T* GetPointer() const;
    template<typename T> void GetPointer(T* &value) const;

    void Unset();
    bool SetBool(bool const& value);
    bool SetInt(int const& value);
    bool SetIntRange(std::pair<int, int> const& intRange);
    bool SetFloat(float const& value);
    bool SetFloatRange(std::pair<float, float> const& floatRange);
    bool SetString(std::string const& value);
    bool SetList(std::vector<std::string> const& value);
    template <typename T> bool SetPointer(T* value);

    bool SetParam(DspParameter const& param);

private:
    bool SetPointer(void* value, const std::type_info *ptrType);
  
    ParamType _type;
    bool _isSet;
    bool _isRangeSet;

    bool _boolValue;

    std::pair<int, int> _intRange;
    int _intValue;

    std::pair<float, float> _floatRange;
    float _floatValue;

    std::string _stringValue;
    std::vector<std::string> _listValue;
    void *_ptrValue;
    const std::type_info *_ptrType = NULL;
};

template<typename T> T* DspParameter::GetPointer() const
{
    if (!_isSet || _type != Pointer || *_ptrType != typeid(T))
    {
        return NULL;
    }

    if (_type == Pointer)
    {
        return static_cast<T*>(_ptrValue);
    }

    return NULL;
}

template<typename T> void DspParameter::GetPointer(T* &value) const
{
  value = GetPointer<T>();
}

template<typename T> DspParameter::DspParameter(ParamType const& type, T *initValue)
    : _type(type)
    , _ptrType(&typeid(T))
    , _isSet(false)
    , _isRangeSet(false)
{
    if (!SetPointer(initValue))
    {
        _type = Null;
    }
}

template<typename T> bool DspParameter::SetPointer(T* value)
{
    return SetPointer((void*)value, &typeid(T));
}


//=================================================================================================

#endif  // DSPPARAMETER_H
