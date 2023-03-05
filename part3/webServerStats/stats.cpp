#include "stats.h"
#include "http_request.h"

#include <string_view>
#include <map>
#include <stdexcept>

using namespace std;

HttpRequest ParseRequest(string_view line) {
	HttpRequest result;

	line.remove_prefix(line.find_first_not_of(' '));

	size_t pos = 0;
	const size_t pos_end = line.npos;
	int counter = 0;

	while(true) {
		const size_t space_pos = line.find(' ', pos);
		if (counter == 0) {
			result.method = line.substr(pos, space_pos - pos);
		} else if (counter == 1) {
			result.uri = line.substr(pos, space_pos - pos);
		} else {
			result.protocol = line.substr(pos, pos_end - pos);
		}
		++counter;

		if (space_pos == pos_end) {
			break;
		} else {
			pos = space_pos + 1;
		}
	}

	return result;

	/*size_t space_pos = line.find(' ', pos);
	result.method = line.substr(pos, space_pos - pos);
	pos = space_pos + 1;

	space_pos = line.find(' ', pos);
	result.uri = line.substr(pos, space_pos - pos);
	pos = space_pos + 1;

	result.protocol = line.substr(pos, line.length() - pos);

	return result; */
}

void Stats::AddMethod(string_view method) {
	try {
		++method_stats.at(method);
	} catch (const out_of_range&) {
		++method_stats["UNKNOWN"];
	}
}

void Stats::AddUri(string_view uri) {
	try {
		++uri_stats.at(uri);
	} catch (const out_of_range&) {
		++uri_stats["unknown"];
	}
}

const map<string_view, int>& Stats::GetMethodStats() const {
	return method_stats;
}

const map<string_view, int>& Stats::GetUriStats() const {
	return uri_stats;
}
