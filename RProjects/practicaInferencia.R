# Toma de muestras aleatorias
totalMedias <-c()
totalVarianzas <-c()

sink("datos.txt")
cat("Muestra -- Media -- Varianza", file = "datos.txt", append = TRUE, sep = "\n")

for (j in 1:100) {
  #1
  muestra <- rnorm(10, mean = 25, sd = sqrt(5))
  media <- mean(muestra)
  varianza <- var(muestra)
  
  #2
  cat(muestra, file = "datos.txt", append = TRUE, sep = "\t")
  cat(media, file = "datos.txt", append = TRUE, sep = "\t")
  cat(varianza, file = "datos.txt", append = TRUE, sep = "\n")

  totalMedias <- c(totalMedias, media)
  totalVarianzas <- c(totalVarianzas, varianza)
}
#3
muestra <- rnorm(1000, mean = 25, sd = sqrt(5))
media <- mean(muestra)
varianza <- var(muestra)

# Distr. media muestral
#4
hist(totalMedias, main = "Histograma de la media muestral")
x = muestra # Puesto porque si no da fallo el resto en las funciones de probabilidad diciendo que quiere X
#5
lines(dnorm(x, mean = media, sd = sqrt(5)), col = "green")
#6
lines(dt(x, df = varianza), col = "purple")

# Distr. varianza muestral
#7
hist(totalVarianzas, main = "Histograma de la varianza muestral")
#8
lines(dchisq(x, df = varianza), col = "blue", main = "Grafica de chi cuadrado")
