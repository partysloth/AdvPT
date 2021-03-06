#pragma once

#include <cassert>
#include <utility> //std::swap
#include <algorithm> // std::find_if
#include <vector> //std::vector

#include "MatrixLike.h"

template<typename T>
using StencilEntry = std::pair<int, T>; // convenience type for stencil entries

template<typename T, size_t rows, size_t cols>
class Stencil : public MatrixLike<T, Stencil<T, rows, cols>, rows, cols> {
public:
	Stencil(const std::vector<StencilEntry<T> >& boundaryEntries, const std::vector<StencilEntry<T> >& innerEntries)
		: boundaryStencil_(boundaryEntries), innerStencil_(innerEntries) { }
	Stencil(const std::vector<StencilEntry<T> >& innerEntries)	// c'tor for stencils w/o explicit boundary handling
		: boundaryStencil_(innerEntries), innerStencil_(innerEntries) { }

	Stencil(const Stencil & o);
	Stencil(Stencil && o) noexcept;

	~Stencil( ) noexcept override { }

	Stencil& operator=(const Stencil & o);
	Stencil& operator=(Stencil && o) noexcept;


	Matrix<T, rows, 1> operator* (const Matrix<T, rows, 1> & o) const override;
    
    //const T & operator() (int r, int c) const ;
    //T & operator() (int r, int c) ;

	Stencil<T, rows, cols> inverseDiagonal( ) const override;

protected:
	std::vector<StencilEntry<T> > boundaryStencil_;	// feel free to change the datatype if convenient
	std::vector<StencilEntry<T> > innerStencil_;	// feel free to change the datatype if convenient
};




template<typename T, size_t rows, size_t cols>
Stencil<T, rows, cols>::Stencil(const Stencil<T, rows, cols> & o) :
	boundaryStencil_(o.boundaryStencil_), 
	innerStencil_(o.innerStencil_)  
	{ }



template<typename T, size_t rows, size_t cols>
Stencil<T, rows, cols>::Stencil(Stencil<T, rows, cols> && o) noexcept :
	boundaryStencil_( std::move(o.boundaryStencil_) ),
	innerStencil_( std::move(o.innerStencil_) )
	{ }


template<typename T, size_t rows, size_t cols>
Stencil<T, rows, cols> & Stencil<T, rows, cols>::operator= (const Stencil<T, rows, cols> & o){
	Stencil tmp(o);
	std::swap(boundaryStencil_, tmp.boundaryStencil_);
	std::swap(innerStencil_, tmp.innerStencil_);
	return *this;
}

template<typename T, size_t rows, size_t cols>
Stencil<T, rows, cols> & Stencil<T, rows, cols>::operator= (Stencil<T, rows, cols> && o) noexcept{
	boundaryStencil_ = std::move(o.boundaryStencil_);
	innerStencil_ = std::move(o.innerStencil_);
	return *this;
}

template<typename T, size_t rows, size_t cols>
Matrix<T, rows, 1>  Stencil<T, rows, cols>::operator* (const Matrix<T, rows, 1> & o) const{
    T sum = 0.0;
    T sum2 = 0.0;
    Matrix<T, rows, 1> temp (0.);
    
    //Boundary
    std::for_each(boundaryStencil_.begin(), boundaryStencil_.end(), [&o,&sum,&sum2](const StencilEntry<T>& entry){
        sum += o(entry.first)*entry.second;
        sum2 += o((o.size()-1)+entry.first)*entry.second;
    });
    temp(0) = sum;
    temp(o.size()-1) = sum2;
    sum = 0.0;
    
    //Inner
    for(int i = 1; i<o.size()-1; ++i){
        std::for_each(innerStencil_.begin(), innerStencil_.end(), [&i,&o,&sum](std::pair<int, T> entry){
            sum += o(i+entry.first)*entry.second;
        });
        temp(i) = sum;
        sum = 0.0;
    }
    return temp;
}

template<typename T, size_t rows, size_t cols>
Stencil<T, rows, cols>  Stencil<T, rows, cols>::inverseDiagonal () const{
    auto it = std::find_if( innerStencil_.begin(), innerStencil_.end(),
                           [](const StencilEntry<T>& element){ return element.first == 0;});
    Stencil<T, rows, cols> temp ({ { 0, 1. } }, { { 0, 1./((*it).second) } });
    return temp;
}

/*
template<typename T, size_t rows, size_t cols>
const T & Stencil<T, rows, cols>::operator() (int r, int c) const {
    return innerStencil_[0].second;
}

template<typename T, size_t rows, size_t cols>
T & Stencil<T, rows, cols>::operator() (int r, int c) {
    return innerStencil_[0].second;
}

*/

