#pragma once
#include <httplib/httplib.h>
#include <packer/sources/PackSource.hpp>

namespace packer
{
    class HttpPackSource : public PackSource
    {
        httplib::Server svr;
        KeyValueCollection key_value_collection_;
        void kv_handler(const httplib::Request &req, httplib::Response &res);
        void toggle_handler(const httplib::Request &req, httplib::Response &res);

        ToggleCollection toggle_collection_;
        TranslationCollection translation_collection_;
    public:
        HttpPackSource() = default;
        void Initialize(PackerArgument packer_argument) override;
        bool Validate() override;
        const std::string name() override { return std::string("HTTP Pack Source"); }
        const KeyValueCollection key_value_collection() override;

        const FileCollection file_collection() override;
        const TranslationCollection translation_collection() override;
        const ToggleCollection toggle_collection() override;
    };
} // namespace packer