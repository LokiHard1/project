#include <iostream>
#include <stdexcept>
#include <cpr/cpr.h>

std::string fetchDataFromAPI(const std::string& url) {
    try {
        auto response = cpr::Get(cpr::Url{url});

        if (response.error) {
            throw std::runtime_error("Ошибка запроса: " + response.error.message);
        }

        int statusCode = response.status_code;

        if (statusCode >= 500) {
            throw std::runtime_error("Ошибка сервера (5xx): " + std::to_string(statusCode));
        }
        if (statusCode >= 400) {
            throw std::runtime_error("Ошибка клиента (4xx): " + std::to_string(statusCode));
        }
        if (response.text.empty()) {
            throw std::runtime_error("Пустой ответ от API");
        }

        return response.text;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при обращении к API: " << e.what() << std::endl;
        return "";
    }
}

int main() {
    std::string url = "https://api.example.com/data";
    std::string data = fetchDataFromAPI(url);

    if (!data.empty()) {
        std::cout << "Полученные данные: " << data << std::endl;
    } else {
        std::cout << "Не удалось получить данные." << std::endl;
    }
}
