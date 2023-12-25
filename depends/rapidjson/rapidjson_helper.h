#ifndef RAPIDJSON_HELPER_H_
#define RAPIDJSON_HELPER_H_

#include <string>
#include <fstream>
#include <log/logger.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

class RapidJsonHelper {
public:
    RapidJsonHelper() = default;

    ErrCode loadFromFile(const std::string path) {
        this->streamFile.open(path);
        CHECK_WITH_INFO(this->streamFile, ErrCode::file_open_error, "open json file(%s) failed!", path.c_str());

        rapidjson::IStreamWrapper streamJson(streamFile);
        this->document.ParseStream(streamJson);
        CHECK_WITH_INFO(this->document.IsObject(), ErrCode::unsupported, "parse json stream failed!");

        return ErrCode::success;
    }

    std::string getString(const std::string node) {
        CHECK_WITH_RET(this->document.HasMember(node.c_str()), std::string());
        return this->document[node.c_str()].GetString();
    }

private:
    std::ifstream       streamFile;
    rapidjson::Document document;
};

#endif // RAPIDJSON_HELPER_H_