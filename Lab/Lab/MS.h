#pragma once 
template <class T, int j> class MS //.h 
//template - ключевое слово, MS - СТРОКА матрицы 
{
public:
    T Str[j];
    T& operator[](int j)
    {
        return Str[j]; //возвращает физическое значение 
    };
    const T& operator[](int j) const
    {
        return Str[j];
    };
};