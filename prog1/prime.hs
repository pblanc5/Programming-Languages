-- Author: Patrick Blanchard
-- Date: 1-28-17
-- Description: Find the nth prime number.

primes :: [Int]
primes = sieve [2..]

sieve :: [Int] -> [Int]
sieve (p:xs) = p : sieve [x | x <- xs, (mod x p) > 0]

main = do
       putStrLn "10th prime:"
       print(primes !! 10)

       putStrLn "100th prime:"
       print(primes !! 100) 

       putStrLn "1000th prime:"
       print(primes !! 1000)	
