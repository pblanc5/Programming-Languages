-- Author: Patrick Blanchard
-- Date: 1-30-17
-- Description: Reverse digits in a number

logBase10 :: Int -> Int
logBase10 n =  if (n > 9) then 1 + logBase10 (div n 10)
               else 0

my_reverse :: Int -> Int
my_reverse n = if (n > 0) then (n `mod` 10) * (10^logBase10 n) + my_reverse (n `div` 10)  
	       else 0

my_reverse2 :: Int -> Int
my_reverse2 n = if (n > 0) then
    ((n `mod` 10) * (10 ^ (truncate (logBase 10 (fromIntegral(n)))))) + (my_reverse2 (n `div` 10))
    else 0
               

main = do
       print (my_reverse 1234)
       print (my_reverse 0123)
       print (my_reverse 1230)
       print (my_reverse 1204)
