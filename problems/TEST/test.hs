
main = do
  x <- getLine
  if read x == 42 then return () else do
    putStrLn(x)
    main
