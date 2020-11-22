#ifndef GIFTIALAB_UTIL_IO_HPP
#define GIFTIALAB_UTIL_IO_HPP

#include "scope_guard.hpp"
#include "log_util.hpp"

#include <iostream>
#include <fstream>
#include <locale>

#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#include <functional>

namespace giftialab {
namespace util {

void for_each_file(const char *dir, std::function<bool(std::wifstream &)> func) {
	DIR *p_dir = opendir(dir);
	if (!p_dir) {
		LOG(ERROR) << "open dir[" << dir << "] failed with err[" << errno << "," << strerror(errno) << "]";
		return;
	}
	util::ScopeGuard sg([&](){
		closedir(p_dir);
	});
	struct dirent *p_dirent = nullptr;
	// total file path
	char file_path[1024];
	file_path[sizeof(file_path) - 1] = 0;
	while (p_dirent = readdir(p_dir)) {
		if (p_dirent->d_type == DT_REG) {
			int ret = snprintf(file_path, sizeof(file_path) - 1, "%s/%s", dir, p_dirent->d_name);
	       		if (ret >= sizeof(file_path) || ret == -1) {
				LOG(ERROR) << "cannot format file path of dir[" << dir << "] and name[" << p_dirent->d_name << "]";
				continue;
			}
			LOG(INFO) << "read file[" << file_path << "]";
			std::wifstream in(file_path);
			in.imbue(std::locale("C.utf8"));
			if (func(in)) {
				continue;
			}
			break;
		}
	}
}

} // ns util
} // ns giftialab

#endif
