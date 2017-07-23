dictionary <- read.csv("diceware.txt")
for (i in 1:5) {
  clave <- 0
  for (i in 0:4) {
    r <- runif(1)
    r <- ceiling(r*6)  
    clave <- clave + r * 10^i 
  }
  
  clave <- round(clave,digits = 0)  
  
  cl = grep(clave, readLines("diceware.txt"), value = TRUE)
  print(gsub("\t","",substring(cl, 7)) )
}


fx = p = (1/7776)
k=100
suma = 0

plot(c(0,k),c(0,k))
rect(0,0,k,1)
esperanza = (1-p)/p

for (x in 1:k) {
  fx = fx * (1-p)
  suma <- suma + fx
  points(x,fx)
  points(x,suma)
}
print(suma)