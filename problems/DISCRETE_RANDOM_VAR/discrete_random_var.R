# 1
pbinom( 4, 30 , 1/6)

num_trials = 10000
trials = rbinom(num_trials, 30, 1/6) # each trial shows how many 6s we got
sum(trials < 5)/num_trials

# qbinom(p = x, size = n, prob = p)
qbinom(0.25, 30, 1/6 ) # Pr(X<=q) > x

pbinom(4, 30, 1/6, lower.tail = F ) # Pr(X<=x)
pbinom(3, 30, 1/6, lower.tail = F )


# 2
# This represents the number of failures which occur in a
# sequence of Bernoulli trials before a target number of
# successes is reached.

# dnbinom(x, size, prob, mu, log = FALSE)
# pnbinom(q, size, prob, mu, lower.tail = TRUE, log.p = FALSE)
# qnbinom(p, size, prob, mu, lower.tail = TRUE, log.p = FALSE)
# rnbinom(n, size, prob, mu)

archer_prob = 0.2
dnbinom(5,3,archer_prob ) # 5 failed trials before 3 success -> 8 total
pnbinom(3,3,archer_prob, lower.tail=F) # greater than 6 tries
pnbinom(5,3, archer_prob) - pnbinom(1, 3, archer_prob)

# 3
