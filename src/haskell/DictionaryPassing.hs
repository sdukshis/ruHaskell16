data Stringable a = Stringable { toString :: a -> String }

data Person = Person { firstname :: String, lastname :: String }

personToString :: Person -> String
personToString p = take 1 (firstname p) ++ ". " ++ lastname p

dStringablePerson :: Stringable Person
dStringablePerson = Stringable {
    toString = personToString
}

bold :: Stringable a -> a -> String -- '=>' became '->'
bold dStringlable a = "<b>" ++ toString dStringlable a ++ "</b>"
-- the context is now a parameter!
main = putStrLn $ bold dStringablePerson $ Person "John" "Smith"
