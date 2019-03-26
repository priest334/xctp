#include "json_wrapper.h"


JsonWrapper::JsonWrapper() {
}


JsonWrapper::~JsonWrapper() {
}


bool JsonWrapper::Parse(const char* str) {
	doc_.Parse<0>(str);
	return !doc_.HasParseError();
}

bool JsonWrapper::Get(const char* key, int& value) {
	bool find = false;
	rpj::Value& v = GetValue(key, find);
	if (find && v.IsInt()) {
		value = v.GetInt();
		return true;
	}
	return false;
}

bool JsonWrapper::GetEx(const char* key, int& value, char septor/* = '.'*/) {
	bool find = false;
	char* pkey = _strdup(key);
	rpj::Value& v = GetValueEx(pkey, find, septor);
	free(pkey);
	if (find && v.IsInt()) {
		value = v.GetInt();
		return true;
	}
	return false;
}

bool JsonWrapper::Get(const char* key, double& value) {
	bool find = false;
	rpj::Value& v = GetValue(key, find);
	if (find && v.IsDouble()) {
		value = v.GetDouble();
		return true;
	}
	return false;
}

bool JsonWrapper::GetEx(const char* key, double& value, char septor/* = '.'*/) {
	bool find = false;
	char* pkey = _strdup(key);
	rpj::Value& v = GetValueEx(pkey, find, septor);
	free(pkey);
	if (find && v.IsDouble()) {
		value = v.GetDouble();
		return true;
	}
	return false;
}

bool JsonWrapper::Get(const char* key, std::string& value) {
	bool find = false;
	rpj::Value& v = GetValue(key, find);
	if (find && v.IsString()) {
		value = v.GetString();
		return true;
	}
	return false;
}

bool JsonWrapper::GetEx(const char* key, std::string& value, char septor/* = '.'*/) {
	bool find = false;
	char* pkey = _strdup(key);
	rpj::Value& v = GetValueEx(pkey, find, septor);
	free(pkey);
	if (find && v.IsString()) {
		value = v.GetString();
		return true;
	}
	return false;
}

bool JsonWrapper::Get(const char* key, std::set<int>& value) {
	bool find = false;
	rpj::Value& v = GetValue(key, find);
	if (find && v.IsArray()) {
		size_t i, len = v.Size();
		for (i = 0; i < len; i++) {
			if (v[i].IsInt()) {
				value.emplace(v[i].GetInt());
			}
		}
		return true;
	}
	return false;
}

bool JsonWrapper::GetEx(const char* key, std::set<int>& value, char septor/* = '.'*/) {
	bool find = false;
	char* pkey = _strdup(key);
	rpj::Value& v = GetValueEx(pkey, find, septor);
	free(pkey);
	if (find && v.IsArray()) {
		size_t i, len = v.Size();
		for (i = 0; i < len; i++) {
			if (v[i].IsInt()) {
				value.emplace(v[i].GetInt());
			}
		}
		return true;
	}
	return false;
}

bool JsonWrapper::Get(const char* key, std::set<double>& value) {
	bool find = false;
	rpj::Value& v = GetValue(key, find);
	if (find && v.IsArray()) {
		size_t i, len = v.Size();
		for (i = 0; i < len; i++) {
			if (v[i].IsDouble()) {
				value.emplace(v[i].GetDouble());
			}
		}
		return true;
	}
	return false;
}

bool JsonWrapper::GetEx(const char* key, std::set<double>& value, char septor/* = '.'*/) {
	bool find = false;
	char* pkey = _strdup(key);
	rpj::Value& v = GetValueEx(pkey, find, septor);
	free(pkey);
	if (find && v.IsArray()) {
		size_t i, len = v.Size();
		for (i = 0; i < len; i++) {
			if (v[i].IsDouble()) {
				value.emplace(v[i].GetDouble());
			}
		}
		return true;
	}
	return false;
}

bool JsonWrapper::Get(const char* key, std::set<std::string>& value) {
	bool find = false;
	rpj::Value& v = GetValue(key, find);
	if (find && v.IsArray()) {
		size_t i, len = v.Size();
		for (i = 0; i < len; i++) {
			if (v[i].IsString()) {
				value.emplace(v[i].GetString());
			}
		}
		return true;
	}
	return false;
}

bool JsonWrapper::GetEx(const char* key, std::set<std::string>& value, char septor/* = '.'*/) {
	bool find = false;
	char* pkey = _strdup(key);
	rpj::Value& v = GetValueEx(pkey, find, septor);
	free(pkey);
	if (find && v.IsArray()) {
		size_t i, len = v.Size();
		for (i = 0; i < len; i++) {
			if (v[i].IsString()) {
				value.emplace(v[i].GetString());
			}
		}
		return true;
	}
	return false;
}

bool JsonWrapper::Get(const char* key, std::vector<int>& value) {
	bool find = false;
	rpj::Value& v = GetValue(key, find);
	if (find && v.IsArray()) {
		size_t i, len = v.Size();
		for (i = 0; i < len; i++) {
			if (v[i].IsInt()) {
				value.emplace_back(v[i].GetInt());
			}
		}
		return true;
	}
	return false;
}

bool JsonWrapper::GetEx(const char* key, std::vector<int>& value, char septor/* = '.'*/) {
	bool find = false;
	char* pkey = _strdup(key);
	rpj::Value& v = GetValueEx(pkey, find, septor);
	free(pkey);
	if (find && v.IsArray()) {
		size_t i, len = v.Size();
		for (i = 0; i < len; i++) {
			if (v[i].IsInt()) {
				value.emplace_back(v[i].GetInt());
			}
		}
		return true;
	}
	return false;
}

bool JsonWrapper::Get(const char* key, std::vector<double>& value) {
	bool find = false;
	rpj::Value& v = GetValue(key, find);
	if (find && v.IsArray()) {
		size_t i, len = v.Size();
		for (i = 0; i < len; i++) {
			if (v[i].IsDouble()) {
				value.emplace_back(v[i].GetDouble());
			}
		}
		return true;
	}
	return false;
}

bool JsonWrapper::GetEx(const char* key, std::vector<double>& value, char septor/* = '.'*/) {
	bool find = false;
	char* pkey = _strdup(key);
	rpj::Value& v = GetValueEx(pkey, find, septor);
	free(pkey);
	if (find && v.IsArray()) {
		size_t i, len = v.Size();
		for (i = 0; i < len; i++) {
			if (v[i].IsDouble()) {
				value.emplace_back(v[i].GetDouble());
			}
		}
		return true;
	}
	return false;
}

bool JsonWrapper::Get(const char* key, std::vector<std::string>& value) {
	bool find = false;
	rpj::Value& v = GetValue(key, find);
	if (find && v.IsArray()) {
		size_t i, len = v.Size();
		for (i = 0; i < len; i++) {
			if (v[i].IsString()) {
				value.emplace_back(v[i].GetString());
			}
		}
		return true;
	}
	return false;
}

bool JsonWrapper::GetEx(const char* key, std::vector<std::string>& value, char septor/* = '.'*/) {
	bool find = false;
	char* pkey = _strdup(key);
	rpj::Value& v = GetValueEx(pkey, find, septor);
	free(pkey);
	if (find && v.IsArray()) {
		size_t i, len = v.Size();
		for (i = 0; i < len; i++) {
			if (v[i].IsString()) {
				value.emplace_back(v[i].GetString());
			}
		}
		return true;
	}
	return false;
}

char* JsonWrapper::GetKey(char*& key, bool& cancel, char septor/* = '.'*/) {
	cancel = true;
	char* ikey = key;
	for (; *key != '\0'; key++) {
		if (*key == septor) {
			*key = '\0';
			*(key++) = '\0';
			cancel = false;
			break;
		}
	}
	return ikey;
}

rpj::Value& JsonWrapper::GetChild(rpj::Value& parent, char* key, bool& find, char septor/* = '.'*/) {
	bool cancel = true;
	char* name = GetKey(key, cancel, septor);
	find = false;
	if (parent.IsObject() && parent.HasMember(name)) {
		if (!cancel) {
			return GetChild(parent[name], key, find, septor);
		} else {
			find = true;
			return parent[name];
		}
	} else {
		return null_;
	}
}

rpj::Value& JsonWrapper::GetValue(const char* key, bool& find) {
	if (doc_.HasMember(key)) {
		find = true;
		return doc_[key];
	}
	find = false;
	return null_;
}

rpj::Value& JsonWrapper::GetValueEx(char* key, bool& find, char septor/* = '.'*/) {
	char* ikey = key;
	bool cancel = true;
	char* name = GetKey(ikey, cancel, septor);
	find = false;
	if (doc_.HasMember(name)) {
		return GetChild(doc_[name], ikey, find, septor);
	}
	return null_;
}


