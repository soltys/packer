#include <string>
namespace packer
{
    class Toggle
    {
    private:
        std::string name_;
        bool isOn_;

    public:
        Toggle(std::string name, bool isOn) : name_(name), isOn_(isOn) {}

        const std::string &name() const { return name_; }
        const bool is_on() const { return isOn_; }
    };
}