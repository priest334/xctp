#include "settings.h"

#include <iostream>
#include <fstream>
#include "json_wrapper.h"


Settings* settings = nullptr;

Settings::Settings() {
	service.address_ = "0.0.0.0";
	service.port_ = "4567";
	service.workers_ = 5;

	ctp.cache_path_ = "";
	ctp.market_front_ = "";
	ctp.broker_id_ = "";
	ctp.user_id_ = "";
	ctp.user_password_ = "";
}

Settings::~Settings() {
}

void Settings::LoadFromBuffer(const string& buffer) {
	JsonWrapper jw;
	if (jw.Parse(buffer.c_str())) {
		jw.GetEx("service.address", service.address_);
		jw.GetEx("service.port", service.port_);
		jw.GetEx("service.workers", service.workers_);

		jw.GetEx("ctp.cache-path", ctp.cache_path_);
		jw.GetEx("ctp.market-front", ctp.market_front_);
		jw.GetEx("ctp.broker-id", ctp.broker_id_);
		jw.GetEx("ctp.user-id", ctp.user_id_);
		jw.GetEx("ctp.user-password", ctp.user_password_);
	}
}

void Settings::LoadFromFile(const string& filename) {
	const size_t max_buffer_length = 2048;
	char fixed_buffer[max_buffer_length+1] = { 0 };
	string buffer = "";
	std::ifstream file(filename);
	if (file.good()) {
		while (!file.eof()) {
			file.read(fixed_buffer, max_buffer_length);
			buffer += fixed_buffer;
		}
	}
	if (!buffer.empty()) {
		LoadFromBuffer(buffer);
	}
}

void Settings::LoadFromUrl(const string& url) {
}







