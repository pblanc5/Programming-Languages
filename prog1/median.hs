-- Author: Patrick Blanchard
-- Date: 1-28-17
-- Description: Calculate the median of a list of numbers

qsort :: [Int] -> [Int]
qsort [] = []
qsort (x:xs) = qsort( filter (< x) xs) 
               ++ [x] ++ 
               qsort( filter (>= x) xs)

median :: [Int] -> Float
median [] = 0
median l = do 
	   let a = qsort l
	   if(mod (length l) 2 == 0) then
               fromIntegral ((a !! ((length a) `div` 2)) + (a !! (((length a) `div` 2)-1))) / 2
           else
              fromIntegral (a !! ((length a) `div` 2))

main = do
       let s = [1,2,6,4,3,8]
       let n = [4,2,6,1,3]

       putStrLn "Even List"
       print (s)
       print (median(s))

       putStrLn "Odd List"
       print (n)
       print (median(n))
