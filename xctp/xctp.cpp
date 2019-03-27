// xctp.cpp main
#include <string>
#include <iostream>
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <boost/program_options.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include "websocket_server.h"
#include "md_user_session_manager.h"
#include "ctp_session.h"
#include "settings.h"
#include "md/user_api_struct_mapper.h"
using std::string;
using std::cin;

#if !defined(OS_WIN)
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif

void Daemonize() {
#if !defined(OS_WIN)
	int pid = fork();
	if (pid != 0) exit(0);

	setsid();
	int fd = open("/dev/null", O_RDWR, 0);
	dup2(fd, 0);
	dup2(fd, 1);
	if (fd>2) close(fd);
#endif
}

int main(int argc, char* argv[]) {
	string config_file = "./xctp.conf";
	boost::program_options::options_description desc("options");
	desc.add_options()
		("config-file,f", boost::program_options::value<std::string>(&config_file));
	boost::program_options::variables_map vm;
	try {
		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
		boost::program_options::notify(vm);
	} catch (boost::exception& e) {
		std::cerr << boost::diagnostic_information(e) << std::endl;
		return 0;
	}

	Daemonize();

	Mapper_CThostFtdcDepthMarketDataField::Load();

	settings = new Settings();
	settings->LoadFromFile(config_file);

	md_user_session_manager = boost::make_shared<MdUserSessionManager>();
	ctp_session = boost::make_shared<CtpSession>();
	ctp_session->StartThread();
	auto server = boost::shared_ptr<WebSocketServer>(new WebSocketServer(settings->service.workers_));
	server->StartThread(settings->service.address_, settings->service.port_);
	while (true) {
		string line;
		cin >> line;
		if (line == "close") {
			server->Close(md_user_session_manager->Get("ctp"));
		} else if (line == "exit") {
			break;
		}
	}
	server->Stop();
	server->Join();
    return 0;
}

