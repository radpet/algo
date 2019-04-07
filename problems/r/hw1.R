# 1

library(MASS)
str(survey)
df = survey[sample(nrow(survey), 50),]
df_w = df[df$Sex=="Female",]
df_w[which.min(df_w$Age),]
df[order(df$Height, decreasing = TRUE),][0:3,]$Sex
mean(df[df$Sex=="Male" & df$Pulse>80,]$Age, na.rm = TRUE)
boxplot(survey$Height ~ survey$Sex )


#2

X = 0
Y = 1
df = rbind(data.frame(val=runif(50, 0, X+1), type='U'), data.frame(val=rexp(50, rate=1/(Y+1)), type='E'))
boxplot(df$val ~ df$type)
df_exp = df[df$type=='E',]$val
hist(df_exp, probability = TRUE)
lines(density(df_exp, na.rm = TRUE) )
xs = seq( 0, 20, 0.2)
y = dexp( xs, rate=1/(Y+1))
lines(xs, y, col = 'blue' )


#4
pgamma(2,shape=2,rate=0.5, lower.tail = FALSE)
qgamma(0.35,shape=2,rate=0.5, lower.tail = FALSE)
#pgamma(4.43,shape=2,0.5, lower.tail = FALSE)

qgamma(0.5,shape=2,rate=0.5)
qgamma(0.25,shape=2,rate=0.5)
qgamma(0.75,shape=2,rate=0.5)


#3

f = function( k, T, n ){
  good=0
  for(i in 1:n) {
    x = floor(runif(3, 1,T))
    s = x[1] + 2*x[2]+3*x[3]
    if(s==k) good = good+1
  }
  return(good/n)
}
T = floor(runif(1,1,10))
k = floor(runif(1,10,30))
f(k,T,10000)


