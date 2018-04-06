# greedy, if no next orders change it, else change the one coming latest
def solve():
    s = input()
    stocks = set([int(x) for x in s.split(' ')])

    o = input()
    orders = [int(x) for x in o.split(' ')]

    if orders[0] not in stocks:
        print("impossible")
        return

    next_orders = {i: 0 for i in range(3000)}
    for order in orders:
        next_orders[order] += 1

    ans = 0

    for i, order in enumerate(orders):
        if order in stocks:
            next_orders[order] -= 1
            continue

        found = False
        for stock in stocks.copy():
            if next_orders[stock] == 0:
                stocks.remove(stock)
                stocks.add(order)
                next_orders[order] -= 1
                ans += 1
                found = True
                break

        if found is False:
            maxIndex = -1
            for stock in stocks:
                for j in range(i + 1, len(orders)):
                    if stock == orders[j]:
                        if maxIndex < j:
                            maxIndex = j
            stocks.remove(orders[maxIndex])
            stocks.add(order)
            next_orders[order] -= 1
            ans += 1

    print (ans)


if __name__ == '__main__':
    solve()
