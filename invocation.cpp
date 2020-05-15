#include <iostream>
#include <map>
#include <string>

void invoc_help(const std::string& name, bool exhaustive)
{
	std::cout << "Usage: " << name << " [OPTION ...] [FILE]\n";
	if (exhaustive) {
		std::cout << "\nOPTION:\n"
			  << " -i, --interactive\n"
			  << "\trun the interpreter interactively\n"
			  << " -v, --verbose\n"
			  << "\texplain what is being done\n"
			  << " --help\n"
			  << "\tdisplay this help and exit\n";
	}
}

bool long_opt(const std::string& name, const std::string arg,
	std::map<std::string, std::string>& opt)
{
	if (arg == "help") {
		opt["help"] = "";
	} else if (arg == "interactive") {
		opt["interactive"] = "";
	} else if (arg == "verbose") {
		opt["verbose"] = "";
	} else {
		std::cerr << name << ": invalid option: ‘--" << arg << "’\n";
		return false;
	}
	return true;
}

bool short_opt(const std::string& name, const std::string arg,
	std::map<std::string, std::string>& opt)
{
	for (auto c = arg.cbegin(); c != arg.cend(); c++) {
		switch (*c) {
		case 'i': opt["interactive"] = ""; break;
		case 'v': opt["verbose"] = ""; break;
		default:
			std::cerr << name << ": invalid option: ‘-" << *c
				  << "’\n";
			return false;
		}
	}
	return true;
}

bool set_file(char** av, std::string& file)
{
	if (*av)
		file = *av++;
	else
		file.clear();
	if (*av)
		return false;
	return true;
}

bool invocation(char* av[], std::map<std::string, std::string>& opt,
	std::string& file)
{
	std::string name;

	name = *av++;
	while (*av && (*av)[0] == '-') {
		if ((*av)[1] == '-') {
			if ((*av)[2] == '\0')
				break;
			if (!long_opt(name, *av + 2, opt))
				return false;
		} else {
			if (!short_opt(name, *av + 1, opt))
				return false;
		}
		av++;
	}
	if (opt.count("help")) {
		invoc_help(name, true);
		return false;
	}
	if (!set_file(av, file)) {
		invoc_help(name, false);
		return false;
	}
	return true;
}
