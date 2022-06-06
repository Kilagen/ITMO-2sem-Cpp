//
// Created by kil4gen on 15.04.2022.
//

#include <chrono>
#include <thread>
#include <curl/curl.h>
#include "single_include/nlohmann/json.hpp"
#include <windows.h>
#include "CurrencyIO.h"


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char *)contents, nmemb * size);
    return size * nmemb;
}

int APIENTRY WinMain(HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
            LPTSTR    lpCmdLine,
            int       cmdShow)
{
    FreeConsole();
    CURL *curl;
    std::string readBuffer;
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.cbr-xml-daily.ru/latest.js");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        while (true) {
            readBuffer.clear();
            curl_easy_perform(curl);
            nlohmann::json jsonData = nlohmann::json::parse(readBuffer);
            auto rates = jsonData["rates"];
            auto timestamp = jsonData["timestamp"];
            for (const auto &t: rates.items()) {
                CurrencyIO::Write(t.key(), t.value(), timestamp);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        }
        curl_easy_cleanup(curl);
    }
    return 0;
}