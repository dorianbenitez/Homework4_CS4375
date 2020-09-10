# ---
## Title: "Homework 4 - Naive Bayes"
## Name: Dorian Benitez (drb160130)
## Course: CS 4375.001

## Description: The purpose of this file is to satisfy the requirements for Assignment 4- Naive Bayes of the Introduction to Machine Learning course. 
  
# ---

df <- read.csv("/Users/dorianbenitez/desktop/hw4_DorianBenitez/titanic_project.csv", header=TRUE)

# This chunk of code will clean up the data prior to use
startTime <- proc.time()
df$pclass <- factor(df$pclass)
df$survived <- factor(df$survived)

# This chunk will handle the data if it is not found
df <- df[!is.na(df$pclass),]
df <- df[!is.na(df$survived),]

# This chunk creates train and test sets 
train <- df[1:900,]
test <- df[901:1046,]

# This chunk creates the Naive Bayes Classification Model
library(e1071)
nb1 <- naiveBayes(survived~pclass+age+sex, data = train)
nb1

# Learning from the data set
pred1 <- predict(nb1, newdata = test, type = "class")
table (pred1, test$survived)
mean (pred1 == test$survived)

pred1_raw <- predict(nb1, newdata = test, type = "raw")
head(pred1_raw)

# Will display the confusion matrix of the data 
library(caret)
confusionMatrix(pred1, test$survived, positive = "1")

# Saves and prints the runtime of the script
endTime <- proc.time()
totTime <- endTime - startTime
print(paste("Total execution time: ", totTime))

cdplot(df$survived~df$pclass)
cdplot(df$survived~df$sex)

names(df)
summary(df)
