import requests

API_KEY = "9283d5e1c01f51fe78b0c5698542fdae"
CIDADE = "Sao Paulo,BR"

URL = f"http://api.openweathermap.org/data/2.5/weather?q={CIDADE}&appid={API_KEY}&units=metric&lang=pt_br"

print(f"--- Sistema de Inteligência Climática - Tomateiro ---")
print(f"Buscando dados para {CIDADE}...\n")

try:
    resposta = requests.get(URL)
    dados = resposta.json()

    if resposta.status_code == 200:
        clima_principal = dados['weather'][0]['main']
        descricao = dados['weather'][0]['description']
        temp = dados['main']['temp']

        print(f"Condição Atual: {descricao.capitalize()}")
        print(f"Temperatura: {temp}°C")

        if clima_principal == 'Rain':
            print("\n🚨 ALERTA: Chuva detectada!")
            print("➡️ Comando Serial: 'C' (Bloquear irrigação para economizar água)")
        else:
            print("\n☀️ Sem previsão de chuva.")
            print("➡️ Comando Serial: 'S' (Irrigação liberada conforme sensores de solo)")

    else:
        print(f"Erro na API: {resposta.status_code}")

except Exception as e:
    print(f"Erro ao conectar: {e}")