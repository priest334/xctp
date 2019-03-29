#pragma once

#include <string>

using std::string;

class Settings {
public:
	Settings();
	~Settings();

	void LoadFromFile(const string& filename);
	void LoadFromBuffer(const string& buffer);
	void LoadFromUrl(const string& url);

	// service settings
	struct {
		string address_;
		string port_;
		int workers_;
	} service;

	struct {
		string cache_path_;
		string market_front_;
		string broker_id_;
		string user_id_;
		string user_password_;
	} ctp;

	struct {
		string url_;
	} auth;

	struct {
		string crlf_;
	}protocol;
};


extern Settings* settings;


