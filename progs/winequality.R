#setting work directory
setwd("C:/RStudio/Wine-Quality")

library(caret)
library(mlbench)
library(rpart)
library(randomForest)

#importing databases
winequality.red <- read.csv("C:/RStudio/Wine-Quality/winequality-red.csv", sep=";")
View(winequality.red)
winequality.white <- read.csv("C:/RStudio/Wine-Quality/winequality-white.csv", sep=";")
View(winequality.white)

#Detecting Outliers via boxplots
boxplot(winequality.red[,12], col = rgb(0,0,1,0.5), main = "Boxplot of Red wine-Quality")
boxplot(winequality.white[,12], col = rgb(0,0,1,0.5), main = "Boxplot of White wine-Quality")

#Removing outliers by subseting data
datar <- subset(winequality.red,!(winequality.red$quality > quantile(winequality.red$quality, probs=c(.01, .95))[2] | winequality.red$quality < quantile(winequality.red$quality, probs=c(.01, .91))[1]) )
dataw<-subset(winequality.white,!(winequality.white$quality > quantile(winequality.white$quality, probs=c(.01, .95))[2] | winequality.white$quality < quantile(winequality.white$quality, probs=c(.01, .91))[1]) )

boxplot(datar[,12],main="Red Wine")
boxplot(dataw[,12], main="White Wine")
#Finding Median of quality for both datasets
a<-median(datar$quality)
b<-median(dataw$quality)

#Converting Regression model into Classificatio

datar[datar$quality > a, 'quality'] <- 'good'
datar[datar$quality < a,'quality'] <- 'bad'  
datar[datar$quality ==a,'quality']<-'normal'
datar$quality <- as.factor(datar$quality)

dataw[dataw$quality > b, 'quality'] <- 'good'
dataw[dataw$quality < b,'quality'] <- 'bad'  
dataw[dataw$quality==b,'quality']<-'normal'
dataw$quality <- as.factor(dataw$quality)

#Spliting the datasets
# set the seed for reproducibility
set.seed(1234) 
temp <- createDataPartition(datar$quality, p = 0.7, list = FALSE)
trainred <- datar[temp, ]
testred <- datar[-temp, ]

temp <- createDataPartition(dataw$quality, p = 0.7, list = FALSE)
trainwhite <- dataw[temp, ]
testwhite <- dataw[-temp, ]

remove(datar)
remove(dataw)
remove(temp)
#Finding Correlation matrix for both datasets
correlationmatrix<-cor(trainred[,1:11])
correlationmatrix2<-cor(trainwhite[,1:11])

correlated1<-findCorrelation(correlationmatrix,cutoff = 0.5)
correlated2<-findCorrelation(correlationmatrix2,cutoff=0.5)

colnames(correlationmatrix)[correlated1]
corrplot::corrplot(correlationmatrix, method = 'number', tl.cex = 0.5,main="Red")

colnames(correlationmatrix2)[correlated2]
corrplot::corrplot(correlationmatrix2, method = 'number', tl.cex = 0.5, main="White")

fitControl_rfe <- rfeControl(functions = rfFuncs, method = 'cv', number = 5) # 5-fold CV
fit_rfe <- rfe(quality ~., data = trainred,sizes = c(1:10),rfeControl = fitControl_rfe)
#features <- predictors(fit_rfe) 
max(fit_rfe$results$Accuracy)
#plot(fit_rfe, type = c('g', 'o'), main = 'Recursive Feature Elimination')

#Remove redundant Attributes
trainred<-trainred[c(-correlated1)]
trainwhite<-trainwhite[c(-correlated2)]

#Random Forest Classifier
fitControl <- trainControl(method = 'cv', number = 5)
fit <- train(x = trainred[,1:8], y =trainred$quality,method = 'rf',preProcess ="range",trControl = fitControl,tuneGrid = expand.grid(.mtry = c(2:6)),n.tree = 1000)
#predicting output
predict <- predict(fit, newdata = testred[,1:11])

#Finding Confusion Matrix Of Predicted against the test dataset
confMat <- confusionMatrix(predict, testred$quality, positive = 'good')
print(confMat)

#Finding importance of features for Red Wine
importance <- varImp(fit, scale = TRUE)
plot(importance, main = 'Feature importance for RED wine via Random Forest classifier')


fit<- train(x = trainwhite[,1:9], y =trainwhite$quality,method = 'rf',preProcess ="range",trControl = fitControl,tuneGrid = expand.grid(.mtry = c(2:6)),n.tree = 1000)
#predicting output
predict <- predict(fit, newdata = testwhite[,1:11])

#Finding Confusion Matrix Of Predicted against the test dataset
confMat <- confusionMatrix(predict, testwhite$quality, positive = 'good')
print(confMat)

#Finding importance of features for White Wine
importance <- varImp(fit, scale = TRUE)
plot(importance, main = 'Feature importance for WHITE wine via Random Forest classifier')








