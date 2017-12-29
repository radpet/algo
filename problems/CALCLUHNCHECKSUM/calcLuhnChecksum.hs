to_list :: Int -> [Int]

to_list n = to_list_helper n []
  where
    to_list_helper:: Int->[Int]->[Int]
    to_list_helper x lst = if x < 10
     then (x `mod` 10):lst
      else to_list_helper (x `div` 10) ((x `mod` 10):lst)

sum_list :: [Int] -> Int
sum_list lst = foldl (+) 0 lst

solve :: [Int] -> Int
solve lst = (sum_list (map( \x -> if ( (snd x) `mod` 2 ) == 0
  then (sum_list (to_list ( (fst x) * 2 ) ) )
  else (fst x) )
  (zip lst [1..]) ) * 9) `mod` 10

calcLuhnChecksum :: Int -> Int
calcLuhnChecksum n = solve (to_list n)

main:: IO()
main = do
  print(calcLuhnChecksum 7992739871)
