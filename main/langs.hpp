#pragma once

#include <map>
#include <string>

class Langs {
public:
	Langs() = default;
	~Langs() = default;

	void init_dictionary();

	std::string lang_by_ext(const std::string& ext) const {
		const auto& const it = langs.find(ext);
		if (it != langs.end()) {
			return it->second;
		}
		return "";
	}

private:
	std::map<std::string, std::string> langs;
};

void Langs::init_dictionary() {
	langs["cpp"] = "C++";
	langs["hpp"] = "C++";
	langs["c++"] = "C++";
	langs["h++"] = "C++";
	langs["cc"] = "C++";
	langs["hh"] = "C++";
	langs["cu"] = "C++"; // Cuda with C++
	langs["cuh"] = "C++"; // Cuda with C++
	langs["c"] = "C";
	langs["h"] = "C";
	langs["py"] = "Python";
	langs["ipynb"] = "Python";
	langs["gd"] = "Godot Script";
	langs["html"] = "HTML";
	langs["css"] = "CSS";
	langs["go"] = "Go";
	langs["mod"] = "Go";
	langs["js"] = "JavaScript";
	langs["sh"] = "Bash";
	langs["java"] = "Java";
	langs["sql"] = "SQL";
	langs["pro"] = "QMake";
	langs["cmake"] = "CMake";
	langs["asm"] = "Assembly";
	langs["cs"] = "C#";
	langs["obj-c"] = "Objective-C";
	langs["objc"] = "Objective-C";
	langs["qss"] = "QSS";
	langs["cob"] = "COBOL";
	langs["ts"] = "TypeScript";
	langs["php"] = "PHP";
	langs["pl"] = "Perl";
	langs["pm"] = "Perl";
	langs["bas"] = "Basic";
	langs["rb"] = "Ruby";
	langs["rbw"] = "Ruby";
	langs["lua"] = "Lua";
	langs["luna"] = "Lua";
	langs["lunaire"] = "Lua";
	langs["anair"] = "Lua";
	langs["swift"] = "Swift";
	langs["sc"] = "Scala";
	langs["scala"] = "Scala";
	langs["dart"] = "Dart";
	langs["vb"] = "Visual Basic";
	langs["d"] = "D";
	langs["f"] = "Fortran";
	langs["for"] = "Fortran";
	langs["f90"] = "Fortran";
	langs["nim"] = "Nim";
	langs["nims"] = "Nim";
	langs["nimble"] = "Nim";
	langs["pas"] = "Pascal";
	langs["pp"] = "Pascal";
	langs["dpr"] = "Delphi";
	langs["r"] = "R";
	langs["rdata"] = "R";
	langs["rds"] = "R";
	langs["rda"] = "R";
	langs["rs"] = "Rust";
	langs["m"] = "MATLAB";
	langs["mat"] = "MATLAB";
	langs["fig"] = "MATLAB";
	langs["mlx"] = "MATLAB";
	langs["mlapp"] = "MATLAB";
	langs["mltbx"] = "MATLAB";
	langs["mlappinstall"] = "MATLAB";
	langs["mlpkginstall"] = "MATLAB";
	langs["adb"] = "Ada";
	langs["ads"] = "Ada";
	langs["jl"] = "Julia";
	langs["fs"] = "F#";
	langs["fsi"] = "F#";
	langs["fsx"] = "F#";
	langs["fsscript"] = "F#";
	//langs[""] = "";
}