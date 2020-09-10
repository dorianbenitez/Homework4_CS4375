# ---
## Title: "Homework 4 - Logistic Regression"
## Name: Dorian Benitez (drb160130)
## Course: CS 4375.001

## Description: 
##  The purpose of this file is to satisfy the requirements for Assignment 4 - Logistic Regression of the Introduction to Machine Learning course.
# ---

# Loads the data necessary to perform logistic regression
library(HSAUR)
data(plasma)
str(plasma)

# Creates a train set based off the selected data
i <- sample(1:nrow(plasma), nrow(plasma), replace = FALSE)
train <- plasma[i,]

# Creates a logistic regression model using the plasma data
glm1 <- glm(ESR~fibrinogen, data = train, family = "binomial")
glm1$coefficients


startTime <- proc.time()

sigmoid <- function(z){
  1.0 / (1+exp(-z))
}

# Create the weight vector, label vector, and data matrix
weights <- c(1, 1)
data_matrix <- cbind(rep(1, nrow(train)), train$fibrinogen)
labels <- as.integer(train$ESR) - 1

weights <- c(1, 1)  
learning_rate <- 0.001

for (i in 1:500000){
  probVec <- sigmoid(data_matrix %*% weights)
  error <- labels - probVec
  weights <- weights + learning_rate * t(data_matrix) %*% error
}
endTime <- proc.time()
weights
print(paste("Total execution time: ", endTime - startTime))

# This chunk will plot the data
plot(plasma$ESR~plasma$fibrinogen)
cdplot(plasma$ESR~plasma$fibrinogen)

# This chunk will further explore the data
summary(glm1)
names(glm1)
head(glm1)