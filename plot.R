#!/usr/bin/Rscript

pdf(file="keydam.pdf")
mydata = read.csv("keydam.csv", header=FALSE)
# X11()
colnames(mydata) <- c("Event", "Key", "Timestamp")
speed <- diff(mydata$Timestamp)
plot(speed)
