#include <ESP8266WiFi.h>

WiFiClientSecure cl;//Cria um cliente seguro (para ter acesso ao HTTPS)
String textFix = "GET /v4/spreadsheets/12IYuWdV0aJa8mQPhsR5C6AVEwZufyC05wufTrTJsSg/values/";
String key = "?key=IzaSyDmot3XwHfsNhqeuKdINMYxpyFK4cY";//Chave de API
//Essas Strings serao auxiliares, para nao precisar ficar re-escrevendo toda hora


void setup()
{
    Serial.begin(115200);//Inicia a comunicacao serial
    WiFi.mode(WIFI_STA);//Habilita o modo estaçao
    WiFi.begin("SUA REDE", "SUA SENHA");//Conecta na sua rede
    delay(3000);//Espera um tempo para se conectar no WiFi

}

void loop()
{

    if (cl.connect("sheets.googleapis.com", 443) == true)//Tenta se conectar ao servidor do Google APIs na porta 443 (HTTPS)
    {
        String toSend = textFix;//Atribuimos a String auxiliar na nova String que sera enviada
        
        toSend += "C2:C4";//Os valores que queremos ler da planilha. Para uma única célula, use algo como "A2"; para ler varios, use algo como "A1:C4".
        toSend += key;//Adicionamos a chave na String
        toSend += " HTTP/1.1";//Completamos o metodo GET para nosso formulario.

        cl.println(toSend);//Enviamos o GET ao servidor-
        cl.println("Host: sheets.googleapis.com");//-
        cl.println();//-
			

        Serial.println("Dado recebido:\n");//Mostra no Serial Monitor todo o pacote recebido.-
        Serial.print(cl.readString());//-
        cl.stop();//Encerramos a conexao com o servidor.
    }
    else
    {
        Serial.println("Erro ao se conectar");
    }
	

    delay(5000);

}
