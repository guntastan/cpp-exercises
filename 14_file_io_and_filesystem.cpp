// exercise 14: file I/O and filesystem
// learn: ifstream, ofstream, fstream, stringstream, filesystem, text and binary files

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

// ==== text file write/read ====

void demonstrateTextFileIO() {
    std::cout << "\n=== text file I/O ===" << std::endl;

    std::ofstream out("students.txt");
    if (!out) {
        throw std::runtime_error("failed to open students.txt for writing");
    }

    out << "alice,20,88.5\n";
    out << "bob,22,91.0\n";
    out << "charlie,19,79.5\n";
    out.close();

    std::ifstream in("students.txt");
    if (!in) {
        throw std::runtime_error("failed to open students.txt for reading");
    }

    std::string line;
    while (std::getline(in, line)) {
        std::cout << "read line: " << line << std::endl;
    }
}

// ==== stringstream parsing ====

struct Student {
    std::string name;
    int age;
    double grade;
};

Student parseStudentLine(const std::string& line) {
    std::stringstream ss(line);
    std::string name, ageText, gradeText;

    std::getline(ss, name, ',');
    std::getline(ss, ageText, ',');
    std::getline(ss, gradeText, ',');

    return {name, std::stoi(ageText), std::stod(gradeText)};
}

void demonstrateStringStream() {
    std::cout << "\n=== stringstream parsing ===" << std::endl;

    std::ifstream in("students.txt");
    if (!in) {
        throw std::runtime_error("failed to open students.txt for parsing");
    }

    std::vector<Student> students;
    std::string line;

    while (std::getline(in, line)) {
        students.push_back(parseStudentLine(line));
    }

    for (const auto& s : students) {
        std::cout << s.name << " | age: " << s.age << " | grade: " << s.grade << std::endl;
    }
}

// ==== fstream read+write ====

void demonstrateFstream() {
    std::cout << "\n=== fstream (read + write) ===" << std::endl;

    std::fstream file("log.txt", std::ios::in | std::ios::out | std::ios::app);
    if (!file) {
        throw std::runtime_error("failed to open log.txt");
    }

    file << "program started\n";
    file << "processed students\n";
    file.close();

    std::ifstream in("log.txt");
    std::string line;
    while (std::getline(in, line)) {
        std::cout << line << std::endl;
    }
}

// ==== binary file I/O ====

void demonstrateBinaryFileIO() {
    std::cout << "\n=== binary file I/O ===" << std::endl;

    std::vector<int> values = {10, 20, 30, 40, 50};

    std::ofstream out("numbers.bin", std::ios::binary);
    if (!out) {
        throw std::runtime_error("failed to open numbers.bin for writing");
    }

    size_t count = values.size();
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));
    out.write(reinterpret_cast<const char*>(values.data()),
              static_cast<std::streamsize>(count * sizeof(int)));
    out.close();

    std::ifstream in("numbers.bin", std::ios::binary);
    if (!in) {
        throw std::runtime_error("failed to open numbers.bin for reading");
    }

    size_t loadedCount = 0;
    in.read(reinterpret_cast<char*>(&loadedCount), sizeof(loadedCount));

    std::vector<int> loaded(loadedCount);
    in.read(reinterpret_cast<char*>(loaded.data()),
            static_cast<std::streamsize>(loadedCount * sizeof(int)));

    std::cout << "loaded values: ";
    for (int v : loaded) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

// ==== filesystem operations ====

void demonstrateFilesystem() {
    std::cout << "\n=== filesystem ===" << std::endl;

    fs::path dir = "data";
    if (!fs::exists(dir)) {
        fs::create_directory(dir);
        std::cout << "created directory: " << dir << std::endl;
    }

    fs::copy_file("students.txt", dir / "students_backup.txt",
                  fs::copy_options::overwrite_existing);

    std::cout << "files in current directory:" << std::endl;
    for (const auto& entry : fs::directory_iterator(".")) {
        std::cout << " - " << entry.path().filename().string();
        if (entry.is_directory()) std::cout << " [dir]";
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "=== exercise 14: file I/O and filesystem ===" << std::endl;

    try {
        demonstrateTextFileIO();
        demonstrateStringStream();
        demonstrateFstream();
        demonstrateBinaryFileIO();
        demonstrateFilesystem();
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\n=== key concepts ===" << std::endl;
    std::cout << "ifstream: read text/binary files" << std::endl;
    std::cout << "ofstream: write text/binary files" << std::endl;
    std::cout << "fstream: read and write same file" << std::endl;
    std::cout << "stringstream: parse/format strings like streams" << std::endl;
    std::cout << "filesystem: path, exists, create_directory, copy_file, iterate" << std::endl;

    return 0;
}