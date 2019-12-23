from scipy import stats
import pandas as pd
import numpy as np


def gausian_pdf(val, mu, std):
    return stats.norm(mu, std).pdf(val)


def load_data():
    return pd.read_csv('./data.csv')


def load_test():
    return pd.read_csv('./test.csv')


HEIGHT = 'height (feet)'
WEIGHT = 'weight (lbs)'
FOOT_SIZE = 'foot size(inches)'
features = [HEIGHT, WEIGHT, FOOT_SIZE]
SEX = 'sex'


# p(Ck | x) ~ p(Ck)Product( p(xi | Ck) ) - continuous gaussian density
def n_b(V, X, y):
    n_classes = np.unique(y)

    stats = {}
    for claz in n_classes:
        # print(claz)
        stats[claz] = X[y == claz].describe()

    labels = []
    probs = []
    for index, v in V.iterrows():
        max_prob = 0
        label = None
        for claz in n_classes:
            prob = 1 / len(n_classes)

            for f in features:
                # print('testing for', claz, 'sample:', f, v[f], stats[claz][f].mean(),
                #       stats[claz][f].std())
                prob *= gausian_pdf(v[f], stats[claz][f]['mean'], stats[claz][f]['std'])
            # print(claz, 'with probability', prob)
            if max_prob < prob:
                max_prob = prob
                label = claz
        probs.append(max_prob)
        labels.append(label)

    return labels, probs


def run():
    df = load_data()
    X = df[[HEIGHT, WEIGHT, FOOT_SIZE]]
    y = df[SEX]

    # print(X)
    # print(y)

    test = load_test()

    labels, probs = n_b(test, X, y)

    print(labels, probs)

    # print(gausian_pdf(1, 1, 1))


if __name__ == '__main__':
    import time

    start = time.time()
    run()
    end = time.time()
    print( (end - start) )

