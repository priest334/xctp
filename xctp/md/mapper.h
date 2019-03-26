#pragma once

#include <map>
#include <string>
#include <sstream>

using std::map;
using std::string;
using std::ostringstream;

enum MapperType {
	MTINT = 1,
	MTDBL,
	MTARR,
	MTSTR
};


template <typename _Class, typename _Value>
class MapperMember {
public:
	typedef _Value ValueType;
	MapperMember(size_t oft) : oft_(oft) {
	}
public:
	string Get(const _Class& obj) {
		ostringstream oss;
		oss << (const ValueType&)(*((ValueType*)((size_t)(&obj) + oft_)));
		return oss.str();
	}
private:
	size_t oft_;
};


template <typename _Class>
class MapperMember<_Class, string> {
public:
	MapperMember(size_t oft) : oft_(oft) {
	}
public:
	string Get(const _Class& obj) {
		ostringstream oss;
		oss << "\"" << (const string&)(*((string*)((size_t)(&obj) + oft_))).c_str() << "\"";
		return oss.str();
	}
private:
	size_t oft_;
};

template <typename _Class>
class MapperMember<_Class, char*> {
public:
	MapperMember(size_t oft) : oft_(oft) {
	}
public:
	string Get(const _Class& obj) {
		ostringstream oss;
		oss << "\"" << (char*)((size_t)(&obj) + oft_) << "\"";
		return oss.str();
	}
private:
	size_t oft_;
};


template <typename _Class>
class ClassMember {
	int type_;
	union {
		MapperMember<_Class, int>* intMember;
		MapperMember<_Class, double>* dblMember;
		MapperMember<_Class, char*>* arrMember;
		MapperMember<_Class, string>* strMember;
	}m;
public:
	ClassMember(int type, size_t oft) : type_(type) {
		switch (type_) {
		case MTINT:
			m.intMember = new MapperMember<_Class, int>(oft);
			break;
		case MTDBL:
			m.dblMember = new MapperMember<_Class, double>(oft);
			break;
		case MTARR:
			m.arrMember = new MapperMember<_Class, char*>(oft);
			break;
		case MTSTR:
			m.strMember = new MapperMember<_Class, string>(oft);
			break;
		default:
			break;
		}
	}

	string Get(const _Class& obj) {
		switch (type_)
		{
		case MTINT:
			return m.intMember->Get(obj);
		case MTDBL:
			return m.dblMember->Get(obj);
		case MTARR:
			return m.arrMember->Get(obj);
		case MTSTR:
			return m.strMember->Get(obj);
		default:
			return "";
		}
	}
};

template <typename _Class>
class JsonMapper {
protected:
	virtual void Resovle() = 0;
	map<string, ClassMember<_Class>* > members_;
public:
	string jstr(const _Class& obj) {
		ostringstream oss;
		oss << "{";
		auto m = members_.begin();
		for (;;) {
			oss << "\"" << m->first.c_str() << "\":" << m->second->Get(obj);
			if (++m == members_.end()) {
				break;
			}
			oss << ",";
		}
		oss << "}";
		return oss.str();
	}
};


template <typename _Mapper>
class StaticMapper {
	typedef _Mapper* InstancePtr;
public:
	static void Load() {
		if (!instance_) {
			instance_ = new _Mapper();
			instance_->Resovle();
		}
	}

	template <typename _Class>
	static string JsonStr(const _Class& obj) {
		if (instance_) {
			return instance_->jstr(obj);
		}
		return "";
	}

	static InstancePtr Global() {
		return instance_;
	}

private:
	static InstancePtr instance_;
};

template <typename _Mapper>
typename StaticMapper<_Mapper>::InstancePtr StaticMapper<_Mapper>::instance_ = nullptr;





