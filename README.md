# Machine Learning in C++
Trying to implement some of machine learning algorithms and techniques on C++. The aim of doing this is not replacing python with C++ but to learn C++ for practical purposes.

# How?
To run my current progress, compile and run.cpp as follows:
```
g++ run.cpp -std=c++17 -o run.o
./run.o
```
I am using `std::any` for which C++17 is required, hence the `-std=c++17 ` flag.
```
bash run.sh
```
^faster. TODO: MAKEFILE.
# Done:
## Data
- A simple CSV reader. See `CSVReader.h`.
- A label encoder for categorical variables. See `preprocess.h`.
- Summarizer in `preprocess.h`. Prints `"mean", "stdv", "count", "min", "20%", "40%", "50%", "60%", "80%", "max"` for each numerical column.
- Summarizer updated in `preprocess.h`. Prints `"count", "unique", "mostfrq", "lstfrq"` for each categorical column.

# Todo:
### Data
- A CSV file reader/writer.
- Data slicing.
- Data summarization for a given arbitrary CSV (mean, median, correlations, quantiles).
- Data clearning and preprocessing (find_na, fill_na, a versatile feature engineering engine).
- Image data - resize, crop, negative, blur, etc.

### Visualizations
- Line plot
- Bar plot
- Point plot

### Loss functions
- MAE, MSE, RMSE
- Cross entropy, negative log loss
- Hinge, huber
- KL Divergence


### Models
- KNN
- Linear regression
- Polynomial regression
- Logistic regression
- Kmeans
- PCA
- GMM
- tSNE
- MLP
- Random forests
- Gradient engine??!
- DNNs??

![](https://i.imgur.com/3lMe1jY.png)