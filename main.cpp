#include <string>
#include <fstream>
#include <iostream>
#include <log/logger.h>
#include <rapidjson/rapidjson_helper.h>

volatile int G_LEVEL_LOGGER = 0;

void showBanner(const std::string version)
{
    printf("========================================================================================\n");
    printf("*  __    _____ _____ _____ __  _   _____ _____ _____ __  _ _____ __                     \n");
    printf("* |  |  |  ___|  _  |  __ |  \\| | |     |  __ |  ___|  \\| |   __|  |                    \n");
    printf("* |  |__|  ___|     |   __|     | |  |  |   __|  ___|     |  |_ |  |__                  \n");
    printf("* |_____|_____|__|__|__|\\_|_|\\__| |_____|__|  |_____|_|\\__|_____|_____| version:%s      \n", version.c_str());
    printf("*                                                                                       \n");
    printf("========================================================================================\n");
}

int main()
{
    std::string pathJson("../params.json");
    RapidJsonHelper json;
    int retLoadJson = json.loadFromFile(pathJson);
    CHECK_WITH_RET(retLoadJson == ErrCode::success, ErrCode::file_open_error);

    showBanner(json.getString("version"));

    return ErrCode::success;
}