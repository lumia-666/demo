#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

bool isValidDateTime(const std::string& datetimeStr) {
    // ��������ʱ���ʽ
    const std::string datetimeFormat = "%Y-%m-%d %H:%M:%S";

    // ���ַ���ת��Ϊʱ���
    std::tm tm = {};
    std::istringstream ss(datetimeStr);
    ss >> std::get_time(&tm, datetimeFormat.c_str());
    if (ss.fail()) {
        return false;
    }
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    // �������ʱ�䷶Χ
    auto now = std::chrono::system_clock::now();
    auto minTime = std::chrono::system_clock::from_time_t(0);
    auto maxTime = now + std::chrono::hours(24 * 365 * 100); // 100���
    if (tp < minTime || tp > maxTime) {
        return false;
    }

    // У���Ƿ��������
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::tm utcTm = *std::gmtime(&t);
    auto diff = std::chrono::duration_cast<std::chrono::seconds>(tp - std::chrono::system_clock::from_time_t(std::mktime(&utcTm))).count();
    if (diff != 0) {
        return false;
    }

    return true;
}

int main() {
    std::string datetimeStr = "2023-04-20 14:30:00";
    bool valid = isValidDateTime(datetimeStr);
    std::cout << "datetime string is " << (valid ? "valid" : "invalid") << std::endl;
    return 0;
}
