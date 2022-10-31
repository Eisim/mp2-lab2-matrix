// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz <= 0 || sz>MAX_VECTOR_SIZE)
      throw out_of_range("Index out of range");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию

  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      this->sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem,v.pMem+sz,pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = 0; pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          if (sz != v.sz) {
              delete[] pMem;
              sz = v.sz;
              pMem = new T[sz]();
          }
          std::copy(v.pMem, v.pMem + sz, pMem);
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      swap(*this,v);
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz || ind < 0)throw out_of_range("Index out of range");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz || ind < 0)throw out_of_range("Index out of range");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;
      for (int i = 0; i < sz; i++)
          if ((*this)[i] != v[i]) return false;
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; i++)
          res[i] = (*this)[i] + val;
      return res;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; i++)
          res[i] =(*this)[i]- val;
      return res;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; i++)
          res[i] = (*this)[i] * val;
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (v.sz != sz) throw("Sizes are not equal");
      TDynamicVector<T> res(*this);
      for (int i = 0; i < sz; i++)
          res[i] =res[i]+ v[i];
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (v.sz != sz) throw("Sizes are not equal");
      TDynamicVector<T> res(*this);
      for (int i = 0; i < sz; i++)
          res[i] =res[i]- v[i];
      return res;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (v.sz != sz) throw("Sizes are not equal");
      T res=0;
      for (int i = 0; i < sz; i++)
          res += (*this)[i]*v[i];
      return res;
  }


  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
      std::swap(lhs.sz, rhs.sz);
      std::swap(lhs.pMem, rhs.pMem);
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s <= 0 || s > MAX_MATRIX_SIZE ) throw out_of_range("Index out of range");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  
  size_t size() const noexcept  { return sz; }

  const T& at(size_t ind1,size_t ind2) const
  {
      if (ind1 >= sz || ind1 < 0 || ind2 >= sz || ind2 < 0)throw out_of_range("Index out of range");
      return pMem[ind1][ind2];
  }


  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return false;
      for (int i = 0; i < sz; i++)
          if ((*this)[i] != m[i]) return false;
      return true;
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
      TDynamicMatrix<T> res[sz];
      for (int i = 0; i < sz; i++) *this[i] *= val;
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != m.sz) throw("Sizes are not equal");
      TDynamicVector<T> res[sz];
      for (int i = 0; i < res.sz; i++) {
          for (int k = 0; k < sz; k++) {
              for (int j = 0; j < sz; j++)
                  res[i] += (pMem[i][k] * m[k][j]);
          }
      }
      return res;

  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw("Sizes are not equal");
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i]=pMem[i]+m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw("Sizes are not equal");
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] - m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != v.sz) throw std::logic_error("Sizes are not equal");
      TDynamicMatrix<T> res;
      for (size_t i = 0; i < sz; i++)
          for (size_t k = 0; k < sz; k++)
              for (size_t j = 0; j < sz; j++)
                  res.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < sz; i++)
          ostr >> v[i] << "\n";
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++)
          ostr << v[i]<<"\n";
      return ostr;
  }
};



#endif
