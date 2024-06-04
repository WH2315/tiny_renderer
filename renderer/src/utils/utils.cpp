#include "utils/utils.hpp"
#include "core/log.hpp"
#include <fstream>

namespace wen {

std::string readFile(const std::string& filename) {
    std::string result;
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in) {
        in.seekg(0, std::ios::end);
        size_t size = in.tellg();
        if (size != -1) {
            result.resize(size);
            in.seekg(0, std::ios::beg);
            in.read(&result[0], size);
            in.close();
        } else {
            WEN_ERROR("Could not open file '{0}'", filename);
        }
    } else {
        WEN_ERROR("Could not open file '{0}'", filename);
    }
    return result;
}

} // namespace wen