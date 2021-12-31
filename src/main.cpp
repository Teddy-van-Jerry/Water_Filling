#include "waterfilling.h"
#include "generator.h"
#include <boost/program_options.hpp>
#include <boost/exception/diagnostic_information.hpp>

using namespace wf;

int main(int argc, char* argv[]) {

    // https://www.boost.org/doc/libs/1_78_0/doc/html/program_options/tutorial.html
    namespace po = boost::program_options;

    Params param = Params::defaultParams();
    bool isAbs = true;
    double norm = 0;
    double norm_dim = 2;

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
        ("print", po::value<bool>(&param.PRINT)->default_value(true),
            "print results on console")
        ("plt", po::value<bool>(&param.PLOT.ENABLE)->default_value(false),
            "plot results using GNU Plot")
        ("plt.title", po::value<wf::Str>(&param.PLOT.TITLE),
            "plot title")
        ("plt.file", po::value<wf::Str>(&param.PLOT.TITLE)->default_value("output.png"),
            "plot file name")
        ("plt.c.low", po::value<wf::Str>(&param.PLOT.COLOR_LOWER)->default_value("lemonchiffon"),
            "plot color of the lower bar")
        ("plt.c.up", po::value<wf::Str>(&param.PLOT.COLOR_UPPER)->default_value("seagreen"),
            "plot color of the upper bar")
        ("plt.w", po::value<double>(&param.PLOT.WIDTH),
            "plot image width")
        ("plt.h", po::value<double>(&param.PLOT.HEIGHT),
            "plot image height")
        ("abs", po::value<bool>(&isAbs),
            "abs generated data")
        ("norm", po::value<double>(&norm),
            "normalize generated data")
        ("norm-dim", po::value<double>(&norm_dim)->default_value(2),
            "norm dimension")
    ;

    po::options_description hidden("Hidden options");
    hidden.add_options()
        ("command", po::value<Str>(), "command")
    ;

    po::options_description cmdline_options;
    cmdline_options.add(generic).add(config).add(hidden);

    po::options_description config_file_options;
    config_file_options.add(config).add(hidden);

    po::options_description visible("Allowed options");
    visible.add(generic).add(config);

    po::positional_options_description p;
    p.add("command", -1);
    po::variables_map vm;
    // https://www.boost.org/doc/libs/1_78_0/doc/html/program_options/reference.html#header.boost.program_options.errors_hpp
    try {
        po::store(po::command_line_parser(argc, argv).
                  options(cmdline_options).positional(p).run(), vm);
        po::notify(vm);
    } catch (po::ambiguous_option e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::error_with_no_option_name e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::error_with_option_name e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::invalid_bool_value e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::invalid_command_line_style e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::invalid_command_line_syntax e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::invalid_config_file_syntax e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::invalid_option_value e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::invalid_syntax e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::multiple_occurrences e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::multiple_values e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::reading_file e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::required_option e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::too_many_positional_options_error e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::unknown_option e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (po::validation_error e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 2;
    }

    if (vm.count("help")) {
        std::cout << "Usage: " << argv[0] << " <command> [options]\n" << std::endl;
        std::cout << "Commands:" << std::endl;
        std::cout << "  optimize                         solve the optimization problem" << std::endl;
        std::cout << "  generate                         generate random test data" << std::endl;
        std::cout << "  (Leave empty)                    generic use\n" << std::endl;
        std::cout << visible << std::endl;
        return 1;
    }

    if (vm.count("command")) {
        Str cmd = vm["command"].as<Str>();
        if (cmd == "optimize") {

        } else if (cmd == "generate") {

        } else {
            std::cerr << "unrecognized command '" + cmd + "'" << std::endl;
        }
    }    

    // if (vm.count("compression")) {
    //     cout << "Compression level was set to " 
    //         << vm["compression"].as<int>() << ".\n";
    // } else {
    //     cout << "Compression level was not set.\n";
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

    // WaterFilling::WaterFilling();

    return 0;
}
