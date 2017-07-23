
######################
#Ejercicio 2
######################

xNum <- c(19.73,29.38,22.85,26.95,30.52,23.35,29.69355,23.01,25.16)
yNum <- c(133.03,217.53,161.20,198.66,226.00,182.07,188.33,180.41,184.48)
# a. Tipo de variable?
# Se esta usando una variable discreta, ya que lo que tenemos es una tabla de valores finitos.

# b. Calcular tiempo(y) y tamaño(x) medio 
xM = sum(xNum)/length(xNum)
yM = mean(yNum)

# c. Desviacion tipica de las 2 variables

#varianzas poblacionales
xVar = sum((xNum - xM)^2) / length(xNum)
yVar = sum((yNum - yM)^2) / length(yNum)

#desv. estandar poblacionales
xSd = sqrt(xVar)
ySd = sqrt(yVar)

# d. Representar los tiempos en un diagrama de cajas
boxplot(yNum, horizontal = TRUE)

# e. Representar los datos en un diagrama de puntos. Calcular  covarianza poblacional.
plot(xNum,yNum)
covPobl = sum(xNum * yNum)/length(xNum) - xM * yM

# f. Calcular y representar la recta de correlacion.
rectaRegresion = lm(yNum~xNum)
abline(rectaRegresion, lwd=1.5)

# g. Utilizar el modelo anterior para calcular el tiempo necesario para una x = 27
sprintf ("La prediccion para 27Mb es de %.4fs", predict(rectaRegresion, data.frame(xNum = 27)))


######################
#Ejercicio 4
######################
# a. Calcular valor de k para que f sea funcion de densidad
func <- function(x, k=1){k*x^2}
z <- integrate(func, lower=0, upper=1)
1/z$value # como k * z == 1, podemos sacar el valor de k diviendo 1/valor de integral

# b. Calcular funcion de distribucion de X
#func <- function(x, k=1/z$value){k*x^2}
#integrate(func, lower=0, upper=t)

integrand <- function(t) {3*t^2}
integral <- Vectorize(function(x) integrate(integrand, lower = 0, upper = x)$value)

# c. Calcular P(X > 1/2)
1 - integral(1/2)

# d. Calcular EX y VAR(X)
func <- function(x){x*3*x^2}
ex <- integrate(func, lower=0, upper=1)

func <- function(x){x^2*3*x^2}
ex2 <- integrate(func, lower=0, upper=1)

varX = as.numeric(ex2[1]) - (as.numeric(ex[1]))^2

# e. Si tenemos 150 observaciones de X, calcular la probabilidad de que al menos 135 sean mayores de 1/2
p = 7/8
m = 150*p 
q = 1 - p
s2 = 150*p*q
s = sqrt(s2)

prob = 1 - pnorm( (135 - m)/(s) )

######################
#Ejercicio 6
######################

datos <- c(595,685,640,619,604,666,608,605,604,619,587,612,632,607,586,582,636,670,638,562,593,610)

# a - Calcular el intervalo de confianza del 99% para la velocidad media
media = mean(datos)
varianza = var(datos)
sd = sd(datos)

# Al saber que n es 22, lo cual es <30 y no conocer la varianza poblacional, usaremos la t de student
# Como es bilateral usaremos 0.995 en vez de 0.99
aux = qt(0.995,21)

variacion = aux * sd/sqrt(length(datos))

upperBound = media + variacion
lowerBound = media - variacion

# b - Podemos afirmar que la velocidad media es de 640Kb/s? Plantear test de hipotesis adecuado 
# con un test de significacion del 99%

# Si suponemos que es bilateral porque queremos conseguir que nuestra velocidad sea de 640Kb/s, tendremos que
# la probabilidad es 2 * P(t21 > aux)
aux = (640-media)/(sd/sqrt(length(datos)))

#Por lo que buscaremos en la tabla la columna que esta en la fila 21 y tiene el valor mas cercano al valor de aux
aux2 = dt(aux,21)

#Y como aux2 es 0.001 que es menor que 0.0025 rechazaremos la hipotesis

