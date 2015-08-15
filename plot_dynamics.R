#!/usr/bin/Rscript

pdf(file="keystoke_dynamics.pdf")


mydata = read.csv("keystoke_dynamics.csv")

mydata$snum <- seq.int(nrow(mydata))

hist(mydata$keypress_duration)
hist(mydata$key_interval)

