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

        if (!(this->streamFile)) { 
            if ((6) >= G_LEVEL_LOGGER) { 
                printf("%s %s " "open json file(%s) failed!" " (%s:%d)\n", "[LearnOpenGL]", "[error]",path.c_str(), "C:\\Users\\WANG\\Documents\\MyPrograms\\learn_opengl\\depends\\rapidjson\\rapidjson_helper.h", 16); 
            }; 
            return ErrCode::file_open_error; 
        }

        rapidjson::IStreamWrapper streamJson(streamFile);
        this->document.ParseStream(streamJson);
        CHECK_WITH_INFO(this->document.IsObject(), ErrCode::unsupported, "parse json stream failed!");

        if (!(this->document.IsObject())) { 
            printf("%s %s " "parse json stream failed!" " (%s:%d)\n", "[LearnOpenGL]", "[error]", "C:\\Users\\WANG\\Documents\\MyPrograms\\learn_opengl\\depends\\rapidjson\\rapidjson_helper.h", 27); 
            return ErrCode::unsupported; 
        }

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