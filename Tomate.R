dias <- 1:30
umidade <- sample(20:80, 30, replace = TRUE)
ph <- round(runif(30, 4.5, 8.5), 1)
nutrientes_adequados <- sample(0:3, 30, replace = TRUE)

dados_tomate <- data.frame(
  Dia = dias,
  Umidade = umidade,
  pH = ph,
  Nutrientes = nutrientes_adequados
)

dados_tomate$Irrigacao <- ifelse(
  dados_tomate$Umidade < 40 & 
  dados_tomate$pH >= 5.8 & dados_tomate$pH <= 7.2 & 
  dados_tomate$Nutrientes >= 2, 
  "Ligada", 
  "Desligada"
)

cat("\n--- Resumo Estatístico dos Sensores ---\n")
summary(dados_tomate[, c("Umidade", "pH", "Nutrientes")])

cat("\n--- Frequência de Acionamento da Bomba no Mês ---\n")
table(dados_tomate$Irrigacao)

cores_grafico <- ifelse(dados_tomate$Irrigacao == "Ligada", "blue", "red")

plot(
  dados_tomate$Umidade, dados_tomate$pH, 
  col = cores_grafico, 
  pch = 19,
  cex = 1.5,
  xlab = "Umidade do Solo (%)", 
  ylab = "Nível de pH Simulado", 
  main = "Análise de Irrigação (Cultura do Tomate)"
)

abline(v = 40, col = "gray", lty = 2, lwd = 2)
abline(h = c(5.8, 7.2), col = "darkgreen", lty = 2, lwd = 2)

legend(
  "topright", 
  legend = c("Bomba Ligada", "Bomba Desligada"), 
  col = c("blue", "red"), 
  pch = 19,
  bg = "white"
)