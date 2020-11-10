import pymc3 as pm
import pandas as pd
import numpy as np

y = np.array([
    ['GD', 2012, 70, 349, 342],
    ['AH', 604, 23, 129, 594],
    ['JC', 508, 15, 181, 220],
    ['MF', 487, 34, 90, 363],
    ['AN', 473, 16, 68, 722],
    ['CC', 224, 16, 28, 94],
    ['HA', 122, 7, 19, 112],
    ['DP', 83, 6, 22, 81],
    ['PE', 82, 5, 9, 28]
])

df = pd.DataFrame(y, columns=['name', 'high', 'junk', 'low', 'medium'])
num_experiments = len(y)
qa_tiers = ['High', 'Junk', 'Low', 'Medium']

df.index = df.name
df = df.drop(['name'], axis=1)

number_of_experiments = len(y)
k = 4
sample_size = -1

with pm.Model() as multinom_test:
    a = pm.Dirichlet('a', a=np.ones(k))
    data_pred = pm.Multinomial('data_pred', n=number_of_experiments, p=a, observed=df, shape=y.shape)
    trace = pm.sample(1000)
    
pm.traceplot(trace[500:])

