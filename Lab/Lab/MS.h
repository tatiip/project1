#pragma once 
template <class T, int j> class MS //.h 
//template - �������� �����, MS - ������ ������� 
{
public:
    T Str[j];
    T& operator[](int j)
    {
        return Str[j]; //���������� ���������� �������� 
    };
    const T& operator[](int j) const
    {
        return Str[j];
    };
};