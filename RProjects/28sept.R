datos <- read.table(file ="fotocasa.txt", header = TRUE)

#media
mean(datos$m2, na.rm = TRUE)
mean(datos$habs, na.rm = TRUE)
mean(datos$precio, na.rm = TRUE)

summary(datos)

#varianza
var(datos$m2)
var(datos$habs)
var(datos$precio)

#desviacion tipica
sd(datos$m2)
sd(datos$habs)
sd(datos$precio)

#diagrama de cajas e histograma
hist(datos$m2, main = names(datos)[1], col = "red", xlab = "Tamaño", ylab = "Frecuencia")
hist(datos$habs)
hist(datos$precio)
boxplot(datos$m2) # muchos datos atipicos, se ve que hay un nucleo de datos y luego muchos separados
boxplot(datos$habs)
boxplot(datos$precio)

#covarianza
for (i in (1:2)){
  for(j in ((i+1):3)){
    x <- datos[,i]
    y <- datos[,j]
    sx<- sd(x)
    sy<- sd(y)
    sxy<- cov(x,y)
    mx <- mean(x)
    my <- mean(y)
    b <- sxy/sx^2
    a <- my - b*mx
    plot(x,y, main = paste(names(datos[j]), " vs ", names(datos[i]) ) ) 
    abline(a,b,col="red")
  }
}
  