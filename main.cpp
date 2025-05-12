#include <iostream>
#include <string>

int solver_main(int argc, char** argv);
int generator_main(int argc, char** argv);

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <mode> [options]\n"
                  << "Modes:\n"
                  << "  solve <input> <output>\n"
                  << "  generate <size> <output>\n";
        return 1;
    }

    std::string mode(argv[1]);
    if (mode == "solve") {
        return solver_main(argc-1, argv+1);  
    } else if (mode == "generate") {
        return generator_main(argc-1, argv+1);  
    } else {
        std::cerr << "Unknown mode: " << mode << std::endl;
        return 1;
    }
}
