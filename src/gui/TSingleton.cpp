/*
 * TSingleton.hpp
 *
 *  Created on: 13.11.2013
 *      Author: kstreser
 */

#ifndef TSINGLETON_HPP_
#define TSINGLETON_HPP_

#include <stdio.h>
#include <stdlib.h>

template <class T>
class TSingleton{

protected:
	static T* m_pSingleton;

public:
	virtual ~TSingleton(){}

	inline static T* Get(){
		if(!m_pSingleton){
			m_pSingleton = new T;
		}
		return m_pSingleton;
	}

	static void Del(){
		if(m_pSingleton){
			delete (m_pSingleton);
			m_pSingleton = NULL;
		}
	}
};
template <class T>
T* TSingleton<T>::m_pSingleton = 0;

#endif /* TSINGLETON_HPP_ */
