#pragma once
#include <string>
namespace packer
{
    class LogEntry
    {
    private:
        std::string level_;
        int64_t date_;
        std::string logger_;
        std::string message_;

    public:
        LogEntry(std::string level, int64_t date, std::string logger, std::string message)
            : level_(level), date_(date), logger_(logger), message_(message) {}

        const std::string &level() const { return level_; }
        const int64_t &date() const { return date_; }
        const std::string &logger() const { return logger_; }
        const std::string &message() const { return message_; }
    };
}