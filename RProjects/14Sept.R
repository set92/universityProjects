#14 Sept 2016 - Introduccion a R, lectura de datos y graficos
datos <- c(3,3,1,3,2,2,1,3,3,1,1,3,1,2,3)
length(datos)

#datos de frecuencia
table(datos)
datosTabulate <- tabulate(datos)

pie(datosTabulate, label=c('Linux','MacOS','Windows'))

#Manera 1 de poner nombres
barplot(datosTabulate, names.arg = c('Linux','MacOS','Windows'))

#Manera 2 de poner nombres en barplot
names(datosTabulate) = c('Linux','MacOS','Windows')
barplot(datosTabulate)

#Leemos de fichero
w1 <- read.csv("feedback.csv", header = TRUE, sep = ',')#header es true por defecto en .csv
names(w1)

ncol <- dim(w1)[2]
for (i in 1:ncol) {
  columna_i <- w1[,i]
  nombre_i<-names(w1)[i]
  tabla_i<-table(columna_i)
  pie(tabla_i)
  barplot(tabla_i)
  hist(tabla_i)
}
