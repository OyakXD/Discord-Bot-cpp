#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <exception>

#include "Bot.h"

void run_bot(const std::string& token) {
    while (true) {
        try {
            Bot DiscordBot(token);
            DiscordBot.start();  // Inicia o bot
        } catch (const std::exception& e) {
            std::cerr << "Erro ao executar o bot: " << e.what() << std::endl;
            std::cerr << "Tentando reiniciar em 5 segundos..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));  // Pausa antes de tentar novamente
        }
    }
}

int main() {
    std::ifstream token_file("../token.txt");
    if (!token_file.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o arquivo token.txt." << std::endl;
        return 1;
    }

    std::string token;
    std::getline(token_file, token);
    token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());

    std::cout << "Token recebido: " << token << std::endl;

    run_bot(token);  // Executa o bot com lógica de reinício

    return 0;
}
