-- Author: Patrick Blancahrd
-- Date: 1-25-17
-- Descriptiion: Approximate Euler's number 

-- Gets the factorial of a number
fac f = foldl (*) 1 [1..f] 

-- Reciporcates all values in the factorial list and adds them up
euler :: Float
euler = 1 + ( foldl (+) 0 ( map (recip) ( map (fac) [1..100] ) ) )
         
main = do
       print (euler)
