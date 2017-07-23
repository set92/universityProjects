datos <- read.csv(file ="horasCafeJubilado.csv", header = TRUE, sep='\t')

stripchart(datos$horas, main="Horas de cafe", pch = 2, col = "blue")
stem(datos$horas)

#La variable es de tipo cuantitativa discreta 

#estadisticos de tendencia central
mean(datos$horas)
median(datos$horas)

#moda
install.packages("modeest") 
library(modeest)
mlv(datos$horas, method = "mfv")[1] 

#tabla frecuencias
tablaFreq <- as.data.frame(table(horas = factor(cut(datos$horas, breaks=9))))
transform(tablaFreq, 
          FreqAc = cumsum(Freq), 
          Rel = round(prop.table(Freq), 3), 
          RelAc = round(cumsum(prop.table(Freq)), 3))

#Porcentaje de veces que el cartero ha pasado antes de las 12:22
quantile(datos$horas,.10)

hist(datos$horas)


#Ejercicio 2
datos <- read.csv(file ="muellePeso.csv", header = TRUE)
pairs(datos)

#variable respuesta ~ variable regresora o independiente
regresion <- lm(longitud ~ peso, data = datos)

plot(x = datos$peso, y = datos$longitud, pch = 2, col = "blue")
#Correlacion
cor(datos$peso, datos$longitud)
#Recta de regresion usando para ello la covarianza
abline(regresion, col="green")

#Manera rapida de saber que longitud le corresponde a peso = 12
predict(regresion, data.frame(peso = 12))

#Hecho de la manera vista en clase
x <- datos$peso
y <- datos$longitud
sx<- sd(x)
sy<- sd(y)
sxy<- cov(x,y)
mx <- mean(x)
my <- mean(y)
b <- sxy/sx^2
a <- my - b*mx
abline(a,b,col="red")

#Recta con forma y = a +bx
y = a +b * 12
print(y)# Valor predicho para x = 12
#Vemos que el metodo rapido y el visto en clase dan lo mismo

dato = a + b * 5 - 37.72
real = a + b * mx - my

error = real - dato
print (abs(error))# Error cuando x = 5 e y = 37.72



