reverseOrdSuff :: Int -> Int
reverseOrdSuff x = foldl (\result y -> (result*10) + y ) 0 (findSuffix (reverse (intToList x [])) [])

intToList :: Int -> [Int] -> [Int]
intToList x res = if (x `div` 10) > 0 then ( intToList (x `div` 10) ( (x `mod` 10):res) ) else x:res

findSuffix :: [Int] -> [Int] -> [Int]
findSuffix [] result = result
findSuffix (x:xs) [] = findSuffix xs [x]
findSuffix (x:xs) result = if (last result) >= x then result else findSuffix xs (result ++ [x])


main::IO()

main = do
  print(reverseOrdSuff 37563)
  print(reverseOrdSuff 32763)
  print(reverseOrdSuff 32567)
  print(reverseOrdSuff 32666)
