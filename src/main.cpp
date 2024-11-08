  #include <iostream>
  #include <fstream>
  #include <string>
  #include <dpp/dpp.h>
  #include <nlohmann/json.hpp>

  using namespace std;
  using namespace dpp;
  using json = nlohmann::json;

  string getBotToken(const string& filePath){
    ifstream file(filePath);
    string token;

    if(file.is_open()){
      json j;
      file >> j;

      if(j.contains("token")){
        token = j["token"].get<string>();        
      } else {
        cerr << "Chave 'token' não encontrada no JSON." << endl;
      }

      file.close();
    } else {
      cerr << "Erro ao abrir o arquivo" << filePath << endl;
    }

    return token;
  }

  int main(){

    /*
      Iniciar o bot
    */
    cluster bot(getBotToken("token.json"));
    bot.on_log(utility::cout_logger());
    bot.start(st_wait);

  }


