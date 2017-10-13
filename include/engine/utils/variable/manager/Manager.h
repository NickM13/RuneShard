#pragma once
#include "..\..\Singleton.h"
#include "..\..\Utilities.h"
#include <map>
#include <set>
#include <vector>

template<class T>
class ManagerSet {
protected:
	std::vector<T> m_unitSet;
public:
	Uint32 getUnitId(T p_unit) {
		Uint32 i = 0;
		for(T unit : m_unitSet) {
			if(unit == p_unit) {
				return i;
			}
			i++;
		}
		m_unitSet.push_back(p_unit);
		return i;
	}
	T getUnit(Uint32 p_id) {
		return m_unitSet[p_id];
	}
};

template<class K, class V>
class ManagerMap {
protected:
	std::map<K, V> m_unitMap;
public:
	bool contains(K key) {
		return (m_unitMap.find(key) != m_unitMap.end());
	}
	void addUnit(K key, V value) {
		if(m_unitMap.find(key) == m_unitMap.end()) {
			m_unitMap.insert({key, value});
		}
	}
	V getUnit(K key) {
		return m_unitMap[key];
	}
};

template<class E>
class ManagerEntity
{
protected:
	std::vector<E> m_unitList;
public:
	Uint32 addUnit(E p_unit) {
		m_unitList.push_back(p_unit);
		return Uint32(m_unitList.size() - 1);
	}
	E& getUnit(Uint32 p_index) {
		return m_unitList.at(p_index);
	}
	Uint32 getUnitCount() {
		return m_unitList.size();
	}
	std::vector<E>& getUnitList() {
		return m_unitList;
	}
	Uint32 getUnitID(E p_unit) {
		for(Uint32 i = 0; i < m_unitList.size(); i++)
			if(p_unit == m_unitList[i])
				return i;
		return addUnit(p_unit);
	}
	void removeUnit(Uint16 p_index) {
		m_unitList.erase(m_unitList.begin() + p_guid);
	}
};