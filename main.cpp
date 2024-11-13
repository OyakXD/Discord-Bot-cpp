#include <iostream>
#include <fstream>
#include <string>
#include "Bot.h"
#include <nlohmann/json.hpp>
using namespace std;

int main() {
    ifstream token_file("../token.json");
    if (!token_file.is_open()) {
        cerr << "Erro: Não foi possivel abrir o arquivo token.json" << endl;
        return 1;
    }

    nlohmann::json config;

    try {
        token_file >> config;

        if (config.contains("token") && !config["token"].is_null() && config["token"].is_string()) {
            string token = config["token"];

            Bot DiscordBot(token);
            DiscordBot.start();
        } else {
            cerr << "Erro: token inválido." << endl;
            return 1;
        }
    } catch (const nlohmann::json::exception& e) {
        cerr << "Erro ao processar o JSON: " << e.what() << endl;
        return 1;
    } catch (const std::exception& e) {
        cerr << "Erro inesperado: " << e.what() << endl;
        return 1;
    }

    cout << "Programa finalizado com sucesso." << endl;
    return 0;
}