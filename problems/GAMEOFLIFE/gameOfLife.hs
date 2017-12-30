
gen_neigh :: (Int, Int) -> [(Int, Int)]

gen_neigh (i, j)= [(i-1, j-1), (i-1, j), (i-1, j+1), (i,j-1), (i, j+1), (i+1, j-1), (i+1, j), (i+1,j+1)]

eqv :: (Int, Int) -> (Int, Int) -> Bool
eqv first second  = ((fst first) == (fst second)) && ((snd first) == (snd second) )

is_inside :: (Int, Int) -> [(Int, Int)] -> Bool
is_inside pos positions  = length (filter (\x -> eqv pos x) positions) == 1

intersect :: [(Int, Int)] -> [(Int, Int)] -> [(Int, Int)]
intersect lst1 lst2 = filter (\x -> is_inside x lst1) lst2

get_status :: (Int, Int) -> [(Int, Int)] -> Int
get_status pos board = length(intersect (gen_neigh pos) board)

gen_dead :: [(Int, Int)] -> [(Int, Int)]
gen_dead board = [x | x <- board , (get_status x board) < 2]

remove_repeating:: [(Int, Int)] -> [(Int, Int)]
remove_repeating seq = iter seq []
    where iter lst res = if null lst then res else if is_inside (head lst) res then iter (tail lst) res else iter (tail lst) (res ++ [(head lst)])


gen_born:: [(Int, Int)] -> [(Int, Int)]
gen_born board = [x | x <- (remove_repeating (concat [gen_neigh  x | x <-board])), (get_status x board) == 3]

gameOfLife:: [(Int, Int)] -> [(Int, Int)]
gameOfLife board = remove_repeating ([x | x <- board, (is_inside x (gen_dead board)) == False] ++ (gen_born board))

main :: IO()

main = do
  {--print( gen_neigh (0,0) )
  print( eqv (1,1) (1,1))
  print( eqv (1,1) (0,0))
  print(is_inside (0,0) [(1,1), (2,2)])
  print(is_inside (0,0) [(1,1), (2,2), (0,0)])
  print(intersect [(0,0),(0,1)] [(0,2), (0,0),(0,3),(0,1)])
  print(get_status (0,0) [(0,-1), (0,0), (0,1)])
  print(get_status (0,-1) [(0,-1), (0,0), (0,1)])
  print(get_status (0, 1) [(0,-1), (0,0), (0,1)])
  print(get_status (-1, 0) [(0,-1), (0,0), (0,1)])
  print(get_status (1, 0) [(0,-1), (0,0), (0,1)])
  print(gen_dead [(0,-1), (0,0), (0,1)])
  print(gen_born [(0,-1), (0,0), (0,1)])
  print(remove_repeating [(1,2), (1,2), (3,4)])
  --}
  print(gameOfLife [(0,0),(0,1),(1,0),(1,1)])
  print(gameOfLife [(0,-1),(0,0),(0,1)])
  print(gameOfLife [(0,1),(1,2),(2,0),(2,1),(2,2)])
