module StringableM where

-- Type class
class Stringable a where
    toString :: a -> String
    dump :: a -> String

data Person = Person {firstname :: String, lastname :: String}

-- Instance
instance Stringable Person where
    toString p = take 1 (firstname p) ++ ". " ++ lastname p
    --dump p = firstname p ++ " " ++ lastname p

-- Algorithm
bold :: (Stringable a) => a -> String
bold a = "<b>" ++ toString a ++ "</b>"

--italic :: (Stringable a) => a -> String
--italic a = "<b>" ++ dump a ++ "</b>"