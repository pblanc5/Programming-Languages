-- Author: Patrick Blanchard
-- Date: 1-28-17 
-- Description: Checks to see if a list is in acsending order

sorted :: [Int] -> Bool
sorted (x:[]) = True
sorted (x:xs) = if (x < (xs !! 0)) then sorted(xs)
                else False

main = do
       let s = [1,2,3,4,5]
       let n = [1,8,3,6,7]
	
       print (s)
       print (sorted(s))

       print (n)
       print (sorted(n))
