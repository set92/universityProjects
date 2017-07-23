#1a
n = 20
x = seq(from = 0, to = 2*n, by = 0.2)
y = dchisq(x,n)
plot(x,y)

#a
pchisq(13.5, 10, lower.tail = FALSE)
#b
qchisq(0.05, 20, lower.tail = FALSE)
#c
pchisq(29.3, 16, lower.tail = TRUE)
#d
qchisq(0.99, 30, lower.tail = TRUE)

#1b
n = 20
x = seq(from = 0, to = 2*n, by = 0.2)
y = dt(x,n)
plot(x,y)

#a
pt(2.7, 10, lower.tail = FALSE)
#b
qt(0.025, 50, lower.tail = FALSE)
#c
pt(1.75, 25, lower.tail = TRUE)
#d
dt(0.90, 30, ncp = 0, lower.tail = TRUE)


# Ejercicio 2
valores = rnorm(50, mean = 0, sd = 1)
var(valores)

vec <- c()
for (i in 1:100) {
  valores = rnorm(50, mean = 0, sd = 1)
  
  vec[i] <- var(valores)
  
}
hist(vec)
for(gdl in c(49)){
  x = seq(from = 0, to = 2*gdl, by = gdl/100)
  y = dchisq(x, 49)*n
  lines(x,y, col=2)
}
