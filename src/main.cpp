/**
 * @file main.cpp
 * @author Teddy van Jerry (me@teddy-van-Jerry.org)
 * @brief Program Command Line Options
 * @version 0.1
 * @date 2022-01-01
 * 
 * @copyright Copyright (c) 2022 Teddy van Jerry
 * 
 */

#include "waterfilling.h"
#include "generator.h"
#include <boost/program_options.hpp>
#include <boost/exception/diagnostic_information.hpp>

using namespace wf;

int main(int argc, char* argv[]) {

    // https://www.boost.org/doc/libs/1_78_0/doc/html/program_options/tutorial.html
    namespace po = boost::program_options;

    Params param = Params::defaultParams();
    Str output_name, input_name;
    Str random_mode = "uniform";
    bool isAbs = true;
    int length_v = 10;
    double min_v = 0;
    double max_v = 1;
    double mean_v = 1;
    double sigma_v = 1;
    double norm = -1;
    double norm_dim = 2;

    po::options_description generic("Generic options");
    generic.add_options()
        ("version,v", "print version string")
        ("help,h", "produce help message")
    ;

    po::options_description config("Configuration");
    config.add_options()
        ("input-data,i", po::value<wf::Str>(&input_name),
            "input data file name")
        ("output,o", po::value<wf::Str>(&output_name),
            "output file name")
        ("precision,p", po::value<double>(&param.PRECISION)->default_value(wf::DEFAULT_PRECISION),
            "optimization precision, i.e. -log10(LINEAR_PRECISION)")
        ("iter-max,k", po::value<int>(&param.ITER_MAX)->default_value(wf::DEFAULT_ITER_MAX),
            "maximum iteration times")
        ("print", po::value<bool>(&param.PRINT)->default_value(true),
            "print results on console")
        ("plt", po::value<bool>(&param.PLOT.ENABLE)->default_value(false),
            "plot results using GNU Plot")
        ("plt.title", po::value<wf::Str>(&param.PLOT.TITLE),
            "plot title")
        ("plt.file", po::value<wf::Str>(&param.PLOT.FILE),
            "plot file name")
        ("plt.c.low", po::value<wf::Str>(&param.PLOT.COLOR_LOWER)->default_value("lemonchiffon"),
            "plot color of the lower bar")
        ("plt.c.up", po::value<wf::Str>(&param.PLOT.COLOR_UPPER)->default_value("seagreen"),
            "plot color of the upper bar")
        ("plt.w", po::value<double>(&param.PLOT.WIDTH),
            "plot image width")
        ("plt.h", po::value<double>(&param.PLOT.HEIGHT),
            "plot image height")
        ("mode,m", po::value<Str>(&random_mode)->default_value("uniform"),
            "random data mode ('uniform' or 'normal')")
        ("length,l", po::value<int>(&length_v),
            "length of test data set")
        ("min", po::value<double>(&min_v),
            "min value for uniform distribution random data generation")
        ("max", po::value<double>(&max_v),
            "max value for uniform distribution random data generation")
        ("mean", po::value<double>(&mean_v),
            "mean value for normal distribution random data generation")
        ("sigma", po::value<double>(&sigma_v),
            "standard deviation for normal distribution random data generation")
        ("abs", po::value<bool>(&isAbs)->default_value(true),
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
            Msgs msgs;
            bool ok;
            Vec alpha = readFile(input_name, &ok);
            if (!ok) return 3;
            Vec x = WaterFilling::optimize(alpha, param, &msgs);
            for (const auto& msg : msgs) std::cerr << msg << std::endl;
            if (!output_name.empty() && !saveAs(output_name, x)) return 3;
        } else if (cmd == "generate") {
            Generator generator;
            Vec alpha;
            if (length_v <= 0) {
                std::cerr << "ERROR: The length of data cannot be zero." << std::endl;
                return 3;
            }
            if (random_mode == "uniform") {
                alpha = generator.uniform(length_v, min_v, max_v);
            } else if (random_mode == "normal") {
                alpha = generator.normal(length_v, min_v, sigma_v);
            } else {
                std::cerr << "ERROR: Unknown random number generation mode '" << random_mode << "'." << std::endl;
                return 3;
            }
            if (isAbs) alpha = abs(alpha);
            if (norm > 0) alpha = normalize(alpha, norm, norm_dim);
            if (param.PRINT) print(alpha);
            if (!generator.saveAs(output_name, alpha)) return 3;
        } else {
            std::cerr << "unrecognized command '" + cmd + "'" << std::endl;
            std::cout << "\nUsage: " << argv[0] << " <command> [options]\n" << std::endl;
            std::cout << "Commands:" << std::endl;
            std::cout << "  optimize                         solve the optimization problem" << std::endl;
            std::cout << "  generate                         generate random test data" << std::endl;
            std::cout << "  (Leave empty)                    generic use\n" << std::endl;
            std::cout << "\nUse \"" << argv[0] << " -h\" for more information." << std::endl;
        }
    }

    return 0;
}
