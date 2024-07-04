#include <packer/sources/HttpPackSource.hpp>
#include <packer/Utils.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>
void packer::HttpPackSource::Initialize(PackerArgument packer_argument)
{
    svr.Get("/", [](const httplib::Request &, httplib::Response &res)
            { 
                std::stringstream sstream;
                get_version_string(sstream);
                res.set_content(sstream.str(), "text/plain"); });
    svr.Post("/stop", [&](const httplib::Request &, httplib::Response &res)
             { svr.stop(); });

    svr.Post("/kv", [&](const httplib::Request &req, httplib::Response &res)
             { kv_handler(req, res); });
    svr.Post("/toggle", [&](const httplib::Request &req, httplib::Response &res)
             { toggle_handler(req, res); });
    svr.Post("/translation", [&](const httplib::Request &req, httplib::Response &res)
             { translation_handler(req, res); });
    std::cout << "HTTP server is starting, to stop 'curl -X POST http://127.0.0.1:8080/stop'" << std::endl;
    svr.listen("127.0.0.1", 8080);
    std::cout << "HTTP server was stopped" << std::endl;
}

bool packer::HttpPackSource::Validate() { return true; }

const packer::KeyValueCollection packer::HttpPackSource::key_value_collection() { return key_value_collection_; }
void packer::HttpPackSource::kv_handler(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "POST /kv" << std::endl;
    auto root = nlohmann::json::parse(req.body);
    KeyValuePackType::from_json(root, key_value_collection_);
    res.set_content("OK", "text/plain");
}

const packer::FileCollection packer::HttpPackSource::file_collection() { return packer::FileCollection(); }

const packer::TranslationCollection packer::HttpPackSource::translation_collection() { return translation_collection_; }
void packer::HttpPackSource::translation_handler(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "POST /translation" << std::endl;
    auto root = nlohmann::json::parse(req.body);
    TranslationPackType::from_json(root, translation_collection_);
    res.set_content("OK", "text/plain");
}

const packer::ToggleCollection packer::HttpPackSource::toggle_collection() { return toggle_collection_; }
void packer::HttpPackSource::toggle_handler(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "POST /toggle" << std::endl;
    auto root = nlohmann::json::parse(req.body);
    TogglePackType::from_json(root, toggle_collection_);
    res.set_content("OK", "text/plain");
}