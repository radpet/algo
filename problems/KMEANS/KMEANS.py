import numpy as np
from sklearn import datasets
import pandas as pd


def load_data():
    iris = datasets.load_iris()
    X = iris['data']
    y = iris.target
    target_names = iris['target_names']
    return X, y, target_names


def kmeans(X, k=3, max_iter=None):
    i = 1
    cluster_core = X[np.random.choice(X.shape[0], k, replace=False)]
    while True:
        # [1,2,3] [4,5,6] -> [1,4,2,5,3,6] -> [1,4],[2,5],[3,5]
        distance = np.ravel(np.sqrt(np.sum((X - cluster_core[:, np.newaxis]) ** 2, axis=2)), order='F') \
            .reshape((X.shape[0], k))

        assigned_cluster = np.argmin(distance, axis=1)

        if i % 100 == 0:
            print(np.unique(assigned_cluster, return_counts=True))

        df = pd.DataFrame(X)
        df['cluster'] = assigned_cluster
        new_core = df.groupby(['cluster']).mean().values

        if np.allclose(new_core, cluster_core):
            print('Converged at {} steps'.format(i))
            break

        cluster_core = new_core

        if max_iter is not None and max_iter < i:
            break
        i += 1

    return assigned_cluster.reshape((1, -1))[0], cluster_core


def run():
    np.random.seed(1234)
    X, y, target_names = load_data()

    clusters, centroids = kmeans(X, k=3, max_iter=1000)
    cluster, counts = np.unique(clusters, return_counts=True)

    print('Found', cluster, counts)
    print(np.unique(y, return_counts=True))

    # from sklearn.datasets import make_moons
    #
    # X, y = make_moons(200, noise=.05, random_state=0)
    # labels, centroids = kmeans(X, k=2, max_iter=1000)
    # import matplotlib.pyplot as plt
    #
    # plt.scatter(X[:, 0], X[:, 1], c=labels[:],
    #             s=50)
    #
    # plt.scatter(centroids[:, 0], centroids[:, 1], c=[0, 1],
    #             s=50, marker='x')
    #
    # plt.show()


if __name__ == '__main__':
    run()
