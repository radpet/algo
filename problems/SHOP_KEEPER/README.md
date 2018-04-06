Problem 6 – Shop Keeper
You are the shop keeper of a store, you will be given a sequence of numbers - S representing the products you have in stock (each number representing a certain product ex. 1 = bread, 2 = flour and so on). You will also be given a list of orders placed by customers – O, represented as a sequence of numbers (each number in the list represents an order for a product of that type ex. 1 = a customer has ordered a bread, 2 = customer has ordered flour and so on). Fulfilling an order does not remove the desired product from your stock (imagine we have infinite amounts of all products in stock). After each order, you are allowed to change a single product in your stock to any product you wish, however the total amount of product types in your stock should remain constant. Knowing all orders in advance, your task is to calculate the minimum amount of changes you need to do in your stock, in order to service all of them.
Input
On the first line, we receive the sequence S, each element of S will be separated from the others by a single space.
On the second line, we receive the list of orders O, each element of O will be separated from the others by a single space.
Output
On a single line print the minimum number of changes needed to service all orders, if it's impossible to service all of them write "impossible" instead.
Constraints
The possible product types will be integer numbers in the range [1…3000].
The sequence of products in stock - S will contain only unique products.
The sequence of the products in stock - S will contain between [1…1500] products.
The sequence of the orders - O will contain between [1…12000] orders.
Allowed time: 140 ms. Allowed Memory: 32 MB.
Examples

Input
Output
1 2 3 4
1 2 2 5 1 3
1
Comments
We start with item types 1, 2, 3 and 4 in stock, the first order comes and it wants an item type 1, checking our stock we have the item so we fulfill the order. After fulfilling an order we have the option to change an item type in our stock, looking ahead in the list of orders we see that the next order is for an item type 2, as we already have that item type in stock we decide not to change anything.
After Order 1 -> No exchange
The second order comes in, since we have 2 in stock, we fulfill that order. We are again offered the chance to change an item type in stock, looking ahead we see the next order is for a 2 as well, having the 2 in stock we decide not to change anything again.
After Order 2 -> No exchange
The third order comes in, it is for item type 2 again, so we fulfill it. Looking ahead in the order list we see the next order is for a 5, since we don't have it in stock we have to exchange an item type for it. In this case we have two good choices, we can either change the 2 or the 4, as we won't need them anymore. We arbitrarily choose to exchange the 2.
After Order 3 -> Exchange 2 for 5.
Stock after exchange: 1 5 3 4
The fourth order comes – it's for a 5, since we exchanged the 2 for it we manage to service the order. Looking ahead, the next item is a 1, since we have it we don't change anything.
After Order 4 -> No exchange
The fifth order comes in for a 1, we have it in stock so we fulfill it. Looking ahead the last order is for a 3, as we also have that in stock we skip any changes again.
After Order 5 -> No exchange
The sixth and last order comes in for a 3, we have it in stock so we fulfill it. Having fulfilled all orders we write the number of changes we did 1.

Input
Output
5 3 1 8
8 10 13 13 5 3 1 13 3 8 14 10
5

Input
Output
5 6 7 8
1 6 6 6 8
impossible
Comments
We take a look at the first order – 1, we don't have it in stock so we immediately fail the order, thus we print "impossible".
