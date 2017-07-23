datos <- read.csv("feedback.csv", header = TRUE, sep = ',')#header es true por defecto en .csv
p = dim(datos)[2]#tamanio

for (j in 1:p) {
  columna <- datos [,j]
  columnaTabulate <- table(columna)
  
  if (is.numeric(columna)) {
    hist(columna, main = names(datos)[j])
  }else{
    barplot(columnaTabulate, main = names(datos)[j])
  }
  pie(columnaTabulate, main = names(datos)[j])
}

#practica 2, media, cuantiles...
columna2 <- datos[,"Tiempo"]
mediaTiempo <- mean(columna2)
print(mediaTiempo)#Media
n <- length(columna2)
suma <- sum(columna2)
a<-suma/n
print(a)

quantile(columna2, 0.5)
median(columna2)#Mediana

columna3 <- datos[,"altura"]
summary(columna3)
boxplot(columna3)
quantile(columna3)



