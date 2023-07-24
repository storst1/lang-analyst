#include "langs.hpp"
#include "lang_stats.hpp"
#include "size_reader.hpp"

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

namespace fs = std::filesystem;

std::vector<std::string> check_gitignore(const std::string& dir_path) {
    std::vector<std::string> ans;
    std::string ignore_path = dir_path + "/.gitignore";
    std::ifstream ignore_file(ignore_path);
    if (!ignore_file.is_open()) {
        return ans;
    }
    std::cout << "Found .gitignore file";
    std::string line;
    while (std::getline(ignore_file, line)) {
        ans.push_back(line);
    }
    return ans;
}

int main()
{
    Langs known_langs;
    known_langs.init_dictionary();
    std::map<std::string, LangStats> project_langs;
    std::vector<std::string> pathes;
    fstream cfg_file("cfg.txt");
    std::string cur_cfg_file;
    while (cfg_file >> cur_cfg_file) {
        pathes.push_back(cur_cfg_file);
    }
    for (const auto& path : pathes) {
        for (auto const& dir_entry : fs::recursive_directory_iterator(path)) {
            if (dir_entry.is_regular_file()) {
                std::stringstream name_stream;
                try {
                    name_stream << dir_entry;
                }
                catch (...) {
                    continue;
                }
                std::string file_name = name_stream.str();
                if (file_name.empty()) {
                    continue;
                }
                std::string file_ext = "";
                int i = file_name.size() - 2;
                bool no_ext = (i >= 0) ? false : true;
                while (!no_ext && file_name[i] != '.') {
                    file_ext += file_name[i];
                    --i;
                    if (i < 0) {
                        no_ext = true;
                    }
                }
                if (no_ext) {
                    continue;
                }
                // Check for cmake
                const std::string cmake_string = "CMakeLists.";
                bool is_cmake = false;
                std::string fake_converted_ext = "";
                if (file_ext == "txt" && file_name.size() - file_ext.size() >= cmake_string.size()) {
                    int j = cmake_string.size() - 1;
                    while (file_name[i] == cmake_string[j]) {
                        --j;
                        --i;
                        if (j < 0) {
                            is_cmake = true;
                            break;
                        }
                    }
                    if (is_cmake) {
                        fake_converted_ext = "cmake";
                    }
                }
                std::reverse(file_ext.begin(), file_ext.end());
                const std::string& ext_to_pass = !fake_converted_ext.empty() ? fake_converted_ext : file_ext;
                std::string cur_lang = known_langs.lang_by_ext(ext_to_pass);
                if (cur_lang == "") {
                    continue;
                }
                LangStats& cur_stats = project_langs[cur_lang];
                ++cur_stats.files;
                cur_stats.size += dir_entry.file_size();
                ++cur_stats.extentions[file_ext];
            }
            //std::cout << dir_entry << '\n';
        }
    }

    // Sort langs by size
    std::vector<std::pair<std::string, LangStats>> projects_langs_vector(project_langs.begin(), project_langs.end());
    std::sort(projects_langs_vector.begin(), projects_langs_vector.end(), [](const auto& left, const auto& right) {return left.second < right.second; });
    std::reverse(projects_langs_vector.begin(), projects_langs_vector.end());

    std::size_t total_size = 0;
    std::cout << std::left << std::setw(25) << "Lang:";
    std::cout << std::left << std::setw(15) << "Size:";
    std::cout << std::left << std::setw(15) << "Files:";
    std::cout << "Extentions found: " << std::endl;
    for (const auto& [lang_name, lang_stats] : projects_langs_vector) {
        std::cout << std::left << std::setw(25) << lang_name;
        std::cout << std::left << std::setw(15) << HumanReadable{ lang_stats.size };
        std::cout << std::left << std::setw(15) << lang_stats.files;
        for (auto it = lang_stats.extentions.begin(); it != lang_stats.extentions.end(); it = std::next(it)) {
            std::cout << it->first << "(" << it->second << ")";
            if (it != std::prev(lang_stats.extentions.end())) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
        total_size += lang_stats.size;
    }
    std::cout << "Total size = " << HumanReadable{ total_size } << std::endl;
}
