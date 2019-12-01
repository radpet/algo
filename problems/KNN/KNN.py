import numpy as np
from sklearn import datasets
from sklearn.model_selection import train_test_split


def load_data():
    iris = datasets.load_iris()
    X = iris['data']
    y = iris.target
    target_names = iris['target_names']
    return X, y, target_names


def KNN(V, X, y, k=3):
    distance = np.sqrt(np.sum((X - V) ** 2, axis=1))
    # print('distances',distance)
    nearest_neighbours_idx = np.argsort(distance)[:k]
    nearest_neighbours = distance[nearest_neighbours_idx]
    nearest_classes = y[nearest_neighbours_idx]
    # print(nearest_classes)
    unique, counts = np.unique(nearest_classes, return_counts=True)
    y_predict = unique[np.argmax(counts)]
    return y_predict, list(zip(nearest_neighbours, nearest_classes))


def normalize(corpus):
    corpus_max = np.max(corpus, axis=0)
    corpus_min = np.min(corpus, axis=0)

    # print(corpus_max.shape,corpus_min.shape)
    # print(corpus_max[0], corpus_min[0])

    def _normalize(X):
        return (X - corpus_min) / (corpus_max - corpus_min)

    return _normalize


def test_normalized(X_dev, X_test, y_dev, y_test):
    normalizer = normalize(X_dev)
    normalized_dev = normalizer(X_dev)
    normalized_test = normalizer(X_test)
    correct = 0
    for idx, t in enumerate(normalized_test):
        print('Vector:', t)
        y_predict, distances = KNN(t, normalized_dev, y_dev, k=5)
        correct += y_predict == y_test[idx]
        print('y_pred:', y_predict)
        print('y_gold:', y_test[idx])

        print('distances', distances)
        print('#' * 10)
    print("Accuracy", correct / normalized_test.shape[0])


def test_without_normalization(X_dev, X_test, y_dev, y_test):
    correct = 0
    for idx, t in enumerate(X_test):
        print('Vector:', t)
        y_predict, distances = KNN(t, X_dev, y_dev, k=5)
        correct += y_predict == y_test[idx]
        print('y_pred:', y_predict)
        print('y_gold:', y_test[idx])
        print('distances', distances)
        print('#' * 10)
    print("Accuracy", correct / X_test.shape[0])


def run():
    X, y, target_names = load_data()
    print('X shape', X.shape)
    print('y shape', y.shape)
    print(target_names)

    X_dev, X_test, y_dev, y_test = train_test_split(X, y, random_state=123, stratify=y)
    print('X dev', X_dev.shape)
    print('X test', X_test.shape)

    # test_without_normalization(X_dev, X_test, y_dev, y_test)
    test_normalized(X_dev, X_test, y_dev, y_test)


if __name__ == '__main__':
    run()
