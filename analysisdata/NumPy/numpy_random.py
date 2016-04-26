#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
简单的随机数据：
	o rand(d0, d1, ... dn)
	o randn(d0, d1, ... dn)
	o randint(low[, high, size])
	o random_integers(low[, high, size])
	o random_sample([size])
	o random[size]
	o ranf([size])
	o sample([size])
	o choice(a[,size , replace, p])
	o bytes(length)

	排列：
	o shuffle(x)
	o permutation(x)

	分布：
	o beta(a, b[, size])								贝塔分布样本，在[0,1]内
	o binomial(n, p[, size])							二项分布的样本
	o chisquare(df[, size])								卡方分布样本
	o exponential([scale, size])						指数分布
	o f(dfnum, dfden[, size])							F分布样本
	o gamma(shape[, scale, size])						伽马分布
	o geometric(p[, size])								几何分布
	o hypergeometric(ngood, nbad, nsample[, size])		超几何分布
	o laplace([loc, scale, size])						拉普拉斯分布样本
	o lognormal([mean, sigma, size])					对数正态分布
	o normal([loc, scale, size])						正态（高斯）分布
	o poisson([lam, size])								泊松分布
	o uniform([low, high, size])						均匀分布

	随机数生成器：
	o RandomState
	o seed([seed])
	o get_state()
	o set_state(state)
"""

import numpy as np
from matplotlib.pyplot import plot, show

cash = np.zeros(10000)
cash[0] = 1000
outcome = np.random.binomial(9, 0.5, size=len(cash))

for i in range(1, len(cash)):
	if outcome[i] < 5:
		cash[i] = cash[i-1] - 1
	elif outcome[i] < 10:
		cash[i] = cash[i-1] + 1
	else:
		raise AssertionError('Unexpected outcome ' + outcome)



print outcome.min()
print outcome.max()

plot(np.arange(len(cash)), cash)
show()