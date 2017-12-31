data Tree a = Empty | Node a (Tree a) (Tree a) deriving (Read, Show)

freeTree :: Tree Char
freeTree =
    Node 'P'
        (Node 'O'
            (Node 'L'
                (Node 'N' Empty Empty)
                (Node 'T' Empty Empty)
            )
            (Node 'Y'
                (Node 'S' Empty Empty)
                (Node 'A' Empty Empty)
            )
        )
        (Node 'L'
            (Node 'W'
                (Node 'C' Empty Empty)
                (Node 'R' Empty Empty)
            )
            (Node 'A'
                (Node 'A'  (Node 'C' Empty  Empty)   Empty)
                (Node 'C' Empty  Empty)
            )
        )

countDepth :: Tree Char ->Int -> Int
countDepth (Node _ l r) k = max (countDepth l (k+1) ) (countDepth r (k+1))
countDepth Empty k = k

isBalanced :: Tree Char -> Int-> Bool
isBalanced (Node _ l r) k = ( ( (countDepth l 0) - (countDepth r 0) ) <= k) && (isBalanced l k) && (isBalanced r k)
isBalanced Empty k = True

main :: IO()

main = do
  print(isBalanced freeTree 1)
