#include "waterfilling.h"
#include "generator.h"
#include "boost/program_options.hpp"

using namespace wf;

int main(int argc, char* argv[]) {

	// https://www.boost.org/doc/libs/1_78_0/doc/html/program_options/tutorial.html
	namespace po = boost::program_options;

	Params param = Params::defaultParams();

	po::options_description generic("Generic options");
	generic.add_options()
		("version,v", "print version string")
		("help,h", "produce help message")    
    ;

	po::options_description config("Configuration");
	config.add_options()
		("precision", po::value<double>(&param.PRECISION)->default_value(wf::DEFAULT_PRECISION),
			"optimization precision, i.e. -log10(LINEAR_PRECISION)")
		("iter-max", po::value<int>(&param.ITER_MAX)->default_value(wf::DEFAULT_ITER_MAX),
			"maximum iteration times")
	;

	po::options_description hidden("Hidden options");
	hidden.add_options()
		("input-file", po::value<Str>(), "input file")
    ;

	po::options_description cmdline_options;
	cmdline_options.add(generic).add(config).add(hidden);

	po::options_description config_file_options;
	config_file_options.add(config).add(hidden);

	po::options_description visible("Allowed options");
	visible.add(generic).add(config);

	po::positional_options_description p;
	p.add("command", 1);
	po::variables_map vm;
	po::store(po::command_line_parser(argc, argv).
			  options(cmdline_options).positional(p).run(), vm);
	po::notify(vm);


	if (vm.count("help")) {
		std::cout << visible << std::endl;
		return 1;
	}

	// if (vm.count("compression")) {
	// 	cout << "Compression level was set to " 
	// 		<< vm["compression"].as<int>() << ".\n";
	// } else {
	// 	cout << "Compression level was not set.\n";
	// }

	// Generator generator;
    // Vec alpha = generator.uniform(20, 0, 10);
	// alpha = normalize(alpha, 2.5, 1);
	// print(alpha);
	// Params params;
	// params.PLOT.ENABLE = true;
	// params.PLOT.FILE = "Test.pdf";
	// params.PLOT.WIDTH = 3;
	// params.PLOT.HEIGHT = 2;
	// Vec x = WaterFilling::optimize(alpha, params);
    // print(alpha);
    // print(x);

    return 0;
}
